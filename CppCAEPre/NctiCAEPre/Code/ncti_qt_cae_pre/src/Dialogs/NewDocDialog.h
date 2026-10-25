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

#include "NctiBaseDialog.h"

#include <QComboBox>

namespace Ui {
class NewDocDialogContent;
}

namespace NCTI {
/**
 * @brief 新建文档对话框类
 * @details 用于创建新文档时选择几何内核和约束条件的对话框
 */
class NewDocDialog : public NctiBaseDialog
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit NewDocDialog(QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~NewDocDialog();

    /**
     * @brief 初始化界面
     */
    void init();

    /**
     * @brief 获取几何内核索引
     * @return 几何内核索引
     */
    int GetGeoKernelIndex();

    /**
     * @brief 获取几何约束索引
     * @return 几何约束索引
     */
    int GetGeoConstraintIndex();

    /**
     * @brief 获取文档信息
     * @return 包含模型、DCM、网格信息的元组
     *         - 0: 模型信息
     *         - 1: DCM信息
     *         - 2: 网格信息
     */
    std::tuple<int, int, int> GetInfo() const;

private:
    Ui::NewDocDialogContent* ui; ///< UI界面指针

    QComboBox* geoKernelComboBox;     ///< 几何内核下拉框
    QComboBox* geoConstraintComboBox; ///< 几何约束下拉框
};
} // namespace NCTI