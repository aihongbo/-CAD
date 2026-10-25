#ifndef NctiSearchTool_H
#define NctiSearchTool_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <vector>
#include <map>
namespace NCTI
{
	class NctiDisplayDocCustomContainer;
	class NctiTopoCell;
	class NctiTopoEdge;
	class NctiTopoFace;
	class NctiDisplayModelBody;
	class DECL_NCTI_PUBFUN NctiSearchTool
	{
	public:
		//查找面的所有内环面（包括内环面相连通的所有面）
		static Ncti_Boolean FindLoopFromFace(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pTopoCell, std::vector<NCTI_MODEL_TAG>& o_FaceCellVec);
		//查找面的所有连接面（包括自己）
		static Ncti_Boolean FindConnectFace(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pTopoCell, std::vector<NCTI_MODEL_TAG>& o_FaceCellVec);
		//查找面的所有相似连接面（包括自己）
		static Ncti_Boolean FindSameConnectFace(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pTopoCell, std::vector<NCTI_MODEL_TAG>& o_FaceCellVec);
		//查找面的所有非平面连接面（包括自己）
		static Ncti_Boolean FindNoPlaneConnectFace(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pTopoCell, std::vector<NCTI_MODEL_TAG>& o_FaceCellVec);
		//查找面的所有的内环
		static Ncti_Boolean FindInnerLoops(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pTopoCell, std::vector<std::vector<NCTI_MODEL_TAG>>& o_EdgeCellVecVec);
		//查找与内环相连通的面（包括内环面相连通的所有面，对有内环的面根据外环长度进行过滤）
		static Ncti_Boolean FindFaceFromLoop(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody, std::vector<NctiTopoEdge*> i_InnerLoop, std::vector<NCTI_MODEL_TAG>& o_FaceCellVec);
		//查找共边
		static Ncti_Boolean FindCommonEdge(NctiDisplayModelBody* i_pModelBody,Ncti_Integer i_nMinCoNum, Ncti_Integer i_nMaxCoNum, std::map<Ncti_Long, std::vector<Ncti_Long>>& o_coNumAndEdgeIdsMap);
	private:
		/*
		static Ncti_Boolean FindLoopFromFaceEx(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pTopoCell,
			std::vector<NctiTopoEdge*>& o_TopoEdgeVec,
			std::map<NctiTopoFace*, Ncti_Integer>& o_FaceLoopMap,
			std::map<NctiTopoEdge*, Ncti_Integer>& o_EdgeMap,
			Ncti_Integer i_mode = 0);
		static Ncti_Boolean FindFaceFromLoopEx(NctiDisplayDocCustomContainer* i_pDocCus, NctiDisplayModelBody* i_pModelBody,
			std::vector<NctiTopoEdge*>& i_EdgeLoopVec,
			std::vector<NctiTopoEdge*>& i_FilterEdgeVec,
			std::vector<NctiTopoFace*>& o_TopoFaceVec,
			Ncti_Boolean i_sizeCondition = false,
			Ncti_Double i_size = 0.);
		static Ncti_Boolean GetEdgeLength(NctiDisplayModelBody* i_pModelBody,
			NctiTopoEdge* i_pTopoEdge,
			Ncti_Double& o_length);*/
	};
}
#endif
