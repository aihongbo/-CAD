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

#include <QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#define MOUSEEVENT_POS_POINT(MouseEventPtr) MouseEventPtr->position().toPoint()
#else
#define MOUSEEVENT_POS_POINT(MouseEventPtr) MouseEventPtr->pos()
#endif

#include "ConfigCustomActionDialog.h"
#include "ui_ConfigCustomActionDialog.h"

#include "CustomActionManager.h"
#include "NctiMessageDialog.h"

#include <QSvgWidget>
#include <QSvgRenderer>
#include <QPainter>
#include <QFileDialog>
#include <QApplication>
#include <QLineEdit>
#include <QMouseEvent>
#include <QIcon>
#include <QDebug>

namespace NCTI {
const QString EDIT_ICON_PATH   = ":/images/custom/edit.svg";
const QString DELETE_ICON_PATH = ":/images/custom/delete.svg";

ConfigCustomDelegate::ConfigCustomDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void ConfigCustomDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    QColor selectedBg(226, 237, 253);
    QColor hoverBg = selectedBg;
    hoverBg.setAlphaF(0.6); // 60%透明度

    if (option.state & QStyle::State_Selected) { painter->fillRect(option.rect, selectedBg); }
    else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(option.rect, hoverBg);
    }

    QString iconPath = index.data(Qt::DecorationRole).toString();
    QString name     = index.data(Qt::DisplayRole).toString();
    QString toolTip  = index.data(Qt::ToolTipRole).toString();

    // 绘制图标
    QIcon icon;
    if (CustomActionManager::isCustomIcon(iconPath)) { icon = QIcon(iconPath); }
    else {
        icon = index.data(Qt::UserRole + 2).value<QIcon>();
    }

    QRect iconRect = calculateIconRect(option);
    if (!icon.isNull()) { icon.paint(painter, iconRect); }

    // 名称
    QRect textRect = calculateTextRect(option);
    painter->setPen(QColor(154, 160, 168));
    QFontMetrics fm(painter->font());
    QString elidedText = fm.elidedText(name, Qt::ElideRight, textRect.width());
    painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, elidedText);

    // 按钮
    QRect editButtonRect = calculateEditButtonRect(option);
    drawIconButton(painter, editButtonRect, EDIT_ICON_PATH);

    QRect deleteButtonRect = calculateDeleteButtonRect(option);
    drawIconButton(painter, deleteButtonRect, DELETE_ICON_PATH);

    painter->restore();
}

void ConfigCustomDelegate::drawButton(QPainter* painter, const QRect& rect, const QString& text) const
{
    QStyleOptionButton buttonOption;
    buttonOption.rect  = rect;
    buttonOption.text  = text;
    buttonOption.state = QStyle::State_Enabled;
    QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
}

void ConfigCustomDelegate::drawIconButton(QPainter* painter, const QRect& rect, const QString& iconPath) const
{
    QSvgRenderer renderer(iconPath);
    if (renderer.isValid()) {
        QRect targetRect = rect.adjusted(1, 1, -1, -1);
        renderer.render(painter, targetRect);
    }
}

QRect ConfigCustomDelegate::calculateIconRect(const QStyleOptionViewItem& option) const
{
    const int iconSize = 24;
    int y              = option.rect.center().y() - iconSize / 2 + 1;
    return QRect(option.rect.left(), y, iconSize, iconSize);
}

QRect ConfigCustomDelegate::calculateTextRect(const QStyleOptionViewItem& option) const
{
    const int iconSize   = 24;
    const int buttonSize = 20;
    const int spacing    = 8;

    QRect iconRect = calculateIconRect(option);
    int textLeft   = iconRect.right() + spacing;

    // 总宽度 - (图标区域 + 按钮总宽度 + 按钮间隔)
    int textWidth = option.rect.width() - (textLeft + 2 * buttonSize + 2 * spacing);
    return QRect(textLeft, option.rect.top() + 4, textWidth, option.rect.height() - 8);
}

QRect ConfigCustomDelegate::calculateEditButtonRect(const QStyleOptionViewItem& option) const
{
    const int buttonSize = 20;
    const int spacing    = 8;
    int y                = option.rect.center().y() - buttonSize / 2; // 垂直居中

    // 右侧留出两个按钮和间隔
    return QRect(option.rect.right() - buttonSize - 2 * spacing - buttonSize, y, buttonSize, buttonSize);
}

QRect ConfigCustomDelegate::calculateDeleteButtonRect(const QStyleOptionViewItem& option) const
{
    const int buttonSize = 20;
    const int spacing    = 8;
    int y                = option.rect.center().y() - buttonSize / 2;
    return QRect(option.rect.right() - buttonSize - spacing, y, buttonSize, buttonSize);
}

bool ConfigCustomDelegate::editorEvent(QEvent* event,
                                       QAbstractItemModel* model,
                                       const QStyleOptionViewItem& option,
                                       const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos              = MOUSEEVENT_POS_POINT(mouseEvent);

        QRect iconRect         = calculateIconRect(option);
        QRect editButtonRect   = calculateEditButtonRect(option);
        QRect deleteButtonRect = calculateDeleteButtonRect(option);

        if (editButtonRect.contains(pos)) {
            Q_EMIT editClicked(index);
            return true;
        }
        else if (deleteButtonRect.contains(pos)) {
            Q_EMIT deleteClicked(index);
            return true;
        }
    }
    else if (event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QRect textRect          = calculateTextRect(option);
        if (textRect.contains(MOUSEEVENT_POS_POINT(mouseEvent))) {
            Q_EMIT titleDoubleClicked(index);
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize ConfigCustomDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 30);
}

///ConfigCustomActionDialog///
ConfigCustomActionDialog::ConfigCustomActionDialog(QWidget* parent, const QString& title)
    : NctiBaseDialog(parent, TitleBarHeight{42})
    , ui(new Ui::ConfigCustomActionDialog)
{
    // 读取并设置QSS样式表
    QFile file(":/style/ConfigCustomActionDialog.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        setBaseStyleSheet(styleSheet);
        file.close();
    }
    
    setupUi();
    setTitle(title);
}

ConfigCustomActionDialog::~ConfigCustomActionDialog()
{
    delete ui;
    delete m_delegate;
}

void ConfigCustomActionDialog::updateActionNameAndIcon(const QString& actionName,
                                                       const QString& newActionName,
                                                       const QString& newIconPath,
                                                       QIcon newIcon)
{
    for (int i = 0; i < m_model.rowCount(); ++i) {
        QModelIndex index = m_model.index(i, 0);
        QString name      = index.data(Qt::DisplayRole).toString();
        if (name == actionName) {
            QString pyFile = index.data(Qt::UserRole + 1).toString();
            m_model.setData(index, newIconPath, Qt::DecorationRole);
            m_model.setData(index, newActionName, Qt::DisplayRole);
            m_model.setData(index, newActionName, Qt::ToolTipRole);
            m_model.setData(index, pyFile, Qt::UserRole + 1);
            m_model.setData(index, newIcon, Qt::UserRole + 2);
            m_model.dataChanged(index, index);
            break;
        }
    }
}

void ConfigCustomActionDialog::setupUi()
{
    auto widget = new QWidget(this);
    ui->setupUi(widget);

    initListView();

    int count = initModelData();

    setWidget(widget);

    int calcHeight = count * (35) + 250;
    setFixedSize(320, std::min(calcHeight, 518));
}

void ConfigCustomActionDialog::initListView()
{
    ui->listView->setContentsMargins(0, 0, 0, 0);
    ui->listView->setFrameShape(QFrame::NoFrame);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->listView->setWrapping(false);
    ui->listView->setResizeMode(QListView::Adjust);

    m_delegate = new ConfigCustomDelegate(this);
    connect(m_delegate, &ConfigCustomDelegate::titleDoubleClicked, this, &ConfigCustomActionDialog::onEditCustomAction);
    connect(m_delegate, &ConfigCustomDelegate::editClicked, this, &ConfigCustomActionDialog::onEditPyScript);
    connect(m_delegate, &ConfigCustomDelegate::deleteClicked, this, &ConfigCustomActionDialog::onRemovePyScript);
    ui->listView->setItemDelegate(m_delegate);
}

void ConfigCustomActionDialog::onEditCustomAction(const QModelIndex& index)
{
    QString name     = index.data(Qt::DisplayRole).toString();
    QString iconPath = index.data(Qt::DecorationRole).toString();
    Q_EMIT sigEditCustomAction(name, iconPath);
}

void ConfigCustomActionDialog::onEditPyScript(const QModelIndex& index)
{
    QString pyFile = index.data(Qt::UserRole + 1).toString();
    if (!pyFile.isEmpty()) { 
        Q_EMIT sigEditPyScript(pyFile); 
    }
    close();
}

void ConfigCustomActionDialog::onRemovePyScript(const QModelIndex& index)
{
    QString itemName = index.data(Qt::DisplayRole).toString();
    if (IsConfirmRemove(itemName)) {
        Q_EMIT sigRemovePyScript(itemName);
        m_model.removeRow(index.row());
    }
}

bool ConfigCustomActionDialog::IsConfirmRemove(const QString& itemName)
{
    auto dlg = std::make_unique<NctiMessageDialog>(this, QStringLiteral("确定要删除吗？"));
    dlg->setFixedSize(260, 210);
    dlg->exec();
    if (3 == dlg->GetCloseCode()) { return true; }
    return false;
}

int ConfigCustomActionDialog::initModelData()
{
    auto dataList = CustomActionManager::getInst().allCustomActions();
    if (dataList.empty()) { return 0; }

    for (auto& data : dataList) {
        QString actionName = CustomActionManager::toQString(data.action_name);
        QString iconPath   = CustomActionManager::toQString(data.icon_path);
        QString pyFile     = CustomActionManager::getInst().getPyFilePath(actionName);
        QIcon icon{CustomActionManager::getThumbnail(data.thumbnail)};

        QStandardItem* item = new QStandardItem;
        item->setData(iconPath, Qt::DecorationRole);
        item->setData(actionName, Qt::DisplayRole);
        item->setData(actionName, Qt::ToolTipRole);
        item->setData(pyFile, Qt::UserRole + 1);
        item->setData(icon, Qt::UserRole + 2);
        m_model.appendRow(item);
    }

    ui->listView->setModel(&m_model);
    return dataList.size();
}
} // namespace NCTI


