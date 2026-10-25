#ifndef NctiCommandCharList_H
#define NctiCommandCharList_H
#include "ncti.h"
namespace NCTI
{
	class NctiCommand;
	struct NctiCommandChar
	{
		NctiCommand*	pCommand;
		char*		pDoName;
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiCommandCharList : public NCTI_BASE_CLASS
	{
	public:
		NctiCommandCharList(Ncti_Integer i_iSize = 100);
		virtual ~NctiCommandCharList();
		Ncti_Integer AddData(NctiCommand* i_pCommand, char*	i_pDoName);
		Ncti_Integer	GetCount();
		NctiCommand* GetCommand(Ncti_Integer i_iNum);
		char* GetDoName(Ncti_Integer i_iNum);
	protected:
		Ncti_Integer expand();
	private:
		Ncti_Integer m_iSize;			
		Ncti_Integer	m_iCount;			
		NctiCommandChar* m_aCommandCharArray;	
	};
}
#endif
