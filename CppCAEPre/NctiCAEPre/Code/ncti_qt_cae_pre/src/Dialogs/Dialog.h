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

#ifndef DIALOG_H
#define DIALOG_H

#include "NctiBaseDialog.h"

#include <QMap>
#include <QFrame>

namespace NCTI {
class Dialog;

/**
 * @brief 对话框委托类
 * @details 用于处理对话框设置UI后的回调操作
 */
class DialogDelegate
{
public:
    /**
     * @brief 构造函数
     */
    DialogDelegate() {}

    /**
     * @brief 析构函数
     */
    virtual ~DialogDelegate() {}

    /**
     * @brief 对话框设置UI后回调函数
     * @param name UI名称
     * @param ui UI指针
     * @param widget 控件指针
     */
    virtual void dialogAfterSetupUi(const QString& name, void* ui, QWidget* widget) = 0;
};

/**
 * @brief 对话框基类
 * @details 提供通用对话框功能的基类，支持动态添加UI和控件
 */
class Dialog : public NctiBaseDialog
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit Dialog(QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    virtual ~Dialog();

    /**
     * @brief 添加默认图片和标签
     */
    void addDefaultImageAndLabel();

    /**
     * @brief 添加默认标签
     */
    void addDefaultLabel();

    /**
     * @brief 获取默认标签
     * @return 默认标签指针
     */
    QLabel* getDefaultLabel();

    /**
     * @brief 添加默认取消和确认按钮
     * @param cancel 取消按钮文本
     * @param ok 确认按钮文本
     */
    void addDefaultCancelAndConfire(const QString& cancel = QStringLiteral("取消"),
                                    const QString& ok     = QStringLiteral("确定"));

    /**
     * @brief 添加默认确认按钮
     * @param ok 确认按钮文本
     */
    void addDefaultConfire(const QString& ok = QStringLiteral("确定"));

    /**
     * @brief 通过UI添加控件
     * @tparam UI_T UI类型
     * @tparam UI_BASE_T UI基类类型
     * @param name 控件名称
     * @param[out] oui UI指针
     * @param[out] owidget 控件指针
     * @param index 插入位置索引
     * @return 添加成功返回true，否则返回false
     */
    template <typename UI_T, typename UI_BASE_T>
    bool addByUi(const QString& name, UI_T** oui = nullptr, QWidget** owidget = nullptr, int index = -1)
    {
        if (contains(name)) {
            return false;
        }

        UI_T* ui = new UI_T;
        if (!addByUi<UI_T, UI_BASE_T>(name, ui, owidget, index)) {
            delete ui;
            return false;
        }

        *oui = ui;
        return true;
    }

    /**
     * @brief 通过UI添加控件
     * @tparam UI_T UI类型
     * @tparam UI_BASE_T UI基类类型
     * @param name 控件名称
     * @param ui UI指针
     * @param[out] owidget 控件指针
     * @param index 插入位置索引
     * @return 添加成功返回true，否则返回false
     */
    template <typename UI_T, typename UI_BASE_T>
    bool addByUi(const QString& name, UI_T* ui, QWidget** owidget = nullptr, int index = -1)
    {
        if (contains(name)) {
            return false;
        }

        addUi(name, ui);

        UI_BASE_T* widget = new UI_BASE_T(m_content);
        ui->setupUi(widget);
        addWidget(name, widget);

        if (m_delegate) {
            m_delegate->dialogAfterSetupUi(name, ui, widget);
        }
        else if (m_afterSetupUiBlock) {
            m_afterSetupUiBlock(name, ui, widget);
        }
        else {
            afterSetupUi(name, ui, widget);
        }

        if (owidget != nullptr)
            *owidget = widget;
        return true;
    }

    /**
     * @brief 通过控件添加UI
     * @param name 控件名称
     * @param ui UI指针
     * @param widget 控件指针
     * @return 添加成功返回true，否则返回false
     */
    bool addByWidget(const QString& name, void* ui, QWidget* widget);

    /**
     * @brief 通过控件添加
     * @param name 控件名称
     * @param widget 控件指针
     * @return 添加成功返回true，否则返回false
     */
    bool addByWidget(const QString& name, QWidget* widget);

    /**
     * @brief 获取UI指针
     * @param name UI名称
     * @return UI指针
     */
    void* getUi(const QString& name);

    /**
     * @brief 获取控件指针
     * @param name 控件名称
     * @return 控件指针
     */
    QWidget* getWidget(const QString& name);

    /**
     * @brief 设置委托
     * @param delegate 委托指针
     */
    void setDelegate(DialogDelegate* delegate);

    /**
     * @brief 设置UI设置后回调函数
     * @param block 回调函数
     */
    void setAfterSetupUiBlock(std::function<void(const QString&, void*, QWidget*)> block);

    /**
     * @brief 接受对话框槽函数
     */
    virtual Q_SLOT void accept();

protected:
    /**
     * @brief UI设置后处理函数
     * @param name UI名称
     * @param ui UI指针
     * @param widget 控件指针
     */
    virtual void afterSetupUi(const QString& name, void* ui, QWidget* widget);

    /**
     * @brief 接受前处理函数
     * @return 处理成功返回true，否则返回false
     */
    virtual bool beforeAccpet();

private:
    /**
     * @brief 添加UI
     * @param name UI名称
     * @param ui UI指针
     * @return 添加成功返回true，否则返回false
     */
    bool addUi(const QString& name, void* ui);

    /**
     * @brief 添加控件
     * @param name 控件名称
     * @param widget 控件指针
     * @param index 插入位置索引
     * @return 添加成功返回true，否则返回false
     */
    bool addWidget(const QString& name, QWidget* widget, int index = -1);

    /**
     * @brief 移除控件
     * @param name 控件名称
     */
    void remove(const QString& name);

    /**
     * @brief 移除UI
     * @param name UI名称
     */
    void removeUi(const QString& name);

    /**
     * @brief 移除控件
     * @param name 控件名称
     */
    void removeWidget(const QString& name);

    /**
     * @brief 检查是否包含指定名称的控件
     * @param name 控件名称
     * @return 包含返回true，否则返回false
     */
    bool contains(const QString& name);

private:
    QFrame* m_content;            ///< 内容框架
    QVBoxLayout* m_contentLayout; ///< 内容布局

    QMap<QString, void*> m_name2Ui;        ///< 名称到UI指针的映射
    QMap<QString, QWidget*> m_name2Widget; ///< 名称到控件指针的映射

    DialogDelegate* m_delegate;                                               ///< 委托指针
    std::function<void(const QString&, void*, QWidget*)> m_afterSetupUiBlock; ///< UI设置后回调函数
};
}; // namespace NCTI

#endif // DIALOG_H