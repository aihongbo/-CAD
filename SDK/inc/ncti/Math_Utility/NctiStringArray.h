#ifndef NctiStringArray_H
#define NctiStringArray_H
#include "ncti.h"
namespace NCTI
{
	/**
	   * @brief internal used
	   */
	class DECL_NCTI NctiStringArray : public NCTI_BASE_CLASS
	{
	public:
		NctiStringArray();
		virtual ~NctiStringArray();
		char**	GetStringArray() { return m_pasString; };
		void AddString(const char*  i_psText);
		Ncti_Integer	GetCount() { return m_count; };
		void Clear();
	private:
		Ncti_Integer m_size;
		Ncti_Integer m_count;
		char**	m_pasString;
	};
}
#endif
