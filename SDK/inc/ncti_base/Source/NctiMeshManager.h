#pragma once
#include "ncti_base.h"
#include <NctiPosition.h>
#include "NctiMeshBody.h"
#include "functional"
#include <string>
#include <set>

namespace NCTI
{
    class DECL_NCTI_BASE NctiBaseInlinePub {
    public:

        Ncti_Integer ElementDim(int tp);

        Ncti_Integer ElementOrder(int tp);

        Ncti_Integer ElementFace(int tp);

        Ncti_Integer ElementEdge(int tp);

        Ncti_Integer ElementVert(int tp);

        std::string ElementName(int tp);
    };

    class NctiDisplayModelBody;
    class NctiDisplayGridMesh;

    /**
    * @brief mesh manager
    */
    class DECL_NCTI_BASE NctiMeshManager
    {
    public:
        static NctiMeshManager& Instance();
        ~NctiMeshManager();

        /**
       * @brief clear all mesh
       */
        void Clear();

        /**
       * @brief Add Mesh Data to manager,internal calculate the number
       * @details used in NctiDisplayGridMesh for display.
       * @return the mesh body
       * @param[in] i_pos,positions
       * @param[in] i_type,element types
       * @param[in] i_data,element datas
       * @param[in] i_tag,element tags
       * @param[in] i_copyData copy mesh data to body
       * @see NctiDisplayGridMesh
       */
        NctiMeshBody* AddMeshData(
            const std::vector<Ncti_Float>& i_pos,
            const std::vector<NctiElementType>& i_type,
            const std::vector<Ncti_UInteger>& i_data,
            const std::vector<Ncti_UInteger>& i_tag,
            Ncti_Boolean i_copyData);

        /**
       * @brief Set Mesh Data to manager,set the number
       * @details used in NctiDisplayGridMesh for load file.
       * @return the mesh body
       * @param[in] pos node positions
       * @param[in] type element types
       * @param[in] data element data
       * @param[in] tag element tags
       * @param[in] i_startNode, first node number
       * @param[in] i_startElem, first element number
       * @see NctiMeshBody
       */
        NctiMeshBody* SetMeshData(
            const std::vector<Ncti_Float>* pos,
            const std::vector<NctiElementType>* type,
            const std::vector<Ncti_UInteger>* data,
            const std::vector<Ncti_UInteger>* i_tag,
            const Ncti_UInteger& i_startNode,
            const Ncti_UInteger& i_startElem);

        /**
       * @brief Remove Mesh Data to manager
       * @details used in NctiDisplayGridMesh for deconstruction
       * @param[in] i_body, the mesh body
       * @see NctiDisplayGridMesh
       */
        void RemoveMeshData(NctiMeshBody* i_body);

        /**
       * @brief Find mesh body form model
       * @param[in] model, the geomtry model
       * @see NctiDisplaySetGeometry
       */
        void LoopBodyProcess(std::function<bool(NctiMeshBody*)>)const;

        /**
       * @brief Find mesh body form pick info
       * @param[in] i_pick, element pick info
       * @see NctiMeshBody
       */
        NctiMeshBody* FindBodyFromPick(const NctiGridPickSet i_pick);

        /**
       * @brief get node position from node number
       * @param[in] i_nid, node number
       * @param[out] o_pos, NctiPosition
       */
        bool GetVertex(Ncti_UInteger i_nid, NctiPosition&o_pos);

        /**
       * @brief get node position from element number
       * @param[in] i_cid, element number
       * @return NctiMeshElement
       */
        NctiMeshElement GetElement(Ncti_UInteger i_cid);
        
    private:
        NctiMeshManager();
        NctiMeshBody* FindBodyFromVertex(Ncti_UInteger e_nid);
        NctiMeshBody* FindBodyFromElement(Ncti_UInteger e_cid);

        std::set<NctiMeshBody*> m_data;
        std::vector<Ncti_UInteger> m_UsedNode;
        std::vector<Ncti_UInteger> m_UsedElement;
        NctiMeshBody* m_lastBody{nullptr};
    };
};