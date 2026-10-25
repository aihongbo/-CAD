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

#ifndef CREATEBOOLEANWGT_H_
#define CREATEBOOLEANWGT_H_

#include <QWidget>
#include "NctiBaseDialog.h"
#include "ncti_base.h"

namespace Ui {
    class CreateBooleanWgtContent;
}

namespace NCTI {
class NctiDocument;
class NctiDisplayObject;

/**
 * @brief 创建布尔运算窗口类
 * @details 用于执行模型间的布尔运算操作（并集、差集、交集）的对话框窗口
 */
class CreateBooleanWgt : public NctiBaseDialog
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param i_pDocument 文档指针
     * @param parent 父窗口指针
     */
    explicit CreateBooleanWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~CreateBooleanWgt();

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
     * @brief 取消按钮槽函数
     */
    void onCanle();
    
    /**
     * @brief 选择第一个对象槽函数
     */
    void onSelect1();
    
    /**
     * @brief 选择第二个对象槽函数
     */
    void onSelect2();
    
    /**
     * @brief 预览按钮槽函数
     */
    void onPreview();

private:
    Ui::CreateBooleanWgtContent* ui;      ///< UI界面指针
    NctiDocument* m_Document;             ///< 文档指针
    NctiDisplayObject* m_DisplayObject1;  ///< 第一个显示对象
    NctiDisplayObject* m_DisplayObject2;  ///< 第二个显示对象
    //0:unit 并集
    //1:cut 差集
    //2:common 交集
    //Ncti_Integer m_DlgType;
};
}
#endif