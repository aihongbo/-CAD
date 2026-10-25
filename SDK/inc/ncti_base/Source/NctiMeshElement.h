#pragma once
#include "ncti_base.h"
#include <NctiPosition.h>
#include "NctiVector.h"
#include <vector>

namespace NCTI
{
    /**
    * @brief mesh element fro data exchange
    */
    class DECL_NCTI_BASE NctiMeshElement {
    public:

        /**
        * @brief construct mesh element
        * @param[in] i_type element type
        * @param[in] i_data element node index array
        * @param[in] i_tag element tag
        * @param[in] i_bias first node number
        */
        NctiMeshElement(NctiElementType i_type, Ncti_UInteger i_tag,const Ncti_UInteger* i_data, Ncti_UInteger i_bias);

        /**
        * @brief get element type
        * @return NctiElementType
        */
        NctiElementType Type()const;

        /**
        * @brief get element tag
        */
        Ncti_UInteger Tag()const;

        /**
        * @brief get all node numbers
        * @details the order is in T/DISA 1231.21-2024,7.2.2.2
        * @param[out] o_nodes NodeNumbers in order
        */
        void AllNode(std::vector<size_t>&o_nodes)const;
        std::vector<Ncti_UInteger> AllNode()const;

        /**
        * @brief replace node number
        * @param[in] i_from node number
        * @param[in] i_to node number
        * @return replace count
        */
        Ncti_UInteger ReplaceNode(Ncti_UInteger i_from, Ncti_UInteger i_to);

        /**
        * @brief get node count
        */
        Ncti_Size NumberOfVertex()const;

        /**
        * @brief get sub face count
        */
        Ncti_Size NumberOfFace()const;

        /**
        * @brief get sub edge count
        */
        Ncti_Size NumberOfEdge()const;

        /**
        * @brief if is high order element
        */
        Ncti_Boolean HighOrder()const;

        /**
        * @brief Dimention
        */
        Ncti_UInteger Dimention()const;

        /**
        * @brief the sub face hash
        * @param[in] i_index face index
        */
        size_t HashFace(Ncti_UInteger i_index)const;

        /**
        * @brief the sub edge hash
        * @param[in] i_index edge index
        */
        size_t HashEdge(Ncti_UInteger i_index)const;

        /**
        * @brief get sub face nodes
        * @param[in] i_index face index
        * @param[out] o_face all nodes number in the face
        */
        void SubFace(Ncti_UInteger i_index, std::vector<Ncti_UInteger>& o_face)const;

        /**
        * @brief get sub face high nodes
        * @param[in] i_index face index
        * @param[out] o_face high order nodes number in the face
        */
        void  HighFace(Ncti_UInteger i_index, std::vector<Ncti_UInteger>& o_face)const;

        /**
        * @brief get sub face low nodes
        * @param[in] i_index face index
        * @param[out] o_face low order nodes number in the face
        */
        void  LowFace(Ncti_UInteger i_index, std::vector<Ncti_UInteger>& o_face)const;

        /**
        * @brief get sub face with out number
        * @details used in display
        * @param[in] i_index face index
        * @param[out] o_face nodes index
        * @return face vertex count
        */
        int  DispFace(Ncti_UInteger i_index, std::vector<Ncti_UInteger>& o_face)const;

        /**
        * @brief get sub face nodes
        * @param[in] i_index face index
        * @param[out] o_face all nodes number in the face
        */
        void SubEdge(Ncti_UInteger i_index, std::vector<Ncti_UInteger>& o_edge)const;

        /**
        * @brief get all element edge from sub face 
        * @param[in] findex face index
        * @return the edge numbers in th element face
        */
        const std::vector<Ncti_UInteger>& SubFaceEdges(Ncti_UInteger findex)const;

        /**
        * @brief get edge index in sub face from element edge 
        * @param[in] findex face index
        * @param[in] enumber the edge number in the element
        * @return the edge index in th face
        */
        int SubFaceEdgeIndex(Ncti_UInteger findex, Ncti_UInteger enumber)const;

        /**
         * @brifef get center for element or sub face or sub edge
         * @param [in] subid subid for edge or face.-1 for all element
         * @param [in] isedge subid is edge or face
         * @return center
         */
        NctiPosition GetCenter(Ncti_UInteger subid, bool isedge)const;

        /**
         * @brifef Get Face Nomal
         * @param [in] findex subid for face
         * @param [out] o_norm
         */
        bool GetFaceNomal(Ncti_UInteger findex, NctiVector& o_norm)const;

        /**
         * @brifef Get edge direction
         * @param [in] eindex subid for edge
         * @param [in] i_node edge contain node. -1 for no constrain
         * @param [out] o_dir
         */
        bool GetEdgeDirection(Ncti_UInteger eindex, NctiVector& o_dir,int i_node = -1)const;

    private:
        Ncti_UInteger m_bias{ 0 };
        NctiElementType m_type;
        Ncti_UInteger m_tag{ 0 };
        const Ncti_UInteger* m_data{ nullptr };
    };
};

