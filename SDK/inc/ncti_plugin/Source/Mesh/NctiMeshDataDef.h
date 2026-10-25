#include <ncti_base.h>
#ifndef NctiMeshDataDef_H
#define NctiMeshDataDef_H

struct Ncti_Mesh_Option
{
	Ncti_Double m_size = 1;
	Ncti_Long m_type = 0;//0:triangle,1:QuadDominant,2:FullQuad
	Ncti_Double m_angleTol = 0.1;
	Ncti_Double m_qualityOpt = 0;
	Ncti_Long m_autoCurvature = 0;
	Ncti_Boolean m_high = false;
	Ncti_Boolean m_bParallel = false;
	Ncti_Boolean m_bDivideClosedFace = false;
};

#endif // !NctiGeoDataDef_H

