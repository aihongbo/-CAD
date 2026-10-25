#pragma once
#include "NctiRenderKit.h"
namespace NCTI
{
    /**
    * @brief visible info or select info for object
    */
    class DECL_NCTI_RENDER NctiRenderVisSelKit : public NctiRenderKit
    {
        NCTI_RENDER_KIT_FUNCTIONS(NctiRenderVisSelKit);

    public:
        NctiRenderVisSelKit();

        enum VisSelKitType
        {
            e_kit_Faces = 0,
            e_kit_Lines,
            e_kit_Vertex,
            e_kit_Text,
            e_kit_Image,
        };

        /**
        * @brief SetEverything visible or selected
        * @param[in] i_boo
        */
        NctiRenderVisSelKit* SetEverything(bool i_boo);

        /**
        * @brief SetFaces visible or selected
        * @param[in] i_boo
        */
        NctiRenderVisSelKit* SetFaces(bool i_boo);

        /**
        * @brief SetLines visible or selected
        * @param[in] i_boo
        */
        NctiRenderVisSelKit* SetLines(bool i_boo);

        /**
        * @brief SetVertexs visible or selected
        * @param[in] i_boo
        */
        NctiRenderVisSelKit* SetVertexs(bool i_boo);

        /**
        * @brief SetText visible or selected
        * @param[in] i_boo
        */
        NctiRenderVisSelKit* SetText(bool i_boo);

        /**
        * @brief SetImage visible or selected
        * @param[in] i_boo
        */
        NctiRenderVisSelKit* SetImage(bool i_boo);

        /**
        * @brief anything had set to true
        * @param[in] i_boo
        */
        bool ShowAnything()const;

        /**
        * @brief ShowFaces
        * @param[out] i_boo
        */
        bool ShowFaces(bool& o_boo)const;

        /**
        * @brief ShowLines
        * @param[out] i_boo
        */
        bool ShowLines(bool& o_boo)const;

        /**
        * @brief ShowVertexs
        * @param[out] i_boo
        */
        bool ShowVertexs(bool& o_boo)const;

        /**
        * @brief ShowTexts
        * @param[out] i_boo
        */
        bool ShowTexts(bool& o_boo)const;

        /**
        * @brief ShowImages
        * @param[out] i_boo
        */
        bool ShowImages(bool& o_boo)const;
    };
}

