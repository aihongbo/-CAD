#ifndef NctiTimerManager_H
#define NctiTimerManager_H
#include "ncti.h"
#include "NctiManager.h"
#include "NctiDisplayObjectList.h"
namespace NCTI
{
	class NctiTimerInterface;
	class NctiDisplayObjectList;
	class NctiBaseView;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiTimerManager : public NctiManager
	{
		NCTI_MANAGER_FUNCTIONS(NctiTimerManager)
	public:
		virtual ~NctiTimerManager();
		void Init();
		void SetTimerInterface(NctiTimerInterface* i_pTimerInterface);
		void SetDisplayObject(NctiDisplayObject* i_pDo);
		void ProcessTimerEvent(Ncti_Integer i_iTimerID);
		void RemoveDisplayObject(NctiDisplayObject* i_pDo);
		Ncti_Integer GetLocalTime(Ncti_Integer& o_iYear, Ncti_Integer& o_iMonth, Ncti_Integer& o_iDay, Ncti_Integer& o_iHour, Ncti_Integer& o_iMinute, Ncti_Integer& o_iSecond);
		void NotifyViewDeletion(NctiBaseView* o_pBaseView);	
		void ExecuteCommandTimer();		
		void TerminateCommandTimer();	
		void SetUpdateSceneTimer(Ncti_Boolean i_bOnOff);
		void Pause();
		void Resume();
		Ncti_Boolean IsPaused();
	protected:
		void set_timer(Ncti_Integer o_iTimerID, Ncti_Integer o_iTick);
		void kill_timer(Ncti_Integer o_iTimerID);
		void clear_displayobject();							
		Ncti_Boolean set_target_frame_rate(Ncti_Boolean i_bOnOff);
	private:
		NctiTimerInterface* m_pTimerInterface;
		NctiDisplayObjectList m_cDoList;
		Ncti_Boolean m_bDoTimerOnOff;
		Ncti_Boolean m_bComTimerOnOff;
		char*	m_pszHeuristic;
		Ncti_Boolean m_bPause;
	};
}

DECL_NCTI NCTI_MANAGER_TYPEDEF(NctiTimerManager)

#endif