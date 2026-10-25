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

#ifndef NCTIMESSAGEBOX_H_
#define NCTIMESSAGEBOX_H_

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class SAFramelessHelper;

namespace NCTI {

#define MESSAGEBOX_INSTANCE NctiMessageBox::Instance()

/**
 * @brief 消息框类
 * @details 用于显示提示信息的自定义消息框对话框
 */
class NctiMessageBox :public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief 获取单例实例
     * @return 消息框实例指针
     */
    static NctiMessageBox* Instance();
    
    /**
     * @brief 显示消息框
     * @param text 消息文本
     * @param title 标题文本
     * @param bCanelBtnVisible 取消按钮是否可见
     */
    void showMessageBox(const QString& text, const QString& title = QStringLiteral("提示"), bool bCanelBtnVisible = false);

protected:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit NctiMessageBox(QWidget* parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~NctiMessageBox();

private:
    /**
     * @brief 初始化UI界面
     */
    void initUI();

private Q_SLOTS:
    /**
     * @brief 关闭按钮槽函数
     */
    void onClose();

private:
    QLabel* m_pTextLabel;                ///< 文本标签
    QLabel* m_pTitleLabel;               ///< 标题标签
    QPushButton* m_pCancelBtn;           ///< 取消按钮
    QPushButton* m_pConfrimBtn;          ///< 确认按钮
    QHBoxLayout* m_pBtnHBoxLayout;       ///< 按钮布局
    SAFramelessHelper* mFramelessHelper; ///< 无边框助手
};
}
#endif