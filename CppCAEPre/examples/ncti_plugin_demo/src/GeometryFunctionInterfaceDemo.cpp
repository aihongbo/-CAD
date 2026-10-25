#include "GeometryFunctionInterfaceDemo.h"
#include "NctiPluginsManager.h"
#include "NctiFuntionInterfaceManager.h"
#include "NctiAxis.h"
#include "NctiGeometryFunctionInterface.h"
using namespace NCTI;

#define NCTI_OBJ_NAME "GeometryFunctionInterfaceDemo"
NCTI_PLUGIN_DEF(GeometryFunctionInterfaceDemo, NctiFunctionInterface, "ncti_plugin_demo", NCTI_OBJ_NAME)

NCTI::GeometryFunctionInterfaceDemo::GeometryFunctionInterfaceDemo()
{
}

NCTI::GeometryFunctionInterfaceDemo::~GeometryFunctionInterfaceDemo()
{
}

NctiGeometryResult NCTI::GeometryFunctionInterfaceDemo::create_box_demo(
    NctiDisplayDocCustomContainer* i_pCustomContainer,
    const NctiPosition& i_pos,
    Ncti_Double i_len,
    Ncti_Double i_width,
    Ncti_Double i_height,
    NCTI_MODEL_TAG& o_ModelBody)
{
    return NctiGeometryResult();
}