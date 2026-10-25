#ifndef NctiDisplayVolumeMesh_H
#define NctiDisplayVolumeMesh_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayMeshObject.h"
namespace NCTI
{
	class NctiDisplayModelBody;
	class NctiRenderGeometryItem;
    class NctiRenderUnstructureItem;
	class NctiMeshBody;
    class NctiBaseView;
    class NctiDisplayOutput;

	class DECL_NCTI_OBJECT NctiDisplayGridMesh : public NctiDisplayMeshObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGridMesh)
	public:
		virtual ~NctiDisplayGridMesh();

        EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller)override;
		EnumNctiResult UpdateDisplay()override;

        void Compress(int)override;
        void UnCompress(int)override;
		int InitPackedData()override;

        EnumNctiResult ActivateData(
			NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer, 
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec)override;

        void ShowOrHideAllCell(Ncti_Boolean i_boo);
        void FindNode(NctiRenderGeometryItem* i_pRender, std::vector<NCTI_MODEL_TAG>& o_NodeVec);
        void GetNodeCoord(std::vector<Ncti_UInteger>& i_NodeVec, std::vector<Ncti_Float>& o_FloatVec);
        void FindElementFromTag(Ncti_UInteger i_tag,std::vector<Ncti_UInteger>&o_elemNumbers)const;

        void SetMeshData(const std::vector<Ncti_Float>& pos,
			const std::vector<NctiElementType>& elemType,
            const std::vector<Ncti_UInteger>& elemTag,
            const std::vector<Ncti_UInteger>& elemData, 
            NctiDisplayModelBody* i_pModelBody);

        void UpdateMergeNode();
        void UpdateFaceCount();
		
        bool IsShowNumber()const;
        bool IsShowVertex()const;

		void AddOutputs(NctiDisplayOutput* i_Output);
		const std::vector<NctiDisplayOutput*>&  GetOutputs() const;

        NctiRenderUnstructureItem* GetGeomtry()const;
        NctiDisplayModelBody* GetModelBody()const;
        NctiMeshBody* GetMeshBody(Ncti_Boolean force = false);

    private:

		NCTI_READ_AND_WRITE_VERSION_FUN(1);
		NCTI_VERSION(1, Ncti_Long, m_unused, sd_read_long);
		NCTI_VERSION(1, Ncti_Long, m_PackedSubNum, sd_read_long);
		NCTI_VERSION(1, Ncti_UInteger, m_StartNode, sd_read_long);
		NCTI_VERSION(1, Ncti_UInteger, m_StartElement, sd_read_long);
		NCTI_VERSION_MODIFY(1, std::vector<Ncti_Float>, m_Position, sd_read_packed);
		NCTI_VERSION_MODIFY(1, std::vector<Ncti_UInteger>, m_ElemTag, sd_read_packed);
		NCTI_VERSION_MODIFY(1, std::vector<NctiElementType>, m_ElemType, sd_read_packed);
		NCTI_VERSION_MODIFY(1, std::vector<Ncti_UInteger>, m_ElemData, sd_read_packed);
		NCTI_VERSION_OBJECT(1, NctiDisplayModelBody*, m_ModelBody, sd_read_long);
		NCTI_VERSION_OBJECT(1, std::vector<NctiDisplayOutput*>, m_Outputs, sd_read_size);

        void CompressTag(int);
        void CompressPosition(int);
        void CompressType(int);
		void CompressElement(int);

        void UnCompressTag(int);
        void UnCompressPosition(int);
        void UnCompressType(int);
        void UnCompressElement(int);

    private:
        std::vector<NctiMeshPacked> m_MeshPackedTagVec;
		std::vector<NctiMeshPacked> m_MeshPackedTypeVec;
        std::vector<NctiMeshPacked> m_MeshPackedPosVec;
        std::vector<NctiMeshPacked> m_MeshPackedElemVec;

        Ncti_Boolean m_PackedIsSame{false};//no save
		NctiRenderUnstructureItem* m_grid{nullptr};//no save
		std::vector<Ncti_Long> m_OutputsIndex;//no save
        NctiMeshBody* m_body{ nullptr };//no save
        bool m_needUpdate{true};
	};
}

#endif
