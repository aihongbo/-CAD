#include "GeometryFunctionDemo.h"
#include "GeometryFunctionInterfaceDemo.h"
#include "NctiGeometryFunctionInterface.h"
#include "NctiModelFunctionResult.h"
#include "NctiPluginsManager.h"
#include "NctiFunctionInterface.h"
#include "NctiFuntionInterfaceManager.h"
#include "NctiSystemPubFun.h"
using namespace NCTI;

#define NCTI_FUNCTION_INTERFACE_BEGIN()\
NctiPluginsManager* pPluginsManager = NctiPluginsManager::instance(); \
NctiFuntionInterfaceManager* pFuntionInterfaceManager = pPluginsManager->GetFuntionInterfaceManager(); \
std::vector<NctiFunctionInterface*> FunctionInterfaceVec = pFuntionInterfaceManager->GetOtherFunctionInterface(); \
for (int i = 0; i < FunctionInterfaceVec.size(); i++)\
{
#define NCTI_FUNCTION_INTERFACE_END()\
if (ModelFunctionResult.IsFunctionImplementation() == true)\
{\
std::chrono::high_resolution_clock::time_point tEnd = std::chrono::high_resolution_clock::now();\
ModelFunctionResult.SetTime(tStart,tEnd);\
Ncti_LongLong UsedPhysicalMemoryE;\
NctiSystemPubFun::getMemoryInfo(UsedPhysicalMemoryE);\
ModelFunctionResult.SetUsedPhysicalMemory(UsedPhysicalMemoryS, UsedPhysicalMemoryE);\
Ncti_Double cpuUsageE = NctiSystemPubFun::getCpuUsage();\
ModelFunctionResult.SetcpuUsage(cpuUsageS, cpuUsageE);\
return ModelFunctionResult; \
}else if(ModelFunctionResult.IsFunctionImplementation() == false && ModelFunctionResult.GetIsModelGeomtry())\
{\
return ModelFunctionResult; \
}\
}\
return NctiGeometryResult();

#define NCTI_FUNCTION_INTERFACE_FUNCCALL(FUNCCALL) \
NCTI_FUNCTION_INTERFACE_BEGIN()\
std::chrono::high_resolution_clock::time_point tStart = std::chrono::high_resolution_clock::now();\
Ncti_LongLong UsedPhysicalMemoryS;\
NctiSystemPubFun::getMemoryInfo(UsedPhysicalMemoryS);\
Ncti_Double cpuUsageS = NctiSystemPubFun::getCpuUsage();\
NctiGeometryResult ModelFunctionResult;\
if(FunctionInterfaceVec[i]->IsTypeName(GeometryFunctionInterfaceDemo::ID))\
{\
GeometryFunctionInterfaceDemo* pGeometryFunctionInterface = (GeometryFunctionInterfaceDemo*)FunctionInterfaceVec[i];\
ModelFunctionResult = pGeometryFunctionInterface->FUNCCALL; \
ModelFunctionResult.SetFUNCCALL(#FUNCCALL);\
}\
NCTI_FUNCTION_INTERFACE_END()\

NCTI::GeometryFunctionDemo::GeometryFunctionDemo()
{

}

NCTI::GeometryFunctionDemo::~GeometryFunctionDemo()
{

}

NctiGeometryResult NCTI::GeometryFunctionDemo::create_box_demo(NctiDisplayDocCustomContainer* i_pCustomContainer, const NctiPosition& i_pos, Ncti_Double i_len, Ncti_Double i_width, Ncti_Double i_height, NCTI_MODEL_TAG& o_ModelBody)
{
    NCTI_FUNCTION_INTERFACE_FUNCCALL(create_box_demo(i_pCustomContainer, i_pos, i_len, i_width, i_height, o_ModelBody))
}