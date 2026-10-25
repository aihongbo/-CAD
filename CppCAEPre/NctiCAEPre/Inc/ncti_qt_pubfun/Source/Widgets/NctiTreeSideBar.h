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
#include <QFrame>

class QToolButton;

namespace NCTI {
    class NctiTreeSidePanel;
    
    /**
     * @brief 树侧边栏类
     * @details 用于管理树形控件侧边栏的界面控件，支持添加侧边按钮和切换视图
     */
    class DECL_NCTI_QT_PUBFUN NctiTreeSideBar : public QFrame
    {
        Q_OBJECT
        NCTI_QT_PUBFUNC_DECLARE_PRIVATE(NctiTreeSideBar)
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        explicit NctiTreeSideBar(QWidget *parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        virtual ~NctiTreeSideBar();
        
        /**
         * @brief 获取当前索引
         * @return 当前索引
         */
        int getCurrentIndex() const;
        
        /**
         * @brief 设置当前索引
         * @param index 索引
         */
        void setCurrentIndex(int index);
        
        /**
         * @brief 获取当前控件
         * @return 控件指针
         */
        QWidget* getCurrentWidget() const;
        
        /**
         * @brief 根据索引获取控件
         * @param index 索引
         * @return 控件指针
         */
        QWidget* getWidget(int index) const;
        
        /**
         * @brief 取消其他按钮选中
         * @param button 按钮指针
         * @return 取消成功返回true，否则返回false
         */
        bool uncheckOtherButtons(QToolButton* button) const;
    
    Q_SIGNALS:
        /**
         * @brief 按钮点击信号
         * @param clickedButton 点击的按钮指针
         */
        void sigButtonClicked(QToolButton* clickedButton);
        
        /**
         * @brief 更新树模型信号
         */
        void updateTreeModel();

    public Q_SLOTS:
        /**
         * @brief 按钮点击槽函数
         * @param checked 是否选中
         */
        void onButtonClicked(bool checked);
        
        /**
         * @brief 显示上下文菜单槽函数
         * @param pos 位置点
         */
        void showContextMenu(const QPoint& pos);
        
    public:
        /**
         * @brief 添加侧边按钮
         * @param icon 图标
         * @param objName 对象名称
         * @param page 页面控件指针
         * @param id ID
         */
        void addSideButton(const QIcon& icon, const QString& objName, QWidget* page, int id);
        
        /**
         * @brief 设置侧边面板
         * @param sidePanel 侧边面板指针
         */
        void setSidePanel(NctiTreeSidePanel* sidePanel);
        
        /**
         * @brief 根据对象名称获取按钮
         * @param objName 对象名称
         * @return 按钮指针
         */
        QToolButton* getButtonByObjName(const QString& objName) const;
    };
}