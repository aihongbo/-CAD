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

#include <QDialog>
#include "UIOption.h"

class QSplitter;
class QLabel;
class QLineEdit;
class QToolButton;
class QPushButton;

namespace NCTI {
    
// 前向声明
class UIOptionTree;
class UIOptionItem;

/**
 * @brief UI选项对话框类
 * @details 继承自QDialog，用于配置和管理UI选项
 */
class NCTI_UIOPTION UIOptionDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit UIOptionDialog(QWidget* parent = nullptr);

private:
    /**
     * @brief 设置UI界面
     */
    void setupUi();
    
    /**
     * @brief 设置左侧控件
     * @param splitter 分割器指针
     * @return 控件指针
     */
    QWidget* setupLeftWidget(QSplitter* splitter);
    
    /**
     * @brief 设置右侧控件
     * @param splitter 分割器指针
     * @return 控件指针
     */
    QWidget* setupRightWidget(QSplitter* splitter);
    
    /**
     * @brief 初始化连接
     */
    void initConnections();
    
    /**
     * @brief 加载系统树数据
     */
    void loadSystemTreeData();
    
    /**
     * @brief 加载自定义树数据
     */
    void loadCustomTreeData();
    
private Q_SLOTS:
    /**
     * @brief 恢复默认设置
     */
    void onRestore();
    
    /**
     * @brief 更新设置
     */
    void onUpdate();
    
    /**
     * @brief 更改Logo
     */
    void onChangeLogo();

private:
    QLabel* mSystemTitle{nullptr};          ///< 系统标题标签
    QLabel* mCustomTitle{nullptr};          ///< 自定义标题标签
    QLabel* mAppLogo{nullptr};              ///< 应用Logo标签
    QLabel* mAppTitle{nullptr};             ///< 应用标题标签
    QToolButton* mAppLogoBtn{nullptr};      ///< 应用Logo按钮
    QLineEdit* mAppTitleEdit{nullptr};      ///< 应用标题编辑框
    QSplitter* mSplitter{nullptr};          ///< 分割器
    QPushButton* mRestoreBtn{nullptr};      ///< 恢复按钮
    QPushButton* mUpdateBtn{nullptr};       ///< 更新按钮
    QLineEdit* mSearchEdit{nullptr};        ///< 搜索编辑框
    UIOptionTree* mSystemTree{nullptr};     ///< 系统树
    UIOptionTree* mCustomTree{nullptr};     ///< 自定义树
    QString mAppLogoPath;                   ///< 应用Logo路径
};
} // namespace NCTI