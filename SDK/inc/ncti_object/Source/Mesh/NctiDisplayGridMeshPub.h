#pragma once
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiPosition.h"
#include <cmath>
#include "vector"

namespace NCTI
{
    class NctiMeshBody;
    class DECL_NCTI_OBJECT NctiDisplayGridMeshPub
    {
    public:
        NctiDisplayGridMeshPub(NctiMeshBody*);

        //网格质量检查-网格颜色分类显示
        void ShowMeshClassifyColor( const std::vector<Ncti_UInteger>& i_allElements, const std::vector<double>& i_ValueVec);

        //nMode 0长宽比 1扭曲度 2雅克比 3最小角度 4最大角度 
        void GetMeshValue(Ncti_Integer nMode, std::vector<Ncti_UInteger>& o_allElements, std::vector<double>& o_ValueVec);

        std::vector<std::string> GetMeshShowText(Ncti_Integer nMode, const std::vector<Ncti_UInteger>& i_allElements);

        void GetMeshAspectRatio(std::vector<Ncti_UInteger>& o_allElements, std::vector<double>& o_ValueVec); //长宽比
        void GetDistortionDegree(std::vector<Ncti_UInteger>& o_allElements, std::vector<double>& o_ValueVec); //扭曲度

        void GetJacobi(std::vector<Ncti_UInteger>& o_allElements, std::vector<double>& o_ValueVec);  // 雅克比
        void GetMinAngle(std::vector<Ncti_UInteger>& o_allElements, std::vector<double>& o_ValueVec);  //最小角度
        void GetMaxAngle(std::vector<Ncti_UInteger>& o_allElements, std::vector<double>& o_ValueVec);  //最大角度

    private:
        NctiMeshBody* m_part{ nullptr };//no save
    };
}

