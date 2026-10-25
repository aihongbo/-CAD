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

#include "NctiMeshQualityDlg.h"

NctiMeshQualityDlg::NctiMeshQualityDlg(int nMode, std::vector<std::string> sTextList, const std::vector<double>& dValueList, QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    m_nMode = nMode;
    m_sTextList = sTextList;
    m_dValueList = dValueList;
    m_restorColor_callback = NULL;
    init();
}

NctiMeshQualityDlg::~NctiMeshQualityDlg()
{}

void NctiMeshQualityDlg::init()
{
    QStringList list;
    for (int i = 0; i < m_sTextList.size(); i++)
    {
        list.append(QString("%1").arg(m_sTextList[i].c_str()));
    }
    m_model = new QStringListModel(list);
    ui.listView->setModel(m_model);

    if (list.isEmpty())
    {
        list.append("");
    }
    ui.lab->setText(list.first());
    ui.lab2->setText(list.first());
    
    //std::vector<std::string> strHintList;
    //strHintList.push_back("最小角度 3D");
    //ui.lab2->setText(QString("%1").arg(strHintList[0].c_str()));
    
    //直方图
    DrawHistogramWidget* drawWidget = new DrawHistogramWidget(m_nMode, m_dValueList, ui.tab);
    drawWidget->setObjectName(QString::fromUtf8("drawWidget"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(drawWidget->sizePolicy().hasHeightForWidth());
    drawWidget->setSizePolicy(sizePolicy1);
    ui.horizontalLayout->addWidget(drawWidget);

    //表格
    ui.tableWidget->setColumnCount(2);  // 设置列数
    if (m_nMode == 2) //雅克比
    {
        ui.tableWidget->setRowCount(4);  // 设置行数
    }
    else
    {
        ui.tableWidget->setRowCount(6);  // 设置行数
    }
    
    // 设置表头
    QStringList headers;
    headers.append("Range");
    headers.append("number of element");
    ui.tableWidget->setHorizontalHeaderLabels(headers);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {background:white;color:grey; }");
    ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {border: 1px solid grey; }");
    int nRow = 6;
    if (m_nMode == 2)  //2 雅克比
        nRow = 4;

    double dMinValue = 999999;
    double dMaxValue = 0;
    for (int i = 0; i < m_dValueList.size(); i++)
    {
        double fValue = m_dValueList[i];
        if (fValue < dMinValue)
            dMinValue = fValue;
        if (fValue > dMaxValue)
            dMaxValue = fValue;
    }

    double dUnit = (dMaxValue - dMinValue) / (double)(nRow - 1);
    QMap<int, int> indexAndNumMap;
    for (int i = 0; i < nRow; i++)
    {
        indexAndNumMap[i] = 0;
    }

    for (int i = 0; i < m_dValueList.size(); i++)
    {
        double aspectRatio = m_dValueList[i];
        int nIndex = (aspectRatio - dMinValue) / dUnit;
        indexAndNumMap[nIndex]++;
    }

    double dUnitList[5] = {0, 0.3,0.5,0.7,1.0 };
    if (m_nMode == 2)  //2 雅克比
    {
        indexAndNumMap.clear();
        for (int i = 0; i < m_dValueList.size(); i++)
        {
            double aspectRatio = m_dValueList[i];
            if (0 <= aspectRatio && aspectRatio <= 0.3)
                indexAndNumMap[0]++;
            else if (0.3 < aspectRatio && aspectRatio <= 0.5)
                indexAndNumMap[1]++;
            else if (0.5 < aspectRatio && aspectRatio <= 0.7)
                indexAndNumMap[2]++;
            else if (0.7 < aspectRatio && aspectRatio <= 1.0)
                indexAndNumMap[3]++;
        }
    }

    for (int i = 0; i < nRow; i++)
    {
        int nIndex = i;
        int nNum = indexAndNumMap[nIndex];
        QString strRange = QString::number(dMinValue + (i * dUnit), 'f', 2) + "-" + QString::number(dMinValue + ((i + 1) * dUnit), 'f', 2);
        if (m_nMode == 2)  //2 雅克比
            strRange = QString::number(dUnitList[i], 'f', 2) + "-" + QString::number(dUnitList[i + 1], 'f', 2);
        QString strNum = QString::number(nNum);
        QTableWidgetItem* item1 = new QTableWidgetItem(strRange);
        QTableWidgetItem* item2 = new QTableWidgetItem(strNum);
        ui.tableWidget->setItem(i, 0, item1);
        ui.tableWidget->setItem(i, 1, item2);
    }
}

void NctiMeshQualityDlg::setCallBack(std::function<void()> func)
{
    m_restorColor_callback = func;
}

void NctiMeshQualityDlg::closeEvent(QCloseEvent* event)
{
    if (m_restorColor_callback)
        m_restorColor_callback();
}

//绘制直方图的类
DrawHistogramWidget::DrawHistogramWidget(int nMode,const std::vector<double>& dValueList, QWidget* parent)
    : QWidget(parent)
{
    m_nMode = nMode;
    m_dValueList = dValueList;
}

void DrawHistogramWidget::GetHotColor(double dColor, int& nR, int& nG, int& nB)
{
    if (dColor < 0)
        dColor = 0;
    if (dColor > 1)
        dColor = 1;
    double dR = 0.0;
    double dG = 0.0;
    double dB = 0.0;
    if (dColor <= 0.25)
    {
        dR = 0;
        dG = dColor * 4;
        dB = 1;
    }
    else if (dColor <= 0.5)
    {
        dR = 0;
        dG = 1;
        dB = 2-dColor*4;
    }
    else if (dColor <= 0.75)
    {
        dR = (dColor - 0.5) * 4;
        dG = 1;
        dB = 0;
    }
    else
    {
        dR = 1;
        dG = 4-dColor*4;
        dB = 0;
    }
    nR = dR * 255;
    nG = dG * 255;
    nB = dB * 255;
}

//绘制直方图
void DrawHistogramWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    double dW = this->width() * 0.88;
    double dH = this->height() * 0.9;

    int nCol = 6;
    if (m_nMode == 2)  //2 雅克比
        nCol = 4;

    painter.setPen(QColor(209,209,209)); 
    QTransform originalTransform = painter.transform();
    painter.translate(0.1 * dW, 0.05* dH);
    //画横线
    double dUnitHeight = dH / 4.0;
    for (int i = 0; i < 5; i++)
    {
        painter.drawLine(QPointF(0,i * dUnitHeight), QPointF(dW, i * dUnitHeight));
    }

    //画竖线
    double dUnitWidth = dW / double(nCol);
    for (int i = 0; i < nCol+1; i++)
    {
        painter.drawLine(QPointF(0 + i * dUnitWidth, 0), QPointF(0 + i * dUnitWidth, dH));
    }

    //计算值
    double dMinValue = 999999;
    double dMaxValue = 0;
    for (int i = 0; i < m_dValueList.size(); i++)
    {
        double fValue = m_dValueList[i];
        if (fValue < dMinValue)
            dMinValue = fValue;
        if (fValue > dMaxValue)
            dMaxValue = fValue;
    }

    double dUnit = (dMaxValue - dMinValue) / (double)(nCol-1);
    if (abs(dUnit) < 0.0000000001)
        dUnit = 0.000001;

    QMap<int, int> indexAndNumMap;
    for (int i = 0; i < nCol; i++)
    {
        indexAndNumMap[i] = 0;
    }

    for (int i = 0; i < m_dValueList.size(); i++)
    {
        double aspectRatio = m_dValueList[i];
        int nIndex = (aspectRatio - dMinValue) / dUnit;
        indexAndNumMap[nIndex]++;
    }

    double dUnitList[5] = {0, 0.3,0.5,0.7,1.0};
    if (m_nMode == 2)  //2 雅克比
    {
        indexAndNumMap.clear();
        for (int i = 0; i < m_dValueList.size(); i++)
        {
            double aspectRatio = m_dValueList[i];
            if (0 <= aspectRatio && aspectRatio <= 0.3)
                indexAndNumMap[0]++;
            else if (0.3 < aspectRatio && aspectRatio <= 0.5)
                indexAndNumMap[1]++;
            else if (0.5 < aspectRatio && aspectRatio <= 0.7)
                indexAndNumMap[2]++;
            else if (0.7 < aspectRatio && aspectRatio <= 1.0)
                indexAndNumMap[3]++;
        }
    }

    painter.setPen(QColor(0, 0, 0));
    int nMaxNum = 0; //最大的数量
    for (int i = 0; i < nCol; i++)
    {
        int nIndex = i;
        int nNum = indexAndNumMap[nIndex];
        if (nNum > nMaxNum)
            nMaxNum = nNum;
        QString strText = QString::number(dMinValue+(i* dUnit),'f', 2) + "-" + QString::number(dMinValue + ((i + 1) * dUnit), 'f', 2);
        if (m_nMode == 2)  //2 雅克比
            strText = QString::number(dUnitList[i], 'f', 2) + "-" + QString::number(dUnitList[i+1], 'f', 2);
        //painter.drawText(QPointF(0.5*dUnitWidth + i * dUnitWidth, dH), strText);
        QRect rect(i * dUnitWidth, dH+2, dUnitWidth, 20);
        painter.drawText(rect, Qt::AlignCenter, strText);
    }

    //竖
    nMaxNum = nMaxNum * 1.1;
    double dNumUnit = nMaxNum / 4.0;
    for (int i = 0; i < 5; i++)
    {
        //painter.drawLine(QPointF(0, i * dUnitHeight), QPointF(dW, i * dUnitHeight));
        QString strText = QString::number((4-i) * dNumUnit, 'f', 1);
        //AlignRight
        QRect rect(-0.1 * dW, i * dUnitHeight-3, 0.1 * dW, dUnitHeight * 0.2);
        painter.drawText(rect, Qt::AlignRight, strText);
    }

    //竖状图及数量说明
    double dColorUnit = 1.0 / (dMaxValue - dMinValue);
    double dHUnit = dH/(double)nMaxNum;
    
    for (int i = 0; i < nCol; i++)
    {
        int nIndex = i;
        int nNum = indexAndNumMap[nIndex];
        double dCurHeight = dHUnit * nNum;
        if (dCurHeight < 1 && nNum > 0) //高度至少给一个单位，避免显示不出来
            dCurHeight = 1;

        double dCurMin = dMinValue + (i * dUnit) - dMinValue;
        double dCurMax = dMinValue + ((i + 1) * dUnit) - dMinValue;
        if (m_nMode == 2)  //2 雅克比
        {
            dCurMin = dUnitList[i] - dMinValue;
            dCurMax = dUnitList[i + 1] - dMinValue;
        }
        double dMinColor = dCurMin * dColorUnit;
        double dMaxColor = dCurMax * dColorUnit;

        //显示中间颜色
        /*double dMidColor = (dMinColor + dMaxColor) / 2.0;
        int nR = 0, nG = 0, nB = 0;
        GetHotColor(dMidColor, nR, nG, nB);
        QColor color(nR, nG, nB);
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);*/

        QRect rectTmp(i * dUnitWidth + 0.25 * dUnitWidth, dH, 0.5 * dUnitWidth, -dCurHeight);

        //渐变颜色
        int nR1 = 0, nG1 = 0, nB1 = 0;
        int nR2 = 0, nG2 = 0, nB2 = 0;
        GetHotColor(dMinColor, nR1, nG1, nB1);
        GetHotColor(dMaxColor, nR2, nG2, nB2);
        QColor color1(nR1, nG1, nB1);
        QColor color2(nR2, nG2, nB2);
        QLinearGradient gradient(rectTmp.topLeft(), rectTmp.topRight()); // 从左到右的渐变
        gradient.setColorAt(0.0, color1);        // 起点颜色为蓝色
        gradient.setColorAt(1.0, color2);         // 终点颜色为红色
        painter.setBrush(gradient);

        painter.setPen(Qt::NoPen);
        painter.drawRect(rectTmp);

        painter.setPen(QColor(0, 0, 255));
        QString strText = QString::number(nNum);
        QRect rect(i * dUnitWidth + 0.25 * dUnitWidth, dH-(dCurHeight+ dUnitHeight*0.2), 0.5 * dUnitWidth, dUnitHeight*0.2);
        painter.drawText(rect, Qt::AlignCenter, strText);
    }
}
