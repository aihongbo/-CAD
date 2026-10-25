#pragma once
#include "ncti_base.h"
#include <NctiPosition.h>
#include <set>
#include "ncti_event.h"
#include "NctiMeshElement.h"
#include "NctiGridPickSet.h"

namespace NCTI
{
    class NctiDisplayGridMesh;
    class NctiDisplayModelBody;
    class NctiRenderUnstructureItem;

    /**
    * @brief mesh body for data exchange
    */
    class DECL_NCTI_BASE NctiMeshBody {
    public:
        /**
         * @brief init the mesh body,no copy data
         * @param[in] pos node positions
         * @param[in] type element types
         * @param[in] data element data
         * @param[in] data element tag
         * */
        NctiMeshBody(const std::vector<Ncti_Float>* pos,
            const std::vector<NctiElementType>* type,
            const std::vector<Ncti_UInteger>* data,
            const std::vector<Ncti_UInteger>* tag = nullptr,
            Ncti_UInteger startNode = 1,
            Ncti_UInteger startElem = 1);

        /**
         * @brief init the mesh body,copy data
         * @param[in] pos node positions
         * @param[in] type element types
         * @param[in] data element data
         * @param[in] data element tag
         * */
        NctiMeshBody(const std::vector<Ncti_Float>& pos,
            const std::vector<NctiElementType>& type,
            const std::vector<Ncti_UInteger>& data,
            const std::vector<Ncti_UInteger>& tag = {},
            Ncti_UInteger startNode =1,
            Ncti_UInteger startElem =1);

        ~NctiMeshBody();

        Ncti_Integer GetDimension()const;

        /**
         * @brief find nodes from area
         * @param[in] i_ptMin area min
         * @param[in] i_ptMax area min
         * @param[in] i_trans trans
         * @param[out] o_pick pick result
         * */
        void FindNodesFromArea(const NctiPosition&i_ptMin,const NctiPosition&i_ptMax, std::set<NctiGridPickSet>&o_pick, const NctiTransf&i_trans)const;

        /**
         * @brief find edges in the edge direction
         * @param [in] i_elemNumber element number
         * @param [in] i_eindex edge index
         * @param [in] i_deg edge angle in degree
         * @param[out] o_pick pick result
         * */
        void FindEdgesFromEdge(Ncti_UInteger i_elemNumber, Ncti_UInteger i_eindex, Ncti_Float i_deg, std::set<NctiGridPickSet>& o_pick)const;

        /**
         * @brief Find SameEdges with edge
         * @param [in] i_elemNumber element number
         * @param [in] i_eindex edge index
         * @param[out] o_pick pick result
         * */
        void FindSameEdges(Ncti_UInteger i_elemNumber, Ncti_Integer i_eindex, std::set<NctiGridPickSet>& o_pick)const;

        /**
         * @brief find faces in the face direction
         * @param [in] i_elemNumber element number
         * @param [in] i_findex face index
         * @param [in] i_deg face angle in degree
         * @param[out] o_pick pick result
         * */
        void FindFacesFromFace(Ncti_UInteger i_elemNumber, Ncti_UInteger i_findex, Ncti_Float i_deg, std::set<NctiGridPickSet>& o_pick)const;

        /**
         * @brief Find SameFaces with face
         * @param [in] i_elemNumber element number
         * @param [in] i_findex face index
         * @param[out] o_pick pick result
         * */
        void FindSameFaces(Ncti_UInteger i_elemNumber, Ncti_UInteger i_findex, std::set<NctiGridPickSet>& o_pick)const;

        /**
         * @brief FindCellFromNode
         * @param [in] i_nodeNumber node number
         * @param[out] o_pick pick result
         * */
        void FindCellFromNode(Ncti_UInteger i_nodeNumber, std::set<NctiGridPickSet>& o_pick)const;

        /**
         * @brief get fist number info
         * @param[out] startNode the first node number
         * @param[out] startElem the first element number
         * */
        void GetStartNumber(Ncti_UInteger& startNode, Ncti_UInteger& startElem)const;

        /**
         * @brief get display mesh object associate with the mesh body
         * @see NctiDisplayGridMesh
         * */
        NctiDisplayGridMesh* GetDispObject()const;

        /**
         * @brief get display geometry object associate with the mesh body
         * @see NctiDisplayModelBody
         * */
        NctiDisplayModelBody* GetModelBody()const;

        /**
         * @brief GetRenderItem
         * @see NctiRenderUnstructureItem
         * */
        NctiRenderUnstructureItem* GetRenderItem()const;

        /**
         * @brief node count
         * */
        Ncti_UInteger NodeCount()const;

        /**
         * @brief all element count
         * */
        Ncti_UInteger ElemCount()const;

        /**
         * @brief get all Node numbers
         * @details get all numbers vector. ranged in internal order
         * @see AllNodePositions
         * */
        void AllNodeNumber(std::vector<Ncti_UInteger>& o_number)const;

        /**
         * @brief get all Node position
         * @details get all position float vector. ranged in internal order
         * @return node positions.format in node0x,node0y,node0z,node1x...
         * @see AllNodeNumber
         * */
        const std::vector<Ncti_Float>& AllNodePositions()const;

        /**
         * @brief get node position from node number
         * @param [in] i_nid node number
         * @param [out] o_pos node position
         * @see NctiPosition
         * */
        bool GetVertex(Ncti_UInteger i_nid, NctiPosition&o_pos)const;

        /**
         * @brief HasVertex
         * @param [in] i_nid node number
         * @return if vertex exist
         * */
        Ncti_Boolean HasVertex(Ncti_UInteger i_nid)const;

        /**
         * @brief get all element data by dimension
         * @param [out] o_type element types
         * @param [out] o_data element nodes.
         */
        void AllElementData(std::vector<NctiElementType>&o_type, std::vector<std::vector<Ncti_UInteger>>& o_data)const;

        /**
         * @brief get all element numbers by dimension
         * @param [out] o_number element numbers
         */
        void AllElementNumber(std::vector<Ncti_UInteger>& o_number)const;

        /**
         * @brief GetDispData
         * @param[out] o_faces display faces
         * @param[out] o_vertex vertex
         */
        struct alignas(4) FaceAttr
        {
            Ncti_UInteger elemIndex;
            Ncti_UInteger edge0Number : 4;
            Ncti_UInteger edge1Number : 4;
            Ncti_UInteger edge2Number : 4;
            Ncti_UInteger edge3Number : 4;
            Ncti_UInteger faceIndex : 4;
            Ncti_UInteger dimention : 4;
            Ncti_UInteger faceCount : 4;
            Ncti_UInteger initCount : 4;
        };
        void UpdateFaceCount(std::vector<FaceAttr>&o_faces)const;

        /**
         * @brief GetDispFace
         * */
        std::vector<Ncti_UInteger> GetDispFace(Ncti_UInteger i_number, Ncti_UInteger i_findex)const;

        /**
         * @brief HasElement
         * @param [in] i_eid element number
         * @return if element exist
         * */
        Ncti_Boolean HasElement(Ncti_UInteger i_eid)const;

        /**
         * @brief get element data from element number
         * @param [in] i_eid element number
         * @return element object
         * @see NctiMeshElement
         * */
        NctiMeshElement GetElement(Ncti_UInteger i_eid)const;

        /**
         * @brief get pick info
         * @return pick set
         * @see NctiGridPickSet
         * */
        const std::set<NctiGridPickSet>& GetPickDatas()const;

        /**
         * @brief judge pick info
         * @retval true not empty
         * @retval false empty
         * */
        bool HasAnyPicked()const;

        /**
         * @brief auto merge node in mesh.the tolerance is 1e-6
         * @return merged element nodes count
         * */
        Ncti_UInteger MergeNode();

        /**
         * @brief get picked element numbers
         * @param[out] o_elemNumber element numbers picked
         * */
        void GetPickedCells(std::vector<Ncti_UInteger>&o_elemNumber)const;

        /**
         * @brief clear pick info
         * */
        void ClearPick();

        /**
         * @brief set pick info for highlight
         * @param i_set cells to be pick
         * @param status 0:set,-1:minus,1:add;
         * @retval:true means changed
         * @retval:false means the same
         * @see NctiGridPickSet
         * */
        bool SetPickDatas(const std::set<NctiGridPickSet>& i_set, const ModifierKeys& i_status);

        /**
         * @brief SetMeshAndModel
         * @warning internal usage. not use it!
         * */
        void SetModelBody(NctiDisplayModelBody* i_pModelBody);
        void SetGridMesh(NctiDisplayGridMesh* i_mesh);
        void SetRenderItem(NctiRenderUnstructureItem* i_mesh);

        /**
         * @brief SetInstanceId
         * @warning internal usage. not use it!
         * */
        void SetInstanceId(const std::pair<Ncti_Integer, Ncti_Integer>&)const;
        Ncti_Integer GetGeomId()const;
        Ncti_Integer GetInsId()const;

    private:
        struct PrivateData;
        PrivateData* _d;
    };

};

