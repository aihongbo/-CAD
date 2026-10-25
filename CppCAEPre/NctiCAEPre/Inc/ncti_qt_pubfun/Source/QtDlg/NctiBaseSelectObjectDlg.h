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

#ifndef NctiBaseSelectObjectDlg_H
#define NctiBaseSelectObjectDlg_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>

namespace NCTI {

    class NctiDisplayObject;
    class NctiDocument;
    
    /**
     * @brief 基础选择对象对话框类
     * @details 所有需要选择对象功能的对话框的基类
     */
    class DECL_NCTI_QT_PUBFUN NctiBaseSelectObjectDlg : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        NctiBaseSelectObjectDlg(NctiDocument* i_pDocument, QWidget* i_parent);
        
        /**
         * @brief 析构函数
         */
        virtual ~NctiBaseSelectObjectDlg();

        /**
         * @brief 选择模式枚举
         * @details 定义了不同的选择模式
         */
        enum SelectMode
        {
            Body = 1 << 0,    ///< 体选择模式
            Face = 1 << 1,    ///< 面选择模式
            Line = 1 << 2,    ///< 线选择模式
            Marker = 1 << 3,  ///< 标记选择模式
        };

    public Q_SLOTS:
        /**
         * @brief 显示槽函数
         */
        void show();

    private Q_SLOTS:
        /**
         * @brief 取消槽函数
         */
        void onCanle();

    protected:
        /**
         * @brief 初始化选择模式
         * @details 初始化为选择对象模式
         */
        void InitSelMode();
        
        /**
         * @brief 回滚选择模式
         * @details 设置回原来状态
         */
        void rollSelMode();
        
    protected:
        NctiDocument* m_Document;   ///< 文档指针
        Ncti_Integer m_SelMode;     ///< 选择模式
        bool m_selBody;             ///< 体选择状态
        bool m_selFace;             ///< 面选择状态
        bool m_selLine;             ///< 线选择状态
        bool m_selMarker;           ///< 标记选择状态

    };
}

#endif // !NctiBaseSelectObjectDlg_H