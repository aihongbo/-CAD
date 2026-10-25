#pragma once
#include "NctiRenderKit.h"
#include "NctiTransf.h"
#include <array>
#include <NctiPosition.h>
#include "NctiRGBAColor.h"

namespace NCTI
{
	class NctiViewerRenderer;

    /**
    * @brief kit for drawing control
    */
	class DECL_NCTI_RENDER NctiRenderDrawingKit : public NctiRenderKit
	{
        NCTI_RENDER_KIT_FUNCTIONS(NctiRenderDrawingKit);

	public:
		NctiRenderDrawingKit();

        enum DrawingKitType
        {
            e_draw_Petra = 0,
            e_draw_ModelMat,
            e_draw_Instance,
            e_draw_ViewNames,
            e_draw_FixedWorld,
            e_draw_DispCondition,
            e_draw_CoordType,
        };

        /**
        * @brief get coord type
        * @param[out] coord
        */
        Ncti_Boolean ShowCoordType(EnumRenderSpaceType& coord);

        /**
        * @brief get model matrix
        * @param[out] o_Transf model matrix
        */
        Ncti_Boolean ShowModelMat(NctiTransf& o_Transf);

        /**
        * @brief GetInstanceCount
        * @return ins count
        */
        Ncti_UInteger GetInstanceCount()const;

        /**
        * @brief get instance matrix and color
        * @return matrix vector add color for all instance
        */
        const std::vector<float>& ShowInstanceAndColor()const;

        /**
        * @brief get view id
        * @details view id 0 for stand view,view id 1 for axis view
        * @param[out] o_ids view id
        */
        Ncti_Boolean ShowViewNames(Ncti_Integer& o_ids);

        /**
        * @brief get display condition
        * @details when world range grate than this,no display for this object
        * @param[out] o_boo condition
        */
        Ncti_Boolean ShowDispCondistion(float& o_boo);

        /**
        * @brief get Penetrate
        * @details Penetrate display when hide from other object
        * @param[out] o_boo Penetrate
        */
        Ncti_Boolean ShowPenetra(float& o_boo);

        /**
        * @brief get Penetrate
        * @details when world pixel per mm grate this,no zoom for camera
        * @param[out] o_boo pixel per mm
        * @param[out] pos fixed position
        */
        Ncti_Boolean ShowFixedSize(float& o_boo, NctiPosition& pos);

        /**
        * @brief set model matrix
        * @param[in] i_Transf model matrix
        */
		NctiRenderDrawingKit* SetModelMat(const NctiTransf& i_Transf);

        /**
        * @brief set model matrix from direction,center,scale
        * @param[in] i_Transf model matrix
        */
        NctiRenderDrawingKit* SetModelMat(const NctiVector& dir, const NctiPosition& pos = { 0,0,0 }, float scale = {1});
        
        /**
        * @brief set instance
        * @param[in] pos instance position
        * @param[in] dir instance direction.size of 1 for all instance
        * @param[in] scale instance scale.size of 1 for all instance
        * @param[in] color instance color.size of 1 for all instance.-1 means no color
        */
        NctiRenderDrawingKit* SetInstance(
            const std::vector<NctiPosition>& pos,
            const std::vector<NctiVector>& dir = { {0,0,1} },
            const std::vector<float>& color = { -1 },
            const std::vector<float>& scale = { 1 });

        /**
        * @brief set instance
        * @param[in] pos instance position
        * @param[in] dir instance direction.size of 1 for all instance
        * @param[in] scale instance scale.size of 1 for all instance
        * @param[in] color instance color.size of 1 for all instance.-1 means no color
        */
        NctiRenderDrawingKit* SetInstance(
            const std::vector<float>& pos,
            const std::vector<NctiVector>& dir = { {0,0,1} },
            const std::vector<float>& color = { -1 },
            const std::vector<float>& scale = { 1 });

        /**
        * @brief SetViewNames
        * @param[in] id
        */
		NctiRenderDrawingKit* SetViewNames(Ncti_Integer id);

        /**
        * @brief SetDispCondition
        * @param[in] cd
        */
		NctiRenderDrawingKit* SetDispCondition(Ncti_Float cd);

        /**
        * @brief SetFixedSize
        * @param[in] size fixed pixel per mm
        * @param[in] pos fixed center
        */
		NctiRenderDrawingKit* SetFixedSize(Ncti_Float size, NctiPosition pos= {0,0,0});

        /**
        * @brief Set Penetrate
        * @param[in] i_boo Penetrate 0~1. <0 mean no Penetrate
        */
		NctiRenderDrawingKit* SetPetra(Ncti_Float i_boo);

        /**
        * @brief Set SetCoordType
        * @param[in] tp coord type
        */
        NctiRenderDrawingKit* SetCoordType(EnumRenderSpaceType tp);

        /**
        * @brief transform the max/min use instance
        */
        void ApplyInstanceBox(NctiPosition& max, NctiPosition& min);

        /**
        * @brief relay model
        */
        Ncti_Boolean IsWorldBox()const;

        /**
        * @brief Simple Mode for particle
        */
        Ncti_Boolean IsSimpleMode()const;

        /**
        * @brief Set Simple mode
        * @param[in] en simple mode
        */
        void SetSimpleMode(Ncti_Boolean en);

        /**
        * @brief InstanceElementLength
        */
        Ncti_UInteger InstanceElementLength()const;

	private:
        NctiPosition m_Max;
        NctiPosition m_Min;
		float m_MaxScale{ 1 };
	};
}

