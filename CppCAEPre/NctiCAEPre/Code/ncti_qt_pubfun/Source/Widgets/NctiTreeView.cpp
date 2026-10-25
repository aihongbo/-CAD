/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#include "NctiTreeView.h"
#include "NctiTreeModel.h"
#include "NctiDebug.h"

#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QHeaderView>

namespace NCTI {
    NctiTreeView::NctiTreeView(QWidget* parent, NctiTreeViewType type)
        : QTreeView(parent)
        , m_type(type)
    {
        // 注册 QItemSelection 类型为元类型，避免跨线程信号传递警告
        qRegisterMetaType<QItemSelection>();
        
        setTreeViewProperty();

        NctiTreeModel* model = new NctiTreeModel(std::vector<NctiTreeModelData>{}, this);
        setModel(model);
        setupConnections();
        installEventFilter(this);

        this->setMinimumWidth(200);
    }

    void NctiTreeView::setupConnections()
    {
        connect(selectionModel(), &QItemSelectionModel::selectionChanged, this, &NctiTreeView::onSelectionChanged);

        connect(this, &QTreeView::pressed, this, &NctiTreeView::onItemClicked);
        connect(this, &QTreeView::doubleClicked, this, &NctiTreeView::onDoubleClicked);
        connect(this, &QTreeView::customContextMenuRequested, this, &NctiTreeView::onTreeViewMenuRequested);

        m_selectionTimer.setSingleShot(true);
        m_selectionTimer.setInterval(0);
    }

    void NctiTreeView::setTreeViewProperty()
    {
        //TreeView属性设置
        setHeaderHidden(true);
        setRootIsDecorated(false);
        setMouseTracking(true);
        setIconSize(QSize(18, 18));

        setEditTriggers(QAbstractItemView::NoEditTriggers);     //禁止编辑
        setSelectionMode(QAbstractItemView::ExtendedSelection); //开启多选
        setContextMenuPolicy(Qt::CustomContextMenu);            //添加右键菜单

        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);    //增加水平滚动条
        setAutoScroll(false);
    }

    void NctiTreeView::mousePressEvent(QMouseEvent* event)
    {
        m_isRubberBandSelecting = false;
        QModelIndex index = indexAt(event->pos());
        if (!index.isValid() && selectionModel()) {
            selectionModel()->clearSelection();
            checkAndTriggerSelectionChange();
        }
        else if (event->button() == Qt::LeftButton) {
            m_selectionStartPos = event->pos();
        }
        QTreeView::mousePressEvent(event);
    }

    void NctiTreeView::mouseMoveEvent(QMouseEvent* event)
    {
        if (!(event->buttons() & Qt::LeftButton)) {
            return QTreeView::mouseMoveEvent(event);
        }

        if (!m_isRubberBandSelecting
            && (event->pos() - m_selectionStartPos).manhattanLength() >= QApplication::startDragDistance()) {
            m_isRubberBandSelecting = true;
        }
        QTreeView::mouseMoveEvent(event);
    }

    void NctiTreeView::mouseReleaseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton/* && m_isRubberBandSelecting*/) {
            m_isRubberBandSelecting = false;
            checkAndTriggerSelectionChange();
        }
        QTreeView::mouseReleaseEvent(event);
    }

    bool NctiTreeView::eventFilter(QObject* obj, QEvent* event)
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Control) {
                m_isCtrlPressed = true;
                return false;
            }
            else if (keyEvent->key() == Qt::Key_Shift) {
                m_isShiftPressed = true;
                return false;
            }
        }
        else if (event->type() == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Control) {
                m_isCtrlPressed = false;
                checkAndTriggerSelectionChange();
                return false;
            }
            else if (keyEvent->key() == Qt::Key_Shift) {
                m_isShiftPressed = false;
                checkAndTriggerSelectionChange();
                return false;
            }
        }
        else if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			if (mouseEvent->button() == Qt::LeftButton && m_isCtrlPressed) {
                return true;
            }
        }
        return QTreeView::eventFilter(obj, event);
    }

    void NctiTreeView::focusOutEvent(QFocusEvent* event) 
    {
        if (m_isCtrlPressed) {
            m_isCtrlPressed = false;
        }

        if (m_isShiftPressed) {
            m_isShiftPressed = false;
        }
        return QTreeView::focusInEvent(event);
    }

    void NctiTreeView::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
    {
        m_selectionTimer.start();
    }

    void NctiTreeView::checkAndTriggerSelectionChange() 
    {
        if (!m_isRubberBandSelecting && !m_isCtrlPressed && !m_isShiftPressed) {
            m_selectionTimer.stop();
            getSelectedItems();
        }
        else {
            m_selectionTimer.start(0);
        }
    }

    void NctiTreeView::onTreeViewMenuRequested(const QPoint& pos)
    {
        if (m_isCtrlPressed || m_isShiftPressed) {
            return;
        }

        QModelIndex index = indexAt(pos);
        if (!index.isValid()) {
            return;
        }
        NctiTreeItem* item = getTreeItem(index);
        if (!item) {
            return;
        }

        QString itemObjName = item->getItemObjName();
        Q_EMIT sigContextMenuRequested(itemObjName, item->getObject());
    }

    NctiTreeItem* NctiTreeView::getTreeItem(const QModelIndex& index)
    {
        if (!index.isValid()) {
            NctiDebug::debug("Invalid index");
            return nullptr;
        }
        NctiTreeModel* model = qobject_cast<NctiTreeModel*>(this->model());
        if (!model) {
            NctiDebug::debug("Invalid model");
            return nullptr;
        }
        NctiTreeItem* item = static_cast<NctiTreeItem*>(index.internalPointer());
        if (!item) {
            NctiDebug::debug("Invalid item");
            return nullptr;
        }
        return item;
    }

    void NctiTreeView::getSelectedItems()
    {
        if (!selectionModel()) {
            return;
        }
        QModelIndexList selectedIndexes = selectionModel()->selectedRows();
        if (selectedIndexes.isEmpty()) {
            return;
        }

        std::vector<void*> vObj;
        for (const QModelIndex& index : selectedIndexes) {
            NctiTreeItem* item = getTreeItem(index);
            if (item) {
                vObj.push_back(item->getObject());
            }
        }
        Q_EMIT sigTreeItemSelected(vObj, selectedIndexes);
    }

    void NctiTreeView::onItemClicked(const QModelIndex& index)
    {
        if (m_isCtrlPressed || m_isShiftPressed) {
            return;
        }

        NctiTreeItem* item = getTreeItem(index);
        if (!item) {
            return;
        }
        QString itemObjName = item->getItemObjName();
        Q_EMIT sigItemClicked(itemObjName, item->getObject());
    }

    void NctiTreeView::onDoubleClicked(const QModelIndex& index)
    {
        NctiTreeItem* item = getTreeItem(index);
        if (!item) {
            return;
        }
        QString itemTypeName = item->getItemTypeName();
        Q_EMIT sigItemDoubleClicked(itemTypeName, item->getObject());
    }

    void NctiTreeView::update(const std::vector<NctiTreeModelData>& vModelData)
    {
        NctiTreeModel* model = qobject_cast<NctiTreeModel*>(this->model());
        if (!model) {
            return;
        }
        if (m_type == NctiTreeViewType::Assemble || m_type == NctiTreeViewType::Object) {
            Q_EMIT sigTreeModelDataChanged(m_type, vModelData);
        }
        
        model->updateData(vModelData);

        expandAll();
        resizeColumnToContents(0);
    }
}

