#ifndef NctiRenderFeatureKit_H
#define NctiRenderFeatureKit_H
#include "NctiRenderKit.h"
namespace NCTI
{
    /**
    * @brief camera info for view
    */
	class DECL_NCTI_RENDER NctiRenderFeatureKit : public NctiRenderKit
	{
        NCTI_RENDER_KIT_FUNCTIONS(NctiRenderFeatureKit);
	public:
        NctiRenderFeatureKit();

        enum FeatureKitType
        {
            e_fea_lineType = 0,
            e_fea_lineWeight,
            e_fea_lineFactor,
            e_fea_vertType,
            e_fea_vertSize,
        };

		enum LineType
		{
			SolidLine = 0,//______________________________
			DotLine,//.  .  .  .  .  .  . 
			DotDashLine,//____ . ____ . _____ . _____.
			CenterLine,//_____ _ _____ _ _____ _ _____ _ 
			DashLine,//____  ____  ____  ____ 
			DotDotLine,//____ . . ____ . . ____ . . ____ . . ____
			DotDotDotLine,//____ . . . ____ . . . ____ . . .
		};

        enum VertexType
        {
            CircleSolid = 0,    ///circle point
            SquareSolid,        ///square point
            SphereSolid,        ///sphere point
        };

        /**
        * @brief SetVertexType
        * @param[in] i_VertexType
        * @see VertexType
        */
        NctiRenderFeatureKit* SetVertexType(VertexType i_VertexType);

        /**
        * @brief set point display pixel
        * @param[in] i_PixelW
        */
        NctiRenderFeatureKit* SetPixelWH(float i_PixelW);

        /**
        * @brief set point display pixel
        * @details display always the size
        * @param[in] i_world
        */
        NctiRenderFeatureKit* SetWorldWH(float i_world);

        /**
        * @brief set line width
        * @param[in] i_weight line width
        */
        NctiRenderFeatureKit* SetLineWidth(float i_weight);

        /**
        * @brief set line type
        * @param[in] i_type line type
        * @see LineType
        */
        NctiRenderFeatureKit* setLineType(LineType i_type);

        /**
        * @brief set line factor. duplicate mode
        * @param[in] factor line factor,0~256
        */
        NctiRenderFeatureKit* SetLineFactor(int factor);//1~256

        /**
        * @brief get line type
        * @param[out] i_type line type
        * @see LineType
        */
		bool ShowLineType(LineType& o_type)const;

        /**
        * @brief get line width
        * @param[out] o_weight line width
        */
		bool ShowLineWidth(float& o_weight)const;

        /**
        * @brief get line factor
        * @param[out] o_LineTypeDashed line factor
        */
		bool ShowLineFactor(int& o_LineTypeDashed)const;

        /**
        * @brief get vertex type
        */
        bool ShowVertexType(VertexType& o_VertexType)const;

        /**
        * @brief get vertex display size in pixel
        */
        bool ShowPixelWH(float& o_PixelW)const;
	};
}
#endif // !NctiRenderFeatureKit_H
