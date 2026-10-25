#ifndef NctiBaseDB_H
#define NctiBaseDB_H
#include "ncti.h"
namespace NCTI
{
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiBaseDB : public NCTI_BASE_CLASS
	{
	public:
		NctiBaseDB();
		virtual ~NctiBaseDB();
	private:
	};
	DECL_NCTI NctiBaseDB* GetBaseDB();
	DECL_NCTI void SetBaseDB(NctiBaseDB* i_pBaseDB);
}
#endif 