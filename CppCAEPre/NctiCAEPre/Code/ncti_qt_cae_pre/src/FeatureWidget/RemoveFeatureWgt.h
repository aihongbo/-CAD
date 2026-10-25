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

#ifndef REMOVEFEATUREWGT_H_
#define REMOVEFEATUREWGT_H_

#include <QWidget>
#include "NctiBaseDialog.h"
#include "SelectModeRoller.h"

#include "ncti_base.h"

namespace Ui {
    class RemoveFeatureWgtContent;
}

namespace NCTI {
class NctiDisplayObject;
class NctiDocument;

/**
 * @brief 移除特征窗口类
 * @details 用于移除模型特征、面或分离面的对话框窗口
 */
class RemoveFeatureWgt : public NctiBaseDialog
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param i_pDocument 文档指针
     * @param mode 选择模式
     * @param removeFeature 移除特征类型（0:移除特征 1:移除面 2:分离面）
     * @param parent 父窗口指针
     */
    explicit RemoveFeatureWgt(NctiDocument* i_pDocument, int mode, int removeFeature, QWidget* parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~RemoveFeatureWgt();
    
    /**
     * @brief 显示窗口
     */
    void show();

private:
    /**
     * @brief 初始化UI界面
     */
    void initUI();

private Q_SLOTS:
    /**
     * @brief 确定按钮槽函数
     */
    void onOK();
    
    /**
     * @brief 取消按钮槽函数
     */
    void onCanle();
    
    /**
     * @brief 获取选择槽函数
     */
    void GetSelection();

private:
    Ui::RemoveFeatureWgtContent* ui;              ///< UI界面指针
    std::vector<NctiDisplayObject*> m_displayobj; ///< 显示对象列表
    std::vector<NCTI_MODEL_TAG> m_cells;          ///< 单元列表
    int m_iRemoveFeature;                         ///< 移除特征类型（0:移除特征 1:移除面 2:分离面）  
	SelectModeRoller* m_selectModeRoller;         ///< 选择模式管理器
    NctiDocument* m_doc;                          ///< 文档指针
};
}
#endif