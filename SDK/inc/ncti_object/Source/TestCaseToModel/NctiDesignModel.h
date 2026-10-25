#ifndef NctiDesignModel_H
#define NctiDesignModel_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class NctiDisplayModelBody;
	class DECL_NCTI_OBJECT NctiDesignModel : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignModel)
	public:
		virtual ~NctiDesignModel();
		virtual void Init();
		virtual std::string GeneratePyScript();
		void AddFaceID(NctiDisplayModelBody* pObject, Ncti_Long faceID, Ncti_Long dialogID);
		void Clear();
		const std::vector<NctiDisplayModelBody*>& GetModelObjects() { return m_ModelObjectVec; }
		const std::vector<Ncti_Long>& GetFaceIDs() { return m_FaceIDVec; }
		const std::vector<Ncti_Long>& GetDialogIDs() { return m_DialogIDVec; }
	private:

		std::vector<NctiDisplayModelBody*> m_ModelObjectVec;
		std::vector<Ncti_Long> m_FaceIDVec;
		std::vector<Ncti_Long> m_DialogIDVec;
		std::vector<Ncti_Size> m_ModelObjectIDVec;//no save
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};

}
#endif // !NctiDesignModel_H
