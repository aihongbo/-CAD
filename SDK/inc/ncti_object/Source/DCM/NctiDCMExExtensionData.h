#ifndef NctiDCMExExtensionData_H
#define NctiDCMExExtensionData_H
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMExExtensionData
	{
	public:
		ncti_DCM_para_ext_type m_ftype;
		ncti_DCM_para_ext_start_type m_fstart_type;
		double m_fstart_parameter;

		ncti_DCM_para_ext_end_type m_fend_type;
		double m_fend_parameter;
	public:
		NctiDCMExExtensionData(
			double start_param,
			double end_param,
			ncti_DCM_para_ext_type type = NCTI_DCM_PARA_EXT_TYPE_LINEAR,
			ncti_DCM_para_ext_start_type start_type = NCTI_DCM_PARA_EXT_START_TYPE_FIXED,
			ncti_DCM_para_ext_end_type end_type = NCTI_DCM_PARA_EXT_END_TYPE_FIXED
		) : m_ftype(type),
			m_fstart_type(start_type),
			m_fend_type(end_type),
			m_fstart_parameter(start_param),
			m_fend_parameter(end_param)
		{

		}

	};
}
#endif