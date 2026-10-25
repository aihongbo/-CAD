#ifndef NctiUserLockerInterface_H
#define NctiUserLockerInterface_H
#include "ncti.h"
namespace NCTI
{
	class NctiUserInterfaceManager;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiUserLockerInterface : public NCTI_BASE_CLASS
	{
	public:
		NctiUserLockerInterface();
		virtual ~NctiUserLockerInterface();
	public:
		virtual EnumNctiResult LockData();
	public:
		void SetUserInterfaceManager(NctiUserInterfaceManager* i_pUserInterfaceManager) { m_UserInterfaceManager = i_pUserInterfaceManager; }
		NctiUserInterfaceManager* GetUserInterfaceManager() { return m_UserInterfaceManager; }
	protected:
		NctiUserInterfaceManager* m_UserInterfaceManager;
	};
}
#endif
