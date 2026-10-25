#ifndef NctiWorkPlaneManager_H
#define NctiWorkPlaneManager_H
#include "NctiDisplayObject.h"
#include "dcl_ncti_object.h"
#include "NctiManager.h"
namespace NCTI
{
	class NctiBaseView;
	class NctiBaseModel;
	class NctiPosition;
	class NctiUnitVector;
	class DECL_NCTI_OBJECT NctiWorkPlaneManager : public NctiManager
	{
		NCTI_MANAGER_FUNCTIONS(NctiWorkPlaneManager)
	public:
		void SetCoordinate(NctiDisplayObject* i_pDo, NctiPosition& i_Origin, NctiUnitVector& i_XAxis, NctiUnitVector& i_YAxis, NctiDisplayObject* i_pDoIns = NULL);
		void GetCoordinate(NctiDisplayObject*& i_pDo, NctiPosition& i_Origin, NctiUnitVector& i_XAxis, NctiUnitVector& i_YAxis);
		void DeActivate(NctiDisplayObject* i_pTarget);
		NctiTransf GetTransfToWCS();
		NctiTransf GetTransfToModel();
		NctiDisplayObject* GetCurrent();
		NctiTransf GetLocalTransf();

	protected:
		NctiDisplayObject* m_pCurrentWorkPlane;
		NctiPosition m_Origin;
		NctiUnitVector m_XAxis;
		NctiUnitVector m_YAxis;
		NctiDisplayObject* m_pDoInstance;
	public:
		static NctiWorkPlaneManager* GetWorkPlaneManager(NctiBaseView* i_pBaseView);
		static NctiWorkPlaneManager* GetWorkPlaneManager(NctiBaseModel* i_pBaseModel);
		static NctiWorkPlaneManager* GetWorkPlaneManager(NctiManager* i_pManager);
	};

}
DECL_NCTI_OBJECT NCTI_MANAGER_TYPEDEF(NctiWorkPlaneManager)

#endif