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

#ifndef NCTI_OBJECT_PTOPERTY_H
#define NCTI_OBJECT_PTOPERTY_H

#include "dcl_ncti_qt_pubfun.h"
#include <QFrame>
#include <QSharedPointer>
#include <QScopedPointer>

class QPushButton;
class QtTreePropertyBrowser;
class QtVariantPropertyManager;
class QtProperty;

namespace NCTI
{
    enum class NctiTreeViewType;
    
    /**
     * @brief 对象属性类
     * @details 用于显示和编辑对象属性的界面控件，基于QtPropertyBrowser实现
     */
    class DECL_NCTI_QT_PUBFUN NctiObjectProperty : public QFrame
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param p_parent 父窗口指针
         */
        NctiObjectProperty(QWidget *p_parent = nullptr);
        
        /**
         * @brief 设置模型对象
         * @param pObj 对象指针
         * @param viewType 树视图类型
         */
        void SetModelObject(void* pObj, const NctiTreeViewType& viewType);

    private:
        /**
         * @brief 参数JSON处理
         * @param groupItem 分组项指针
         * @param jsonVal JSON值引用
         */
        void ParameterJson(QtProperty* groupItem, QJsonValue& jsonVal);
        
        /**
         * @brief 设置界面
         */
        void setupUI();
        
        QtTreePropertyBrowser* m_PropertyBrowser = nullptr;      ///< 属性浏览器指针
        QtVariantPropertyManager* m_PropertyManager = nullptr;   ///< 属性管理器指针
    };
}

#endif // NCTI_OBJECT_PTOPERTY_H