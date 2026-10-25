#ifndef NctiTopoLoop_H
#define NctiTopoLoop_H
#include "NctiTopoCell.h"
namespace NCTI
{
	class NctiTopoEdge;
	class NctiTopoFace;
	class DECL_NCTI_GEOM_ENGINE NctiTopoLoop : public NctiTopoCell
	{
		NCTI_GEOM_FUNCTIONS(NctiTopoLoop)
	public:
		NctiTopoLoop();
		virtual ~NctiTopoLoop();
	public:
		NCTI_GE_ATT_DEF(std::vector<NctiTopoEdge*>, m_TopoEdgeVec)
			NCTI_GE_ATT_DEF(NctiTopoFace*, m_TopoFace)
	public:
		void AddTopoEdge(NctiTopoEdge* i_pTopoEdge);
	};
}
#endif
