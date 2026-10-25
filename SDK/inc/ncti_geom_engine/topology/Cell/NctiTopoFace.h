#ifndef NctiTopoFace_H
#define NctiTopoFace_H
#include "NctiTopoCell.h"
namespace NCTI
{
	class NctiGeomSurface;
	class NctiTopoLoop;
	class NctiPolyTriangulation;
	class DECL_NCTI_GEOM_ENGINE NctiTopoFace : public NctiTopoCell
	{
		NCTI_GEOM_FUNCTIONS(NctiTopoFace)
	public:
		NctiTopoFace();
		virtual ~NctiTopoFace();
	public:
		void AddTopoLoop(NctiTopoLoop* i_pTopoLoop);
		NctiPolyTriangulation* Triangulation(Ncti_Poly_MeshPurpose i_theMeshPurpose);
	public:
		NCTI_GE_ATT_DEF(NctiGeomSurface*, m_GeomSurface)
		NCTI_GE_ATT_DEF(std::vector<NctiTopoLoop*>, m_TopoLoopVec)
		NCTI_GE_ATT_DEF(NctiPolyTriangulation*, m_ActiveTriangulation)
	private:
		std::vector<NctiPolyTriangulation*> m_Triangulations;
		Ncti_Double m_Tolerance;
		Ncti_Boolean m_NaturalRestriction;
	
	};
}
#endif
