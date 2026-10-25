#ifndef NctiUtilityEx_H
#define NctiUtilityEx_H
#include "dcl_ncti_object.h"
#include "NctiVector.h"
#include "NctiPosition.h"
#include "NctiTransf.h"
#include "ncti.h"
#include "NctiSketchComDefine.h"
namespace NCTI
{
	class NctiDisplayObject;
	class NctiBaseView;
	class NctiDisplayObject;
	class NctiSelectionDataList;
	class NctiDisplayObjectList;
	class NctiDisplaySketchObject;
	class NctiRenderGeometryItem;
}
using namespace NCTI;
void  NctiSortArray(int  i_iNum, int* i_aiArray);
int  NctiUniqueArray(int  i_iNum, int* i_aiArray);
NctiRenderGeometryItem* NctiCreateTransArrow(NctiPosition  i_cPosCenter, NctiVector  i_cVecDir, double  i_dLength, double  i_dRatio, double  i_dRadCylinder, double  i_dRadCone);
void  NctiConvertWCSFilePath(const char* i_psFileFullPath, wchar_t*& i_pwsPathReturned);
void DECL_NCTI_OBJECT  MakeDimensionText(char* i_szInputText, char*& o_szOutputText);
int  ParseString(const char* i_string, char  i_delimiter, int  i_offset, char* o_ret_string);

void  ConvertEulerZyzToTransf(double i_dAngleZ0, double i_dAngleY, double i_dAngleZ1, NctiTransf& o_transf);
void  ConvertEulerXyzToTransf(double i_dAngleX, double i_dAngleY, double i_dAngleZ, NctiTransf& o_transf);
void DECL_NCTI_OBJECT  ConvertEulerToTransf(EnumNctiEuler i_eEuler, double i_dAngle1, double i_dAngle2, double i_dAngle3, NctiTransf& o_transf);
void DECL_NCTI_OBJECT  ConvertTransfToEulerZyz(const NctiTransf& i_transf, double& o_dAngleZ0, double& o_dAngleY, double& o_dAngleZ1);
void DECL_NCTI_OBJECT  ConvertTransfToEulerXyz(const NctiTransf& i_transf, double& o_dAngleX, double& o_dAngleY, double& o_dAngleZ);
void DECL_NCTI_OBJECT ConvertTransfToEuler(const NctiTransf& i_transf, EnumNctiEuler i_eEuler, double& o_dAngle1, double& o_dAngle2, double& o_dAngle3);
void  NctiReverseArray(int iNum, NctiUnitVector*& auvecToReverse);
void  NctiReverseArray(int iNum, NctiPosition*& auvecToReverse);
EnumNctiResult DECL_NCTI_OBJECT api_ncti_get_original_do_from_selection(NctiSelectionDataList& i_pSelectionData, NctiDisplayObjectList& o_listSelected, const  char* i_pszTypeName = NULL);

#endif