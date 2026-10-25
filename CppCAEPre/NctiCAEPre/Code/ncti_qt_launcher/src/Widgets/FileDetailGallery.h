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

#pragma once

#include <QScrollArea>
#include "FileDatabase.h"

class QLabel;
class QPushButton;
namespace NCTI {
    /**
     * @brief 最近文件类型枚举
     */
    enum RecentFileType {
        RECENT_FILE,   ///< 最近文件
        ALL_FILE,      ///< 所有文件
        ASSEMBLY_FILE, ///< 装配文件
        PARTS_FILE,    ///< 零件文件
        FAVORITE_FILE  ///< 收藏文件
    };

    class NctiContextMenu;
    
    /**
     * @brief 文件详情控件类
     * @details 显示单个文件的详细信息，包括缩略图、文件名和更新时间
     */
    class FileDetailWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param data 文件详情数据
         * @param parent 父窗口指针
         */
        FileDetailWidget(const FileDetail& data, QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~FileDetailWidget();
        
        /**
         * @brief 更新数据
         * @param data 文件详情数据
         */
        void updateData(const FileDetail& data);
        
        /**
         * @brief 获取文件路径
         * @return 文件路径字符串
         */
        std::string getFilePath() const;
        
    public:
        static const int fixedWidth = 338;   ///< 固定宽度
        static const int fixedHeight = 274;  ///< 固定高度

    protected:
        /**
         * @brief 绘制事件处理
         * @param event 绘制事件指针
         */
        void paintEvent(QPaintEvent* event) override;
        
        /**
         * @brief 鼠标移动事件处理
         * @param event 鼠标事件指针
         */
        void mouseMoveEvent(QMouseEvent* event) override;
        
        /**
         * @brief 鼠标按下事件处理
         * @param event 鼠标事件指针
         */
        void mousePressEvent(QMouseEvent* event) override;
        
        /**
         * @brief 鼠标双击事件处理
         * @param event 鼠标事件指针
         */
        void mouseDoubleClickEvent(QMouseEvent* event) override;
        
        /**
         * @brief 上下文菜单事件处理
         * @param event 上下文菜单事件指针
         */
        void contextMenuEvent(QContextMenuEvent* event) override;
        
#if QT_VERSION_MAJOR >= 6
        /**
         * @brief 鼠标进入事件处理
         * @param event 鼠标进入事件指针
         */
        void enterEvent(QEnterEvent* event) override;
#else
        /**
         * @brief 鼠标进入事件处理
         * @param event 事件指针
         */
        void enterEvent(QEvent* event) override;
#endif
        
        /**
         * @brief 鼠标离开事件处理
         * @param event 事件指针
         */
        void leaveEvent(QEvent* event) override;

    private Q_SLOTS:
        /**
         * @brief 收藏按钮点击槽函数
         * @param checked 是否选中
         */
        void onFavoriteClicked(bool checked);
        
        /**
         * @brief 打开文件槽函数
         */
        void onOpenFile();
        
        /**
         * @brief 删除记录槽函数
         */
        void onDeleteRecord();

    Q_SIGNALS:
        /**
         * @brief 详情控件点击信号
         */
        void sigDetailWidgetClicked();
        
        /**
         * @brief 新建装配信号
         */
        void sigNewAssemblyClicked();
        
        /**
         * @brief 新建部件信号
         */
        void sigNewPartClicked();
        
        /**
         * @brief 打开文件信号
         * @param filePath 文件路径
         */
        void sigOpenFile(const QString& filePath);
        
        /**
         * @brief 删除记录信号
         * @param filePath 文件路径
         */
        void sigDeleteRecord(const QString& filePath);

    private:
        /**
         * @brief 判断是否为新建文档控件数据
         * @param data 文件详情数据
         * @return 是新建文档控件数据返回true，否则返回false
         */
        bool isNewDocWidgetData(const FileDetail& data);
        
        /**
         * @brief 判断点是否在图像区域内
         * @param point 点坐标
         * @return 在图像区域内返回true，否则返回false
         */
        bool isPointInImageArea(const QPoint& point);
        
        /**
         * @brief 绘制新建文档控件
         * @param painter 绘图设备
         */
        void drawNewDocWidget(QPainter& painter);
        
        /**
         * @brief 绘制项目控件
         * @param painter 绘图设备
         */
        void drawItemWidget(QPainter& painter);
        
        /**
         * @brief 初始化删除按钮
         */
        void initDeleteButton();
        
        /**
         * @brief 初始化收藏按钮
         */
        void initFavoriteButton();
        
        /**
         * @brief 初始化新建文档菜单
         */
        void initNewDocMenu();
        
        /**
         * @brief 初始化新项目菜单
         */
        void initNewItemMenu();
        
        /**
         * @brief 显示上下文菜单
         * @param pos 菜单位置
         */
        void showContextMenu(const QPoint& pos);
        
        /**
         * @brief 设置收藏图标
         * @param checked 是否选中
         */
        void setFavoriteIcon(bool checked);
        
        /**
         * @brief 格式化更新时间
         * @param update_time 更新时间戳
         * @return 格式化后的时间字符串
         */
        QString formatUpdateTime(std::uint64_t update_time);
        
        /**
         * @brief 获取当前时间（秒）
         * @return 当前时间戳
         */
        std::uint64_t getCurrentTimeInSeconds();

    private:
        const int thumbnailHeight = 200;  ///< 缩略图高度
        const int contentHeight = 74;     ///< 内容区域高度
        const int iconSize = 20;          ///< 图标大小

        FileDetail mDetailData;                    ///< 文件详情数据
        QPushButton* mDeleteButton{ nullptr };     ///< 删除按钮
        QPushButton* mFavoriteButton{ nullptr };   ///< 收藏按钮
        QLabel* mFileNameLabel{ nullptr };         ///< 文件名标签
        NctiContextMenu* mNewDocMenu{ nullptr };   ///< 新建文档菜单
        NctiContextMenu* mNewItemMenu{ nullptr };  ///< 新项目菜单
        QPixmap* mThumbnail{ nullptr };            ///< 缩略图
        QPixmap* mAddItem{ nullptr };              ///< 添加项目图标
        QRect mThumbnailRect;                      ///< 缩略图矩形区域
        bool mMouseOver = false;                   ///< 鼠标悬停状态
    };

    /**
     * @brief 文件详情画廊类
     * @details 管理和显示文件详情控件的集合，支持网格布局和文件操作
     */
    class FileDetailGallery : public QScrollArea
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        FileDetailGallery(QWidget* parent = nullptr);

        /**
         * @brief 加载数据
         * @param listData 文件详情数据列表
         */
        void loadData(const std::vector<FileDetail>& listData);

        /**
         * @brief 获取文件列表
         * @param fileType 文件类型
         * @return 文件详情列表
         */
        static std::vector<FileDetail> getFileList(RecentFileType fileType);
        
        /**
         * @brief 根据文件名获取文件列表
         * @param fileName 文件名
         * @return 文件详情列表
         */
        static std::vector<FileDetail> getFileList(const QString& fileName);

        /**
         * @brief 添加文件到文件列表
         * @param fileDetail 文件详情
         */
        static void setFileList(const FileDetail& fileDetail);

        /**
         * @brief 获取ncti文件的缩略图
         * @param nctiFilePath ncti文件路径
         * @return 缩略图路径
         */
        static QString getNctiThumbnail(const QString& nctiFilePath);
        
        /**
         * @brief 获取ncti文件的缩略图BLOB数据
         * @param nctiFilePath ncti文件路径
         * @return 缩略图BLOB数据
         */
        static std::vector<char> getNctiThumbnailBlob(const QString& nctiFilePath);

        /**
         * @brief 更新收藏状态
         * @param fileDetail 文件详情
         */
        static void updateFavorite(const FileDetail& fileDetail);
        
        /**
         * @brief 移除文件
         * @param filePath 文件路径
         */
        static void removeFile(const QString& filePath);

    Q_SIGNALS:
        /**
         * @brief 详情控件点击信号
         */
        void sigDetailWidgetClicked();
        
        /**
         * @brief 新建装配信号
         */
        void sigNewAssembly();
        
        /**
         * @brief 新建部件信号
         */
        void sigNewPart();
        
        /**
         * @brief 打开文件信号
         * @param filePath 文件路径
         */
        void sigOpenFile(const QString& filePath);
        
        /**
         * @brief 删除记录信号
         * @param filePath 文件路径
         */
        void sigDeleteRecord(const QString& filePath);
        
    protected:
        /**
         * @brief 调整大小事件处理
         * @param event 调整大小事件指针
         */
        void resizeEvent(QResizeEvent* event) override;
    
    private:
        /**
         * @brief 调整画廊大小
         */
        void resizeGallery();
        
        /**
         * @brief 获取新建文档控件
         * @return 文件详情控件指针
         */
        FileDetailWidget* getNewDocWidget();
        
        /**
         * @brief 更新池中的控件
         * @param detail 文件详情
         * @return 文件详情控件指针
         */
        FileDetailWidget* updatePoolWidget(const FileDetail& detail);
        
    private:
        static const int itemSpace_h = 22;  ///< 水平间距
        static const int itemSpace_v = 37;  ///< 垂直间距
        QList<FileDetailWidget*> mWidgetList;   ///< 当前显示的控件列表
        QList<FileDetailWidget*> mPoolWidgets;  ///< 可复用的控件池
        FileDetailWidget* mNewDocWidget = nullptr;  ///< 新建文档控件
        QWidget* mCenterWidget{ nullptr };          ///< 中心控件
    };
}