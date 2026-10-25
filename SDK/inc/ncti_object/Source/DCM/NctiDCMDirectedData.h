#ifndef NctiDCMDirectedData_H
#define NctiDCMDirectedData_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMDirectedData
	{
	public:
		ncti_DCM_directed_type	m_fdirected_type;
		NctiDCMEXVec2d			m_fdirection;
		NCTI_G_NODE m_fg_node;
	public:
		NctiDCMDirectedData(ncti_DCM_directed_type i_dt, const NctiDCMEXVec2d* i_direction, NCTI_G_NODE i_gn);
		ncti_DCM_directed_type get_type(NctiDCMEXVec2d* o_dir, NCTI_G_NODE* o_gn);
	};
}
#endif