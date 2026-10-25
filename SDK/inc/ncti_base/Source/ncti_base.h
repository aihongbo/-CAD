#ifndef ncti_base_H
#define ncti_base_H

#include "ncti_dcl_base.h"
#include "NctiDummyBaseClass.h"
#include <cstring>
#include <type_traits>
#include <functional>
#ifndef M_E
#define M_E        2.71828182845904523536   // e
#endif

#ifndef M_LOG2E
#define M_LOG2E    1.44269504088896340736   // log2(e)
#endif

#ifndef M_LOG10E
#define M_LOG10E   0.434294481903251827651  // log10(e)
#endif

#ifndef M_LN2
#define M_LN2      0.693147180559945309417  // ln(2)
#endif

#ifndef M_LN10
#define M_LN10     2.30258509299404568402   // ln(10)
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923   // pi/2
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616  // pi/4
#endif

#ifndef M_1_PI
#define M_1_PI     0.318309886183790671538  // 1/pi
#endif

#ifndef M_2_PI
#define M_2_PI     0.636619772367581343076  // 2/pi
#endif

#ifndef M_2_SQRTPI
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#endif

#ifndef M_SQRT2
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)
#endif

#define NCTI_BASE_CLASS NctiDummyBaseClass

#define NCTI_NEW new
#define NCTI_DELETE delete
#define NCTI_FREE free
#define NCTI_MALLOC malloc
#define NCTI_CALLOC calloc
#define NCTI_SAFE_REALLOC ncti_safe_realloc
#define NCTI_REALLOC realloc

enum DECL_NCTI_BASE EnumNctiViewMode
{
    NCTI_VIEW_MODE_ZPLUS = 0,
    NCTI_VIEW_MODE_ZMINUS,
    NCTI_VIEW_MODE_YPLUS,
    NCTI_VIEW_MODE_YMINUS,
    NCTI_VIEW_MODE_XPLUS,
    NCTI_VIEW_MODE_XMINUS,
    NCTI_VIEW_MODE_ISO,
    NCTI_VIEW_MODE_COUNT
};

enum DECL_NCTI_BASE EnumNctiResult
{
	NCTI_FAILED = 0,
	NCTI_SUCCEEDED,
	NCTI_PENDING
};

enum DECL_NCTI_BASE EnumModelDoc
{
	NCTI_GEOM_OCC = 0,
	NCTI_GEOM_CGM,
	NCTI_GEOM_ACIS,
	NCTI_GEOM_OD,
	NCTI_GEOM_PK,
	NCTI_GEOM_PS,
	NCTI_GEOM_HT,
	NCTI_GEOM_C3D,
	NCTI_GEOM_AMCAX,
	NCTI_GEOM_IDEE,
	NCTI_GEOM_HC,//HOOPSExchange
	NCTI_GEOM_OTHER
};

enum DECL_NCTI_BASE EnumGCSDoc
{
	NCTI_GCS_DCM = 0,
	NCTI_GCS_PSCS,
	NCTI_GCS_HTGC,
	NCTI_GCS_GCS
};

enum DECL_NCTI_BASE EnumMeshDoc
{
    NCTI_MESH_GMSH = 0,
	NCTI_MESH_MESHGEMS,
	NCTI_MESH_PANAMESH,
	NCTI_MESH_NETGEN,
    NCTI_MESHDOC_NUM
};

enum DECL_NCTI_BASE EnumRenderType
{
    NCTI_RENDER_VULKAN,
    NCTI_RENDER_VTK
};

typedef unsigned short NctiTypeCommandStatus;
#define NCTI_COMMAND_STATUS_UNKNOWN		0x00
#define NCTI_COMMAND_STATUS_ACTIVE		0x01		
#define NCTI_COMMAND_STATUS_EXECUTABLE	0x02
#define NCTI_COMMAND_STATUS_ON			0x04

#define NCTI_RESABS 1e-6
#define NCTI_RESFIT 1e-3
#define NCTI_RESMCH 1e-10
#define NCTI_RESNOR 1e-10

#define NCTI_DELETE_CHAR(CH_VALUE)\
if (CH_VALUE)\
{\
   NCTI_DELETE[] (CH_VALUE);\
   (CH_VALUE) = nullptr; \
}
#define NCTI_DELETE_OBJECT(CH_VALUE)\
if (CH_VALUE)\
{\
   NCTI_DELETE (CH_VALUE);\
   (CH_VALUE) = nullptr; \
}

#define NCTI_DELETE_OBJECTSET(CH_VALUE)\
for(auto &ptr:(CH_VALUE))\
if (ptr)NCTI_DELETE ptr;\
(CH_VALUE).clear()

#define NCTI_DELETE_OBJECTARR(CH_VALUE)\
for(auto &ptr:(CH_VALUE))\
if (ptr)\
{\
   NCTI_DELETE ptr;\
   ptr = nullptr; \
}

#define NCTI_DELETE_OBJECTMAP(CH_VALUE)\
for(auto &item:(CH_VALUE))\
if (item.second)\
{\
   NCTI_DELETE item.second;\
   item.second = nullptr; \
}(CH_VALUE).clear()

#define NCTI_DELETE_OBJECTVEC(CH_VALUE)\
NCTI_DELETE_OBJECTARR(CH_VALUE)(CH_VALUE).clear()

#define NCTI_COPY_CHAR(CH_TO_VALUE, CH_FROM_VALUE) \
if (CH_FROM_VALUE)\
{\
    CH_TO_VALUE = new char[std::strlen(CH_FROM_VALUE) + 1]; \
    std::strcpy(CH_TO_VALUE, CH_FROM_VALUE);\
}
#define NCTI_MODEL_TAG void*
enum DECL_NCTI_BASE EnumNctiEdgeGeomType
{
	NCTI_EDGE_GEOM_TYPE_UNKNOWN = -1,
	NCTI_EDGE_GEOM_TYPE_LINE,
	NCTI_EDGE_GEOM_TYPE_CIRCLE,
	NCTI_EDGE_GEOM_TYPE_ELLIPSE,
	NCTI_EDGE_GEOM_TYPE_HELIX,
	NCTI_EDGE_GEOM_TYPE_NURBS,
	NCTI_EDGE_GEOM_TYPE_SPLINE
};
#define NCTI_PI 3.1415926535898
#define NCTI_SIZE_FILE_PATH			2048
#define NCTI_DBL_EPSILON      2.2204460492503131e-016
#define NCTI_DBL_MAX          1.7976931348623158e+308
#define NCTI_FLT_MAX          3.402823466e+38F 
#define NCTI_UINT_MAX         0xffffffff 

#define Ncti_strcmp strcmp
#ifdef _MSC_VER
#define Ncti_stricmp _stricmp
#else
#include <strings.h>
#define Ncti_stricmp strcasecmp
#endif

//data
typedef int           Ncti_Integer;
typedef unsigned int  Ncti_UInteger;
typedef double        Ncti_Double;
typedef bool          Ncti_Boolean;
typedef float         Ncti_Float;
typedef char          Ncti_Char;
typedef unsigned char Ncti_Byte;
typedef void*         Ncti_Address;
typedef unsigned long long Ncti_Size;
typedef long          Ncti_Long;
typedef wchar_t       Ncti_WChar;
typedef char*         Ncti_PChar;
typedef long long     Ncti_LongLong;
typedef short         Ncti_Short;

DECL_NCTI_BASE void* ncti_safe_realloc(void* o_char, Ncti_Size i_charsize, Ncti_Size i_newsize);
#ifdef _MSC_VER
typedef Ncti_LongLong Ncti_Pysize;
#else
typedef Ncti_Long     Ncti_Pysize;
#endif


namespace NCTI
{
	enum DECL_NCTI_BASE NctiElementType :unsigned char {
		Point1 = 0,
		Edge2,
		Edge3,
		Triangle3,
		Triangle6,
		Quadrangle4,
		Quadrangle8,
		Quadrangle9,
		Tetrahedron4,
		Tetrahedron10,
		Hexahedron8,
		Hexahedron20,
		Hexahedron27,
		Prism6,
		Prism15,
		Prism18,
		Pyramid5,
		Pyramid13,
		Pyramid14,
		E_ELEM_TYPE_COUNT,
		E_ELEM_POLY_LINE,
    };

    enum DECL_NCTI_BASE NctiSelectType
    {
        ELEM_Entity = 0,
        ELEM_Vertex = 1,
        ELEM_Cell = 2,
        ELEM_Face = 3,
        ELEM_Edge = 4,
    };

	enum DECL_NCTI_BASE NctiErrorType
	{
		Success = 0,
		NoLicense,
		Invalid,
		ErrroMachineId,
		Expire,
		LicenseError,
		InvalidProduct,
        FontError,
		PythonError,
        ConfigError,
        PluginError,
        PathError,
		Error
	};

	struct DECL_NCTI_BASE NctiTessellateParam
	{
		Ncti_Double dRoughnessScale;
		Ncti_Boolean bEdgeLength;
		Ncti_Double dEdgeLength;
		Ncti_Double CATPI;
		Ncti_Double tessellateAngle;
		Ncti_Double tessellateSag;
		Ncti_Float Scale;
		NctiTessellateParam()
		{
			dRoughnessScale = 1.0;
			bEdgeLength = false;
			dEdgeLength = 1.0;
			CATPI = NCTI_PI;
			tessellateAngle = (CATPI / 6.0);
			tessellateSag = 0.001;
			Scale = 0.1f;
		}
	};
}
#define INVALID_KEY nullptr


template <typename T>
inline void hash_combine(size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

#ifdef _WIN32
#define NCTI_WIN
#elif __APPLE__
#define NCTI_MACOS
#elif __linux__
#define NCTI_LINUX
#elif __unix__
#define NCTI_UNIX
#else
// 其他系统下的代码
#endif

#ifndef NCTI_DIM_SYS 
#define NCTI_DIM_SYS void*
#endif

#ifndef NCTI_G_NODE 
#define NCTI_G_NODE void*
#endif

#ifndef NCTI_P_NODE 
#define NCTI_P_NODE void*
#endif

#ifndef NCTI_D_NODE 
#define NCTI_D_NODE void*
#endif

#ifndef NCTI_V_NODE 
#define NCTI_V_NODE void*
#endif

#ifndef NCTI_R_NODE 
#define NCTI_R_NODE void*
#endif

#ifndef NCTI_E_NODE 
#define NCTI_E_NODE void*
#endif

#ifndef NCTI_B_NODE 
#define NCTI_B_NODE void*
#endif

#ifndef NCTI_DR_NODE 
#define NCTI_DR_NODE void*
#endif

#ifdef __GNUC__
#include <math.h>
#endif

#endif // !ncti_base_H
