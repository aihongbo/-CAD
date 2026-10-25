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

#include "NctiFramelessManager.h"

#include <memory>
#include <QWidget>
#include <QRect>
#include <QRubberBand>
#include <QHoverEvent>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>

namespace NCTI {

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#define MOUSEEVENT_GLOBALPOS_POINT(MouseEventPtr) MouseEventPtr->globalPosition().toPoint()
#define HOVEREVENT_POS_POINT(HoverEventPtr)       HoverEventPtr->position().toPoint()
#else
#define MOUSEEVENT_GLOBALPOS_POINT(MouseEventPtr) MouseEventPtr->globalPos()
#define HOVEREVENT_POS_POINT(HoverEventPtr)       HoverEventPtr->pos()
#endif

class NctiFramelessWindowHandler;
class NctiFramelessManager::PrivateData
{
    friend class NctiFramelessManager;
    friend class NctiFramelessWindowHandler;
public:
    PrivateData(NctiFramelessManager* p)
        : q_ptr(p)
    {
    }
private:
    NctiFramelessManager* q_ptr{ nullptr };
    PrivateData(const PrivateData&) = delete;
    PrivateData& operator=(const PrivateData&) = delete;

    // 窗口数据映射
    QHash<QWidget*, NctiFramelessWindowHandler*> mWindowHandlerMap;
    bool mMovable            = true;  // 可移动
    bool mResizable          = true;  // 可缩放
    bool mRubberBandOnMove   = false; // 移动橡皮筋
    bool mRubberBandOnResize = false; // 缩放橡皮筋
    int mBorderWidth         = 5;     // 边框宽度
    int mTitleHeight         = 30;    // 标题栏高度
};

// 鼠标边缘位置枚举
enum CursorEdgePosition {
    None   = 0,
    Left   = 1 << 0,
    Right  = 1 << 1,
    Top    = 1 << 2,
    Bottom = 1 << 3,
    // 组合位置
    TopLeft     = Top | Left,
    TopRight    = Top | Right,
    BottomLeft  = Bottom | Left,
    BottomRight = Bottom | Right
};

class CursorPosCalculator
{
public:
    CursorPosCalculator() = default;
    
    void reset()
    {
        mEdgePosition = None;
        mIsCacheValid = false;
    }
    
    void recalculate(const QPoint& globalMousePos, const QRect& frameRect, int borderWidth, int titleHeight)
    {
        // 参数无变化，直接返回
        if (mIsCacheValid && mLastMousePos == globalMousePos && mLastFrameRect == frameRect
            && mLastBorderWidth == borderWidth && mLastTitleHeight == titleHeight) {
            return;
        }

        // 更新缓存
        mLastMousePos    = globalMousePos;
        mLastFrameRect   = frameRect;
        mLastBorderWidth = borderWidth;
        mLastTitleHeight = titleHeight;
        mIsCacheValid    = true;

        // 边界检查：鼠标不在窗口附近
        if (!isPointInRect(globalMousePos, frameRect.adjusted(-borderWidth, -borderWidth, borderWidth, borderWidth))) {
            mEdgePosition = None;
            return;
        }

        // 获取坐标
        int mouseX      = globalMousePos.x();
        int mouseY      = globalMousePos.y();
        int frameX      = frameRect.x();
        int frameY      = frameRect.y();
        int frameWidth  = frameRect.width();
        int frameHeight = frameRect.height();

        // 计算边界区域
        int leftRegionStart   = frameX;
        int leftRegionEnd     = frameX + borderWidth;
        int rightRegionStart  = frameX + frameWidth - borderWidth;
        int rightRegionEnd    = frameX + frameWidth;
        int topRegionStart    = frameY;
        int topRegionEnd      = frameY + borderWidth;
        int bottomRegionStart = frameY + frameHeight - borderWidth;
        int bottomRegionEnd   = frameY + frameHeight;

        // 位运算确定鼠标位置
        int positionBits = 0;

        // 检查左右边缘
        if (mouseX >= leftRegionStart && mouseX <= leftRegionEnd) {
            positionBits |= Left;
        }
        else if (mouseX >= rightRegionStart && mouseX <= rightRegionEnd) {
            positionBits |= Right;
        }

        // 检查上下边缘
        if (mouseY >= topRegionStart && mouseY <= topRegionEnd) {
            positionBits |= Top;
        }
        else if (mouseY >= bottomRegionStart && mouseY <= bottomRegionEnd) {
            positionBits |= Bottom;
        }

        // 设置结果
        mEdgePosition = static_cast<CursorEdgePosition>(positionBits);
    }
    
    bool isOnEdge() const            { return mEdgePosition != None; }
    bool isOnLeftEdge() const        { return mEdgePosition & Left; }
    bool isOnRightEdge() const       { return mEdgePosition & Right; }
    bool isOnTopEdge() const         { return mEdgePosition & Top; }
    bool isOnBottomEdge() const      { return mEdgePosition & Bottom; }
    bool isOnTopLeftEdge() const     { return mEdgePosition == TopLeft; }
    bool isOnBottomLeftEdge() const  { return mEdgePosition == BottomLeft; }
    bool isOnTopRightEdge() const    { return mEdgePosition == TopRight; }
    bool isOnBottomRightEdge() const { return mEdgePosition == BottomRight; }

private:
    CursorEdgePosition mEdgePosition = None;
    QPoint mLastMousePos{-1, -1};
    QRect mLastFrameRect { 0, 0, 0, 0};
    int mLastBorderWidth{0};
    int mLastTitleHeight{0};
    bool mIsCacheValid{false};
    
    bool isPointInRect(const QPoint& point, const QRect& rect) const
    {
        return (point.x() >= rect.x() && point.x() <= rect.x() + rect.width() && point.y() >= rect.y()
                && point.y() <= rect.y() + rect.height());
    }
};

struct WindowInteractionContext 
{
    QRect frameGeometry;
    QRect normalGeometry;
    bool isMaximized{false};
    bool isFullScreen{false};
    int minWidth{0};
    int minHeight{0};
    int titleHeight{0};
    int borderWidth{0};
    
    bool isValid{false};
    
    void update(const QWidget* widget, int titleHeight, int borderWidth) 
    {
        frameGeometry = widget->frameGeometry();
        normalGeometry = widget->normalGeometry();
        isMaximized = widget->isMaximized();
        isFullScreen = widget->isFullScreen();
        minWidth = widget->minimumWidth();
        minHeight = widget->minimumHeight();
        this->titleHeight = titleHeight;
        this->borderWidth = borderWidth;
        isValid = true;
    }
    
    // 检查是否在标题栏区域
    bool isTitlePressed(const QPoint& pos) const 
    {
        return pos.y() < titleHeight;
    }
    
    // 检查是否应跳过缩放操作
    bool shouldSkipResizeOperation() const 
    {
        return isMaximized || isFullScreen;
    }
};

class NctiFramelessWindowHandler
{
public:
    explicit NctiFramelessWindowHandler(NctiFramelessManager::PrivateData* d, QWidget* pTopLevelWidget);
    ~NctiFramelessWindowHandler();
    QWidget* widget();

    // 事件处理：鼠标按下、释放、移动、悬停、离开、双击
    bool handleWidgetEvent(QEvent* event);

    // 更新橡皮筋状态
    void updateRubberBandStatus();

private:
    // 缓存管理
    void updateWindowStateCache();
    inline bool isWidgetMaximized() const { return mWinCtx.isMaximized; }
    inline bool isWidgetFullScreen() const { return mWinCtx.isFullScreen; }
    inline bool isResizableOperationAllowed() const { return !mWinCtx.shouldSkipResizeOperation(); }
    inline bool isTitlePressed(const QPoint& pos) const { return mWinCtx.isTitlePressed(pos); }
    
    // 更新鼠标光标样式
    void updateCursorShape(const QPoint& globalMousePos);

    // 调整窗口大小
    void resizeWidget(const QPoint& globalMousePos);

    // 移动窗口
    void moveWidget(const QPoint& globalMousePos);

    // 处理鼠标按下事件
    bool handleMousePressEvent(QMouseEvent* event);

    // 处理鼠标释放事件
    bool handleMouseReleaseEvent(QMouseEvent* event);

    // 处理鼠标移动事件
    bool handleMouseMoveEvent(QMouseEvent* event);

    // 处理鼠标离开事件
    bool handleLeaveEvent(QEvent* event);

    // 处理鼠标悬停事件
    bool handleHoverMoveEvent(QHoverEvent* event);

    // 处理鼠标双击事件
    bool handleDoubleClickedMouseEvent(QMouseEvent* event);

private:
    NctiFramelessManager::PrivateData* d_ptr{nullptr};
    std::unique_ptr<QRubberBand> mRubberBand;
    QWidget* mWidget{nullptr};

    QPoint mDragPos;
    CursorPosCalculator mPressedMousePos;
    CursorPosCalculator mMoveMousePos;
    bool mLeftButtonPressed{false};
    bool mLeftButtonTitlePressed{false};

    bool mCursorShapeChanged{false};
    Qt::WindowFlags mWindowFlags;
    
    WindowInteractionContext mWinCtx{};
};


NctiFramelessWindowHandler::NctiFramelessWindowHandler(NctiFramelessManager::PrivateData* d, QWidget* pTopLevelWidget)
    : d_ptr(d)
    , mWidget(pTopLevelWidget)
{
    if (!pTopLevelWidget) {
        return;
    }
    mWindowFlags = mWidget->windowFlags();
    mWidget->setMouseTracking(true);
    mWidget->setAttribute(Qt::WA_Hover, true);
    updateWindowStateCache();
    updateRubberBandStatus();
}

NctiFramelessWindowHandler::~NctiFramelessWindowHandler()
{
    mWidget->setMouseTracking(false);
    mWidget->setWindowFlags(mWindowFlags);
    mWidget->setAttribute(Qt::WA_Hover, false);
}

QWidget* NctiFramelessWindowHandler::widget()
{
    return (mWidget);
}

// 更新窗口状态缓存
void NctiFramelessWindowHandler::updateWindowStateCache()
{
    mWinCtx.update(mWidget, d_ptr->mTitleHeight, d_ptr->mBorderWidth);
}

bool NctiFramelessWindowHandler::handleWidgetEvent(QEvent* event)
{
    // 对于可能改变窗口状态的事件，先更新缓存
    if (event->type() == QEvent::MouseButtonDblClick || 
        event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::MouseButtonRelease) {
        updateWindowStateCache();
    }
    
    // clang-format off
    switch (event->type()) {
        case QEvent::MouseButtonPress:    return (handleMousePressEvent(static_cast<QMouseEvent*>(event)));
        case QEvent::MouseButtonRelease:  return (handleMouseReleaseEvent(static_cast<QMouseEvent*>(event)));
        case QEvent::MouseMove:           return (handleMouseMoveEvent(static_cast<QMouseEvent*>(event)));
        case QEvent::Leave:               return (handleLeaveEvent(static_cast<QMouseEvent*>(event)));
        case QEvent::HoverMove:           return (handleHoverMoveEvent(static_cast<QHoverEvent*>(event)));
        case QEvent::MouseButtonDblClick: return (handleDoubleClickedMouseEvent(static_cast<QMouseEvent*>(event)));
        default: break;
    }
    // clang-format on
    return (false);
}

void NctiFramelessWindowHandler::updateRubberBandStatus()
{
    if (d_ptr->mRubberBandOnMove || d_ptr->mRubberBandOnResize) {
        if (!mRubberBand) {
            mRubberBand = std::make_unique<QRubberBand>(QRubberBand::Rectangle);
        }
    }
    else {
        mRubberBand.reset();
    }
}

void NctiFramelessWindowHandler::updateCursorShape(const QPoint& globalMousePos)
{
    // 全屏或最大化状态时重置光标
    if (isWidgetFullScreen() || isWidgetMaximized()) {
        if (mCursorShapeChanged) {
            mWidget->unsetCursor();
            mCursorShapeChanged = false;
        }
        return;
    }

    // 使用缓存的几何信息
    mMoveMousePos.recalculate(globalMousePos, mWinCtx.frameGeometry, mWinCtx.borderWidth, mWinCtx.titleHeight);

    // 设置鼠标光标
    if (mMoveMousePos.isOnTopLeftEdge() || mMoveMousePos.isOnBottomRightEdge()) {
        mWidget->setCursor(Qt::SizeFDiagCursor);
        mCursorShapeChanged = true;
    }
    else if (mMoveMousePos.isOnTopRightEdge() || mMoveMousePos.isOnBottomLeftEdge()) {
        mWidget->setCursor(Qt::SizeBDiagCursor);
        mCursorShapeChanged = true;
    }
    else if (mMoveMousePos.isOnLeftEdge() || mMoveMousePos.isOnRightEdge()) {
        mWidget->setCursor(Qt::SizeHorCursor);
        mCursorShapeChanged = true;
    }
    else if (mMoveMousePos.isOnTopEdge() || mMoveMousePos.isOnBottomEdge()) {
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

void NctiFramelessWindowHandler::resizeWidget(const QPoint& globalMousePos)
{
    // 使用缓存的几何信息
    QRect origRect = d_ptr->mRubberBandOnResize ? mRubberBand->frameGeometry() : mWinCtx.frameGeometry;

    // 获取坐标
    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();

    // 根据边缘检测计算新边界
    if (mPressedMousePos.isOnTopLeftEdge()) {
        left = globalMousePos.x();
        top = globalMousePos.y();
    }
    else if (mPressedMousePos.isOnBottomLeftEdge()) {
        left = globalMousePos.x();
        bottom = globalMousePos.y();
    }
    else if (mPressedMousePos.isOnTopRightEdge()) {
        right = globalMousePos.x();
        top = globalMousePos.y();
    }
    else if (mPressedMousePos.isOnBottomRightEdge()) {
        right = globalMousePos.x();
        bottom = globalMousePos.y();
    }
    else if (mPressedMousePos.isOnLeftEdge()) {
        left = globalMousePos.x();
    }
    else if (mPressedMousePos.isOnRightEdge()) {
        right = globalMousePos.x();
    }
    else if (mPressedMousePos.isOnTopEdge()) {
        top = globalMousePos.y();
    }
    else if (mPressedMousePos.isOnBottomEdge()) {
        bottom = globalMousePos.y();
    }

    // 创建新矩形
    QRect newRect(QPoint(left, top), QPoint(right, bottom));

    // 检查最小尺寸
    if (newRect.isValid()) {
        // 检查最小宽度
        if (mWinCtx.minWidth > newRect.width()) {
            if (left != origRect.left()) {
                newRect.setLeft(origRect.left());
            } else {
                newRect.setRight(origRect.right());
            }
        }
        
        // 检查最小高度
        if (mWinCtx.minHeight > newRect.height()) {
            if (top != origRect.top()) {
                newRect.setTop(origRect.top());
            } else {
                newRect.setBottom(origRect.bottom());
            }
        }

        // 应用新几何形状
        if (d_ptr->mRubberBandOnResize) {
            mRubberBand->setGeometry(newRect);
        } else {
            mWidget->setGeometry(newRect);
        }
    }
}

void NctiFramelessWindowHandler::moveWidget(const QPoint& globalMousePos)
{
    if (d_ptr->mRubberBandOnMove) {
        mRubberBand->move(globalMousePos - mDragPos);
    }
    else {
        mWidget->move(globalMousePos - mDragPos);
    }
}

bool NctiFramelessWindowHandler::handleMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        mLeftButtonPressed = true;
        // 使用缓存的标题栏高度进行标题区域判断
        mLeftButtonTitlePressed = isTitlePressed(event->pos());

        auto gp = MOUSEEVENT_GLOBALPOS_POINT(event);
        
        // 使用缓存的窗口几何信息
        mPressedMousePos.recalculate(gp, mWinCtx.frameGeometry, mWinCtx.borderWidth, mWinCtx.titleHeight);

        mDragPos = gp - mWinCtx.frameGeometry.topLeft();

        if (mPressedMousePos.isOnEdge()) {
            // 窗口在最大化状态时，点击边界不做任何处理
            if (isWidgetMaximized()) {
                return false;
            }
            
            if (d_ptr->mRubberBandOnResize) {
                mRubberBand->setGeometry(mWinCtx.frameGeometry);
                mRubberBand->show();
                return true;
            }
        }
        else if (d_ptr->mRubberBandOnMove && mLeftButtonTitlePressed) {
            // 窗口在最大化状态时，点击标题栏不做任何处理
            if (isWidgetMaximized()) {
                return false;
            }
            
            mRubberBand->setGeometry(mWinCtx.frameGeometry);
            mRubberBand->show();
            return true;
        }
    }
    return false;
}

bool NctiFramelessWindowHandler::handleMouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        mLeftButtonPressed      = false;
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

bool NctiFramelessWindowHandler::handleMouseMoveEvent(QMouseEvent* event)
{
    QPoint p = MOUSEEVENT_GLOBALPOS_POINT(event);
    
    if (mLeftButtonPressed) {
        // 使用缓存的状态检查可缩放性
        if (d_ptr->mResizable && mPressedMousePos.isOnEdge()) {
            if (isWidgetMaximized()) {
                // 窗口在最大化状态时，点击边界不做任何处理
                return false;
            }
            
            resizeWidget(p);
            return true;
        }
        else if (d_ptr->mMovable && mLeftButtonTitlePressed) {
            if (isWidgetMaximized()) {
                // 先求出窗口到鼠标的相对位置
                QRect normalGeometry = mWinCtx.normalGeometry;
                mWidget->showNormal();
                p.ry() -= 10;
                p.rx() -= (normalGeometry.width() / 2);
                mWidget->move(p);
                // 这时要重置mDragPos
                mDragPos = QPoint(normalGeometry.width() / 2, 10);
                
                // 更新窗口状态缓存
                updateWindowStateCache();
                return true;
            }
            
            moveWidget(p);
            return true;
        }
        return false;
    }
    else if (d_ptr->mResizable) {
        updateCursorShape(p);
    }
    return false;
}

bool NctiFramelessWindowHandler::handleLeaveEvent(QEvent* event)
{
    Q_UNUSED(event)
    if (!mLeftButtonPressed) {
        mWidget->unsetCursor();
        return true;
    }
    return false;
}

bool NctiFramelessWindowHandler::handleHoverMoveEvent(QHoverEvent* event)
{
    if (d_ptr->mResizable) {
        updateCursorShape(mWidget->mapToGlobal(HOVEREVENT_POS_POINT(event)));
    }
    return false;
}

bool NctiFramelessWindowHandler::handleDoubleClickedMouseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && mWidget) {
        QMainWindow* mainwindow = qobject_cast<QMainWindow*>(mWidget);
        if (mainwindow && (mainwindow->windowFlags() & Qt::WindowMaximizeButtonHint)) {
            // 使用缓存的标题栏高度进行标题区域判断
            if (isTitlePressed(event->pos())) {
                if (isWidgetMaximized()) {
                    mWidget->showNormal();
                } else {
                    mWidget->showMaximized();
                }
                
                // 窗口状态可能改变，更新缓存
                updateWindowStateCache();
                return true;
            }
        }
    }
    return false;
}

//===================================================
// NctiFramelessManager
//===================================================
NctiFramelessManager::NctiFramelessManager(QObject* parent)
    : QObject(parent)
    , d_ptr(new NctiFramelessManager::PrivateData(this))
{
    d_ptr->mMovable      = true;
    d_ptr->mResizable    = true;
    d_ptr->mRubberBandOnResize = false;
    d_ptr->mRubberBandOnMove   = false;
    if (parent) {
        QWidget* w = qobject_cast<QWidget*>(parent);
        if (w) {
            w->setWindowFlags(w->windowFlags() | Qt::FramelessWindowHint);
            setMovable(true); 
            setResizable(true);
            setRubberBandOnMove(false);
            setRubberBandOnResize(true);
            activateOn(w);
        }
    }
}

NctiFramelessManager::~NctiFramelessManager()
{
    qDeleteAll(d_ptr->mWindowHandlerMap.values());
    d_ptr->mWindowHandlerMap.clear();
}

void NctiFramelessManager::activateOn(QWidget* topLevelWidget)
{
    if (!topLevelWidget || d_ptr->mWindowHandlerMap.contains(topLevelWidget)) {
        return;
    }
    NctiFramelessWindowHandler* data = new NctiFramelessWindowHandler(d_ptr.get(), topLevelWidget);
    d_ptr->mWindowHandlerMap.insert(topLevelWidget, data);
    topLevelWidget->installEventFilter(this);
}

void NctiFramelessManager::deactivateOn(QWidget* topLevelWidget)
{
    if (!topLevelWidget)
        return;

    auto* data = d_ptr->mWindowHandlerMap.take(topLevelWidget);
    if (data) {
        topLevelWidget->removeEventFilter(this);
        delete data;
    }
}

void NctiFramelessManager::setRubberBandOnMove(bool movable)
{
    d_ptr->mRubberBandOnMove             = movable;
    QList<NctiFramelessWindowHandler*> list = d_ptr->mWindowHandlerMap.values();

    Q_FOREACH (NctiFramelessWindowHandler* data, list) {
        data->updateRubberBandStatus();
    }
}

void NctiFramelessManager::setMovable(bool movable)
{
    d_ptr->mMovable = movable;
}

void NctiFramelessManager::setResizable(bool resizable)
{
    d_ptr->mResizable = resizable;
}

void NctiFramelessManager::setRubberBandOnResize(bool resizable)
{
    d_ptr->mRubberBandOnResize           = resizable;
    QList<NctiFramelessWindowHandler*> list = d_ptr->mWindowHandlerMap.values();

    Q_FOREACH (NctiFramelessWindowHandler* data, list) {
        data->updateRubberBandStatus();
    }
}

void NctiFramelessManager::setBorderWidth(int width)
{
    if (width > 0) {
        d_ptr->mBorderWidth = width;
    }
}

void NctiFramelessManager::setTitleHeight(int height)
{
    if (height > 0) {
        d_ptr->mTitleHeight = height;
    }
}

bool NctiFramelessManager::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        case QEvent::MouseButtonDblClick:
        case QEvent::Leave:
        case QEvent::HoverMove:
        {
            if (auto* widget = static_cast<QWidget*>(obj)) {
                if (auto* data = d_ptr->mWindowHandlerMap.value(widget)) {
                    return data->handleWidgetEvent(event);
                }
            }
            break;
        }

        default: break;
    }
    return (QObject::eventFilter(obj, event));
}

}