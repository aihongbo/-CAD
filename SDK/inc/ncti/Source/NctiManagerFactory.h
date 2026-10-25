#ifndef NctiManagerFactory_H
#define NctiManagerFactory_H
#include "ncti.h"
namespace NCTI
{
	class NctiManager;
	class NctiBaseModel;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiManagerGenerator : public NCTI_BASE_CLASS
	{
		friend class NctiManagerFactory;
	public:
		NctiManagerGenerator(Ncti_Integer& o_iManagerType, const char* i_cpManagerName, NctiManager*(*)(...));
		void SetNext(NctiManagerGenerator* i_pNext) { m_pNextGenerator = i_pNext; };
		NctiManagerGenerator* GetNext() { return m_pNextGenerator; };
		const char* GetManagerName() { return m_cpManagerName; };
		NctiManager* GenerateManager();
		Ncti_Integer GetManagerType() { return m_iManagerType; }
	private:
		Ncti_Integer m_iManagerType;
		const char* m_cpManagerName;
		NctiManager* (*m_pProcPointer)(...);
		NctiManagerGenerator* m_pNextGenerator;
	};
	class DECL_NCTI NctiManagerFactory
	{
	public:
		NctiManagerFactory(void);
		virtual ~NctiManagerFactory(void);
	public:
		Ncti_Integer GenerateManager(NctiBaseModel* i_pBaseModel, NctiManager**& i_paManagerGenerated);
	};
	DECL_NCTI NctiManagerFactory* GetManagerFactory();
}
#endif // !NctiManagerFactory_H
