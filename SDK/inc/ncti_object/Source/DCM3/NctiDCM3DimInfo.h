#ifndef NctiDCM3DimInfo_H
#define NctiDCM3DimInfo_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCM3Def.h"
#include "NctiDCMEXVec3d.h"
#include <iostream>
namespace NCTI
{
	/**
	* @brief dimension help information
	* @details set the dimension help data
	*/
	class NctiDCM3DimInfo
	{
	public:
		ncti_DCM3_half_space fhalf_space;
		NctiDCMEXVec3d fhelp_point;
		double fhelp_parameter;
		ncti_DCM3_help_points fhelp_type;

		double fu_parameter;
		double fv_parameter;

		Ncti_Boolean IsUpdated;

		NctiDCM3DimInfo() {
			fhalf_space = NCTI_DCM3_HALF_SPACE_NOT_SPECIFIED;
			fhelp_point = NctiDCMEXVec3d(0,0,0);
			fhelp_parameter = 0;
			fhelp_type = NCTI_DCM3_DIM_TO_CENTRE;
			fu_parameter = 0; fv_parameter = 0;
			IsUpdated = false;
		}
	};
}
#endif
