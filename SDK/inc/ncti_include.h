#ifndef Ncti_include_H
#define Ncti_include_H
#include <vector>
#include <math.h>
#include <string>

namespace NCTI
{
	struct NctiMeshData
	{
		std::vector<float> positions;
		std::vector<unsigned int> triangles;
		std::vector<float> normals;
		std::vector<float> uvs;
		char* ModelId{nullptr};
		std::string Name;
	};
	struct NctiMeshDataPt
	{
		int nType;
		const float* positions;
		const int* triangles;
		const float* normals;
		const float* uvs;
		int positionsSize;
		int trianglesSize;
		int normalsSize;
		int uvsSize;
		void* obj;
		NctiMeshDataPt()
		{
			positions = nullptr;
			triangles = nullptr;
			normals = nullptr;
			uvs = nullptr;
			positionsSize = 0;
			trianglesSize = 0;
			normalsSize = 0;
			uvsSize = 0;
			nType = -1;//-1 or 3: -1 not include mesh type.
			obj = nullptr;
		}
	};
	struct NctiMeshPacked
	{
		unsigned char* m_packed;
		unsigned char m_buf[4] = { 0 };
		unsigned char m_Props[5] = { 0 };
		unsigned int m_bufSize;
		NctiMeshPacked()
		{
			m_packed = nullptr;
		}
	};
}

extern "C"
{
    typedef struct
    {
        std::vector<std::string> DracoFileNameVec;
        std::vector<std::string> DracoModelIdVec;
        std::vector<std::string> USDMD5Vec;
    }DracoDataInfor;
};

#endif // 

