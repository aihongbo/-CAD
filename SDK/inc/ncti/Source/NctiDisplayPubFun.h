#ifndef NctiDisplayPubFun_H
#define NctiDisplayPubFun_H
#include "ncti.h"
#include <vector>
namespace NCTI
{
	class NctiDisplayDocCustomContainer;
	class NctiDisplayObject;
	/**
	* @brief something function, internal use
	*/
	class DECL_NCTI NctiDisplayPubFun
	{
	public:
		NctiDisplayPubFun();
		~NctiDisplayPubFun();
	public:
		static NctiDisplayDocCustomContainer* GetDocCustomContainerFromObject(NctiDisplayObject* i_pDisplayObject);
		static Ncti_Boolean GetAllBody(NctiDisplayDocCustomContainer* i_pCustomContainer, std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec);
	};
}
#endif
