#ifndef NctiParametricObject_H
#define NctiParametricObject_H
#include "ncti_base.h"
#include "ncti_dcl.h"
#include "NctiDisplayObject.h"
namespace NCTI
{
	class NctiDisplayDocCustomContainer;
	class DECL_NCTI NctiParametricObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiParametricObject)
	public:
		virtual ~NctiParametricObject();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
	protected:
		NCTI_VERSION(1, std::vector<NctiDisplayObject*>, m_InputObject, sd_read_size);
		NCTI_VERSION(1, std::vector<NctiDisplayObject*>, m_Result, sd_read_size);
		NCTI_VERSION(1, std::vector<NCTI_MODEL_TAG>, m_InputBody, sd_read_size);
		std::vector<Ncti_Size> m_bodyIndex;
		std::vector<Ncti_Size> m_InputObjIndex;
		std::vector<Ncti_Size> m_ResObjectIndex;
	public:
		void SetInputObj(std::vector<NctiDisplayObject*> i_pInputObject);
		void SetResult(std::vector<NctiDisplayObject*> i_pRes);
		EnumNctiResult SetInputBody(NctiDisplayObject* i_pCustomContainer, std::vector<NCTI_MODEL_TAG> i_pBody);
		void SetInputBodyIndex(std::vector<Ncti_Size> i_index);

		std::vector<NctiDisplayObject*> GetInputObj();
		std::vector<NctiDisplayObject*> GetResult();
		std::vector<NCTI_MODEL_TAG> GetInputBody();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)



	};

}
#endif // !NctiParametricObject_H
