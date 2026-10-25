#pragma once

#include "NctiRenderKit.h"
#include "NctiRGBAColor.h"

namespace NCTI
{
    /**
    * @brief color info for object
    */
    class DECL_NCTI_RENDER NctiRenderMaterialKit : public NctiRenderKit
    {
        NCTI_RENDER_KIT_FUNCTIONS(NctiRenderMaterialKit);

    public:
        NctiRenderMaterialKit();

        enum MaterialMappingKitType
        {
            e_mat_FaceColor = 0,
            e_mat_LineColor,
            e_mat_VertexColor,
            e_mat_BackFaceColor,
            e_mat_TextColor,
            e_mat_LineAlpha,
            e_mat_FaceAlpha,
            e_mat_Highlight,
            e_mat_Specular,
            e_mat_Shininess,
        };

        /**
        * @brief SetFaceColor
        * @param[in] i_color
        */
        NctiRenderMaterialKit* SetFaceColor(const RGBAColor& i_color);
        /**
        * @brief ShowBackFaceColor
        * @param[out] i_color
        */
        bool ShowBackFaceColor(RGBAColor& o_color);
        /**
        * @brief SetLineColor
        * @param[in] i_color
        */
        NctiRenderMaterialKit* SetLineColor(const RGBAColor& i_color);

        /**
        * @brief SetVertexColor
        * @param[in] i_color
        */
        NctiRenderMaterialKit* SetVertexColor(const RGBAColor& i_color);

        /**
        * @brief SetBackFaceColor
        * @param[in] i_color
        */
        NctiRenderMaterialKit* SetBackFaceColor(const RGBAColor& i_color);

        /**
        * @brief SetTextColor
        * @param[in] i_color
        */
        NctiRenderMaterialKit* SetTextColor(const RGBAColor& i_color);

        /**
        * @brief SetLineAlpha
        * @param[in] i_alpha
        */
        NctiRenderMaterialKit* SetLineAlpha(Ncti_Double i_alpha);

        /**
        * @brief SetFaceAlpha
        * @param[in] i_alpha
        */
        NctiRenderMaterialKit* SetFaceAlpha(Ncti_Double i_alpha);

        /**
        * @brief SetFaceAlpha and SetLineAlpha
        * @param[in] i_alpha
        */
        NctiRenderMaterialKit* SetAlpha(Ncti_Double i_alpha);
        /**
        * @brief SetHighlightColor
        * @param[in] i_HighlightColor
        */
        NctiRenderMaterialKit* SetHighlightColor(const RGBAColor& i_HighlightColor);

        /**
        * @brief SetPreHighlightColor
        * @param[in] i_color
        */
        NctiRenderMaterialKit* SetSpecularColor(const RGBAColor& i_color);
        /**
        * @brief SetPreHighlightColor
        * @param[in] i_shin
        */
        NctiRenderMaterialKit* SetShininess(const Ncti_Float& i_shin);

        /**
        * @brief get highlight color
        * @param[out] o_HighlightColor highlight color
        */
        Ncti_Boolean ShowHighlightColor(RGBAColor& o_HighlightColor);

        /**
        * @brief get Specular color
        * @param[out] o_Color Specular color
        */
        Ncti_Boolean ShowSpecularColor(RGBAColor& o_Color);

        /**
        * @brief ShowShininess
        * @param[out] o_out Shininess
        */
        Ncti_Boolean ShowShininess(Ncti_Float& o_out);

        /**
        * @brief ShowFaceColor
        * @param[out] i_color
        */
        bool ShowFaceColor(RGBAColor& o_color);

        /**
        * @brief ShowLineColor
        * @param[out] i_color
        */
        bool ShowLineColor(RGBAColor& o_color);

        /**
        * @brief ShowVertexColor
        * @param[out] i_color
        */
        bool ShowVertexColor(RGBAColor& o_color);

        /**
        * @brief ShowTextColor
        * @param[out] i_color
        */
        bool ShowTextColor(RGBAColor& o_color);
    };
}

