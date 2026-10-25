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

#ifndef CREATEFILLETWGT_H_
#define CREATEFILLETWGT_H_

#include <QWidget>
#include "NctiBaseDialog.h"
#include "ncti_base.h"

namespace Ui {
    class CreateFilletWgtContent;
}

namespace NCTI {
class NctiDocument;
class NctiDisplayObject;
class NctiWindowPlatform;

/**
 * @brief 创建圆角窗口类
 * @details 用于创建和设置模型圆角参数的对话框窗口
 */
class CreateFilletWgt : public NctiBaseDialog
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param i_pDocument 文档指针
     * @param parent 父窗口指针
     */
    explicit CreateFilletWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~CreateFilletWgt();

private:
    /**
     * @brief 初始化UI界面
     */
    void initUI();
    
    /**
     * @brief 更新视图
     */
    void UpdateView();

private Q_SLOTS:
    /**
     * @brief 确定按钮槽函数
     */
    void onOk();
    
    /**
     * @brief 选择边槽函数
     */
    void onSelEdge();
    
    /**
     * @brief 取消按钮槽函数
     */
    void onCanle();
    
    /**
     * @brief 预览按钮槽函数
     */
    void onPreview();

private:
    Ui::CreateFilletWgtContent* ui;              ///< UI界面指针
    NctiDocument* m_Document;                    ///< 文档指针
    std::vector<NCTI_MODEL_TAG> m_SelectCells;   ///< 选择的单元列表
    std::vector<NctiDisplayObject*> m_SelObjVec; ///< 选择的对象列表
};
}
#endif