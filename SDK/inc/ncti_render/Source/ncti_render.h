#ifndef Ncti_render_H
#define Ncti_render_H
#include "ncti_dcl_render.h"

namespace NCTI
{


    /**
     * @brief cord space type
     * @see NctiRenderDrawingKit::ShowCoordType
     */
    enum DECL_NCTI_RENDER EnumRenderSpaceType
    {
        e_space_Pixel = 0,  ///pixel coord,0~window size
        e_space_Window,     //window coord,-1~1
        e_space_World,       //world coord
        e_space_World2D       //world coord,in the front display
    };

    /**
     * @brief EnumRenderLightType
     * @see PointLightAtt
     */
    enum DECL_NCTI_RENDER EnumRenderLightType
    {
        e_light_ambient = 0,
        e_light_screen,
        e_light_directien,
        e_light_point,
    };

    enum DECL_NCTI_RENDER RenderAlgnX
    {
        e_alx_center=0,
        e_alx_left,
        e_alx_right
    };
    enum DECL_NCTI_RENDER RenderAlgnY
    {
        e_aly_center=0,
        e_aly_top,
        e_aly_bot
    };

    enum DECL_NCTI_RENDER RenderKitType
    {
        e_rkt_drawing = 0,
        e_rkt_feature,
        e_rkt_material,
        e_rkt_select,
        e_rkt_visable,
        e_rkt_cout
    };
}

#endif // !1
