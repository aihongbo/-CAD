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
#include "dcl_ncti_uioption.h"

#include "NctiBaseDialog.h"

namespace Ui {
class AddUIActionDialog;
}

#include <QListView>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

namespace NCTI {
    
/**
 * @brief UI动作数据结构体
 * @details 存储UI动作的各种属性数据
 */
struct UIActionData
{
    QString iconPath;   ///< 图标路径
    QString actionName; ///< 动作名称
    QString slotName;   ///< 槽函数名称
    QString pyScript;   ///< Python脚本
};

/**
 * @brief 添加UI动作对话框类
 */
class NCTI_UIOPTION AddUIActionDialog : public NctiBaseDialog
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     * @param title 标题
     * @param actionName 动作名称
     */
    explicit AddUIActionDialog(QWidget* parent, const QString& title, const QString& actionName = "");
    
    /**
     * @brief 析构函数
     */
    ~AddUIActionDialog();
    
    /**
     * @brief 设置UI界面
     */
    void setupUi();
    
    /**
     * @brief 获取状态
     * @return 状态值
     */
    int GetStatus() const;
    
    /**
     * @brief 获取数据
     * @return UIActionData结构体
     */
    UIActionData getData() const;
    
    /**
     * @brief 设置数据
     * @param data UIActionData结构体
     */
    void setData(const UIActionData& data);

protected:
    /**
     * @brief 取消保存处理
     */
    void onNoSave();
    
    /**
     * @brief 保存处理
     */
    void onSave();
    
    /**
     * @brief 检查编辑框是否为空
     * @param edit 编辑框指针
     * @param tip 提示文本
     * @return true表示为空，false表示不为空
     */
    bool checkEditEmpty(QLineEdit* edit, const QString& tip);

private:
    /**
     * @brief 保存状态枚举
     */
    enum SaveStatus { 
        Cancel, ///< 取消
        Save    ///< 保存
    };
    
    Ui::AddUIActionDialog* ui;          ///< UI界面指针
    UIActionData mUIActionData;         ///< UI动作数据
    SaveStatus mSaveStatus{SaveStatus::Cancel}; ///< 保存状态
    QString mOriginActionName;          ///< 原始动作名称
    bool mEditMode{false};              ///< 编辑模式
};
} // namespace NCTI