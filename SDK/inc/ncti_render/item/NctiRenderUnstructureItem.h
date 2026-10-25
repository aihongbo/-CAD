#ifndef NctiRenderUnstructureItem_H
#define NctiRenderUnstructureItem_H
#include "NctiRenderGeometryItem.h"
#include <ncti_base.h>
#include <NctiMeshManager.h>

namespace NCTI
{
    class NctiMeshBody;
    class NctiViewerRenderer;

    /**
     * @brief Unstructured grid Render Object
     */
	class DECL_NCTI_RENDER NctiRenderUnstructureItem : public NctiRenderGeometryItem
	{
        NCTI_RENDER_FUNCTIONS(NctiRenderUnstructureItem);
    public:
        /**
         * @brief construct
         * @param[in] body mesh body
         */
		NctiRenderUnstructureItem(const NctiMeshBody* body);
        ~NctiRenderUnstructureItem();

        /**
         * @brief UpdateMergeNode
         */
        void UpdateMeshModify(GeomAttrType);
        /**
         * @brief Get bounding box.completion virtual function
         */
        bool GetBox(NctiViewerRenderer* i_pViewerRenderer, NctiPosition& o_Max, NctiPosition& o_Min)override;
        /**
         * @brief clone self.completion virtual function
         */
		NctiRenderGeometryItem* clone()const override;

        /**
         * @brief completion virtual function
         * @return face count
         */
        Ncti_Size GetVertexCount()const override;

        /**
         * @brief get vertex position
         * @param[in] index vertex index
         */
        NctiPosition GetPosition(int index)const override;

        /**
         * @brief GetPositions
         */
        const VertexDataType& GetPositions()const override;

        /**
         * @brief get the mesh body
         * @see NctiMeshBody
         */
        NctiMeshBody* GetMeshBody()const;

        /**
         * @brief get the vertex size
         */
        Ncti_Size GetVertSize()const;

        /**
         * @brief get element number
         */
        Ncti_Size GetCellSize()const;
        
        /**
         * @brief clear the highlight
         * @param[in] isprev only clear preview highlight
         */
        bool InitHightlight(bool isprev = false);

        /**
         * @brief set the highlight
         * @param[in] set the pick set to highlight
         * @param[in] isPreview preview highlight
         */
        bool SetHighlight(const std::set<NctiGridPickSet>& set,Ncti_Boolean isPreview=false);

        /**
         * @brief if has some highlight
         */
        bool HasAnyHighLight()const;

        /**
         * @brief SetShowVertex
         */
        bool SetShowVertex(Ncti_Boolean show);

        /*
        * @brief ShowVertex
         * @return true for show vertex,else not show vertex
         *
        */
        bool ShowVertex()const;

        /**
         * @brief SetShowNumber
         */
        bool SetShowNumber(Ncti_Boolean show);

        /*
        * @brief ShowNumber
         * @return true for show number,else not show number
         *
        */
        bool ShowNumber()const;

        /**
         * @brief set the element visible
         * @param[in] cellNumber the element numbers
         */
        bool SetCellVisible(const std::vector<Ncti_UInteger>&cellNumber,bool vis);

        /**
         * @brief vis all the element
         */
        bool InitCellVisible(bool vis);

        /**
         * @brief vis all the element
         */
        bool FilterVisible(std::set<NctiGridPickSet>& vis);

        /**
         * @brief set element color
         * @param[in] cellNumber element to set color
         * @param[in] color 0 to 1 means blue to red,other value represent colorless
         *            empty mean all the element the same color      
         */
        bool SetCellColor(const std::vector<Ncti_UInteger>& cellNumber, const std::vector<float> &color);

        /**
         * @brief clear element color
         * @param[in] cellNumber element to clear color. empty means clear all element color
         */
        bool ClearCellColor(const std::vector<Ncti_UInteger>& cellNumber);

        /**
         * @brief HasCellColor
         */
        Ncti_Boolean HasCellColor()const;

        /**
         * @brief set node color
         * @param[in] nodeNumber node to set color
         * @param[in] color 0 to 1 means blue to red,other value represent colorless
         *            empty mean all the element the same color
         */
        bool SetNodeColor(const std::vector<Ncti_UInteger>& nodeNumber, const std::vector<float> &color);

        /**
         * @brief clear element color
         * @param[in] nodeNumber element to clear color. empty means clear all node color
         */
        bool ClearNodeColor(const std::vector<Ncti_UInteger>& nodeNumber);

        /**
         * @brief save current grid color
         */
        void HoldGridColor();

        /**
         * @brief restore the color saved
         */
        void RestorGridColor();
        
        /**
         * @brief get face index data
         * @details internal usage
         * @param[out] o_byte attr size
         * @return vertex:uint4,element index
         */
        const Ncti_Byte* GetFaceIndex(Ncti_UInteger& o_byte)const;

        /**
         * @brief get face attar data
         * @details internal usage
         * @param[out] o_byte attr size
         * @return vertex:uint2,face,FaceAttr
         */
        const Ncti_Byte* GetFaceAttr(Ncti_UInteger& o_byte)const;

        /**
         * @brief get cell attar data
         * @details internal usage
         * @param[out] o_byte attr size
         * @return uniform:uint1,cell color,std::vector<ElemAttr>
         */
        const Ncti_Byte* GetCellAttr(Ncti_UInteger& o_byte)const;

        /**
         * @brief get node position data
         * @details internal usage
         * @param[out] o_byte attr size
         * @return uniform:float3,vertex position
         */
        const Ncti_Byte* GetNodePosition(Ncti_UInteger& o_byte)const;

        /**
         * @brief get node color data
         * @details internal usage
         * @param[out] o_byte attr size
         * @return uniform:float1,node color
         */
        const Ncti_Byte* GetNodeColor(Ncti_UInteger& o_byte)const;

        /**
         * @brief init boundary
         */
        void InitBondary();

    private:
        class PrivateData;
        PrivateData* _d;
	};
}
#endif // !NctiRenderMarkerItem_H
