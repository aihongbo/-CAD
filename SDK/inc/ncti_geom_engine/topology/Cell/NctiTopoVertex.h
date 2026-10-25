#ifndef NctiTopoVertex_H
#define NctiTopoVertex_H
#include "NctiTopoCell.h"
namespace NCTI
{
	class NctiGeomPoint;
	class NctiPosition;
	class NctiTopoEdge;
	class DECL_NCTI_GEOM_ENGINE NctiTopoVertex : public NctiTopoCell
	{
		NCTI_GEOM_FUNCTIONS(NctiTopoVertex)
	public:
		NctiTopoVertex();
		virtual ~NctiTopoVertex();
	public:
		NCTI_GE_ATT_DEF(NctiGeomPoint*, m_pGeomPoint)
	public:
		void AddTopoEdge(NctiTopoEdge* i_TopoEdge);
	public:
		const std::vector<NctiTopoEdge*>& GetTopoEdge() { return m_TopoEdgeVec; }
	private:
		std::vector<NctiTopoEdge*> m_TopoEdgeVec;
		
	};
}
#endif
