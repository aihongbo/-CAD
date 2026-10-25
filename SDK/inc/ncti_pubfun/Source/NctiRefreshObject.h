#ifndef NctiRefreshObject_H
#define NctiRefreshObject_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <functional>
#include <map>
#include <vector>
namespace NCTI
{
	class NctiDisplayObjectList;
	class NctiDisplayDocCustomContainer;
	class NctiDisplayObject;
	class NctiBaseModel;
	class DECL_NCTI_PUBFUN NctiRefreshObject
	{
	public:
		NctiRefreshObject();
		virtual ~NctiRefreshObject();
		void Start(NctiBaseModel* i_pBaseModel, NctiDisplayObjectList& i_pObjVec);
		void Finsh();
	public:
		static NctiRefreshObject& Instance();
		static void UpdateAllPhysicalObj(NctiBaseModel* i_pBaseModel);
	private:
		void Update();
		//Physical
		void UpdatePhysicalSet();
		void UpdatePhysicalConstraint();
		void UpdatePhysicalLoad();
		void UpdatePhysicalCoupling();
		void UpdatePhysicalStep();

		//
		static NctiRefreshObject m_RefreshObject;
		NctiBaseModel* m_pBaseModel;
		std::map<NctiDisplayDocCustomContainer*, std::vector<NctiDisplayObject*>> m_mapDocObjects;
		Ncti_Boolean m_bHasSet;
		Ncti_Boolean m_bHasPhysical;
	};
}
#endif
