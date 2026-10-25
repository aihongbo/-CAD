#pragma once
#include "ncti_base.h"
#include <NctiPosition.h>
#include <set>

namespace NCTI
{
    /**
    * @brief grid mesh pick set for a cell/an edge/ a vertex /a face 
    */
    class DECL_NCTI_BASE NctiGridPickSet
    {
    public:
        NctiGridPickSet();

        /**
        * @brief construct from tag
        * @param[in] tag the pick set internal data
        * @see NctiDisplayGridMesh::FindNode
        */
        NctiGridPickSet(NCTI_MODEL_TAG tag);

        /**
        * @brief construct from tag
        * @param[in] tag the pick set internal data
        * @see NctiDisplayGridMesh::FindNode
        */
        NctiGridPickSet(Ncti_LongLong tag);

        /**
        * @brief construct from pick info
        * @param[in] tp the pick set type
        * @param[in] num the pick set number.
                     vertex number for type ELEM_Vertex else element number cell/face/edge
        * @param[in] subnum the sub index for ELEM_Face or ELEM_Edge
        * @see NctiSelectType
        */
        NctiGridPickSet(NctiSelectType tp, Ncti_UInteger num, Ncti_UInteger subnum);

        /**
        * @brief whether the pick set is valid
        * @details if the not use the internal data construct,will invalid
        * @return true for valid
        */
        bool Valid()const;

        /**
        * @brief pick set type
        * @return NctiSelectType
        */
        std::string String()const;
        std::wstring StringW()const;

        /**
        * @brief pick set type
        * @return NctiSelectType
        */
        NctiSelectType Type()const;

        /**
        * @brief pick set Number
        * @return vertex number for type ELEM_Vertex else element number cell/face/edge
        */
        Ncti_UInteger Number()const;

        /**
        * @brief pick set Number
        * @return face index for type ELEM_Face, edge index for type ELEM_Edge
        */
        Ncti_UInteger SubNumber()const;

        /**
        * @brief the internal data
        */
        Ncti_LongLong RawData()const;

        /**
        * @brief the internal data
        * @details for external data change
        * @see GetNameFromSelManager
        */
        NCTI_MODEL_TAG Tag()const;

        /**
        * @brief convert this pick to vertex pick in Mesh
        * @param[out] o_vertex Vertex picks
        */
        void ConvertVertex(std::set<NctiGridPickSet>&o_vertex)const;

        /**
        * @brief convert this pick to Cell pick in Mesh
        * @param[in] convert3d whether convert to 3d cell from face/edge/vertex
        * @param[out] o_cell Cell picks
        */
        void ConvertCell(std::set<NctiGridPickSet>& o_cell)const;

        /**
        * @brief convert this pick to vertex Edge in Mesh
        * @param[in] convert3d whether convert to 3d cell from face/edge/vertex
        * @param[out] o_edge Edge picks
        */
        void ConvertEdge(std::set<NctiGridPickSet>& o_edge)const;

        /**
        * @brief convert this pick to Face pick in Mesh
        * @param[in] convert3d whether convert to 3d cell from face/edge/vertex
        * @param[out] o_face Face picks
        */
        void ConvertFace(std::set<NctiGridPickSet>& o_face)const;

        bool operator<(const NctiGridPickSet&)const;
        bool operator==(const NctiGridPickSet&)const;
        bool operator!=(const NctiGridPickSet&)const;

    private:
        Ncti_LongLong m_tag;
    };

    class NctiRenderGeometryItem;
    class NctiRenderSegmentItem;

    /**
    * @brief pick result for render
    * @see NctiBaseView::PointSelectOnSegment,NctiBaseView::BoxSelectOnSegment
    */
    struct DECL_NCTI_BASE NctiPickSelectObjectStr
    {
        Ncti_Double t = 1;                          ///picked depth
        NctiRenderGeometryItem* GeoItem{ nullptr }; ///picked geometry item
        NctiRenderSegmentItem* InsItem{ nullptr };  ///picked instance key
        NctiPosition model{ 0,0,0 };                ///picked position in world
        std::set<NctiGridPickSet> cells;            ///picked cell for grid mesh
    };
};

