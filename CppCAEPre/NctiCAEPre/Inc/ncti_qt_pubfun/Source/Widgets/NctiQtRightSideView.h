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

#include "dcl_ncti_qt_pubfun.h"
#include "ncti_base.h"
#include <QFrame>

class QToolButton;
class QUrl;
namespace NCTI
{
#ifdef NCTI_ENABLE_AIQA_SERVICE
    class NctiQtWebPubFunImpl;
#endif
    class NctiTreeSideBar;
    class NctiTreeSidePanel;
    class NctiObjectProperty;
    class NctiQtPythonScriptEdit;
    /**
     * @brief 右侧视图类
     * @details 用于管理右侧停靠面板的视图控件，包含脚本编辑器和属性面板
     */
    class DECL_NCTI_QT_PUBFUN NctiQtRightSideView : public QFrame
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        NctiQtRightSideView(QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        virtual ~NctiQtRightSideView();

        /**
         * @brief 获取编辑器视图
         * @return 脚本编辑器指针
         */
        NctiQtPythonScriptEdit* editorView();
        
        /**
         * @brief 获取属性视图
         * @return 对象属性指针
         */
        NctiObjectProperty* propertyView();

        /**
         * @brief 视图枚举
         */
        enum View {
            ViewEditor = 0,     ///< 编辑器视图
            ViewProperty,       ///< 属性视图
            ViewChat,
            ViewFav,
        };
        
        /**
         * @brief 隐藏脚本编辑器视图
         */
        void hideScriptEditor();
        
        /**
         * @brief 切换当前视图
         * @param view 视图类型
         */
        void changeCurrentView(View view);
        
        /**
         * @brief 获取当前视图
         * @return 当前视图类型
         */
        View currentView();

        /**
        * @brief 设置聊天和收藏视图的URL
        */
        void setUrl(const QUrl& chat, const QUrl& fav);
        
        /**
        * @brief 设置数据库路径
        */
        void setDbPath(const QString& path);

        /**
        * @brief 更新命令收藏视图
        */
        void updateFavView();

    Q_SIGNALS:
        /**
         * @brief 侧边栏可见性信号
         * @param index 索引
         * @param visible 是否可见
         */
        void sigSidePanelVisible(int index, bool visible);

    private Q_SLOTS:
        /**
         * @brief 侧边按钮点击槽函数
         * @param clickedButton 点击的按钮指针
         */
        void onSideButtonClicked(QToolButton* clickedButton);

    private:
        /**
         * @brief 设置界面
         */
        void setupUi();

    private:
        NctiQtPythonScriptEdit* m_EditerView{ nullptr }; ///< 编辑器视图指针
        NctiObjectProperty* m_PropertyView{ nullptr };   ///< 属性视图指针
        NctiTreeSideBar* m_SideBar{ nullptr };           ///< 侧边栏指针
        NctiTreeSidePanel* m_SidePanel{ nullptr };       ///< 侧边面板指针

#ifdef NCTI_ENABLE_AIQA_SERVICE
        std::unique_ptr<NctiQtWebPubFunImpl> m_WebPubFunImpl; ///< Web类指针
#endif
    };
};