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

#ifndef NctiWindowPlatformContainer_h
#define NctiWindowPlatformContainer_h

#include <QWidget>

namespace NCTI {
	class NctiWindowPlatform;
    class NctiDocument;
	
    /**
	 * @brief 窗口平台容器类
	 * @details 用于管理窗口平台的容器控件
	 */
	class NctiWindowPlatformContainer : public QWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pParent 父控件指针
		 */
		NctiWindowPlatformContainer(QWidget *i_pParent = nullptr);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiWindowPlatformContainer();

        /**
         * @brief 创建平台窗口
         */
        void CreatePlatform();

		/**
		 * @brief 获取平台窗口
		 */
        NctiWindowPlatform* GetPlatform() const;

        /**
         * @brief 关闭平台窗口
         */
        void ClosePlatform();
        
        /**
         * @brief 获取当前视图文档
         */
        NctiDocument* GetCurrentViewDocument();

    Q_SIGNALS:
        void updatePlatform();

	protected:
		/**
		 * @brief 调整大小事件处理
		 * @param i_pEvent 事件指针
		 */
		void resizeEvent(QResizeEvent *i_pEvent) override;
		
		/**
		 * @brief 移动事件处理
		 * @param event 事件指针
		 */
        void moveEvent(QMoveEvent* event) override;

	private:
		NctiWindowPlatform* m_platform{ nullptr };  ///< 平台指针
        QTimer* m_updateTimer{ nullptr };           ///< 更新定时器
        QPoint m_lastPos;                           ///< 上次位置
        QSize m_lastSize;                           ///< 上次大小
	};
}

#endif // !NctiWindowPlatformContainer_h