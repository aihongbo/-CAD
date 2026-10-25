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

#ifndef MAINWINDOW_CONTAINER_H
#define MAINWINDOW_CONTAINER_H

#include "SARibbonMainWindow.h"
#include "FileDetailGallery.h"

#include "IPCServerManager.h"
#include "WindowMask.h"

#include <QStackedWidget>
#include <QWidget>
#include <QTimer>
#include <QTreeWidget>
#include <QLineEdit>

namespace NCTI {

    class WindowMask;
    
    /**
     * @brief 主窗口容器类
     * @details 管理主窗口及其子窗口的容器类
     */
	class MainwindowContainer : public SARibbonMainWindow
	{
		Q_OBJECT

	public:
		MainwindowContainer(QWidget* parent = nullptr);
		~MainwindowContainer();

        /**
         * @brief 读取ncti文件的缩略图
         * @param nctiFilePath ncti文件路径
         * @param thumbnailPath 目标缩略图路径
         */
        static bool readNctiFileImage(const QString& nctiFilePath, const QString& thumbnailPath);

    protected:
        /**
         * @brief 关闭事件处理
         * @param e 关闭事件指针
         */
        void closeEvent(QCloseEvent* e) override;
        
        /**
         * @brief 调整大小事件处理
         * @param event 调整大小事件指针
         */
        void resizeEvent(QResizeEvent* event) override;

        /**
         * @brief 显示事件处理
         * @param event 显示事件指针
         */
        void showEvent(QShowEvent* event) override;
    
    private Q_SLOTS:
        /**
         * @brief 标题标签关闭槽函数
         * @param index 标签索引
         */
        void onTitleTabClose(int index);
        
        /**
         * @brief 套接字断开连接槽函数
         * @param socket 套接字指针
         */
        void onSocketDisconnected(QLocalSocket* socket);
        
        /**
         * @brief 处理窗口ID消息槽函数
         * @param socket 套接字指针
         * @param msgData 消息数据
         */
        void onMsgTypeWindowId(QLocalSocket* socket, const MessageData& fromData);


        /**
         * @brief 处理任务详情消息槽函数
         * @param msgData 消息数据
         */
        void onMsgTaskDetail(const MessageData& msgData);

        /**
         * @brief 处理退出保存消息槽函数
         * @param msgData 消息数据
         */
        void onMsgTypeExitSave(const MessageData& msgData);

        /**
         * @brief 处理文档更新消息槽函数
         * @param msgData 消息数据
         */
        void onMsgTypeDocDirty(const MessageData& msgData);

        /**
         * @brief 处理数据更新消息槽函数
         * @param msgData 消息数据
         */
        void onMsgTypeDataUpdate(const MessageData& msgData);
        
        /**
         * @brief 项改变槽函数
         * @param currentItem 当前项指针
         * @param previousItem 前一项指针
         */
        void onItemChanged(QTreeWidgetItem* currentItem, QTreeWidgetItem* previousItem);
        
        /**
         * @brief 搜索最近文件槽函数
         */
        void onSearchRecentFiles();
        
        /**
         * @brief 更新最近文件槽函数
         */
        void onUpdateRecentFiles();
        
    private:
        /**
         * @brief 创建子进程
         * @param type 子进程类型
         */
        void createSubProcess(const QString& type);

        /**
         * @brief 创建子进程
         * @param info 子进程信息
         */
        void createSubProcess(const TaskDetail& detail);

        /**
         * @brief 移除堆叠控件
         * @param widget 控件指针
         */
        void removeStackedWidget(QWidget* widget);
        
        /**
         * @brief 保存文件详情到数据库
         * @param msgData 消息数据
         */
        void saveFileDetailToDB(const MessageData& msgData);
        
    private:
        /**
         * @brief 设置UI界面
         */
        void setupUi();
        
        /**
         * @brief 设置功能区UI界面
         */
        void setupRibbonUi();
        
        /**
         * @brief 设置初始化图标标题
         */
        void setupIniIconTitle();
        
        /**
         * @brief 重新翻译功能区UI界面
         */
        void retranslateRibbonUi();
        
        /**
         * @brief 连接信号
         */
        void connectSignals();
     
        /**
         * @brief 初始化标题标签添加控件
         */
        void initTitleTabAddWidget();

        /**
         * @brief 标题标签改变槽函数
         * @param index 标签索引
         */
        void onTitleTabChanged(int index);
        
        /**
         * @brief 动作触发槽函数
         * @param action 动作指针
         */
        void onActionTriggered(QAction* action);

        /**
         * @brief 创建空白页
         */
        void createBlankPage();
       
        /**
         * @brief 创建最近文件页
         */
        void createRecentFilePage();
        
        /**
         * @brief 创建左侧控件
         * @return 控件指针
         */
        QWidget* createLeftSideWidget();
        
        /**
         * @brief 创建右侧控件
         * @return 控件指针
         */
        QWidget* createRightSideWidget();
        
        /**
         * @brief 初始化树控件
         * @param treeWidget 树控件指针
         */
        void initTreeWidget(QTreeWidget* treeWidget);
        
        /**
         * @brief 添加树控件数据
         * @param treeWidget 树控件指针
         */
        void addTreeWidgetData(QTreeWidget* treeWidget);
        
        /**
         * @brief 添加主页面标签
         */
        void addMainPageTab();
        
        /**
         * @brief 添加标题标签
         * @param nctiFilePath ncti文件路径
         */
        void addTitleTab(const QString& nctiFilePath = QString());
        
        /**
         * @brief 更新标题标签数据
         * @param msgData 消息数据
         */
        void updateTitleTabData(const MessageData& msgData);
        
        /**
         * @brief 移除标题标签
         * @param window_id 窗口ID
         */
        void removeTitleTab(int64_t window_id);
        
        /**
         * @brief 设置标签文本
         * @param text 文本内容
         */
        void setTabText(const QString& text);
        
        /**
         * @brief 获取新标签的文本
         */
        QString getNewTabText();

        /**
         * @brief 获取标签文本
         * @param index 标签索引
         * @return 标签文本
         */
        QString getTabText(int index) const;
        
        /**
         * @brief 判断标签是否被选中
         * @param index 标签索引
         * @return 选中返回true，否则返回false
         */
        bool isTabSelected(int index);

        /**
         * @brief 获取标签窗口ID
         * @param index 标签索引
         * @return 窗口ID
         */
        int64_t getTabWindowId(int index);
        
        /**
         * @brief 设置标题标签数据
         * @param tabbar 标签栏指针
         * @param index 标签索引
         * @param isLoading 是否正在加载
         * @param windowId 窗口ID
         */
        void setTitleTabData(QTabBar* tabbar, int index, bool isLoading, int64_t windowId);

        /**
         * @brief 新建零件槽函数
         */
        void onNewPart();

        /**
         * @brief 新建装配体槽函数
         */
        void onNewAssembly();

        /**
         * @brief 打开文件槽函数
         */
        void onOpenFile();
        
        /**
         * @brief 打开ncti文件槽函数
         * @param filePath 文件路径
         */
        void onOpenNctiFile(const QString& filePath);

        /**
         * @brief 检查文件是否存在
         * @param filePath 文件路径
         */
        bool checkFileExist(const QString& filePath);
        
        /**
         * @brief 移除记录槽函数
         * @param filePath 文件路径
         */
        void onRemoveRecord(const QString& filePath);
        
        /**
         * @brief 移除记录
         * @param filePath 文件路径
         * @param tips 提示信息
         */
        void removeRecord(const QString& filePath, const QString& tips);

    private:
        RecentFileType mRecentFileType{ RecentFileType::ALL_FILE };  ///< 最近文件类型
        std::unique_ptr<WindowMask> mWinMask;             ///< 窗口遮罩
        std::unique_ptr<IPCServerManager> mIpcManager;    ///< IPC管理器
        std::unique_ptr<TaskDetail> mTaskDetail;          ///< 任务详情
        QStackedWidget* mStackedWidget{ nullptr };        ///< 堆叠控件
        QWidget* mBlankPage{ nullptr };                   ///< 空白页
        QWidget* mRecentFilePage{ nullptr };              ///< 最近文件页
        QLineEdit* mSearchLineEdit{ nullptr };            ///< 搜索行编辑器
        FileDetailGallery* mFileDetailGallery{ nullptr }; ///< 文件详情画廊
        QString mSearchText;                              ///< 搜索文本
        QString mCachedExePath;                           ///< 缓存子进程路径
	};
}
#endif // MAINWINDOW_CONTAINER_H