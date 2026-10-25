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
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPolygonF>

/**
 * @brief 模型颜色预览控件类
 * @details 用于预览模型各部分颜色设置效果的控件
 */
class ModelColorPreviewWidget : public QWidget
{
	Q_OBJECT

public:
	/**
	 * @brief 构造函数
	 * @param parent 父控件指针
	 */
	ModelColorPreviewWidget(QWidget* parent = nullptr);

	/**
	 * @brief 设置点颜色
	 * @param color 颜色值
	 */
	void set_pointColor(QColor color);
	
	/**
	 * @brief 设置线颜色
	 * @param color 颜色值
	 */
	void set_lineColor(QColor color);
	
	/**
	 * @brief 设置面颜色
	 * @param color 颜色值
	 */
	void set_faceColor(QColor color);
	
	/**
	 * @brief 设置选中颜色
	 * @param color 颜色值
	 */
	void set_selectColor(QColor color);

	/**
	 * @brief RGB颜色转HSV颜色
	 * @param color RGB颜色值
	 */
	void rgbToHsv(QColor color);
    
protected:
    /**
     * @brief 绘制事件处理
     * @param event 绘制事件指针
     */
    void paintEvent(QPaintEvent* event) override;
    
    /**
     * @brief 鼠标按下事件处理
     * @param event 鼠标事件指针
     */
	void mousePressEvent(QMouseEvent* event) override;

private:
	QPolygonF polygon;           ///< 外部多边形
	QPointF innerPoint;          ///< 内部点

	QColor pointColor;           ///< 点的颜色
	QColor lineColor;            ///< 线条颜色
	QColor faceColor;            ///< 正面的填充颜色
	QColor topFaceColor;         ///< 上面颜色
	QColor leftFaceColor;        ///< 左面颜色
	QColor selectColor;          ///< 高亮颜色

	bool isChecked = false;      ///< 是否选中
};