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

#include "FramelessHelper.h"

#include <QRubberBand>
#include <QHoverEvent>
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

namespace NCTI {

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#ifndef MOUSEEVENT_GLOBALPOS_POINT
#define MOUSEEVENT_GLOBALPOS_POINT(MouseEventPtr) MouseEventPtr->globalPosition().toPoint()
#endif
#else
#ifndef MOUSEEVENT_GLOBALPOS_POINT
#define MOUSEEVENT_GLOBALPOS_POINT(MouseEventPtr) MouseEventPtr->globalPos()
#endif
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#ifndef HOVEREVENT_POS_POINT
#define HOVEREVENT_POS_POINT(HoverEventPtr) HoverEventPtr->position().toPoint()
#endif
#else
#ifndef HOVEREVENT_POS_POINT
#define HOVEREVENT_POS_POINT(HoverEventPtr) HoverEventPtr->pos()
#endif
#endif

    class FramelessPrivateWidgetData;

    /*****
     * FramelessHelperPrivate
     * 存储界面对应的数据集合，以及是否可移动、可缩放属性
     *****/
    class FramelessHelper::PrivateData
    {
        NCTI_QT_PUBFUNC_DECLARE_PUBLIC(FramelessHelper)
            friend class FramelessPrivateWidgetData;

    public:
        PrivateData(FramelessHelper* p);
        QHash<QWidget*, FramelessPrivateWidgetData*> mWidgetDataHash;
        bool mWidgetMovable{ true };
        bool mWidgetResizable{ true };
        bool mRubberBandOnResize{ true };
        bool mRubberBandOnMove{ true };
    };

    FramelessHelper::PrivateData::PrivateData(FramelessHelper* p)
        : q_ptr(p)
    {
    }

    /*****
     * CursorPosCalculator
     * 计算鼠标是否位于左、上、右、下、左上角、左下角、右上角、右下角
     *****/
    class SAPrivateFramelessCursorPosCalculator
    {
    public:
        explicit SAPrivateFramelessCursorPosCalculator();
        void reset();
        void recalculate(const QPoint& globalMousePos, const QRect& frameRect);

    public:
        bool mIsOnEdges{ true };
        bool mIsOnLeftEdge{ true };
        bool mIsOnRightEdge{ true };
        bool mIsOnTopEdge{ true };
        bool mIsOnBottomEdge{ true };
        bool mIsOnTopLeftEdge{ true };
        bool mIsOnBottomLeftEdge{ true };
        bool mIsOnTopRightEdge{ true };
        bool mIsOnBottomRightEdge{ true };

        static int s_borderWidth;
        static int s_titleHeight;
    };

    int SAPrivateFramelessCursorPosCalculator::s_borderWidth = 5;
    int SAPrivateFramelessCursorPosCalculator::s_titleHeight = 30;

    /***** CursorPosCalculator *****/
    SAPrivateFramelessCursorPosCalculator::SAPrivateFramelessCursorPosCalculator()
    {
        reset();
    }

    void SAPrivateFramelessCursorPosCalculator::reset()
    {
        mIsOnEdges = false;
        mIsOnLeftEdge = false;
        mIsOnRightEdge = false;
        mIsOnTopEdge = false;
        mIsOnBottomEdge = false;
        mIsOnTopLeftEdge = false;
        mIsOnBottomLeftEdge = false;
        mIsOnTopRightEdge = false;
        mIsOnBottomRightEdge = false;
    }

    void SAPrivateFramelessCursorPosCalculator::recalculate(const QPoint& gMousePos, const QRect& frameRect)
    {
        int globalMouseX = gMousePos.x();
        int globalMouseY = gMousePos.y();

        int frameX = frameRect.x();
        int frameY = frameRect.y();

        int frameWidth = frameRect.width();
        int frameHeight = frameRect.height();

        mIsOnLeftEdge = (globalMouseX >= frameX && globalMouseX <= frameX + s_borderWidth);

        mIsOnRightEdge = (globalMouseX >= frameX + frameWidth - s_borderWidth && globalMouseX <= frameX + frameWidth);

        mIsOnTopEdge = (globalMouseY >= frameY && globalMouseY <= frameY + s_borderWidth);

        mIsOnBottomEdge = (globalMouseY >= frameY + frameHeight - s_borderWidth && globalMouseY <= frameY + frameHeight);

        mIsOnTopLeftEdge = mIsOnTopEdge && mIsOnLeftEdge;
        mIsOnBottomLeftEdge = mIsOnBottomEdge && mIsOnLeftEdge;
        mIsOnTopRightEdge = mIsOnTopEdge && mIsOnRightEdge;
        mIsOnBottomRightEdge = mIsOnBottomEdge && mIsOnRightEdge;

        mIsOnEdges = mIsOnLeftEdge || mIsOnRightEdge || mIsOnTopEdge || mIsOnBottomEdge;
    }

    /*****
     * WidgetData
     * 更新鼠标样式、移动窗体、缩放窗体
     *****/
    class FramelessPrivateWidgetData
    {
    public:
        explicit FramelessPrivateWidgetData(FramelessHelper::PrivateData* pd, QWidget* pTopLevelWidget);
        ~FramelessPrivateWidgetData();
        QWidget* widget();

        // 处理鼠标事件-划过、按下、释放、移动
        bool handleWidgetEvent(QEvent* event);

        // 更新橡皮筋状态
        void updateRubberBandStatus();

    private:
        // 更新鼠标样式
        void updateCursorShape(const QPoint& gMousePos);

        // 重置窗体大小
        void resizeWidget(const QPoint& gMousePos);

        // 移动窗体
        void moveWidget(const QPoint& gMousePos);

        // 处理鼠标按下
        bool handleMousePressEvent(QMouseEvent* event);

        // 处理鼠标释放
        bool handleMouseReleaseEvent(QMouseEvent* event);

        // 处理鼠标移动
        bool handleMouseMoveEvent(QMouseEvent* event);

        // 处理鼠标离开
        bool handleLeaveEvent(QEvent* event);

        // 处理鼠标进入
        bool handleHoverMoveEvent(QHoverEvent* event);

        // 处理鼠标双击事件
        bool handleDoubleClickedMouseEvent(QMouseEvent* event);

    private:
        FramelessHelper::PrivateData* d_ptr{ nullptr };
        QRubberBand* mRubberBand{ nullptr };
        QWidget* mWidget{ nullptr };
        QPoint mDragPos;
        SAPrivateFramelessCursorPosCalculator mPressedMousePos;
        SAPrivateFramelessCursorPosCalculator mMoveMousePos;
        bool mLeftButtonPressed{ false };
        bool mCursorShapeChanged{ false };
        bool mLeftButtonTitlePressed{ false };
        Qt::WindowFlags mWindowFlags;
    };

    /***** WidgetData *****/
    FramelessPrivateWidgetData::FramelessPrivateWidgetData(FramelessHelper::PrivateData* pd, QWidget* pTopLevelWidget)
        : d_ptr(pd)
        , mWidget(pTopLevelWidget)
    {
        mWindowFlags = mWidget->windowFlags();
        mWidget->setMouseTracking(true);
        mWidget->setAttribute(Qt::WA_Hover, true);

        updateRubberBandStatus();
    }

    FramelessPrivateWidgetData::~FramelessPrivateWidgetData()
    {
        mWidget->setMouseTracking(false);
        mWidget->setWindowFlags(mWindowFlags);
        mWidget->setAttribute(Qt::WA_Hover, false);

        delete mRubberBand;
        mRubberBand = nullptr;
    }

    QWidget* FramelessPrivateWidgetData::widget()
    {
        return (mWidget);
    }

    bool FramelessPrivateWidgetData::handleWidgetEvent(QEvent* event)
    {
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            return (handleMousePressEvent(static_cast<QMouseEvent*>(event)));

        case QEvent::MouseButtonRelease:
            return (handleMouseReleaseEvent(static_cast<QMouseEvent*>(event)));

        case QEvent::MouseMove:
            return (handleMouseMoveEvent(static_cast<QMouseEvent*>(event)));

        case QEvent::Leave:
            return (handleLeaveEvent(static_cast<QMouseEvent*>(event)));

        case QEvent::HoverMove:
            return (handleHoverMoveEvent(static_cast<QHoverEvent*>(event)));

        case QEvent::MouseButtonDblClick:
            return (handleDoubleClickedMouseEvent(static_cast<QMouseEvent*>(event)));

        default:
            break;
        }
        return (false);
    }

    void FramelessPrivateWidgetData::updateRubberBandStatus()
    {
        if (d_ptr->mRubberBandOnMove || d_ptr->mRubberBandOnResize) {
            if (NULL == mRubberBand) {
                mRubberBand = new QRubberBand(QRubberBand::Rectangle);
            }
        }
        else {
            delete mRubberBand;
            mRubberBand = NULL;
        }
    }

    void FramelessPrivateWidgetData::updateCursorShape(const QPoint& gMousePos)
    {
        if (mWidget->isFullScreen() || mWidget->isMaximized()) {
            if (mCursorShapeChanged) {
                mWidget->unsetCursor();
            }
            return;
        }

        mMoveMousePos.recalculate(gMousePos, mWidget->frameGeometry());

        if (mMoveMousePos.mIsOnTopLeftEdge || mMoveMousePos.mIsOnBottomRightEdge) {
            mWidget->setCursor(Qt::SizeFDiagCursor);
            mCursorShapeChanged = true;
        }
        else if (mMoveMousePos.mIsOnTopRightEdge || mMoveMousePos.mIsOnBottomLeftEdge) {
            mWidget->setCursor(Qt::SizeBDiagCursor);
            mCursorShapeChanged = true;
        }
        else if (mMoveMousePos.mIsOnLeftEdge || mMoveMousePos.mIsOnRightEdge) {
            mWidget->setCursor(Qt::SizeHorCursor);
            mCursorShapeChanged = true;
        }
        else if (mMoveMousePos.mIsOnTopEdge || mMoveMousePos.mIsOnBottomEdge) {
            mWidget->setCursor(Qt::SizeVerCursor);
            mCursorShapeChanged = true;
        }
        else {
            if (mCursorShapeChanged) {
                mWidget->unsetCursor();
                mCursorShapeChanged = false;
            }
        }
    }

    void FramelessPrivateWidgetData::resizeWidget(const QPoint& gMousePos)
    {
        QRect origRect;

        if (d_ptr->mRubberBandOnResize) {
            origRect = mRubberBand->frameGeometry();
        }
        else {
            origRect = mWidget->frameGeometry();
        }

        int left = origRect.left();
        int top = origRect.top();
        int right = origRect.right();
        int bottom = origRect.bottom();

        origRect.getCoords(&left, &top, &right, &bottom);

        int minWidth = mWidget->minimumWidth();
        int minHeight = mWidget->minimumHeight();

        if (mPressedMousePos.mIsOnTopLeftEdge) {
            left = gMousePos.x();
            top = gMousePos.y();
        }
        else if (mPressedMousePos.mIsOnBottomLeftEdge) {
            left = gMousePos.x();
            bottom = gMousePos.y();
        }
        else if (mPressedMousePos.mIsOnTopRightEdge) {
            right = gMousePos.x();
            top = gMousePos.y();
        }
        else if (mPressedMousePos.mIsOnBottomRightEdge) {
            right = gMousePos.x();
            bottom = gMousePos.y();
        }
        else if (mPressedMousePos.mIsOnLeftEdge) {
            left = gMousePos.x();
        }
        else if (mPressedMousePos.mIsOnRightEdge) {
            right = gMousePos.x();
        }
        else if (mPressedMousePos.mIsOnTopEdge) {
            top = gMousePos.y();
        }
        else if (mPressedMousePos.mIsOnBottomEdge) {
            bottom = gMousePos.y();
        }

        QRect newRect(QPoint(left, top), QPoint(right, bottom));

        if (newRect.isValid()) {
            if (minWidth > newRect.width()) {
                if (left != origRect.left()) {
                    newRect.setLeft(origRect.left());
                }
                else {
                    newRect.setRight(origRect.right());
                }
            }
            if (minHeight > newRect.height()) {
                if (top != origRect.top()) {
                    newRect.setTop(origRect.top());
                }
                else {
                    newRect.setBottom(origRect.bottom());
                }
            }

            if (d_ptr->mRubberBandOnResize) {
                mRubberBand->setGeometry(newRect);
            }
            else {
                mWidget->setGeometry(newRect);
            }
        }
    }

    void FramelessPrivateWidgetData::moveWidget(const QPoint& gMousePos)
    {
        if (d_ptr->mRubberBandOnMove) {
            mRubberBand->move(gMousePos - mDragPos);
        }
        else {
            mWidget->move(gMousePos - mDragPos);
        }
    }

    bool FramelessPrivateWidgetData::handleMousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton) {
            mLeftButtonPressed = true;
            mLeftButtonTitlePressed = event->pos().y() < mMoveMousePos.s_titleHeight;

            QRect frameRect = mWidget->frameGeometry();
            auto gp = MOUSEEVENT_GLOBALPOS_POINT(event);
            mPressedMousePos.recalculate(gp, frameRect);

            mDragPos = gp - frameRect.topLeft();

            if (mPressedMousePos.mIsOnEdges) {
                if (mWidget->isMaximized()) {
                    // 窗口在最大化状态时，点击边界不做任何处理
                    return (false);
                }
                if (d_ptr->mRubberBandOnResize) {
                    mRubberBand->setGeometry(frameRect);
                    mRubberBand->show();
                    return (true);
                }
            }
            else if (d_ptr->mRubberBandOnMove && mLeftButtonTitlePressed) {
                if (mWidget->isMaximized()) {
                    // 窗口在最大化状态时，点击标题栏不做任何处理
                    return (false);
                }
                mRubberBand->setGeometry(frameRect);
                mRubberBand->show();
                return (true);
            }
        }
        return (false);
    }

    bool FramelessPrivateWidgetData::handleMouseReleaseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton) {
            mLeftButtonPressed = false;
            mLeftButtonTitlePressed = false;
            mPressedMousePos.reset();
            if (mRubberBand && mRubberBand->isVisible()) {
                mRubberBand->hide();
                mWidget->setGeometry(mRubberBand->geometry());
                return (true);
            }
        }
        return (false);
    }

    bool FramelessPrivateWidgetData::handleMouseMoveEvent(QMouseEvent* event)
    {
        QPoint p = MOUSEEVENT_GLOBALPOS_POINT(event);
        if (mLeftButtonPressed) {
            if (d_ptr->mWidgetResizable && mPressedMousePos.mIsOnEdges) {
                if (mWidget->isMaximized()) {
                    // 窗口在最大化状态时，点击边界不做任何处理
                    return (false);
                }
                resizeWidget(p);
                return (true);
            }
            else if (d_ptr->mWidgetMovable && mLeftButtonTitlePressed) {
                if (mWidget->isMaximized()) {
                    // 先求出窗口到鼠标的相对位置
                    QRect normalGeometry = mWidget->normalGeometry();
                    mWidget->showNormal();
                    p.ry() -= 10;
                    p.rx() -= (normalGeometry.width() / 2);
                    mWidget->move(p);
                    // 这时要重置mDragPos
                    mDragPos = QPoint(normalGeometry.width() / 2, 10);
                    return (true);
                }
                moveWidget(p);
                return (true);
            }
            return (false);
        }
        else if (d_ptr->mWidgetResizable) {
            updateCursorShape(p);
        }
        return (false);
    }

    bool FramelessPrivateWidgetData::handleLeaveEvent(QEvent* event)
    {
        Q_UNUSED(event)
            if (!mLeftButtonPressed) {
                mWidget->unsetCursor();
                return (true);
            }
        return (false);
    }

    bool FramelessPrivateWidgetData::handleHoverMoveEvent(QHoverEvent* event)
    {
        if (d_ptr->mWidgetResizable) {
            updateCursorShape(mWidget->mapToGlobal(HOVEREVENT_POS_POINT(event)));
        }
        return (false);
    }

    bool FramelessPrivateWidgetData::handleDoubleClickedMouseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton) {
            if (mWidget) {
                QMainWindow* mainwindow = qobject_cast<QMainWindow*>(mWidget);
                if (mainwindow) {
                    if (mainwindow->windowFlags() & Qt::WindowMaximizeButtonHint) {
                        // 在最大化按钮显示时才进行shownormal处理
                        bool titlePressed = event->pos().y() < mMoveMousePos.s_titleHeight;
                        if (titlePressed) {
                            if (mWidget->isMaximized()) {
                                mWidget->showNormal();
                            }
                            else {
                                mWidget->showMaximized();
                            }
                            return (true);
                        }
                    }
                }
            }
        }
        return (false);
    }

    //===================================================
    // FramelessHelper
    //===================================================
    FramelessHelper::FramelessHelper(QObject* parent)
        : QObject(parent)
        , d_ptr(new FramelessHelper::PrivateData(this))
    {
        d_ptr->mWidgetMovable = true;
        d_ptr->mWidgetResizable = true;
        d_ptr->mRubberBandOnResize = false;
        d_ptr->mRubberBandOnMove = false;
        if (parent) {
            QWidget* w = qobject_cast<QWidget*>(parent);
            if (w) {
                w->setWindowFlags(w->windowFlags() | Qt::FramelessWindowHint);
                setWidgetMovable(true);      // 设置窗体可移动
                setWidgetResizable(true);    // 设置窗体可缩放
                setRubberBandOnMove(false);  // 设置橡皮筋效果-可移动
                setRubberBandOnResize(true); // 设置橡皮筋效果-可缩放
                activateOn(w);               // 激活当前窗体
            }
        }
    }

    FramelessHelper::~FramelessHelper()
    {
        QList<QWidget*> keys = d_ptr->mWidgetDataHash.keys();
        int size = keys.size();

        for (int i = 0; i < size; ++i) {
            delete d_ptr->mWidgetDataHash.take(keys[i]);
        }
    }

    bool FramelessHelper::eventFilter(QObject* obj, QEvent* event)
    {
        switch (event->type()) {
        case QEvent::MouseMove:
        case QEvent::HoverMove:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::Leave:
        {
            FramelessPrivateWidgetData* data = d_ptr->mWidgetDataHash.value(static_cast<QWidget*>(obj));
            if (data) {
                return (data->handleWidgetEvent(event));
            }
            break;
        }

        default:
            break;
        }
        return (QObject::eventFilter(obj, event));
    }

    void FramelessHelper::activateOn(QWidget* topLevelWidget)
    {
        if (!d_ptr->mWidgetDataHash.contains(topLevelWidget)) {
            FramelessPrivateWidgetData* data = new FramelessPrivateWidgetData(d_ptr.get(), topLevelWidget);
            d_ptr->mWidgetDataHash.insert(topLevelWidget, data);

            topLevelWidget->installEventFilter(this);
        }
    }

    void FramelessHelper::removeFrom(QWidget* topLevelWidget)
    {
        FramelessPrivateWidgetData* data = d_ptr->mWidgetDataHash.take(topLevelWidget);

        if (data) {
            topLevelWidget->removeEventFilter(this);
            delete data;
        }
    }

    void FramelessHelper::setRubberBandOnMove(bool movable)
    {
        d_ptr->mRubberBandOnMove = movable;
        QList<FramelessPrivateWidgetData*> list = d_ptr->mWidgetDataHash.values();

        Q_FOREACH(FramelessPrivateWidgetData * data, list) {
            data->updateRubberBandStatus();
        }
    }

    void FramelessHelper::setWidgetMovable(bool movable)
    {
        d_ptr->mWidgetMovable = movable;
    }

    void FramelessHelper::setWidgetResizable(bool resizable)
    {
        d_ptr->mWidgetResizable = resizable;
    }

    void FramelessHelper::setRubberBandOnResize(bool resizable)
    {
        d_ptr->mRubberBandOnResize = resizable;
        QList<FramelessPrivateWidgetData*> list = d_ptr->mWidgetDataHash.values();

        Q_FOREACH(FramelessPrivateWidgetData * data, list) {
            data->updateRubberBandStatus();
        }
    }

    void FramelessHelper::setBorderWidth(int width)
    {
        if (width > 0) {
            SAPrivateFramelessCursorPosCalculator::s_borderWidth = width;
        }
    }

    void FramelessHelper::setTitleHeight(int height)
    {
        if (height > 0) {
            SAPrivateFramelessCursorPosCalculator::s_titleHeight = height;
        }
    }

    bool FramelessHelper::widgetMovable()
    {
        return (d_ptr->mWidgetMovable);
    }

    bool FramelessHelper::widgetResizable()
    {
        return (d_ptr->mWidgetResizable);
    }

    bool FramelessHelper::rubberBandOnMove()
    {
        return (d_ptr->mRubberBandOnMove);
    }

    bool FramelessHelper::rubberBandOnResize()
    {
        return (d_ptr->mRubberBandOnResize);
    }

    uint FramelessHelper::borderWidth()
    {
        return (SAPrivateFramelessCursorPosCalculator::s_borderWidth);
    }

    uint FramelessHelper::titleHeight()
    {
        return (SAPrivateFramelessCursorPosCalculator::s_titleHeight);
    }
}