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

#ifndef NctiQtAiModelAddLabelDlg_H
#define NctiQtAiModelAddLabelDlg_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include "ui_NctiAiAddLabel.h"

namespace NCTI {
    class NctiDisplayObject;
    class NctiDocument;
    
    /**
     * @brief AI模型添加标签对话框类
     * @details 用于为AI模型添加标签的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiQtAiModelAddLabelDlg : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        NctiQtAiModelAddLabelDlg(NctiDocument* i_pDocument, QWidget* i_parent);
        
        /**
         * @brief 析构函数
         */
        ~NctiQtAiModelAddLabelDlg();
        
        /**
         * @brief 获取实例
         * @return 实例指针
         */
        static NctiQtAiModelAddLabelDlg* Instance();
        
        /**
         * @brief 设置实例
         * @param pNctiQtAiModelAddLabelDlg 实例指针
         */
        static void SetInstance(NctiQtAiModelAddLabelDlg* pNctiQtAiModelAddLabelDlg);

    public Q_SLOTS:
        /**
         * @brief 显示槽函数
         */
        void show();

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
         * @brief 获取选择槽函数
         */
        void getSelection();

    private:
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

    private:
        Ui::NctiAiAddLabel* m_ui;                  ///< UI界面指针
        NctiDocument* m_Document;                  ///< 文档指针
        std::vector<NctiDisplayObject*> m_displayobj;  ///< 显示对象列表
        std::vector<NCTI_MODEL_TAG> m_cells;        ///< 单元标签列表
        bool m_selBody;                            ///< 体选择状态
        bool m_selFace;                            ///< 面选择状态
        bool m_selLine;                            ///< 线选择状态
        bool m_selMarker;                          ///< 标记选择状态
        static NctiQtAiModelAddLabelDlg* m_instance;  ///< 实例指针
    };
}

#endif // !NctiQtAiModelAddLabelDlg_H