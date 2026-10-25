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

#ifndef NCTI_FRAMELESS_MANAGER_H
#define NCTI_FRAMELESS_MANAGER_H

#include "dcl_ncti_uioption.h"

#include <QObject>
#include <QDialog>

class QWidget;
class QVBoxLayout;
class QLabel;

namespace NCTI {
    class NCTI_UIOPTION NctiFramelessManager : public QObject
    {
        Q_OBJECT
    public:
        explicit NctiFramelessManager(QObject* parent);
        ~NctiFramelessManager();

        // 激活窗体功能
        void activateOn(QWidget* topLevelWidget);
        // 移除窗体功能
        void deactivateOn(QWidget* topLevelWidget);
        // 设置窗体可移动
        void setMovable(bool movable);
        // 设置窗体可缩放
        void setResizable(bool resizable);
        // 设置移动橡皮筋
        void setRubberBandOnMove(bool movable);
        // 设置缩放橡皮筋
        void setRubberBandOnResize(bool resizable);
        // 设置边框宽度
        void setBorderWidth(int width);
        // 设置标题栏高度
        void setTitleHeight(int height);

    protected:
        // 事件过滤：处理移动、缩放等
        virtual bool eventFilter(QObject* obj, QEvent* event) override;
    private:
        // 内部数据
        class PrivateData;
        friend class NctiFramelessManager::PrivateData;
        std::unique_ptr<PrivateData> d_ptr;
        friend class NctiFramelessWindowHandler;
    };
}

#endif // !NCTI_FRAMELESS_MANAGER_H
