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

#ifndef NCTIQTAIEXTRUSIONIDENTIFIERDLG_H
#define NCTIQTAIEXTRUSIONIDENTIFIERDLG_H

#include "dcl_ncti_qt_pubfun.h"
#include "ui_NctiExtrusionIdentifier.h"
#include "ncti_base.h"
#include "NctiBaseUtility.h"

#include <QWidget>

namespace NCTI
{
    class NctiDocument;
    class NctiWindowPlatform;

    /**
     * @brief AI拉伸标识对话框类
     * @details 用于AI拉伸特征标识的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiQtAiExtrusionIdentifierDlg : public QWidget
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         * @param i_pPlatform 平台指针
         */
        explicit NctiQtAiExtrusionIdentifierDlg(NctiDocument* i_pDocument, QWidget* i_parent, NctiWindowPlatform* i_pPlatform);
        
        /**
         * @brief 析构函数
         */
        ~NctiQtAiExtrusionIdentifierDlg();
        
        /**
         * @brief 获取实例
         * @return 实例指针
         */
        static NctiQtAiExtrusionIdentifierDlg* Instance();
        
        /**
         * @brief 设置实例
         * @param pNctiQtAiExtrusionIdentifierDlg 实例指针
         */
        static void SetInstance(NctiQtAiExtrusionIdentifierDlg* pNctiQtAiExtrusionIdentifierDlg);

    private Q_SLOTS:
        /**
         * @brief 拉伸面按钮点击槽函数
         */
        void onExtrusionFaceButtonClick();

    private:
        /**
         * @brief 初始化对话框
         */
        void Init();
        
        /**
         * @brief 重置选择模式
         */
        void ResetSelectedMode();

        NctiDocument* m_pDocument{};                              ///< 文档指针
        Ui::NctiExtrusionIdentifierDlg* m_ui{};                   ///< UI界面指针
        NctiWindowPlatform* m_pPlatform{};                        ///< 平台指针
        std::vector<Ncti_Size> ids;                               ///< ID列表
        static NctiQtAiExtrusionIdentifierDlg* m_instance;        ///< 实例指针
    };
}

#endif //NCTIQTAIEXTRUSIONIDENTIFIERDLG_H