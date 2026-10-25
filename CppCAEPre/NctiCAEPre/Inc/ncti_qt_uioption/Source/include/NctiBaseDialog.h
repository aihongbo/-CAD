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

#ifndef NCTI_BASE_DIALOG_H
#define NCTI_BASE_DIALOG_H

#include "dcl_ncti_uioption.h"

#include <QObject>
#include <QDialog>

class QWidget;
class QVBoxLayout;
class QLabel;

namespace NCTI {
    struct NCTI_UIOPTION TitleBarHeight {
        int value;
        constexpr explicit TitleBarHeight(int v) : value(v) {}
    };


    class NCTI_UIOPTION NctiBaseDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit NctiBaseDialog(QWidget* parent = nullptr, TitleBarHeight height = TitleBarHeight{ 24 }, bool bResizable = false);
        ~NctiBaseDialog();

        /**
         * @brief 获取标题栏
         */
        QWidget* getTitleBar();
        
        /**
         * @brief 获取标题标签
         */
        QLabel* getTitleLabel();

        /**
         * @brief 显示/隐藏关闭按钮
         */
        void showCloseButton(bool bVisible);
        
        /**
         * @brief 设置标题
         * @param title 标题文本
         * @param height 高度
         * @param margins 边距
         */
        void setTitle(const QString& title, int height = 32, const QMargins& margins = QMargins({ 23,0,17,0 }));
        
        /**
         * @brief 设置大小
         */
        void setSize(const QSize& size);
        
        /**
         * @brief 设置控件
         */
        void setWidget(QWidget* widget);
        
        /**
         * @brief 拒绝操作
         */
        void reject() override;

        /**
         * @brief 获取布局
         */
        QVBoxLayout* getLayout();

        /**
         * @brief 获取关闭按钮
         */
        QPushButton* getCloseButton() const;

         /**
         * @brief 设置样式表
         */
        void setBaseStyleSheet(const QString& styleSheet);
      
    protected:
        /**
         * @brief 获取标题栏高度
         */
        int titleBarHeight();
        
    Q_SIGNALS:
        /**
         * @brief 关闭信号
         */
        void sigClose();

        /**
         * @brief 完成信号
         */
        void finish();

    private:
        class PrivateData;
        friend class NctiBaseDialog::PrivateData;
        std::unique_ptr<PrivateData> d_ptr;

        Q_DISABLE_COPY(NctiBaseDialog)
    };
}

#endif // !NCTI_BASE_DIALOG_H
