#ifndef NctiUserProgressBar_H
#define NctiUserProgressBar_H
#include "ncti.h"
namespace NCTI
{
	class NctiUserInterfaceManager;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiUserProgressBar : public NCTI_BASE_CLASS
	{
	public:
		NctiUserProgressBar();
		virtual ~NctiUserProgressBar();
	public:
		virtual void Start(const Ncti_Char* i_Name){}
		virtual void End(){}
	public:
		void SetUserInterfaceManager(NctiUserInterfaceManager* i_pUserInterfaceManager) { m_UserInterfaceManager = i_pUserInterfaceManager; }
		NctiUserInterfaceManager* GetUserInterfaceManager() { return m_UserInterfaceManager; }
	protected:
		NctiUserInterfaceManager* m_UserInterfaceManager;
	};
}
#endif
