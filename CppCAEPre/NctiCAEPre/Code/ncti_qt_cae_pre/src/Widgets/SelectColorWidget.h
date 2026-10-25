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
#include <QProgressBar>
#include <QLabel>
#include <QLineEdit>

#include "ColorLabel.h"
#include "ColorLineEdit.h"

/**
 * @brief 颜色选择控件类
 * @details 集成颜色图谱、RGB输入和颜色预览功能的颜色选择控件
 */
class SelectColorWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父控件指针
     */
    explicit SelectColorWidget(QWidget* parent = nullptr);
    
    /**
     * @brief 初始化控件
     */
    void init();

    /**
     * @brief 更新绘制
     * @param color 颜色值
     */
    void updatePaint(const QColor& color);

    /**
     * @brief 更新颜色控件
     * @param color 颜色值
     */
    void updateColor(const QColor& color);

protected:
    /**
     * @brief 显示事件处理
     * @param event 显示事件指针
     */
    void showEvent(QShowEvent* event) override;

    /**
     * @brief 失去焦点事件处理
     * @param event 焦点事件指针
     */
    void focusOutEvent(QFocusEvent* event) override;

Q_SIGNALS:
    /**
     * @brief 输入颜色信号
     * @param color 输入的颜色值
     */
    void inputColor(const QColor& color);

private Q_SLOTS:
    /**
     * @brief 更新颜色和点位置槽函数
     */
    void onUpdateColorAndPoint();
    
    /**
     * @brief 更新RGB和点位置槽函数
     */
    void onUpdateRgbAndPoint();

public:
    /**
     * @brief 获取颜色标签控件
     * @return 颜色标签控件指针
     */
    ColorLabel* getSelectColorLabel();
    
    /**
     * @brief 获取红色进度条控件
     * @return 红色进度条控件指针
     */
    QProgressBar* getRedColorProgressBar();
    
    /**
     * @brief 获取绿色进度条控件
     * @return 绿色进度条控件指针
     */
    QProgressBar* getGreenColorProgressBar();
    
    /**
     * @brief 获取蓝色进度条控件
     * @return 蓝色进度条控件指针
     */
    QProgressBar* getBuleColorProgressBar();
    
    /**
     * @brief 获取红色比例输入框
     * @return 红色比例输入框指针
     */
    ColorLineEdit* getRedColorProportionNum();
    
    /**
     * @brief 获取绿色比例输入框
     * @return 绿色比例输入框指针
     */
    ColorLineEdit* getGreenColorProportionNum();
    
    /**
     * @brief 获取蓝色比例输入框
     * @return 蓝色比例输入框指针
     */
    ColorLineEdit* getBuleColorProportionNum();
    
    /**
     * @brief 获取颜色名称输入框
     * @return 颜色名称输入框指针
     */
    ColorLineEdit* getColorName();
    
private:
    ColorLabel* selectColorLabel;              ///< 颜色标签控件
    QProgressBar* redColorProgressBar;         ///< 红色进度条控件
    QProgressBar* greenColorProgressBar;       ///< 绿色进度条控件
    QProgressBar* blueColorProgressBar;        ///< 蓝色进度条控件
    ColorLineEdit* redColorProportionNum;      ///< 红色比例输入框
    ColorLineEdit* greenColorProportionNum;    ///< 绿色比例输入框
    ColorLineEdit* blueColorProportionNum;     ///< 蓝色比例输入框
    QLabel* redColorProportion;                ///< 红色比例标签
    QLabel* greenColorProportion;              ///< 绿色比例标签
    QLabel* blueColorProportion;               ///< 蓝色比例标签

    ColorLineEdit* colorName;                  ///< 颜色名称输入框
};