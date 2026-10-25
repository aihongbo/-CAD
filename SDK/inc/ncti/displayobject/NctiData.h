#ifndef NctiData_H
#define NctiData_H
#include "ncti.h"
#include "NctiReferenceCounterManager.h"
#define NCTI_DATA_DEF( NCTI_CLASS_NAME ) \
namespace NCTI \
{\
class NctiData_##NCTI_CLASS_NAME : public NctiData \
{ \
public: \
	NctiData_##NCTI_CLASS_NAME( void* pClientObject, NctiReferenceCounterManager* i_pRefMan) : NctiData( pClientObject, i_pRefMan ){}; \
    virtual ~NctiData_##NCTI_CLASS_NAME(){ release_data(); };\
    NCTI_CLASS_NAME* GetData(){ return (NCTI_CLASS_NAME*)m_pClientObject; }; \
    virtual void release_data() \
    { \
        if ( m_pRefMan != nullptr ) \
        { \
            void* pTarget = m_pRefMan->Release( m_pClientObject ); \
            if ( pTarget != nullptr ) \
            { \
                NCTI_DELETE (NCTI_CLASS_NAME*)m_pClientObject; \
                m_pClientObject = nullptr; \
            } \
        } \
    } \
};\
}
namespace NCTI
{
	class NctiReferenceCounterManager;
	class DECL_NCTI NctiData : public NCTI_BASE_CLASS
	{
	public:
		NctiData(void* i_pClientObject, NctiReferenceCounterManager* i_pRefMan);
		void* GetData() { return m_pClientObject; };
		NctiReferenceCounterManager* GetReferenceCounterManager() { return m_pRefMan; }
	protected:
		virtual void release_data() = 0;

	protected:
		void*	m_pClientObject;
		NctiReferenceCounterManager* m_pRefMan;
	};
}
#endif // !NctiData_H
