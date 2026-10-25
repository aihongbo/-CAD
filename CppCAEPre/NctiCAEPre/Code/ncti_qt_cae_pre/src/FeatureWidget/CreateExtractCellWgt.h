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

#ifndef CREATEEXTRACTCELLWGT_H_
#define CREATEEXTRACTCELLWGT_H_

#include <QWidget>
#include "NctiBaseDialog.h"
#include "ncti_base.h"

namespace Ui {
    class CreateExtractCellWgtContent;
}

namespace NCTI {
class NctiDisplayObject;
class NctiDocument;

/**
 * @brief 创建抽取要素窗口类
 * @details 用于从模型中抽取特定类型要素（点、边、面）的对话框窗口
 */
class CreateExtractCellWgt : public NctiBaseDialog
{
    Q_OBJECT

public:
    /**
     * @brief 抽取类型枚举
     */
    enum class ExtType { 
        Unknow,  ///< 未知类型
        Face,    ///< 面
        Edge,    ///< 边
        Point    ///< 点
    };

    /**
     * @brief 构造函数
     * @param i_pDocument 文档指针
     * @param parent 父窗口指针
     */
    explicit CreateExtractCellWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~CreateExtractCellWgt();
    
    /**
     * @brief 显示窗口
     */
    void show();

private:
    /**
     * @brief 初始化UI界面
     */
    void initUI();
    
    /**
     * @brief 获取当前选择类型
     * @return 抽取类型
     */
    ExtType getCurrSelType();
    
    /**
     * @brief 获取抽取类型ID
     * @param cellIds cellID列表
     * @param type 抽取类型
     */
    void getExtTypeId(std::vector<Ncti_Long>& cellIds, ExtType type);

private Q_SLOTS:
    /**
     * @brief 取消按钮槽函数
     */
    void onCanle();
    
    /**
     * @brief 抽取按钮槽函数
     */
    void onExtract();
    
    /**
     * @brief 选择按钮槽函数
     */
    void onSelected();
    
    /**
     * @brief 单选按钮切换槽函数
     */
    void onRadioButtonToggled();

private:
    NctiDocument* m_Document;                     ///< 文档指针
    Ui::CreateExtractCellWgtContent* ui;          ///< UI界面指针
    std::vector<NctiDisplayObject*> m_SelObjVec; ///< 选择的对象列表
    std::vector<NCTI_MODEL_TAG> m_cells;         ///< 单元列表
};
}
#endif