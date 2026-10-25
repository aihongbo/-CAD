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

#ifndef LOADINGSPINNERWIDGET_H
#define LOADINGSPINNERWIDGET_H

#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include <QTimer>
#include <QColor>

namespace NCTI {

    using FuncCallback = std::function<void()>;

    /**
     * @brief 加载旋转控件类
     * @details 用于显示加载旋转动画的控件，支持自定义颜色、大小和旋转速度等属性
     */
    class DECL_NCTI_QT_PUBFUN LoadingSpinnerWidget : public QWidget
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         * @param centerOnParent 是否居中于父窗口
         * @param disableParentWhenSpinning 旋转时是否禁用父窗口
         */
        LoadingSpinnerWidget(QWidget* parent = nullptr, bool centerOnParent = true, bool disableParentWhenSpinning = true);
        
        /**
         * @brief 构造函数
         * @param modality 窗口模态性
         * @param parent 父窗口指针
         * @param centerOnParent 是否居中于父窗口
         * @param disableParentWhenSpinning 旋转时是否禁用父窗口
         */
        LoadingSpinnerWidget(Qt::WindowModality modality, QWidget* parent = nullptr, bool centerOnParent = true, bool disableParentWhenSpinning = true);

        ~LoadingSpinnerWidget();

        /**
         * @brief 显示加载控件
         * @param parent 父窗口指针
         * @param callback 回调函数
         * @param finishCb 加载结束回调函数
         * @param pt 位置点
         * @param clr 颜色
         */
        static void showLoading(QWidget* parent, FuncCallback callback, FuncCallback finishCb = nullptr, QPoint pt = QPoint{}, QColor clr = QColor{});

    public Q_SLOTS:
        /**
         * @brief 开始旋转
         */
        void start();
        
        /**
         * @brief 停止旋转
         */
        void stop();

    public:
        /**
         * @brief 设置颜色
         * @param color 颜色
         */
        void setColor(QColor color);
        
        /**
         * @brief 获取颜色
         * @return 颜色
         */
        QColor color();

        /**
         * @brief 设置圆度
         * @param roundness 圆度
         */
        void setRoundness(qreal roundness);
        
        /**
         * @brief 获取圆度
         * @return 圆度
         */
        qreal roundness() const;

        /**
         * @brief 设置最小轨迹不透明度
         * @param minimumTrailOpacity 最小轨迹不透明度
         */
        void setMinimumTrailOpacity(qreal minimumTrailOpacity);
        
        /**
         * @brief 获取最小轨迹不透明度
         * @return 最小轨迹不透明度
         */
        qreal minimumTrailOpacity() const;

        /**
         * @brief 设置轨迹淡出百分比
         * @param trail 轨迹淡出百分比
         */
        void setTrailFadePercentage(qreal trail);
        
        /**
         * @brief 获取轨迹淡出百分比
         * @return 轨迹淡出百分比
         */
        qreal trailFadePercentage() const;

        /**
         * @brief 设置每秒转数
         * @param revolutionsPerSecond 每秒转数
         */
        void setRevolutionsPerSecond(qreal revolutionsPerSecond);
        
        /**
         * @brief 获取每秒转数
         * @return 每秒转数
         */
        qreal revolutionsPerSecond() const;

        /**
         * @brief 设置线条数
         * @param lines 线条数
         */
        void setNumberOfLines(int lines);
        
        /**
         * @brief 获取线条数
         * @return 线条数
         */
        int numberOfLines() const;

        /**
         * @brief 设置线条长度
         * @param length 线条长度
         */
        void setLineLength(int length);
        
        /**
         * @brief 获取线条长度
         * @return 线条长度
         */
        int lineLength() const;

        /**
         * @brief 设置线条宽度
         * @param width 线条宽度
         */
        void setLineWidth(int width);
        
        /**
         * @brief 获取线条宽度
         * @return 线条宽度
         */
        int lineWidth() const;

        /**
         * @brief 设置内半径
         * @param radius 内半径
         */
        void setInnerRadius(int radius);
        
        /**
         * @brief 获取内半径
         * @return 内半径
         */
        int innerRadius() const;

        /**
         * @brief 设置文本
         * @param text 文本内容
         */
        void setText(QString text);

        /**
         * @brief 是否正在旋转
         * @return 正在旋转返回true，否则返回false
         */
        bool isSpinning() const;

        /**
         * @brief 设置是否居中于父窗口
         * @param bCenter 是否居中
         */
        void setCenterOnParent(bool bCenter);

        void setPyState(void* state);

    private Q_SLOTS:
        /**
         * @brief 旋转槽函数
         */
        void rotate();

    protected:
        /**
         * @brief 绘制事件处理
         * @param paintEvent 绘制事件指针
         */
        void paintEvent(QPaintEvent* paintEvent) override;

        /**
         * @brief 绘制线条
         * @param painter 绘图设备指针
         * @param index 索引
         */
        void drawLine(QPainter* painter, int index) const;

    private:
        /**
         * @brief 计算距离主线的距离
         * @param current 当前索引
         * @param primary 主线索引
         * @param totalNrOfLines 总线条数
         * @return 距离
         */
        static int lineCountDistanceFromPrimary(int current, int primary, int totalNrOfLines);
        
        /**
         * @brief 计算当前线条颜色
         * @param distance 距离
         * @param totalNrOfLines 总线条数
         * @param trailFadePerc 轨迹淡出百分比
         * @param minOpacity 最小不透明度
         * @param color 颜色
         * @return 线条颜色
         */
        static QColor currentLineColor(int distance, int totalNrOfLines, qreal trailFadePerc, qreal minOpacity, QColor color);

        /**
         * @brief 初始化
         */
        void initialize();
        
        /**
         * @brief 更新大小
         */
        void updateSize();
        
        /**
         * @brief 更新定时器
         */
        void updateTimer();
        
        /**
         * @brief 更新位置
         */
        void updatePosition();

    private:
        QColor  m_color{ Qt::white };                    ///< 颜色
        qreal   m_roundness{ 62.0 };                     ///< 圆度
        qreal   m_minTrailOpacity{ 15.0 };               ///< 最小轨迹不透明度
        qreal   m_trailFadePercentage{ 100.0 };          ///< 轨迹淡出百分比
        qreal   m_revolutionsPerSecond{ 1.0 };           ///< 每秒转数
        int     m_numberOfLines{ 8 };                    ///< 线条数
        int     m_lineLength{ 10 };                      ///< 线条长度
        int     m_lineWidth{ 4 };                        ///< 线条宽度
        int     m_innerRadius{ 10 };                     ///< 内半径
        bool    m_centerOnParent{ true };                ///< 是否居中于父窗口
        bool    m_disableParentWhenSpinning{ true };     ///< 旋转时是否禁用父窗口
        int     m_currentCounter{ 0 };                   ///< 当前计数器
        bool    m_isSpinning{ false };                   ///< 是否正在旋转
        QString m_text;                                  ///< 文本内容
        QScopedPointer<QTimer> m_timer;                  ///< 定时器指针
        void* m_pyState{ nullptr };                      ///< py线程状态
        LoadingSpinnerWidget(const LoadingSpinnerWidget&) = delete;
        LoadingSpinnerWidget& operator=(const LoadingSpinnerWidget&) = delete;
    };

}
#endif // LOADINGSPINNERWIDGET_H