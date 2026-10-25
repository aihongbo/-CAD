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

#include "SelectColorWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QShowEvent>
#include <QDoubleValidator>
#include <QDebug>

SelectColorWidget::SelectColorWidget(QWidget* parent)
    : QWidget(parent)
    , selectColorLabel(new ColorLabel(this))
    , redColorProgressBar(new QProgressBar(this))
    , greenColorProgressBar(new QProgressBar(this))
    , blueColorProgressBar(new QProgressBar(this))
{
    init();
    // 设置焦点策略，确保Widget可以接收键盘事件
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_StyledBackground, true);
    connect(redColorProportionNum, &ColorLineEdit::updateColor, this, &SelectColorWidget::onUpdateColorAndPoint);
    connect(greenColorProportionNum, &ColorLineEdit::updateColor, this, &SelectColorWidget::onUpdateColorAndPoint);
    connect(blueColorProportionNum, &ColorLineEdit::updateColor, this, &SelectColorWidget::onUpdateColorAndPoint);
    connect(colorName, &ColorLineEdit::updateColor, this, &SelectColorWidget::onUpdateRgbAndPoint);
}

void SelectColorWidget::init()
{
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->layout()->setContentsMargins(5, 0, 0, 0);
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->layout()->setContentsMargins(0, 5, 0, 5);
    selectColorLabel->setFixedSize(136, 109);
   
    colorName = new ColorLineEdit(this);
    colorName->setObjectName("colorName_ColorLineEdit");
    colorName->setFixedSize(100, 23);
    vLayout->addWidget(redColorProgressBar);
    vLayout->addWidget(greenColorProgressBar);
    vLayout->addWidget(blueColorProgressBar);
    vLayout->addWidget(colorName);

    redColorProgressBar->setFixedSize(100, 23);
    greenColorProgressBar->setFixedSize(100, 23);
    blueColorProgressBar->setFixedSize(100, 23);
    redColorProgressBar->setTextVisible(false);
    greenColorProgressBar->setTextVisible(false);
    blueColorProgressBar->setTextVisible(false);
    redColorProgressBar->setRange(0, 1000);
    greenColorProgressBar->setRange(0, 1000);
    blueColorProgressBar->setRange(0, 1000);
    
    QHBoxLayout* r_topLayout = new QHBoxLayout(redColorProgressBar);
    QHBoxLayout* g_topLayout = new QHBoxLayout(greenColorProgressBar);
    QHBoxLayout* b_topLayout = new QHBoxLayout(blueColorProgressBar);
    r_topLayout->setContentsMargins(10, 0, 0, 0);
    g_topLayout->setContentsMargins(10, 0, 0, 0);
    b_topLayout->setContentsMargins(10, 0, 0, 0);

    redColorProportion = new QLabel(this);
    greenColorProportion = new QLabel(this);
    blueColorProportion = new QLabel(this);
    redColorProportion->setObjectName("red_ColorProportion");
    greenColorProportion->setObjectName("green_ColorProportion");
    blueColorProportion->setObjectName("blue_ColorProportion");
    redColorProportion->setText(tr("红色："));
    greenColorProportion->setText(tr("绿色："));
    blueColorProportion->setText(tr("蓝色："));
    redColorProportionNum = new ColorLineEdit(this);
    greenColorProportionNum = new ColorLineEdit(this);
    blueColorProportionNum = new ColorLineEdit(this);
    redColorProportionNum->setObjectName("red_ColorProportionNum");
    greenColorProportionNum->setObjectName("green_ColorProportionNum");
    blueColorProportionNum->setObjectName("blue_ColorProportionNum");
    // 设置输入验证器，确保只接受数字输入
    QDoubleValidator* validator = new QDoubleValidator(0.0, 1.0, 3, this);
    redColorProportionNum->setValidator(validator);
    greenColorProportionNum->setValidator(validator);
    blueColorProportionNum->setValidator(validator);

    r_topLayout->addSpacing(5);
    r_topLayout->addWidget(redColorProportion);
    r_topLayout->addWidget(redColorProportionNum);
    g_topLayout->addSpacing(5);
    g_topLayout->addWidget(greenColorProportion);
    g_topLayout->addWidget(greenColorProportionNum);
    b_topLayout->addSpacing(5);
    b_topLayout->addWidget(blueColorProportion);
    b_topLayout->addWidget(blueColorProportionNum);
    
    hLayout->addWidget(selectColorLabel);
    hLayout->addLayout(vLayout);
}

void SelectColorWidget::onUpdateColorAndPoint()
{
    bool ok;
    double r = redColorProportionNum->text().toDouble(&ok);
    double g = greenColorProportionNum->text().toDouble(&ok);
    double b = blueColorProportionNum->text().toDouble(&ok);

    if (ok) {
        int r_i = r * 255;
        int g_i = g * 255;
        int b_i = b * 255;

        QColor color(r_i, g_i, b_i);
        QPalette palette;
        palette.setColor(QPalette::Window, color);
        QString hexColor = color.name().toUpper();
        colorName->setText(hexColor);

        updatePaint(color);
        Q_EMIT inputColor(color);
    }
}

void SelectColorWidget::onUpdateRgbAndPoint()
{
    QString hexColor = colorName->text();
    QColor color(hexColor);
    if (color.isValid()) {
        double r = static_cast<double>(color.red()) / 255.0;
        double g = static_cast<double>(color.green()) / 255.0;
        double b = static_cast<double>(color.blue()) / 255.0;

        QString str_r = QString::number(r, 'f', 3);
        QString str_g = QString::number(g, 'f', 3);
        QString str_b = QString::number(b, 'f', 3);

        redColorProportionNum->setText(str_r);
        greenColorProportionNum->setText(str_g);
        blueColorProportionNum->setText(str_b);

        updatePaint(color);
        Q_EMIT inputColor(color);
    }
}

ColorLabel* SelectColorWidget::getSelectColorLabel()
{
    return selectColorLabel;
}

QProgressBar* SelectColorWidget::getRedColorProgressBar()
{
    return redColorProgressBar;
}

QProgressBar* SelectColorWidget::getGreenColorProgressBar()
{
    return greenColorProgressBar;
}

QProgressBar* SelectColorWidget::getBuleColorProgressBar()
{
    return blueColorProgressBar;
}

ColorLineEdit* SelectColorWidget::getRedColorProportionNum()
{
    return redColorProportionNum;
}

ColorLineEdit* SelectColorWidget::getGreenColorProportionNum()
{
    return greenColorProportionNum;
}

ColorLineEdit* SelectColorWidget::getBuleColorProportionNum()
{
    return blueColorProportionNum;
}

ColorLineEdit* SelectColorWidget::getColorName()
{
    return colorName;
}

void SelectColorWidget::updatePaint(const QColor& color)
{
    QList<QPoint> matchPoints = selectColorLabel->findColorsInImage(color, 30);
    if (!matchPoints.isEmpty()) {
        QPoint firstMatchPoint = matchPoints.first(); // 获取第一个匹配点的坐标
        selectColorLabel->setSelectedPoint(firstMatchPoint);
    }
}

void SelectColorWidget::updateColor(const QColor& color)
{
    double r = static_cast<double>(color.red()) / 255.0;
    double g = static_cast<double>(color.green()) / 255.0;
    double b = static_cast<double>(color.blue()) / 255.0;

    redColorProgressBar->setValue(static_cast<int>(r * 1000));
    greenColorProgressBar->setValue(static_cast<int>(g * 1000));
    blueColorProgressBar->setValue(static_cast<int>(b * 1000));

    QString str_r = QString::number(r, 'f', 3);
    QString str_g = QString::number(g, 'f', 3);
    QString str_b = QString::number(b, 'f', 3);

    redColorProportionNum->setText(str_r);
    greenColorProportionNum->setText(str_g);
    blueColorProportionNum->setText(str_b);
    colorName->setText(color.name().toUpper());
    updatePaint(color);
}

void SelectColorWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    setFocus();
}

void SelectColorWidget::focusOutEvent(QFocusEvent* event)
{
    QWidget::focusOutEvent(event);
    hide();
}