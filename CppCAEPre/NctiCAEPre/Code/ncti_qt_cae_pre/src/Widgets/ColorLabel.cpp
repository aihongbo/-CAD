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

#include "ColorLabel.h"
#include <QDebug>
#include <QPainter>

ColorLabel::ColorLabel(QWidget* parent) 
    : QLabel(parent)
    , colorPixmap(":/Option/SelectColorWidget.png")
    , selectedPoint(-1, -1)
    , circleRadius(5)
{
    setMouseTracking(true);
    setStyleSheet("background: transparent;"); // 确保背景透明
    if (!colorPixmap.isNull()) {
        setFixedSize(colorPixmap.size());
    }
}

void ColorLabel::setColorPixmap(const QPixmap& pixmap)
{
    colorPixmap = pixmap;
    setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 根据QLabel的大小缩放图片
}

void ColorLabel::mousePressEvent(QMouseEvent* event)
{
    if (!colorPixmap.isNull()) {
        QPoint clickPos = event->pos();
        QImage image = colorPixmap.toImage();
        QColor color = image.pixelColor(clickPos);

        Q_EMIT colorPicked(color); // 发出颜色选中信号
    }
    QPoint point = event->pos(); // 获取鼠标位置
    setSelectedPoint(point); // 调用方法设置选中点
}

void ColorLabel::setSelectedPoint(const QPoint& point) {
    if (selectedPoint != point) {
        selectedPoint = point;
        update();
    }
}

void ColorLabel::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawPixmap(rect(), colorPixmap);

    // 如果selectedPoint有效，则绘制小白圈
    if (selectedPoint.x() != -1 && selectedPoint.y() != -1) {
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::white, 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(QPointF(selectedPoint), circleRadius, circleRadius);
    }
}

QList<QPoint> ColorLabel::findColorsInImage(const QColor& targetColor, int tolerance) {
    QList<QPoint> matchPoints;
    QImage colorMap = colorPixmap.toImage();
    for (int y = 0; y < colorMap.height(); ++y) {
        for (int x = 0; x < colorMap.width(); ++x) {
            QColor pixelColor = colorMap.pixelColor(x, y);
            if (qAbs(pixelColor.red() - targetColor.red()) <= tolerance &&
                qAbs(pixelColor.green() - targetColor.green()) <= tolerance &&
                qAbs(pixelColor.blue() - targetColor.blue()) <= tolerance) {
                matchPoints.append(QPoint(x, y));
            }
        }
    }
    return matchPoints; // 返回所有匹配点的列表
}