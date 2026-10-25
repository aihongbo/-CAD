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
#include "UIOptionItemModel.h"

#include <QMimeData>
#include <QList>

namespace NCTI {

/**
 * @brief UI选项MIME数据类
 * @details 继承自QMimeData，用于处理UI选项的拖放操作数据
 */
class NCTI_UIOPTION UIOptionMimeData : public QMimeData
{
    Q_OBJECT
public:
    /**
     * @brief 项列表类型定义
     */
    using ItemList = QList<UIOptionItem*>;
    
    /**
     * @brief 构造函数
     * @param itemList 项列表
     */
    UIOptionMimeData(ItemList itemList);
    
    /**
     * @brief 获取MIME类型
     * @return MIME类型字符串
     */
    static QString mimeType();
    
    /**
     * @brief 获取项列表
     * @return 项列表的常量引用
     */
    ItemList const& itemList() const noexcept { return mItemList; }

private:
    ItemList mItemList; ///< 项列表
};
} // namespace NCTI