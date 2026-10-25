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

#include "FileDetailGallery.h"

#include <QtEvents>
#include <QApplication>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QStandardPaths>
#include <QVBoxLayout>

#include "NctiContextMenu.h"
#include "mainwindow_container.h"

#include <locale>
#include <codecvt>

namespace NCTI {

    static QFont getFileNameFont(QFont::Weight weight)
    {
        QFont font;
        font.setFamily("HarmonyOS Sans SC");
        font.setPixelSize(16);
        font.setWeight(weight);
        return font;
    }

    static QFont getSubTitleFont(QFont::Weight weight = QFont::Normal)
    {
        QFont font;
        font.setFamily("HarmonyOS Sans SC");
        font.setPixelSize(14);
        font.setWeight(weight);
        return font;
    }

    static QPixmap* getThumbnail(const std::vector<char>& thumbnail)
    {
        QByteArray byteArray(thumbnail.data(), static_cast<int>(thumbnail.size()));
        QImage image;
        if (image.loadFromData(byteArray)) {
            QPixmap* pixmap = new QPixmap(QPixmap::fromImage(image));
            return pixmap;
        }
        return nullptr;
    }

    static std::vector<char> getBlobThumbnail(const std::wstring& thumbnail)
    {
        // 将宽字符串转换为UTF-8字符串
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_path = converter.to_bytes(thumbnail);

        std::ifstream file(utf8_path, std::ios::binary | std::ios::ate);
        if (file) {
            size_t size = file.tellg();
            file.seekg(0);

            std::vector<char> buffer(size);
            file.read(buffer.data(), size);
            return buffer;
        }
        return std::vector<char>();
    }

    FileDetailWidget::FileDetailWidget(const FileDetail& data, QWidget* parent)
        : mDetailData(data)
        , QWidget(parent)
    {
        setObjectName("fileDetailWidget");
        setFixedSize(fixedWidth, fixedHeight);

        initDeleteButton();
        initFavoriteButton();

        if (isNewDocWidgetData(mDetailData)) {
            mThumbnail = new QPixmap(":/recentpage/new_item.svg");
            mAddItem = new QPixmap(":/recentpage/add_item.png");
            initNewDocMenu();
        }
        else {
            mThumbnail = getThumbnail(mDetailData.thumbnail);
        }

        // 初始化QLabel
        mFileNameLabel = new QLabel(this);
        mFileNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        mFileNameLabel->setWordWrap(false);
        mFileNameLabel->setStyleSheet("color: #52555a;");
        mFileNameLabel->setFont(getFileNameFont(QFont::Medium));
    }

    void FileDetailWidget::initDeleteButton()
    {
        mDeleteButton = new QPushButton(this);
        mDeleteButton->setObjectName("deleteButton");
        mDeleteButton->setStyleSheet(
            "border: none;"
            "background: transparent;"
        );
        mDeleteButton->setIcon(QIcon(":/recentpage/delete.svg"));
        mDeleteButton->setIconSize(QSize(iconSize, iconSize));
        mDeleteButton->setCursor(QCursor(Qt::PointingHandCursor));
        connect(mDeleteButton, &QPushButton::clicked, this, &FileDetailWidget::onDeleteRecord);
    }

    void FileDetailWidget::initFavoriteButton()
    {
        mFavoriteButton = new QPushButton(this);
        mFavoriteButton->setObjectName("favoriteButton");
        mFavoriteButton->setCheckable(true);
        mFavoriteButton->setChecked(mDetailData.favorite == 1);
        mFavoriteButton->setStyleSheet(
            "border: none;"
            "background: transparent;"
        );
        setFavoriteIcon(mDetailData.favorite == 1);
        mFavoriteButton->setIconSize(QSize(iconSize, iconSize));
        mFavoriteButton->setCursor(QCursor(Qt::PointingHandCursor));
        connect(mFavoriteButton, &QPushButton::clicked, this, &FileDetailWidget::onFavoriteClicked);
    }

    FileDetailWidget::~FileDetailWidget()
    {
    }

    void FileDetailWidget::updateData(const FileDetail& data)
    {
        if (mDetailData.file_path == data.file_path 
            && mDetailData.update_time == data.update_time) {
            return;
        }
        mDetailData = data;
        mThumbnail = getThumbnail(mDetailData.thumbnail);
        update();
    }

    std::string FileDetailWidget::getFilePath() const
    {
        return mDetailData.file_path;
    }

    void FileDetailWidget::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角矩形背景
        QRect rect = this->rect().adjusted(1, 1, -1, -1);
        painter.setBrush(QBrush(Qt::white));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect, 8, 8);

        if (mDetailData.file_path.empty()) {
            drawNewDocWidget(painter);
        }
        else {
            drawItemWidget(painter);
        }
    }

    void FileDetailWidget::drawNewDocWidget(QPainter& painter)
    {
        if (mThumbnail) {
            painter.drawPixmap(0, 0, fixedWidth, fixedHeight, *mThumbnail);
        }
        if (mAddItem) {
            int startX = (fixedWidth - 50) / 2;
            painter.drawPixmap(startX, 95, 50, 48, *mAddItem);
        }

        // 设置字体和颜色
        int textStartY = 163;
        painter.setFont(getFileNameFont(QFont::Bold));
        painter.setPen(QColor("#1c72f3"));

        // 绘制文件名和收藏按钮
        painter.drawText(0, textStartY, fixedWidth, 16,
            Qt::AlignCenter | Qt::AlignVCenter, QString::fromUtf8(mDetailData.file_name.c_str()));

        mDeleteButton->setVisible(false);
        mFavoriteButton->setVisible(false);
    }

    void FileDetailWidget::drawItemWidget(QPainter& painter)
    {
        // 绘制边框
        QRect borderRect = this->rect().adjusted(1, 1, -1, -1);
        if (mMouseOver) {
            QPen borderPen(QColor("#1C72F3"));
            borderPen.setWidth(2);
            painter.setPen(borderPen);
        }
        else {
            QPen borderPen(QColor("#dee3ed"));
            borderPen.setWidth(1);
            painter.setPen(borderPen);
        }
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(borderRect, 8, 8);

        if (mThumbnail) {
            mThumbnailRect = QRect(0, 0, fixedWidth, thumbnailHeight);
            painter.drawPixmap(mThumbnailRect, *mThumbnail);
        }

        int textStartY = thumbnailHeight + 16;
        int textWidth = fixedWidth - 66; // 预留空间给收藏按钮
        QFontMetrics fm(mFileNameLabel->font());
        int fontHeight = fm.height();
        QRect textRect(16, textStartY, textWidth, fontHeight);
        mFileNameLabel->setGeometry(textRect);

        QString fileName = QString::fromUtf8(mDetailData.file_name.c_str());
        // 使用QFontMetrics截断过长的文件名
        QString elidedText = fm.elidedText(fileName, Qt::ElideRight, textWidth);
        mFileNameLabel->setText(elidedText);
        mFileNameLabel->setToolTip(fileName);

        mDeleteButton->setGeometry(fixedWidth - 58, textStartY, iconSize, iconSize);
        mFavoriteButton->setGeometry(fixedWidth - 28, textStartY, iconSize, iconSize);

        // 绘制更新时间
        painter.setFont(getSubTitleFont());
        painter.setPen(QColor("#777b80"));
        textStartY = thumbnailHeight + 44;
        painter.drawText(16, textStartY, fixedWidth - 10, 20, Qt::AlignLeft | Qt::AlignVCenter
            , formatUpdateTime(mDetailData.update_time));
    }

    void FileDetailWidget::mouseMoveEvent(QMouseEvent* event)
    {
        QWidget::mousePressEvent(event);
    }

    void FileDetailWidget::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton && mDetailData.file_path.empty())
        {
            showContextMenu(event->pos());
            //Q_EMIT sigDetailWidgetClicked();
        }
        QWidget::mousePressEvent(event);
    }

    void FileDetailWidget::mouseDoubleClickEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton && isPointInImageArea(event->pos())) {
            onOpenFile();
        }
        QWidget::mouseDoubleClickEvent(event);
    }

    void FileDetailWidget::contextMenuEvent(QContextMenuEvent* event)
    {
        showContextMenu(event->pos());
    }

#if QT_VERSION_MAJOR >= 6
    void FileDetailWidget::enterEvent(QEnterEvent* event)
    {
        if (!mMouseOver) {
            mMouseOver = true;
            update();
        }
        QWidget::enterEvent(event);
    }
#else
    void FileDetailWidget::enterEvent(QEvent* event)
    {
        if (!mMouseOver) {
            mMouseOver = true;
            update();
        }
        QWidget::enterEvent(event);
    }
#endif

    void FileDetailWidget::leaveEvent(QEvent* event)
    {
        if (mMouseOver) {
            mMouseOver = false;
            update();
        }
        QWidget::leaveEvent(event);
    }

    bool FileDetailWidget::isNewDocWidgetData(const FileDetail& data)
    {
        if (data.file_path.empty()
            && data.ncti_type.empty()
            && data.thumbnail.empty()
            && data.update_time == 0) {
            return true;
        }
        return false;
    }

    bool FileDetailWidget::isPointInImageArea(const QPoint& point)
    {
        if (mDetailData.file_path.empty()) {
            return false;
        }
        return mThumbnailRect.contains(point);
    }

    void FileDetailWidget::onFavoriteClicked(bool checked)
    {
        mDetailData.favorite = checked;
        setFavoriteIcon(checked);

        FileDetailGallery::updateFavorite(mDetailData);
    }

    void FileDetailWidget::initNewDocMenu()
    {
        mNewDocMenu = new NctiContextMenu(this);
        mNewDocMenu->setMinimumWidth(120);
        
        QAction* newAssembly = new QAction(QIcon(":/file/new_assembly.svg"), QStringLiteral("新建装配"), this);
        connect(newAssembly, &QAction::triggered, this, &FileDetailWidget::sigNewAssemblyClicked);

        QAction* newPart = new QAction(QIcon(":/file/new_part.svg"), QStringLiteral("新建部件"), this);
        connect(newPart, &QAction::triggered, this, &FileDetailWidget::sigNewPartClicked);
        
        mNewDocMenu->addAction(newAssembly);
        mNewDocMenu->addAction(newPart);
    }

    void FileDetailWidget::initNewItemMenu()
    {
        mNewItemMenu = new NctiContextMenu(this);
        mNewItemMenu->setMinimumWidth(120);
        QAction* aOpenFile = new QAction(QIcon(":/file/open.svg"), QStringLiteral("打开文件"), this);
        connect(aOpenFile, &QAction::triggered, this, &FileDetailWidget::onOpenFile);
        QAction* aDeleteRecord = new QAction(QIcon(":/file/delete.svg"), QStringLiteral("删除记录"), this);
        connect(aDeleteRecord, &QAction::triggered, this, &FileDetailWidget::onDeleteRecord);
        mNewItemMenu->addAction(aOpenFile);
        mNewItemMenu->addAction(aDeleteRecord);
    }

    void FileDetailWidget::showContextMenu(const QPoint& pos)
    {
        if (mDetailData.file_path.empty() && mNewDocMenu) {
            QPoint globalPos = mapToGlobal(pos);
            mNewDocMenu->exec(globalPos);
            return;
        }

        if (mNewItemMenu) {
            QPoint globalPos = mapToGlobal(pos);
            mNewItemMenu->exec(globalPos);
        }
    }

    void FileDetailWidget::onOpenFile()
    {
        Q_EMIT sigOpenFile(QString::fromUtf8(mDetailData.file_path.c_str()));
    }
    
    void FileDetailWidget::onDeleteRecord()
    {
        Q_EMIT sigDeleteRecord(QString::fromUtf8(mDetailData.file_path.c_str()));
    }                                                                       

    void FileDetailWidget::setFavoriteIcon(bool checked)
    {
        if (checked) {
            mFavoriteButton->setIcon(QIcon(":/recentpage/favorite.svg")); // 收藏状态图标
        }
        else {
            mFavoriteButton->setIcon(QIcon(":/recentpage/unfavorite.svg")); // 未收藏状态图标
        }
    }

    QString FileDetailWidget::formatUpdateTime(std::uint64_t update_time)
    {
        QDateTime dateTime = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(update_time));
        QString timeFormat = QStringLiteral("更新于 yyyy.MM.dd  HH:mm");
        return dateTime.toString(timeFormat);
    }

    std::uint64_t FileDetailWidget::getCurrentTimeInSeconds()
    {
        // 获取当前时间的秒级时间戳
        return static_cast<std::uint64_t>(QDateTime::currentSecsSinceEpoch());
    }

    ////////////////////////////////////////////////////////////
    FileDetailGallery::FileDetailGallery(QWidget* parent)
        : QScrollArea(parent)
    {
        mCenterWidget = new QWidget(this);

        mNewDocWidget = getNewDocWidget();
        connect(mNewDocWidget, &FileDetailWidget::sigOpenFile, this, &FileDetailGallery::sigOpenFile);
        connect(mNewDocWidget, &FileDetailWidget::sigDeleteRecord, this, &FileDetailGallery::sigDeleteRecord);
        
        //添加主布局
        QVBoxLayout* layout = new QVBoxLayout(mCenterWidget);
        layout->setSpacing(itemSpace_v);
        layout->setContentsMargins(itemSpace_v, itemSpace_v, itemSpace_v, itemSpace_v);

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setWidget(mCenterWidget);
        mCenterWidget->setLayout(layout);
    }

    std::vector<FileDetail> FileDetailGallery::getFileList(RecentFileType fileType)
    {
        std::vector<FileDetail> details;
        switch (fileType) {
        case RecentFileType::RECENT_FILE: {
            details = FileDatabase::getInst()->findRecentFiles();
        }break;
        case RecentFileType::ALL_FILE: {
            details = FileDatabase::getInst()->findAllFiles();
        }break;
        case RecentFileType::ASSEMBLY_FILE: {
            details = FileDatabase::getInst()->findByType("assembly");
        }break;
        case RecentFileType::PARTS_FILE: {
            details = FileDatabase::getInst()->findByType("part");
        }break;
        case RecentFileType::FAVORITE_FILE: {
            details = FileDatabase::getInst()->findByFavorite();
        }break;
        default:
            break;
        }
        return details;
    }

    std::vector<FileDetail> FileDetailGallery::getFileList(const QString& fileName)
    {
        QByteArray ba = fileName.toUtf8();
        std::string file_name = ba.toStdString();
        return FileDatabase::getInst()->findByName(file_name);
    }

    void FileDetailGallery::setFileList(const FileDetail& fileDetail)
    { 
        auto files = FileDatabase::getInst()->findByPath(fileDetail.file_path);
        if (!files.empty()) {
            FileDatabase::getInst()->updateDetail(fileDetail);
        }
        else {
            FileDatabase::getInst()->insertRecord(fileDetail);
        }
    }

    QString FileDetailGallery::getNctiThumbnail(const QString& nctiFilePath)
    {
        //获取临时文件目录
        QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
        if (tempPath.isEmpty()) {
            return QString();
        }
        QFileInfo fileInfo(nctiFilePath);
        QString thumbnailPath = QStringLiteral("%1/%2.png").arg(tempPath).arg(fileInfo.completeBaseName());
        QFile thumbnailFile(thumbnailPath);
        if (thumbnailFile.exists()) {
            thumbnailFile.remove();
        }

        if (MainwindowContainer::readNctiFileImage(nctiFilePath, thumbnailPath)) {
            return thumbnailPath;
        }

        qWarning() << "Failed to read file image";
        return QString();
    }

    std::vector<char> FileDetailGallery::getNctiThumbnailBlob(const QString& nctiFilePath)
    {
        QString thumbnailPath = getNctiThumbnail(nctiFilePath);
        if (thumbnailPath.isEmpty()) {
            // 使用默认封面
            QFile defaultCover(":/recentpage/cover_default.png");
            if (!defaultCover.open(QIODevice::ReadOnly)) {
                qWarning() << "cover_default.png open failed.";
                return {};
            }
            QByteArray imageData = defaultCover.readAll();
            defaultCover.close();
            return { imageData.begin(), imageData.end() };
        }
        return getBlobThumbnail(thumbnailPath.toStdWString());
    }

    void FileDetailGallery::updateFavorite(const FileDetail& fileDetail)
    {
        FileDatabase::getInst()->updateDetail(fileDetail);
    }

    void FileDetailGallery::removeFile(const QString& filePath)
    {
        FileDatabase::getInst()->deleteRecord(std::string(filePath.toUtf8()));
    }

    FileDetailWidget* FileDetailGallery::getNewDocWidget()
    {
        FileDetail data;
        data.file_name = "创建项目，开始工作吧~";
        FileDetailWidget* detailWidget = new FileDetailWidget(data, mCenterWidget);
        connect(detailWidget, &FileDetailWidget::sigDetailWidgetClicked, this, &FileDetailGallery::sigDetailWidgetClicked);
        connect(detailWidget, &FileDetailWidget::sigNewAssemblyClicked, this, &FileDetailGallery::sigNewAssembly);
        connect(detailWidget, &FileDetailWidget::sigNewPartClicked, this, &FileDetailGallery::sigNewPart);
        return detailWidget;
    }

    FileDetailWidget* FileDetailGallery::updatePoolWidget(const FileDetail& detail)
    {
        if (mPoolWidgets.empty()) { return nullptr; }

        for (auto it = mPoolWidgets.begin(); it != mPoolWidgets.end(); ++it) {
            if ((*it)->getFilePath() == detail.file_path) {
                (*it)->updateData(detail);
                FileDetailWidget* widget = *it;
                mPoolWidgets.erase(it);
                return widget;
            }
        }
        return nullptr;
    }

    void FileDetailGallery::loadData(const std::vector<FileDetail>& listData)
    {
        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(mCenterWidget->layout());
        if (!layout) { return; }

        mPoolWidgets.clear();
        
        if (!mWidgetList.isEmpty()) {
            layout->removeWidget(mNewDocWidget);
            mWidgetList.removeAt(0);

            //通过移除所有子控件来清空布局
            Q_FOREACH(FileDetailWidget * widget, mWidgetList) {
                layout->removeWidget(widget);
                mPoolWidgets.push_back(widget); // 移入回收池
            }
            mWidgetList.clear();
        }

        for (const auto& data : listData) {
            // 从组件池中获取控件
            FileDetailWidget* widget = updatePoolWidget(data);
            if (!widget) {
                widget = new FileDetailWidget(data, mCenterWidget);
                connect(widget, &FileDetailWidget::sigOpenFile, this, &FileDetailGallery::sigOpenFile);
                connect(widget, &FileDetailWidget::sigDeleteRecord, this, &FileDetailGallery::sigDeleteRecord);
            }
            layout->addWidget(widget);
            mWidgetList.append(widget);
        }

        //清空多余的widget
        Q_FOREACH(FileDetailWidget* widget, mPoolWidgets) {
            layout->removeWidget(widget);
            widget->deleteLater();
        }
        
        layout->insertWidget(0, mNewDocWidget);
        mWidgetList.insert(0, mNewDocWidget);

        resizeGallery();
    }

    void FileDetailGallery::resizeEvent(QResizeEvent* event)
    {
        QScrollArea::resizeEvent(event);
        resizeGallery();
    }

    void FileDetailGallery::resizeGallery()
    {
        if (mWidgetList.isEmpty() || !mCenterWidget->layout()) return;

        const int item_width = FileDetailWidget::fixedWidth;
        const int item_height = FileDetailWidget::fixedHeight;
        const int item_space_h = itemSpace_h;
        const int item_space_v = itemSpace_v;

        const int scrollbar_width = verticalScrollBar()->isVisible() ? verticalScrollBar()->width() : 0;

        // 使用QScrollArea的视口宽度
        const int viewport_width = this->viewport()->width();
        const int available_width = viewport_width - scrollbar_width;

        // 计算列数
        int col_count = qMax((available_width + item_space_h) / (item_width + item_space_h), 1);
        col_count = qMin(col_count, mWidgetList.size());

        // 行数
        int row_count = qMax((mWidgetList.size() + col_count - 1) / col_count, 1);
        int total_height = row_count * (item_height + item_space_v) + item_space_v * 2;

        mCenterWidget->setMinimumHeight(total_height);
        mCenterWidget->resize(viewport_width, total_height);

        int total_left = (viewport_width - col_count * (item_width + item_space_h)) / 2;
        int total_top = item_space_v;

        for (int i = 0, cur_row = 0, cur_col = 0; i < mWidgetList.size(); i++) {
            QPoint pos(
                total_left + cur_col * (item_width + item_space_h),
                total_top + cur_row * (item_height + item_space_v));

            FileDetailWidget* widget = mWidgetList.at(i);
            QPropertyAnimation* ani = new QPropertyAnimation(widget, "pos");
            ani->setStartValue(widget->pos());
            ani->setEndValue(pos);
            ani->setDuration(300);
            ani->setEasingCurve(QEasingCurve::OutQuad);
            connect(ani, &QPropertyAnimation::finished, ani, &QObject::deleteLater);
            ani->start();

            if (++cur_col >= col_count) {
                cur_col = 0;
                ++cur_row;
            }
        }
    }
}
