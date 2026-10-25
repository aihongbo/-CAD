#ifndef NctiSystemPubFun_H
#define NctiSystemPubFun_H
#include "ncti_dcl_base.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "ncti_base.h"
#include "ncti_include.h"
namespace NCTI
{
	class DECL_NCTI_BASE NctiSystemPubFun
	{
	public:
		NctiSystemPubFun();
		~NctiSystemPubFun();
	public:
		//static FILE* readfileByRB(const char* UTF8);
		static Ncti_Boolean WriteCTM(
			const char* i_FullFileName,
			Ncti_Size i_VertexCount,
			Ncti_Size i_TriangleCount,
			Ncti_Size i_UVMapCount,
			Ncti_Size i_Normals,
			const std::vector<NctiMeshPacked>& i_MeshPackedUVVec,
			const std::vector<NctiMeshPacked>& i_MeshPackedPosVec,
			const std::vector<NctiMeshPacked>& i_MeshPackedNorVec,
			const std::vector<NctiMeshPacked>& i_MeshPackedTriVec
			);
	public:
		static void api_ctmStreamWrite(FILE* f,  const void* aBuf, Ncti_UInteger aCount);
		static void api_ctmStreamWriteUINT(FILE* f, Ncti_UInteger i_aValue);
		static void api_ctmStreamWriteSTRING(FILE* f, const char* aValue);
	public:
		static void getMemoryInfo(Ncti_LongLong& o_UsedPhysicalMemory);
		static Ncti_Double getCpuUsage();
	};
}
#endif // !NctiSystemPubFun_H
