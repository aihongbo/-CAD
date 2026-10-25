#ifndef Nctiuuid_h
#define Nctiuuid_h
#include "ncti_dcl_base.h"
namespace NCTI
{
	/**
	* @brief create a uuid, support windows and linux
	*/
	class DECL_NCTI_BASE Nctiuuid
	{
	public:
		/**
	    * @brief create a uuid, support windows and linux
		* @param[out] o_uuid, return the uuid , it need to be deleted
	    */
		static bool generate(char*& o_uuid);
	};
}
#endif
