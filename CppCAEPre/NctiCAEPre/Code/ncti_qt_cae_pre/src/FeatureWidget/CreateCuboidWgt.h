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

#ifndef CREATECUBOIDWGT_H_
#define CREATECUBOIDWGT_H_

#include <QWidget>
#include "NctiBaseDialog.h"
#include "ncti_base.h"

namespace Ui {
    class CreateCuboidWgtContent;
}

namespace NCTI {
class NctiDocument;
class NctiDisplayObject;
class NctiPosition;

/**
 * @brief 创建长方体窗口类
 * @details 用于创建和设置长方体参数的对话框窗口
 */
class CreateCuboidWgt : public NctiBaseDialog
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param i_pDocument 文档指针
     * @param parent 父窗口指针
     */
    explicit CreateCuboidWgt(NctiDocument* i_pDocument, QWidget* parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~CreateCuboidWgt();
    
    /**
     * @brief 设置位置
     * @param pt 位置坐标
     */
    void SetPosition(NctiPosition pt);
    
    /**
     * @brief 获取实例
     * @return 实例指针
     */
    static CreateCuboidWgt* instance();
    
    /**
     * @brief 设置实例
     * @param pDlg 窗口实例指针
     */
    static void SetInstance(CreateCuboidWgt* pDlg);
    
    /**
     * @brief 获取位置回调函数
     * @param pt 位置坐标
     */
    static void GetPositionFun(NctiPosition pt);

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
     * @brief 文本改变槽函数
     * @param text 文本内容
     */
    void onTextChanged(const QString& text);

    /**
     * @brief 预览按钮槽函数
     */
    void onPreview();

private:
    Ui::CreateCuboidWgtContent* ui;              ///< UI界面指针
    NctiDocument* m_Document;                    ///< 文档指针
    std::vector<NCTI_MODEL_TAG> m_SelectCells;   ///< 选择的单元列表
    std::vector<NctiDisplayObject*> m_SelObjVec; ///< 选择的对象列表
    static CreateCuboidWgt* m_Instance;          ///< 单例实例指针
};
}
#endif