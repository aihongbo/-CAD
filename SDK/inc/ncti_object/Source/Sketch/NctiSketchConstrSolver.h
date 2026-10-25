#ifndef NctiSketchConstrSolver_H
#define NctiSketchConstrSolver_H
#include "dcl_ncti_object.h"
#include "ncti_base.h"
#include "NctiSketchConstrManager.h"
#include <memory>
#include <map>
#include <vector>
namespace NCTI
{
	class NctiDisplayDocSketch;
	class NctiDisplaySketchObject;
	class NctiDisplayDCMDimSys;
	class NctiDisplayDCMDimension;
	class NctiDisplayDCMGeometry;
	class NctiDisplayDocCustomContainer;
	class NctiVector;
	class DECL_NCTI_OBJECT NctiSketchConstrSolver : public NCTI_BASE_CLASS
	{
	public:
		NctiSketchConstrSolver(NctiDisplayDocSketch* i_sketchDoc);
		~NctiSketchConstrSolver();

	public:
		bool drag(const std::vector<NctiDisplaySketchObject*>& i_dragedObjs, const NctiVector& i_vecMove);
		bool solve();
		bool isOverDefined();
		void apply();

		NctiSketchConstrManager* getSketchConstrManager() const;
	private:
		std::shared_ptr<NctiDisplayDCMDimSys> createConstrSystem();
		bool createConstraints(std::shared_ptr<NctiDisplayDCMDimSys> i_constrSys, const std::vector<NctiSketchConstrGroup>& i_constrGroups, std::vector<std::shared_ptr<NctiDisplayDCMDimension>>& o_constrObjs);
		std::shared_ptr<NctiDisplayDCMGeometry> createConstrGeometry(NctiDisplaySketchObject* i_pGeom);
		bool fixGeometries(std::shared_ptr<NctiDisplayDCMDimSys> i_constrSys, const std::vector<NctiDisplaySketchObject*>& i_fixGeoms);
		NCTI_G_NODE addGeometryToSystem(NctiDisplayDocCustomContainer* i_pDocCustom, NctiDisplayDCMDimSys* i_pDimSys, NctiDisplayDCMGeometry* i_pGeom);
		void eraseConstrNodes(std::shared_ptr<NctiDisplayDCMDimSys> i_constrSys);
		bool isOverDefined(std::shared_ptr<NctiDisplayDCMDimSys> i_constrSys, const std::vector<std::shared_ptr<NctiDisplayDCMDimension>>& i_constrObjs, bool& o_overdefined);
	private:
		NctiDisplayDocSketch* m_sketchDoc;
		std::map<NctiDisplaySketchObject*, std::shared_ptr<NctiDisplayDCMGeometry>> m_geomMap;
		bool m_overdefind;
	};
}
#endif // !NctiSketchConstrSolver_H
