#ifndef NctiDesignPrism_H
#define NctiDesignPrism_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignPrism : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignPrism)
	public:
		virtual ~NctiDesignPrism();
		virtual void Init();
		virtual std::vector<std::string> GeneratePyScripts();
		void SetLengthVector(NctiVector vec);
		std::string GetFaceName();
	private:
		NctiVector m_LengthVector;					//拉伸长度向量
		std::vector<std::string> m_SubCurveCmds;	//子命令：创建线条、封闭曲线
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignPrism_H
