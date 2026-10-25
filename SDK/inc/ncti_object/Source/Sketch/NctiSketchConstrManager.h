#ifndef NctiSketchConstrManager_H
#define NctiSketchConstrManager_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCMDef.h"
using NctiSketchConstrId = uint64_t;

namespace NCTI
{
	class NctiDisplayDocSketch;
	class NctiDisplaySketchObject;
	class NctiDisplayDCMDimSys;

	struct DECL_NCTI_OBJECT NctiSketchConstrGroup
	{
		NctiSketchConstrId constrId;
		ncti_DCM_d_type constrType;
		NCTI_VERSION_OBJECT(1, NctiDisplaySketchObject*, geometry1, sd_read_size);
		NCTI_VERSION_OBJECT(1, NctiDisplaySketchObject*, geometry2, sd_read_size);
		NCTI_VERSION_OBJECT(1, NctiDisplaySketchObject*, geometry3, sd_read_size);
		Ncti_Double value;
		NctiSketchConstrGroup(ncti_DCM_d_type i_dt = NCTI_DCM_DISTANCE, NctiSketchConstrId i_id = -1)
			: constrType(i_dt)
			, constrId(i_id)
		{
			geometry1 = nullptr;
			geometry2 = nullptr;
			geometry3 = nullptr;
			value = 0;
		}
	};
	
	class DECL_NCTI_OBJECT NctiSketchConstrManager : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiSketchConstrManager)
	private:
		struct NctiVersionObject
		{
			NCTI_VERSION_OBJECT(1, NctiDisplaySketchObject*, geometry, sd_read_size)
		};
	public:
		virtual ~NctiSketchConstrManager();
		virtual void Init();

	public:
		NctiDisplayDocSketch* getSketchDoc();

		NctiSketchConstrId addConstraint(ncti_DCM_d_type i_constrType, NctiDisplaySketchObject* i_pSktGeom1, Ncti_Double i_value);
		NctiSketchConstrId addConstraint(ncti_DCM_d_type i_constrType, NctiDisplaySketchObject* i_pSktGeom1, NctiDisplaySketchObject* i_pSktGeom2, Ncti_Double i_value = 0);
		NctiSketchConstrId addConstraint(ncti_DCM_d_type i_constrType, NctiDisplaySketchObject* i_pSktGeom1, NctiDisplaySketchObject* i_pSktGeom2, NctiDisplaySketchObject* i_pSktGeom3);

		void removeConstraint(NctiSketchConstrId i_constrId);
		void removeConstraints(const std::vector<NctiSketchConstrId>& i_constrIds);
		void removeConstraints(const std::vector< NctiDisplaySketchObject*> i_curves);

		void fixGeometry(NctiDisplaySketchObject* i_pSktGeom);
		void getConstrGroups(std::vector<NctiSketchConstrGroup>& o_groups) const;
		void getFixedGeometries(std::vector<NctiDisplaySketchObject*>& o_pSktGeoms) const;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

		NctiSketchConstrId genID();
	private:
		std::map<NctiSketchConstrId, NctiSketchConstrGroup> m_constrGroups;
		std::vector<NctiVersionObject> m_fixedGeoms;
	};
}
#endif
