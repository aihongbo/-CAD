/*
 * Copyright (c) 2026 粤港澳大湾区（广东）国创中心
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

#ifndef NctiDCM3TwoGeometriesWidget_H
#define NctiDCM3TwoGeometriesWidget_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include "NctiDCM3SingleGeometryWidget.h"
#include <QWidget>

class QLabel;
class QComboBox;
class QLineEdit;
namespace NCTI {
    class NctiDisplayModelBody;
    /**
     * @brief 添加材料对话框类
     * @details 用于添加材料属性的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiDCM3TwoGeometriesWidget : public NctiDCM3SingleGeometryWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        NctiDCM3TwoGeometriesWidget(NctiDocument* i_pDoc, int i_dimType, NctiMode i_mode, const char* i_DimObjName = nullptr, QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiDCM3TwoGeometriesWidget();

        void setSelLabelTexts(const QString& i_text1, const QString& i_text2);

        virtual void execute() override;
    private:
        void init();
        void setSelectedText();

    private Q_SLOTS:
        void selBodyCellClick(bool boo);

    private:
        QString m_selLabelText2;
    protected:
        NctiDisplayModelBody* m_pSelBody2;
        Ncti_Long* m_selCellID2;

        QLabel* m_selLabel2;
        QComboBox* m_alignBox;
        QLineEdit* m_valueEidt;
    };
}

#endif // !NctiDCM3TwoGeometriesWidget_H