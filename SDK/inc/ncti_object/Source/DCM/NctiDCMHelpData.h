#ifndef NctiDCMHelpData_H
#define NctiDCMHelpData_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
#include <NctiDCMManager.h>
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMHelpData
	{
	public:
		NctiDCMEXVec2d m_fpoint;
		double m_fparam;
		ncti_DCM_ellipse_parameter m_feparam;
		NCTI_P_NODE m_fp_node;
		bool m_isUpdated;
		NctiDCMHelpData(NCTI_DCM_logical f = NCTI_DCM_FALSE) : m_fparam(0.0), m_feparam(NCTI_DCM_ELLIPSE_PARAMETER_PARAMETER), m_fp_node(NULL), m_isUpdated(false) {}
		void set_help_data(NctiDCMEXVec2d* v) 
		{
			if (*v != m_fpoint)
			{
				m_fpoint = *v;
				m_isUpdated = true;
			}
		}
		void set_help_data(double d) 
		{ 
			if (std::abs(m_fparam - d) > NctiDCMManager::instance()->LIN_RES)
			{
				m_fparam = d;
				m_isUpdated = true;
			}
		};
		void set_help_data(ncti_DCM_ellipse_parameter ep) { m_feparam = ep; }
		void set_help_data(NCTI_P_NODE p) { m_fp_node = p; }
		double get_param() const { return m_fparam; }
	};
}
#endif
