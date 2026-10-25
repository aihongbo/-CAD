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

#ifndef NctiDCM3SingleGeometryWidget_H
#define NctiDCM3SingleGeometryWidget_H

#include "ncti_base.h"
#include "dcl_ncti_qt_pubfun.h"
#include "NctiDCM3BaseWidget.h"
#include "NctiDCM3Def.h"
#include <QWidget>

class QVBoxLayout;
class QLabel;
namespace NCTI {
    class NctiDisplayModelBody;
    class NctiDocument;
    class NctiDisplayDCM3DimSys;
    class NctiDisplayDCM3Dimension;
    class NctiDisplayDCM3Geometry;
    class NctiDCM3Set;

    /**
     * @brief 添加装配约束对话框类
     * @details 用于添加装配约束的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiDCM3SingleGeometryWidget : public NctiDCM3BaseWidget
    {
        Q_OBJECT
    public:

        enum NctiMode
        {
            NCTI_MODE_NEW,
            NCTI_MODE_EDIT,
            NCTI_MODE_READ
        };
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        NctiDCM3SingleGeometryWidget(NctiDocument* i_pDoc, int i_dimType, NctiMode i_mode, const char* i_DimObjName = nullptr, QWidget* i_parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiDCM3SingleGeometryWidget();

        void setSelLabelText(const QString& i_text);

        virtual void execute() override;
    public:
         static bool GetOrCreateDimSys(NctiDocument* i_pDoc, NctiDisplayDCM3DimSys*& o_pDimSys);
         static bool GetOrCreateSet(NctiDocument* i_pDoc, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayModelBody* pBody, NctiDCM3Set*& o_pSet);
         static bool GetOrCreateGeometry(NctiDocument* i_pDoc, NctiDisplayDCM3DimSys* i_pDimSys, NctiDCM3Set* i_pSet, Ncti_Long i_CellID, NctiDisplayDCM3Geometry*& o_pGeom);
         static bool GetDimension(NctiDocument* i_pDoc, NctiDisplayDCM3Geometry* i_pGeom1, NctiDisplayDCM3Geometry* i_pGeom2, NctiDisplayDCM3Geometry* i_pGeom3, ncti_DCM3_d_type i_dt, NctiDisplayDCM3Dimension*& o_pDim);
    private:
        void init();

        void setSelectedText();

    private Q_SLOTS:
        void selBodyCellClick(bool boo);

    private:
        QString m_selLabelText;
    protected:
        std::string m_DimObjName;
        NctiMode m_mode;

        NctiDisplayModelBody* m_pSelBody1;
        Ncti_Long* m_selCellID1;

        QVBoxLayout* m_mainLayout;
        QVBoxLayout* m_contentLayout;
        QLabel* m_selLabel1;
    };
}

#endif // !NctiDCM3SingleGeometryWidget_H