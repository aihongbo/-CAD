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

#include "ModelColorPreviewWidget.h"

#include <QPainter>
#include <QMouseEvent>

ModelColorPreviewWidget::ModelColorPreviewWidget(QWidget* parent)
    : QWidget(parent)
    , pointColor(QColor("#f8cb16"))
    , lineColor(QColor("#ffffff")) // 初始线条颜色
    , faceColor(QColor("#d4dff7")) // 初始面颜色
    , selectColor(QColor("#f5800f"))
    , isChecked(false)
{
    rgbToHsv(faceColor);
    setAttribute(Qt::WA_StyledBackground, true);
    polygon << QPointF(15, 23) << QPointF(15, 83) << QPointF(45, 106) << QPointF(110, 98) << QPointF(110, 25) << QPointF(72, 19);//顶点
    innerPoint = QPointF(45, 29);
    setFixedSize(130, 130);
}
void ModelColorPreviewWidget::set_pointColor(QColor color)
{
    pointColor = color;
    update();
}
void ModelColorPreviewWidget::set_lineColor(QColor color)
{
    lineColor = color;
    update();
}

void ModelColorPreviewWidget::set_faceColor(QColor color)
{
    faceColor = color;
    rgbToHsv(color);
    update();
}
void ModelColorPreviewWidget::set_selectColor(QColor color)
{
    selectColor = color;
    update();
}
void ModelColorPreviewWidget::rgbToHsv(QColor color)
{
    int h, s, v;
    color.getHsv(&h, &s, &v); // 获取HSV值

    topFaceColor = QColor::fromHsv(h, s, static_cast<int>(v * 0.70f));
    leftFaceColor = QColor::fromHsv(h, s, static_cast<int>(v * 0.40f));
}
void ModelColorPreviewWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔颜色为黑色，绘制边
    QPen lpen(isChecked ? selectColor : lineColor);
    lpen.setWidth(1);
    painter.setPen(lpen);
    painter.drawPolygon(polygon);

    painter.drawLine(innerPoint, QPointF(15, 23));
    painter.drawLine(innerPoint, QPointF(45, 106));
    painter.drawLine(innerPoint, QPointF(110, 25));

    // 定义多边形区域并设置填充颜色
    QPolygonF polygon1 = QPolygonF() << QPointF(15, 83) << QPointF(15, 23) << QPointF(45, 29) << QPointF(45, 106);
    painter.setBrush(isChecked ? selectColor : leftFaceColor);
    painter.drawPolygon(polygon1);

    QPolygonF polygon2 = QPolygonF() << QPointF(45, 29) << QPointF(45, 106) << QPointF(110, 98) << QPointF(110, 25);
    painter.setBrush(isChecked ? selectColor : faceColor);
    painter.drawPolygon(polygon2);

    QPolygonF polygon3 = QPolygonF() << QPointF(15, 23) << QPointF(45, 29) << QPointF(110, 25) << QPointF(72, 19);
    painter.setBrush(isChecked ? selectColor : topFaceColor);
    painter.drawPolygon(polygon3);

    QPen pen(isChecked ? selectColor : pointColor);
    pen.setWidth(3);
    painter.setPen(pen);

    // 设置正方形的边长
    qreal squareSize = 6.0;

    for (const QPointF& point : polygon)
    {
        QRectF rect(point.x() - squareSize / 2, point.y() - squareSize / 2, squareSize, squareSize);
        painter.setBrush(isChecked ? selectColor : pointColor); // 设置填充模式
        painter.setPen(isChecked ? selectColor : pointColor); // 设置边框颜色
        painter.drawRect(rect); // 绘制正方形,代表点。
    }
    //内部点绘制
    QRectF innerRect(innerPoint.x() - squareSize / 2, innerPoint.y() - squareSize / 2, squareSize, squareSize);
    painter.setBrush(isChecked ? selectColor : pointColor);
    painter.setPen(isChecked ? selectColor : pointColor);
    painter.drawRect(innerRect);
}

void ModelColorPreviewWidget::mousePressEvent(QMouseEvent* event)
{
    if (polygon.containsPoint(event->pos(), Qt::OddEvenFill)) {
        if (isChecked == true)
        {
            isChecked = false;
            update(); // 触发重绘
        }
        else {
            isChecked = true;
            update();
        }

    }
    else {
        isChecked = false;
        update();
    }
}
