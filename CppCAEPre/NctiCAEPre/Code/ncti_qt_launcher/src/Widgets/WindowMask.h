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

#include <QPushButton>

namespace NCTI {
    /**
     * @brief 窗口遮罩类
     * @details 用于在窗口上显示遮罩层，通常用于模态对话框背景
     */
    class WindowMask : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         */
        explicit WindowMask(QWidget *parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~WindowMask() = default;

        /**
         * @brief 添加控件
         * @param widget 控件指针
         */
        void addWidget(QWidget* widget);
        
        /**
         * @brief 设置遮罩颜色
         * @param color 颜色
         * @param opacity 透明度
         */
        void setMaskColor(const QColor& color, float opacity);
        
        /**
         * @brief 设置顶层窗口
         * @param widget 窗口控件指针
         */
        void setTopWidget(QWidget* widget);
        
    private:
        /**
         * @brief 初始化
         */
        void init();
        
        /**
         * @brief 显示事件处理
         * @param event 显示事件指针
         */
        void showEvent(QShowEvent* event) override;
        
        /**
         * @brief 事件过滤器
         * @param watched 被观察对象
         * @param event 事件指针
         * @return 是否处理事件
         */
        bool eventFilter(QObject* watched, QEvent* event) override;
        
    private:
        QWidget* m_topWidget{ nullptr };    ///< 顶层窗口
        QWidget* m_widget{ nullptr };       ///< 遮罩中显示的窗口
    };
}