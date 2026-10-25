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

#include "AddCustomActionDialog.h"
#include "ui_AddCustomActionDialog.h"

#include <QDebug>
#include <QPushButton>
#include <QSvgWidget>
#include <QSvgRenderer>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QToolTip>

namespace NCTI {

CustomIconModel::CustomIconModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void CustomIconModel::addSvg(const QString& path)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_svgList.append(path);
    endInsertRows();
}

int CustomIconModel::rowCount(const QModelIndex& parent) const
{
    return m_svgList.size();
}

QVariant CustomIconModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::UserRole) { return m_svgList.at(index.row()); }
    return QVariant();
}
////////////////////////////////////////////////////////////
CustomIconDelegate::CustomIconDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void CustomIconDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index == m_selectedIndex) { painter->fillRect(option.rect, QColor(0, 120, 215, 100)); }

    QString svgPath = index.data(Qt::UserRole).toString();
    QSvgRenderer renderer(svgPath);
    if (renderer.isValid()) {
        QRectF targetRect(option.rect.x(), option.rect.y(), option.rect.width(), option.rect.height());
        renderer.render(painter, targetRect);
    }
}

bool CustomIconDelegate::editorEvent(QEvent* event,
                                     QAbstractItemModel* model,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (index != m_selectedIndex) {
            m_selectedIndex = index;
            model->dataChanged(model->index(0, 0), model->index(model->rowCount() - 1, 0));
        }
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize CustomIconDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(24, 24);
}

void CustomIconDelegate::setDefaultSelectedIndex(const QModelIndex& index)
{
    m_selectedIndex = index;
}

void CustomIconDelegate::clearSelectedIndex()
{
    m_selectedIndex = QModelIndex();
}

AddCustomActionDialog::AddCustomActionDialog(QWidget* parent, const QString& title, const QString& actionName)
    : NctiBaseDialog(parent, TitleBarHeight{ 42 })
    , ui(new Ui::AddCustomActionDialog)
    , m_originActionName(actionName)
{
    // 读取并设置QSS样式表
    QFile file(":/style/AddCustomActionDialog.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        setBaseStyleSheet(styleSheet);
        file.close();
    }

    setupUi();
    setTitle(title);

    if (!m_originActionName.isEmpty()) {
        ui->lineEdit->setText(m_originActionName);
        m_isAddMode = false;
    }

    connect(ui->noSaveBtn, &QPushButton::clicked, this, &AddCustomActionDialog::onNoSave);
    connect(ui->saveBtn, &QPushButton::clicked, this, &AddCustomActionDialog::onSave);
}

AddCustomActionDialog::~AddCustomActionDialog()
{
    delete ui;
    delete m_delegate;
}

void AddCustomActionDialog::setupUi()
{
    auto widget = new QWidget(this);
    ui->setupUi(widget);

    ui->lineEdit->setPlaceholderText(QStringLiteral("请输入命令名称"));
    ui->actionName->setText(QStringLiteral("命令名称："));
    ui->defaultLogo->setText(QStringLiteral("默认图标："));
    ui->customLogo->setText(QStringLiteral("自定义图标："));

    ui->noSaveBtn->setText(QStringLiteral("取消"));
    ui->saveBtn->setText(QStringLiteral("保存"));

    ui->selectLogoBtn->setIcon(QIcon(":/images/custom/add.svg"));
    ui->selectLogoBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui->selectLogoBtn->setContentsMargins(0, 0, 0, 0);
    connect(ui->selectLogoBtn, &QToolButton::clicked, this, &AddCustomActionDialog::onSelectLogoFromLocal);

    ui->showLogoBtn->setCheckable(true);
    ui->showLogoBtn->setVisible(false);
    ui->showLogoBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui->showLogoBtn->setContentsMargins(0, 0, 0, 0);
    ui->showLogoBtn->setFixedSize(28, 28);
    ui->showLogoBtn->setIconSize(QSize(24, 24));
    connect(ui->showLogoBtn, &QToolButton::toggled, this, &AddCustomActionDialog::onSelectLocalLogo);

    addDefaultLogo();

    setWidget(widget);
}

void AddCustomActionDialog::initListView()
{
    ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setSpacing(6);
    ui->listView->setFlow(QListView::LeftToRight);
    ui->listView->setContentsMargins(0, 0, 0, 0);
    ui->listView->setFrameShape(QFrame::NoFrame);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listView->setWrapping(true);
    ui->listView->setResizeMode(QListView::Adjust);
}

void AddCustomActionDialog::addDefaultLogo()
{
    initListView();

    for (int i = 0; i < 21; i++) {
        m_model.addSvg(QString(":/images/custom/icon%1.svg").arg(i));
    }

    ui->listView->setModel(&m_model);
    m_delegate = new CustomIconDelegate(ui->listView);
    ui->listView->setItemDelegate(m_delegate);

    connect(ui->listView, &QListView::clicked, this, [this](const QModelIndex& index) {
        QString svgPath = index.data(Qt::UserRole).toString();
        SetIcon(svgPath, true);
    });

    // 设置默认选中项
    setDefaultIcon();
}

void AddCustomActionDialog::setDefaultIcon()
{
    QModelIndex defaultIndex = m_model.index(0, 0);
    m_delegate->setDefaultSelectedIndex(defaultIndex);
    ui->listView->setCurrentIndex(defaultIndex);
    QString defaultSvgPath = defaultIndex.data(Qt::UserRole).toString();
    SetIcon(defaultSvgPath, true);
    m_model.dataChanged(m_model.index(0, 0), m_model.index(m_model.rowCount() - 1, 0));
}

void AddCustomActionDialog::onSelectLogoFromLocal()
{
    QString filter   = "Images (*.svg *.png *.jpg);;All Files (*)";
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image"), "", filter);
    if (!filePath.isEmpty()) {
        QString fileExtension = filePath.split(".").last().toLower();
        if (fileExtension == "svg" || fileExtension == "png" || fileExtension == "jpg") { SetIcon(filePath, false); }
        else {
            QMessageBox::warning(this, tr("Unsupported Format"), tr("Only SVG, PNG, and JPG formats are supported."));
        }
    }
}

void AddCustomActionDialog::onSelectLocalLogo(bool selected)
{
    if (selected) {
        m_delegate->clearSelectedIndex();
        ui->listView->setCurrentIndex(QModelIndex());

        // 重绘所有项，更新选中状态
        m_model.dataChanged(m_model.index(0, 0), m_model.index(m_model.rowCount() - 1, 0));
    }
}

int AddCustomActionDialog::GetStatus() const
{
    return (m_saveStatus == SaveStatus::Cancel) ? 0 : 1;
}

QString AddCustomActionDialog::actionName()
{
    return m_actionName;
}

QString AddCustomActionDialog::iconPath()
{
    return m_iconPath;
}

void AddCustomActionDialog::onNoSave()
{
    m_saveStatus = SaveStatus::Cancel;
    close();
}

void AddCustomActionDialog::onSave()
{
    QString actionName = ui->lineEdit->text();
    if (actionName.isEmpty()) {
        // 提示名称不能为空
        QToolTip::showText(ui->lineEdit->mapToGlobal(QPoint(0, 0)), "名称不能为空！");
        return;
    }

    std::string action_name = CustomActionManager::toString(actionName);
    bool bSameName          = CustomActionManager::getInst().isCustomActionExists(action_name);
    if (bSameName) {
        if (m_isAddMode || actionName != m_originActionName) {
            QToolTip::showText(ui->lineEdit->mapToGlobal(QPoint(0, 0)), "已存在相同的命令名称，请重新输入！");
            return;
        }
    }

    m_actionName = actionName;
    m_saveStatus = SaveStatus::Save;
    close();
}

void AddCustomActionDialog::UpdateIcon(const QString& actionName, const QString& icon_path)
{
    if (!CustomActionManager::isCustomIcon(icon_path)) {
        // 不是默认图标，使用数据库保存图标
        std::string action_name   = CustomActionManager::toString(actionName);
        CustomAction customAction = CustomActionManager::getInst().findByName(action_name);
        if (customAction.action_name == action_name) {
            if (!customAction.thumbnail.empty()) {
                QPixmap pix;
                pix.loadFromData(reinterpret_cast<const uchar*>(customAction.thumbnail.data()),
                                 static_cast<int>(customAction.thumbnail.size()));
                SetIcon(QIcon(pix), false);
                return;
            }
        }
    }

    QString iconPath = icon_path;
    if (!QFile::exists(iconPath)) { iconPath = ":/images/custom/icon0.svg"; }

    //更新默认图标
    for (int i = 0; i < m_model.rowCount(); ++i) {
        QModelIndex index = m_model.index(i, 0);
        QString svgPath   = index.data(Qt::UserRole).toString();
        if (svgPath == iconPath) {
            m_delegate->setDefaultSelectedIndex(index);
            ui->listView->setCurrentIndex(index);
            SetIcon(svgPath, true);
            m_model.dataChanged(m_model.index(0, 0), m_model.index(m_model.rowCount() - 1, 0));
            return;
        }
    }

    // 如果没有匹配到，设置默认图标
    setDefaultIcon();
}

void AddCustomActionDialog::SetIcon(const QString& iconPath, bool useDefaultIcon)
{
    m_iconPath = iconPath;
    SetIcon(QIcon(iconPath), useDefaultIcon);
}

void AddCustomActionDialog::SetIcon(const QIcon& icon, bool useDefaultIcon)
{
    if (useDefaultIcon) { ui->showLogoBtn->setChecked(false); }
    else {
        ui->showLogoBtn->setIcon(icon);
        ui->showLogoBtn->setChecked(true);
        ui->showLogoBtn->setVisible(true);
    }
}
} // namespace NCTI
