#ifndef NctiTestCaseToModelManage_H
#define NctiTestCaseToModelManage_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
namespace NCTI
{
	
	/**
	* @brief Design model manage
	*/
	class DECL_NCTI_OBJECT NctiTestCaseToModelManage : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiTestCaseToModelManage)
	public:
		virtual ~NctiTestCaseToModelManage();
		virtual void Init();

		
		/**
		* @brief Get the next name
		* @return name
		*/
		std::string GetNextModelName();
	private:
		std::vector<NctiDisplayObject*> m_TransfermodelVec;
		std::vector<Ncti_Long> m_TransfermodelIDVec;
		Ncti_Long m_ModelID;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiTestCaseToModelManage_H
