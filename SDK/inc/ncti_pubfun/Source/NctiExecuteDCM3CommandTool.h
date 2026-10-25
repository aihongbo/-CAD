#ifndef NctiExecuteDCM3CommandTool_H
#define NctiExecuteDCM3CommandTool_H
#include "ncti_base.h"
#include "dcl_ncti_pubfun.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiCommandManager;
	class NctiDisplayDCM3DimSys;
	class NctiDisplayDCM3Dimension;
	class NctiDisplayDCM3Geometry;
	class NctiDisplayDCM3Point;
	class NctiDisplayDCM3Line;
	class NctiDisplayDCM3Plane;
	class NctiDisplayDCM3Circle;
	class NctiDisplayDCM3Cylinder;
	class NctiDCM3Set;
	class NctiDisplayModelBody;
	class NctiPosition;
	class NctiVector;
	/**
	* @brief dcm3 command executor
	* @details execute dcm3 commands
	* @see NctiDCM3Def
	*/
	class DECL_NCTI_PUBFUN NctiExecuteDCM3CommandTool
	{
	public:
		NctiExecuteDCM3CommandTool();
		~NctiExecuteDCM3CommandTool();

		static bool ExecuteCreateDimSysCommand(NctiCommandManager* i_pComMan, const char* i_dimSysName, NctiDisplayDCM3DimSys*& o_pDimSys);
		static bool ExecuteCreateDimensionCommand(NctiCommandManager* i_pComMan, const char* i_dimName, ncti_DCM3_d_type i_dt, double i_value, NctiDisplayDCM3Dimension*& o_pDim);
		static bool ExecuteCreatePointCommand(NctiCommandManager* i_pComMan, const char* i_pointName, NctiDisplayDCM3DimSys* i_pDimSys, const NctiPosition& i_pos, NctiDisplayModelBody* i_pModelBody, NctiDisplayDCM3Point*& o_pPoint);
		static bool ExecuteCreateLineCommand(NctiCommandManager* i_pComMan, const char* i_lineName, NctiDisplayDCM3DimSys* i_pDimSys, const NctiPosition& i_pos, const NctiVector& i_dir, NctiDisplayModelBody* i_pModelBody, NctiDisplayDCM3Line*& o_pLine);
		static bool ExecuteCreateCircleCommand(NctiCommandManager* i_pComMan, const char* i_circleName, NctiDisplayDCM3DimSys* i_pDimSys, const NctiPosition& i_centre, const NctiVector& i_normal, double i_radius, NctiDisplayModelBody* i_pModelBody, NctiDisplayDCM3Circle*& o_pCircle);
		static bool ExecuteCreatePlaneCommand(NctiCommandManager* i_pComMan, const char* i_planeName, NctiDisplayDCM3DimSys* i_pDimSys, const NctiPosition& i_pos, const NctiVector& i_normal, NctiDisplayModelBody* i_pModelBody, NctiDisplayDCM3Plane*& o_pPlane);
		static bool ExecuteCreateCylinderCommand(NctiCommandManager* i_pComMan, const char* i_cylinderName, NctiDisplayDCM3DimSys* i_pDimSys, const NctiPosition& i_pos, const NctiVector& i_normal, double i_radius, double i_height, NctiDisplayModelBody* i_pModelBody, NctiDisplayDCM3Cylinder*& o_pCylinder);
		static bool ExecuteCreateGeometryCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayModelBody* i_pDataSourceBody, long i_CellID, NctiDisplayDCM3Geometry*& o_pGeom);
		static bool ExecuteCreateSetCommand(NctiCommandManager* i_pComMan, const char* i_setName, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayModelBody* i_pModelBody, const std::vector<NctiDisplayDCM3Geometry*>& i_pGeomVec, const std::vector<Ncti_Long>& i_CellIDVec, NctiDCM3Set*& o_pSet);


		static bool ExecuteFixCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayDCM3Geometry* i_pGeom);
		static bool ExecuteAdddCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayDCM3Dimension* i_pDim, NctiDisplayDCM3Geometry* i_pGeom1, NctiDisplayDCM3Geometry* i_pGeom2, NctiDisplayDCM3Geometry* i_pGeom3, const char* i_resNodeName);
		static bool ExecuteMoveToSetCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3DimSys* i_pDimSys, NctiDCM3Set* i_pSet, const std::vector<NctiDisplayDCM3Geometry*>& i_pGeomVec);
		static bool ExecuteEraseGeometryCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayDCM3Geometry* i_pGeom);
		static bool ExecuteEraseDimensionCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayDCM3Dimension* i_pDim);
		static bool ExecuteEvaluateCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3DimSys* i_pDimSys, const std::vector<NctiDisplayDCM3Geometry*>& i_pGeomVec = {}, bool i_incremental = false);

		static bool ExecuteEditAlignmentCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3Dimension* i_pDim, ncti_DCM3_alignment i_align);
		static bool ExecuteEditSurfOrientCommand(NctiCommandManager* i_pComMan, NctiDisplayDCM3Dimension* i_pDim, ncti_DCM3_surface_orientation i_orient);

		static bool ExecuteExportAssemblyScriptCommand(NctiCommandManager* i_pComMan, const char* i_filename);
	};
}
#endif // !NctiExecuteDCM3CommandTool_H
