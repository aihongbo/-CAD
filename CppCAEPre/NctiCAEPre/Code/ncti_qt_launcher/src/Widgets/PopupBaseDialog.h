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

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "NctiQtCommon.h"

namespace NCTI {

    /**
     * @brief 弹出基础对话框类
     * @details 所有弹出对话框的基类，提供统一的样式和功能
     */
    class PopupBaseDialog : public QDialog 
    {
        Q_OBJECT
        NCTI_QT_PUBFUNC_DECLARE_PRIVATE(PopupBaseDialog)
    public:
        /**
         * @brief 构造函数
         * @param parent 父窗口指针
         * @param isFeatureWgt 是否为特征控件
         * @param titleBarHeight 标题栏高度
         * @param bResizable 是否可调整大小
         */
        explicit PopupBaseDialog(QWidget* parent = nullptr, bool isFeatureWgt = false, int titleBarHeight = 24, bool bResizable = false);
        
        /**
         * @brief 析构函数
         */
        ~PopupBaseDialog();

        /**
         * @brief 获取标题栏
         * @return 标题栏控件指针
         */
        QWidget* getTitleBar();
        
        /**
         * @brief 获取标题标签
         * @return 标题标签指针
         */
        QLabel* getTitleLabel();

        /**
         * @brief 显示/隐藏关闭按钮
         * @param bVisible 是否可见
         */
        void showCloseButton(bool bVisible);
        
        /**
         * @brief 设置标题
         * @param title 标题文本
         */
        void setTitle(const QString& title);
        
        /**
         * @brief 设置大小
         * @param size 大小
         */
        void setSize(const QSize& size);
        
        /**
         * @brief 设置控件
         * @param widget 控件指针
         */
        void setWidget(QWidget* widget);
        
        /**
         * @brief 拒绝操作
         */
        void reject() override;
        
    protected:
        /**
         * @brief 获取标题栏高度
         * @return 标题栏高度
         */
        int titleBarHeight();
        
    Q_SIGNALS:
        /**
         * @brief 关闭信号
         */
        void sigClose();
        
        /**
         * @brief 确认信号
         */
        void sigConfrim();
        
        /**
         * @brief 取消信号
         */
        void sigCancle();

    private:
        Q_DISABLE_COPY(PopupBaseDialog)
    };

}