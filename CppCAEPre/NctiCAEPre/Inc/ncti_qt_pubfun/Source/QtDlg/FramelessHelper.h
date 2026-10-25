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

#ifndef FRAMELESSHELPER_H
#define FRAMELESSHELPER_H

#include "dcl_ncti_qt_pubfun.h"

#include <QObject>
#include <memory>

class QWidget;

namespace NCTI {

    /**
     * @brief 无边框助手类
     * @details 用于实现无边框窗口的移动和缩放功能
     */
    class DECL_NCTI_QT_PUBFUN FramelessHelper : public QObject
    {
        Q_OBJECT
        NCTI_QT_PUBFUNC_DECLARE_PRIVATE(FramelessHelper)
        friend class FramelessPrivateWidgetData;

    public:
        /**
         * @brief 构造函数
         * @param parent 父对象指针
         */
        explicit FramelessHelper(QObject* parent);
        
        /**
         * @brief 析构函数
         */
        ~FramelessHelper();
        
        /**
         * @brief 激活窗体
         * @param topLevelWidget 顶层窗口指针
         */
        void activateOn(QWidget* topLevelWidget);

        /**
         * @brief 移除窗体
         * @param topLevelWidget 顶层窗口指针
         */
        void removeFrom(QWidget* topLevelWidget);

        /**
         * @brief 设置窗体移动
         * @param movable 是否可移动
         */
        void setWidgetMovable(bool movable);

        /**
         * @brief 设置窗体缩放
         * @param resizable 是否可缩放
         */
        void setWidgetResizable(bool resizable);

        /**
         * @brief 设置橡皮筋移动
         * @param movable 是否启用橡皮筋移动
         */
        void setRubberBandOnMove(bool movable);

        /**
         * @brief 设置橡皮筋缩放
         * @param resizable 是否启用橡皮筋缩放
         */
        void setRubberBandOnResize(bool resizable);

        /**
         * @brief 设置边框的宽度
         * @param width 边框宽度
         */
        void setBorderWidth(int width);

        /**
         * @brief 设置标题栏高度
         * @param height 标题栏高度
         */
        void setTitleHeight(int height);

        /**
         * @brief 窗体是否可缩放
         * @return 可缩放返回true，否则返回false
         */
        bool widgetResizable();
        
        /**
         * @brief 窗体是否可移动
         * @return 可移动返回true，否则返回false
         */
        bool widgetMovable();
        
        /**
         * @brief 是否启用橡皮筋移动
         * @return 启用返回true，否则返回false
         */
        bool rubberBandOnMove();
        
        /**
         * @brief 是否启用橡皮筋缩放
         * @return 启用返回true，否则返回false
         */
        bool rubberBandOnResize();
        
        /**
         * @brief 获取边框宽度
         * @return 边框宽度
         */
        uint borderWidth();
        
        /**
         * @brief 获取标题栏高度
         * @return 标题栏高度
         */
        uint titleHeight();

    protected:
        /**
         * @brief 事件过滤，进行移动、缩放等
         * @param obj 对象指针
         * @param event 事件指针
         * @return 处理了事件返回true，否则返回false
         */
        virtual bool eventFilter(QObject* obj, QEvent* event);
    };
}

#endif // !FRAMELESSHELPER_H