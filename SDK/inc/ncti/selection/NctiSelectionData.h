#ifndef NctiSelectionData_H
#define NctiSelectionData_H
#include "ncti.h"

#define NCTI_SELDATA_TYPEDEF( SELDATA_NAME, IDENTITY_STRING ) const char* SELDATA_NAME::ID = IDENTITY_STRING;

#define NCTI_SELDATA_FUNCTIONS( SELDATA_NAME )	\
public:\
	static const char* ID;\
	virtual const char* TypeName(){ return SELDATA_NAME::ID; };\
public:

namespace NCTI
{
	class NctiRenderSegmentItem;
	class NctiViewerRenderer;
	class NctiPosition;
	/**
	* @brief The Base Selection Data Class
	* @see NctiDummyBaseClass
	*/
    class DECL_NCTI NctiSelectionData : public NctiDummyBaseClass
	{
	public:
		NctiSelectionData();
		virtual ~NctiSelectionData();
	public:
		virtual const char* TypeName();
		Ncti_Boolean IsTypeName(const char*  i_pszName);

        void SetFilterFlag(Ncti_Boolean  i_bFilterFlag) { m_bFilterFlag = i_bFilterFlag; };
        Ncti_Boolean GetFilterFlag() { return m_bFilterFlag; };

        virtual NctiSelectionData* MakeCopy();
		virtual NctiSelectionData& operator =(NctiSelectionData&  i_cSource) { return  i_cSource; };
		virtual Ncti_Boolean operator ==(NctiSelectionData&  i_cSource) { return false; };
		virtual Ncti_Integer GetHashIndex() = 0;

		virtual void highlight(Ncti_Boolean high);

        virtual void GetBox(NctiPosition& o_ptMin, NctiPosition& o_ptMax);

	private:
		Ncti_Boolean m_bFilterFlag; 
	};
}
#endif
