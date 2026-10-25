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

#ifndef NctiMeshQualityDlg_H
#define NctiMeshQualityDlg_H
#include <QtWidgets>
#include <QDialog>
#include <QPaintEvent>
#include "ui_NctiMeshQualityDlg.h"
#include <string>

/**
 * @brief 绘制直方图控件类
 * @details 用于绘制网格质量直方图的自定义控件
 */
class DrawHistogramWidget : public QWidget {
public:
    /**
     * @brief 构造函数
     * @param nMode 模式
     * @param dValueList 值列表
     * @param parent 父窗口指针
     */
    DrawHistogramWidget(int nMode, const std::vector<double>& dValueList, QWidget* parent = nullptr);

private:
    int m_nMode;                           ///< 模式 0长宽比 1扭曲度 2雅克比 3最小角度 4最大角度
    std::vector<double> m_dValueList;      ///< 值列表
    
    /**
     * @brief 获取热点颜色
     * @param dColor 颜色值
     * @param nR 红色分量
     * @param nG 绿色分量
     * @param nB 蓝色分量
     */
    void GetHotColor(double dColor, int& nR, int& nG, int& nB);
    
protected:
    /**
     * @brief 绘制事件处理
     * @param event 绘制事件指针
     */
    void paintEvent(QPaintEvent* event) override;
};

//using MeshDialogCallback = std::function<void()>;

/**
 * @brief 网格质量对话框类
 * @details 用于显示和分析网格质量的对话框
 */
class NctiMeshQualityDlg : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param nMode 模式
     * @param sTextList 文本列表
     * @param dValueList 值列表
     * @param parent 父窗口指针
     */
    NctiMeshQualityDlg(int nMode, std::vector<std::string> sTextList, const std::vector<double>& dValueList,QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~NctiMeshQualityDlg();

    /**
     * @brief 初始化对话框
     */
    void init();
    
    /**
     * @brief 设置回调函数
     * @param func 回调函数
     */
    void setCallBack(std::function<void()> func);
    
protected:
    /**
     * @brief 关闭事件处理
     * @param event 关闭事件指针
     */
    void closeEvent(QCloseEvent* event) override;
    
private:
    QStringListModel* m_model;                    ///< 字符串列表模型指针

    int m_nMode;                                  ///< 模式 0长宽比 1扭曲度 2雅克比 3最小角度 4最大角度
    std::vector<std::string> m_sTextList;         ///< 文本列表
    std::vector<double> m_dValueList;             ///< 值列表
    std::function<void()> m_restorColor_callback;  ///< 恢复颜色回调函数
    
private:
    Ui::NctiMeshQualityDlg ui;                     ///< UI界面
};
#endif // !NctiMeshQualityDlg_H