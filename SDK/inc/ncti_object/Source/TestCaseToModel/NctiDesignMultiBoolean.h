#ifndef NctiDesignMultiBoolean_H
#define NctiDesignMultiBoolean_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignMultiBoolean : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignMultiBoolean)

	public:
		enum BOOLEAN_TYPE
		{
			BOOLEAN_UNKNOWN = -1,
			BOOLEAN_UNIT = 0,
			BOOLEAN_CUT = 1,
			BOOLEAN_INTERSECT = 2
		};
		virtual ~NctiDesignMultiBoolean();
		virtual void Init();
		virtual std::string GeneratePyScript();
		BOOLEAN_TYPE GetBooleanType() { return m_BooleanType; }
		void SetBooleanType(BOOLEAN_TYPE BooleanType);
		const std::vector<std::string>& GetBaseModelNames() { return m_BaseModelNames; }
		const std::vector<std::string>& GetToolModelNames() { return m_ToolModelNames; }
	private:
		BOOLEAN_TYPE m_BooleanType;
		std::vector<std::string> m_BaseModelNames;
		std::vector<std::string> m_ToolModelNames;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignMultiBoolean_H
