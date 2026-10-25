#ifndef NctiDesignModelObject_H
#define NctiDesignModelObject_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignModelObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignModelObject)
	public:
		virtual ~NctiDesignModelObject();
		virtual void Init();
		virtual std::string GeneratePyScript();
		virtual std::vector<std::string> GeneratePyScripts();
		void SetObjectName(std::string name);
		const std::string GetObjectName();
	protected:
		std::string m_strCmd;				//创建最终对象命令
		std::string m_strObjectName;		//创建对象name
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignModelObject_H
