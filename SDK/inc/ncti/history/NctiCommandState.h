#ifndef NctiCommandState_H
#define NctiCommandState_H
#include "ncti.h"
namespace NCTI
{
	class NctiBulletinBoard;
	class NctiDisplayObject;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiCommandState : public NCTI_BASE_CLASS
	{
	public:
		NctiCommandState();
		virtual ~NctiCommandState();
	public:
		NctiBulletinBoard* GetLastBulletinBoard() { return m_pLastBulletinBoard; };
		void SetCommandPrompt(const char* i_cpCommandPrompt);
		const char* GetCommandPrompt() { return m_cpCommandPrompt; }
		void SetCallbackInfo(NctiDisplayObject* i_pDoCallback, EnumNctiDoCallbackType i_eDoCallbackType);
		void GetCallbackInfo(NctiDisplayObject*& o_pDoCallback, EnumNctiDoCallbackType& o_eDoCallbackType);
		void SetDepthLevel(Ncti_Integer i_iDepthLevel) { m_iDepthLevel = i_iDepthLevel; }
		NctiCommandState* GetNext() { return m_pNextState; }
		void SetNext(NctiCommandState* i_pCommandState) { m_pNextState = i_pCommandState; }
		void SetSibling(NctiCommandState* i_pSibling){ m_pSibling = i_pSibling; }
		NctiCommandState* GetSibling() { return m_pSibling; }
		void SetPrevious(NctiCommandState* i_pCommandState) { m_pPreviousState = i_pCommandState; }
		Ncti_Boolean Merge(NctiCommandState*& i_pComStatSource);
		void Add(NctiBulletinBoard* i_pBulletinBoard);
		NctiBulletinBoard* GetFirstBulletinBoard() { return m_pFirstBulletinBoard; }
		Ncti_Boolean IsOpen() { return m_bOpen; }
		void SetOpen(Ncti_Boolean i_bOpen) { m_bOpen = i_bOpen; }
		NctiCommandState* GetPrevious() { return m_pPreviousState; }
		void DeleteSibling();
		void RollBack();
		void RollForward();
		Ncti_Integer	GetDepthLevel() { return m_iDepthLevel; }
		Ncti_Boolean InsertFirstBulletinBoard(NctiBulletinBoard* i_pBB);
	private:
		Ncti_Boolean m_bOpen;
		Ncti_Integer	m_iDepthLevel;
		char* m_cpCommandPrompt;
		NctiBulletinBoard* m_pFirstBulletinBoard;
		NctiBulletinBoard* m_pLastBulletinBoard;
		NctiDisplayObject* m_pDoCallback;
		EnumNctiDoCallbackType m_eDoCallbackType;

		NctiCommandState* m_pPreviousState;
		NctiCommandState* m_pNextState;
		NctiCommandState* m_pSibling;
	};
}
#endif
