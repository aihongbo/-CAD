#ifndef NctiDisplayFrequencyStep_H
#define NctiDisplayFrequencyStep_H
#include "NctiDisplayFBStep.h"
#include "NctiPhyParaDef.h"
#include <NctiMeshManager.h>
namespace NCTI
{
	//模态分析步	
	/**
	* @brief The frequency step object
	*/
	class DECL_NCTI_OBJECT NctiDisplayFrequencyStep : public NctiDisplayFBStep
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayFrequencyStep)
	public:
		virtual ~NctiDisplayFrequencyStep();
	public:
		virtual void Init();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
