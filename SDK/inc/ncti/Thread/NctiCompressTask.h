#ifndef NctiCompressTask_H
#define NctiCompressTask_H
#include "NctiThreadTask.h"
#include "ncti_include.h"
#include "ncti_dcl.h"
namespace NCTI
{
	class NctiCompress;
	class NctiDisplayMeshObject;
	class NctiDisplayObjectList;
	class NctiDisplayObject;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiCompressTask : public NctiThreadTask
	{
	public:
		NctiCompressTask();
		virtual ~NctiCompressTask();
	public:
		enum TaskType
		{
			Nothing,
			save_compress,
			read_compress,
			save_compress_tri,
			read_compress_tri
		};
	public:
		virtual NctiThreadAny run();
	private:
		Ncti_Integer m_PackedSubNumIndex;
		TaskType m_Type;
		std::vector<NctiDisplayObject*> m_ObjVec;
	public:
		void save_compress_data(const std::vector<NctiDisplayObject*>& i_ObjVec, Ncti_Integer i_num);
		void read_compress_data(const std::vector<NctiDisplayObject*>& i_ObjVec, Ncti_Integer i_num);

		void save_compress_tri_data(const std::vector<NctiDisplayObject*>& i_DisplayMeshObjectVec, Ncti_Integer i_num);
		void read_compress_tri_data(const std::vector<NctiDisplayObject*>& i_DisplayMeshObjectVec, Ncti_Integer i_num);
	public:
		static void save_compress_task(NctiDisplayObjectList* i_pObjList);
		static void read_compress_task(NctiDisplayObjectList* i_pObjList);
	};
}
#endif
