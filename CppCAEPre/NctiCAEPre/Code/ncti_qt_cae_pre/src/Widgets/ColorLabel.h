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
#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include <QPixmap>
#include <QImage>

/**
 * @brief 颜色标签控件类
 * @details 用于显示颜色图谱并允许用户通过点击选择颜色的控件
 */
class ColorLabel : public QLabel
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父控件指针
     */
    explicit ColorLabel(QWidget* parent = nullptr);
    
    /**
     * @brief 设置颜色图谱
     * @param pixmap 颜色图谱图片
     */
    void setColorPixmap(const QPixmap& pixmap); 
    
    /**
     * @brief 设置选中点位置
     * @param point 选中点坐标
     */
    void setSelectedPoint(const QPoint& point);
    
    /**
     * @brief 在图片中查找指定颜色的点
     * @param targetColor 目标颜色
     * @param tolerance 容差值
     * @return 匹配点坐标列表
     */
    QList<QPoint> findColorsInImage(const QColor& targetColor, int tolerance = 0);

Q_SIGNALS:
    /**
     * @brief 颜色选择信号
     * @param color 选中的颜色
     */
    void colorPicked(const QColor& color); 

protected:
    /**
     * @brief 鼠标按下事件处理
     * @param event 鼠标事件指针
     */
    void mousePressEvent(QMouseEvent* event) override; 
    
    /**
     * @brief 绘制事件处理
     * @param event 绘制事件指针
     */
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap colorPixmap;     ///< 颜色图谱图片
    QPoint selectedPoint;    ///< 选中点的位置
    int circleRadius;        ///< 小白圈的半径
};