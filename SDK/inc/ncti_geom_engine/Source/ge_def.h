#ifndef ge_def_H
#define ge_def_H
#include "ncti_dcl_geom_engine.h"
#include "ncti_base.h"
#include <math.h>
#include <algorithm>
#include <float.h>
namespace NCTI
{
	enum Ncti_GeomAbs_BSplKnotDistribution
	{
		Ncti_GeomAbs_NonUniform,
		Ncti_GeomAbs_Uniform,
		Ncti_GeomAbs_QuasiUniform,
		Ncti_GeomAbs_PiecewiseBezier
	};
	enum BSplCLib_KnotDistribution
	{
		Ncti_BSplCLib_NonUniform,
		Ncti_BSplCLib_Uniform
	};
	enum BSplCLib_MultDistribution
	{
		Ncti_BSplCLib_NonConstant,
		Ncti_BSplCLib_Constant,
		Ncti_BSplCLib_QuasiConstant
	};
	enum Ncti_GeomAbs_Shape
	{
		Ncti_GeomAbs_C0,
		Ncti_GeomAbs_G1,
		Ncti_GeomAbs_C1,
		Ncti_GeomAbs_G2,
		Ncti_GeomAbs_C2,
		Ncti_GeomAbs_C3,
		Ncti_GeomAbs_CN
	};
	enum Ncti_Orientation
	{
		Ncti_FORWARD,
		Ncti_REVERSED,
		Ncti_INTERNAL,
		Ncti_EXTERNAL
	};

	enum Ncti_MeshAlgoType
	{
		Ncti_MeshAlgoType_DEFAULT = -1,
		Ncti_MeshAlgoType_Watson = 0,
		Ncti_MeshAlgoType_Delabella,
	};

	const Ncti_Size MEMORY_BLOCK_SIZE_HUGE = 1024 * 1024;
	enum Ncti_IMeshDataStatus
	{
		IMeshData_NoError = 0x0,   //!< Mesh generation is successful.
		IMeshData_OpenWire = 0x1,   //!< Notifies open wire problem, which can potentially lead to incorrect results.
		IMeshData_SelfIntersectingWire = 0x2,   //!< Notifies self-intersections on discretized wire, which can potentially lead to incorrect results.
		IMeshData_Failure = 0x4,   //!< Failed to generate mesh for some faces.
		IMeshData_ReMesh = 0x8,   //!< Deflection of some edges has been decreased due to interference of discrete model.
		IMeshData_UnorientedWire = 0x10,  //!< Notifies bad orientation of a wire, which can potentially lead to incorrect results.
		IMeshData_TooFewPoints = 0x20,  //!< Discrete model contains too few boundary points to generate mesh.
		IMeshData_Outdated = 0x40,  //!< Existing triangulation of some faces corresponds to greater deflection than specified by parameter.
		IMeshData_Reused = 0x80,  //!< Existing triangulation of some faces is reused as far as it fits specified deflection.
		IMeshData_UserBreak = 0x100  //!< User break
	};
	enum Ncti_Poly_MeshPurpose
	{
		// main flags
		Poly_MeshPurpose_NONE = 0,      //!< no special use (default)
		Poly_MeshPurpose_Calculation = 0x0001, //!< mesh for algorithms
		Poly_MeshPurpose_Presentation = 0x0002, //!< mesh for presentation (LODs usage)
		// special purpose bits (should not be set externally)
		Poly_MeshPurpose_Active = 0x0004, //!< mesh marked as currently active in a list
		Poly_MeshPurpose_Loaded = 0x0008, //!< mesh has currently loaded data
		Poly_MeshPurpose_AnyFallback = 0x0010, //!< a special flag for BRep_Tools::Triangulation() to return any other defined mesh,
		//   if none matching other criteria was found user-defined flags should have higher values
		Poly_MeshPurpose_USER = 0x0020  //!< application-defined flags
	};

}
using namespace NCTI;


#define NCTI_TOLERANCE3 1e-3
#define NCTI_TOLERANCE6 1e-6
#define NCTI_TOLERANCE10 1e-10
#define NCTI_TOLERANCE20 1e-20

#define NCTI_TOLERANCE NCTI_TOLERANCE6

#define NCTI_FALSE false
#define NCTI_TRUE  true

#define NCTI_NULL nullptr


#define NCTI_OVERRIDE override

#endif
