#ifndef NctiDisplayPolyMesh_H
#define NctiDisplayPolyMesh_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayMeshObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayPolyMesh : public NctiDisplayMeshObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayPolyMesh)
	public:
		virtual ~NctiDisplayPolyMesh();

        EnumNctiResult UpdateDisplay()override;
        EnumNctiResult ActivateData(
            NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec)override;

        void Compress(int)override;
        void UnCompress(int)override;
        void CompressTri(int)override;
        void UnCompressTri(int)override;
        int InitPackedData()override;

    public:
        void SetRenderMeshDataForDisplay(
            const std::vector<Ncti_Float>& positions,
            const std::vector<Ncti_UInteger>& triangles,
            const std::vector<Ncti_Float>& normals);

        void SetNormalVec(const std::vector<Ncti_Float>& normals);
        void SetUV(const std::vector<Ncti_Float>& uv);
        void SetPositions(const std::vector<Ncti_Float>& i_positions);

        const std::vector<Ncti_Float>& GetUV();
        const std::vector<Ncti_Float>& GetNormals();
        const std::vector<Ncti_Float>& GetPositions();
        const std::vector<Ncti_UInteger>& GetTriangles();

    private:
        NCTI_READ_AND_WRITE_VERSION_FUN(1)
            NCTI_VERSION(1, Ncti_Long, m_PackedSubNum, sd_read_long)
            NCTI_VERSION_MODIFY(1, std::vector<Ncti_Float>, m_uv, sd_read_packed)
            NCTI_VERSION_MODIFY(1, std::vector<Ncti_Float>, m_normals, sd_read_packed)
            NCTI_VERSION_MODIFY(1, std::vector<Ncti_Float>, m_positions, sd_read_packed)
            NCTI_VERSION_MODIFY(1, std::vector<Ncti_UInteger>, m_triangles, sd_read_packed)

        void CompressUV(int);
        void CompressPosition(int);
        void CompressNormal(int);
        void UnCompressUV(int);
        void UnCompressPosition(int);
        void UnCompressNormal(int);
        void UnCompressTriangle(int);
        void CompressTriangle(int);

        std::vector<NctiMeshPacked> m_MeshPackedUVVec;
        std::vector<NctiMeshPacked> m_MeshPackedPosVec;
        std::vector<NctiMeshPacked> m_MeshPackedNorVec;
        std::vector<NctiMeshPacked> m_MeshPackedTriVec;
        Ncti_Boolean m_PackedIsSameUV;
        Ncti_Boolean m_PackedIsSamePos;
        Ncti_Boolean m_PackedIsSameNor;
        Ncti_Boolean m_PackedIsSameTri;
	};
}

#endif
