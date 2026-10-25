#ifndef NctiRGBAColor_H
#define NctiRGBAColor_H
#include "ncti_render.h"
#include "ncti_base.h"
#include "NctiPosition.h"

namespace NCTI
{
    /**
     * @brief rgba color
     */
	class DECL_NCTI_RENDER RGBAColor
	{
	public:
		RGBAColor();

        /**
         * @brief construct
         * @param[in] iRed iRed
         * @param[in] iGreen iGreen
         * @param[in] iBlue iBlue
         * @param[in] iAlpha iAlpha
         */
		RGBAColor(Ncti_Double iRed, Ncti_Double iGreen, Ncti_Double iBlue, Ncti_Double iAlpha);

        /**
         * @brief construct.iAlpha = 1
         * @param[in] iRed iRed
         * @param[in] iGreen iGreen
         * @param[in] iBlue iBlue
         */
		RGBAColor(Ncti_Double iRed, Ncti_Double iGreen, Ncti_Double iBlue);

        /**
         * @brief construct
         * @param[in] iRed iRed
         * @param[in] iGreen iGreen
         * @param[in] iBlue iBlue
         * @param[in] iAlpha iAlpha
         */
		RGBAColor(Ncti_Float iRed, Ncti_Float iGreen, Ncti_Float iBlue, Ncti_Float iAlpha);

        /**
         * @brief construct.iAlpha = 1
         * @param[in] iRed iRed
         * @param[in] iGreen iGreen
         * @param[in] iBlue iBlue
         */
		RGBAColor(Ncti_Float iRed, Ncti_Float iGreen, Ncti_Float iBlue);

        /**
         * @brief construct iAlpha = 255
         * @param[in] iRed iRed
         * @param[in] iGreen iGreen
         * @param[in] iBlue iBlue
         */
		RGBAColor(Ncti_Integer iRed, Ncti_Integer iGreen, Ncti_Integer iBlue);

        /**
         * @brief construct
         * @param[in] iRed iRed
         * @param[in] iGreen iGreen
         * @param[in] iBlue iBlue
         * @param[in] iAlpha iAlpha
         */
		RGBAColor(Ncti_Integer iRed, Ncti_Integer iGreen, Ncti_Integer iBlue, Ncti_Integer iAlpha);

        /**
         * @brief construct from uint32
         * @param[in] i_hex 0x00rrggbb
         */
		RGBAColor(Ncti_UInteger i_hex);

        /**
         * @brief construct from string
         * @param[in] str_hex hex string "00rrggbb"
         */
		RGBAColor(std::string str_hex);

        /**
         * @brief construct from RGBAColor
         * @param[in] iColor iColor
         */
		RGBAColor(const RGBAColor& iColor);;


        /**
         * @brief to string
         * @param[in] iColor iColor
         */
		std::string HexArgbToString();

        /**
         * @brief to hex
         */
		Ncti_UInteger HexArgb();

        /**
         * @brief to string
         */
        std::string HexRgbToString();
            
        /**
        * @brief to hex
        */
		Ncti_UInteger Hexrgb();

        /**
        * @brief to hex
        */
		Ncti_UInteger Hexbgr();

        Ncti_Float red;
        Ncti_Float green;
        Ncti_Float blue;
        Ncti_Float alpha;
        void operator=(const RGBAColor& iSrcColor);
        bool operator==(const RGBAColor& iSrcColor1)const;
        bool operator!=(const RGBAColor& iSrcColor1)const;
		static void ToBGA(Ncti_UInteger i_hex, Ncti_Integer& o_b, Ncti_Integer& o_g, Ncti_Integer& o_r);
	};

    struct DECL_NCTI_RENDER PointLightAtt
    {
        RGBAColor m_LightColor{ 1.0,1.0,1.0,0.1 };
        NctiPosition m_LightParam{ 0.0f,0.0f,1.0f };
        EnumRenderLightType m_Type{ e_light_screen };
        Ncti_Boolean m_IsEnable{false};
        Ncti_Boolean operator!=(const PointLightAtt&)const;
        Ncti_Boolean operator==(const PointLightAtt&)const;
    };
}

namespace std {
    template<>
    struct hash<NCTI::RGBAColor> {
        size_t operator()(const NCTI::RGBAColor& p) const noexcept {
            std::size_t seed = 0;
            hash_combine(seed, p.red);
            hash_combine(seed, p.green);
            hash_combine(seed, p.blue);
            hash_combine(seed, p.alpha);
            return seed;
        }
    };

    template<>
    struct hash<NCTI::PointLightAtt> {
        size_t operator()(const NCTI::PointLightAtt& p) const noexcept {
            std::size_t seed = 0;
            hash_combine(seed, p.m_LightColor);
            hash_combine(seed, p.m_LightParam);
            hash_combine(seed, p.m_Type);
            hash_combine(seed, p.m_IsEnable);
            return seed;
        }
    };
}

#endif
