#ifndef NctiBaseUtility_H
#define NctiBaseUtility_H
#include "ncti_base.h"
#include "NctiPosition.h"
#include "NctiVector.h"
#include "NctiUnitVector.h"
#include "NctiTransf.h"
#include "ncti_include.h"
#include <vector>
using namespace NCTI;


#define EPSILON		(1.0e-7)
/** 
* @brief request memory
* @param[in] o_char, a memory if it is not nullptr
* @param[in] i_charsize, if the o_char isn't nullptr,it is the o_char size
* @param[in] i_newsize, the new memory size
* @return void*, return new meory
*/
DECL_NCTI_BASE void* ncti_safe_realloc(void* o_char, Ncti_Size i_charsize, Ncti_Size i_newsize);
/**
* @brief convert long to char
* @param[in] i_long
* @param[in] o_result
* @return Ncti_Size, the size of o_result
*/
DECL_NCTI_BASE Ncti_Size LongToChar(long i_long, char * o_result);
DECL_NCTI_BASE Ncti_Double distance_to_plane(const NctiPosition& posBase_, const NctiPosition& posPlane_, const NctiUnitVector& vec);
DECL_NCTI_BASE Ncti_Double distance_to_point(const NctiPosition& posBase_, const NctiPosition& posTarget_);
DECL_NCTI_BASE NctiPosition proj_pt_to_plane(const NctiPosition& posBase_, const NctiPosition& posPlane_, const NctiUnitVector& vec);
DECL_NCTI_BASE NctiPosition proj_pt_to_line(const NctiPosition& posBase_, const NctiPosition& posLine_, const NctiUnitVector& vec);
DECL_NCTI_BASE Ncti_Double angle_between(const NctiVector& vec, const NctiVector& vecTarget_, const NctiVector* normal = nullptr);
DECL_NCTI_BASE Ncti_Boolean intersect_line_plane(const NctiPosition& posLine_, const NctiVector& dirLine_, const NctiPosition& posPlane_, const NctiUnitVector& vec, Ncti_Double& t, NctiPosition& posIntersected_);
DECL_NCTI_BASE Ncti_Boolean closest_points(const NctiPosition& posLineBase_, const NctiUnitVector vecLine_, const NctiPosition& posLineTarget_, const NctiUnitVector vec, Ncti_Double& t, NctiPosition& posClosestOnBase_, Ncti_Double& tt, NctiPosition& posClosestOnTarget_);
DECL_NCTI_BASE Ncti_Double distance_to_line_squared(const NctiPosition& posBase_, const NctiPosition& posLine_, const NctiUnitVector& vec);
DECL_NCTI_BASE int intersect_2_circles(const NctiPosition & center1, Ncti_Double radius1, const NctiPosition & center2, Ncti_Double radius2, const NctiVector & plane_normal, NctiPosition & intersection1, NctiPosition & intersection2);
DECL_NCTI_BASE Ncti_Boolean intersect_pt_to_line_by_distance(const NctiPosition& i_posBase, const NctiPosition& i_LineSPos, const NctiPosition& i_LineEPos, Ncti_Double i_distance, std::vector<NctiPosition>& o_ResultPos);
//! 计算多个坐标点组成的多边形的法向量
//! @param [out] o_normal	- 返回的法向量
//! @param [in] i_points	- 顶点数组
//! @param [in] i_count	- 顶点个数
//! @return	如果所有的顶点位于一个平面并计算法向成功，返回True,否则返回False
DECL_NCTI_BASE Ncti_Boolean compute_polygon_normal(NctiVector& o_normal, const NctiPosition* i_points, const size_t i_count);
DECL_NCTI_BASE Ncti_Boolean compute_triangle_normal(NctiVector& o_normal, const NctiPosition& i_p1, const NctiPosition& i_p2, const NctiPosition& i_p3);

DECL_NCTI_BASE void	matrix_from_vector_to_vector(NCTI::NctiMatrix& o_mat, const NCTI::NctiUnitVector& i_from, const NCTI::NctiUnitVector& i_to);
DECL_NCTI_BASE void	matrix_from_vector_to_vector(NCTI::NctiMatrix& o_mat, const NCTI::NctiVector& i_from, const NCTI::NctiVector& i_to);
DECL_NCTI_BASE int	computeKnots(int i_order, Ncti_Boolean i_closed, int i_numPoles, std::vector<double>& o_knots);
DECL_NCTI_BASE int	prepareKnots(int i_order, Ncti_Boolean i_closed, int i_numPoles, std::vector<int>& o_knot_mult, std::vector<double>& o_knots);

DECL_NCTI_BASE void api_create_frustum(NctiMeshData& o_ret, 
    double hight,double topRadius, double botRadius,
    bool visTop, bool visBot,double botPos, int res, NctiVector dir);

DECL_NCTI_BASE NctiMeshData api_create_arrow(
    double height, double diameter, bool upArrow = true,
    double factorArrowHeight = 0.2,double factorCylinderDiameter = 0.382,
    int res = 15, NctiVector dir = { 0,0,1 });

DECL_NCTI_BASE unsigned int api_clz_generic(uint32_t x);
DECL_NCTI_BASE unsigned int api_clz_generic(uint64_t x);

Ncti_Double safe_acos(Ncti_Double val);
Ncti_Double safe_asin(Ncti_Double val);
Ncti_Double safe_atan2(Ncti_Double y, Ncti_Double x);
DECL_NCTI_BASE char* InterceptString(const char *str, const char *left_str, const char *right_str);

DECL_NCTI_BASE EnumNctiResult api_convert_transf(const NctiTransf& i_trnsf, Ncti_Double o_matrix[16]);
DECL_NCTI_BASE EnumNctiResult api_convert_transf( Ncti_Double i_matrix[16], NctiTransf& o_trnsf);

DECL_NCTI_BASE EnumNctiResult api_convert_transf(const NctiTransf& i_trnsf, Ncti_Float o_matrix[16]);
DECL_NCTI_BASE EnumNctiResult api_convert_transf( Ncti_Float i_matrix[16], NctiTransf& o_trnsf);

DECL_NCTI_BASE Ncti_Boolean IsNaN(Ncti_Double dat);

namespace NCTI
{
	/**
	* @brief the base function
	* @details help to deal with some algorithm problems 
	*/
	class DECL_NCTI_BASE NctiBaseUtility
	{
	public:
		/**
	   * @brief order the tow points,such as ptMin And ptMax 
	   * @param[in] o_ptS
	   * @param[in] o_ptE
	   */
		static void Order(NctiPosition& o_ptS, NctiPosition& o_ptE);
		/**
	   * @brief find the file path of file name
	   * @param[in] i_cpFullFileName, the file name
	   * @param[out] o_cpDir, return the path, it is not ending with '/'
	   * @param[out] o_cpFilename,return the name of file
	   */
		static void FindFileNameAndDirectory(const char* i_cpFullFileName, char* o_cpDir, char* o_cpFilename);
		/**
	   * @brief find the file suffix of file name
	   * @param[in] i_cpFullFileName, the file name
	   * @param[out] o_cpSuffix, the file suffix of file name
	   */
		static void FindFileSuffix(const char* i_cpFullFileName, char* o_cpSuffix);
		/**
	   * @brief find the file name of file name, it is not include suffix.
	   * @param[in] i_cpFullFileName, the file name
	   * @param[out] o_cpFileName, the file name of file name, it is not include suffix.
	   */
		static void FindFileNameWithoutSuffix(const char* i_cpFullFileName, char* o_cpFileName);
		/**
	   * @brief determine whether two points are the same
	   * @param[in] i_p1
	   * @param[in] i_p2
	   * @param[in] i_res, it is a precision control
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean same_point(NctiPosition const& i_p1, NctiPosition const& i_p2, const Ncti_Double i_res);
		/**
	   * @brief determine whether all points are the same
	   * @param[in] i_p1
	   * @param[in] i_p2
	   * @param[in] i_res, it is a precision control
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean same_points(std::vector<NctiPosition> const & i_p1, std::vector<NctiPosition> const & i_p2, const Ncti_Double i_res);
		/**
	   * @brief determine whether two vectors are the same
	   * @param[in] i_p1
	   * @param[in] i_p2
	   * @param[in] i_res, it is a precision control
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean same_vector(NctiVector const& i_p1, NctiVector const& i_p2, const Ncti_Double i_res);
		/**
	   * @brief get box of point,include i_PositionVec, o_ptMax, and o_ptMin
	   * @param[in] i_PositionVec, it is a point
	   * @param[out] o_ptMax
	   * @param[out] o_ptMin
	   */
		static void GetBox(const NctiPosition& i_PositionVec, NctiPosition& o_ptMax, NctiPosition& o_ptMin);
		/**
	   * @brief get box of point,include i_PositionVec, o_ptMax, and o_ptMin
	   * @param[in] i_PositionVec, it is a point list
	   * @param[out] o_ptMax
	   * @param[out] o_ptMin
	   */
		static void GetBox(const std::vector<NctiPosition>& i_PositionVec, NctiPosition& o_ptMax, NctiPosition& o_ptMin);
		/**
	   * @brief get box of point,include i_PositionVec, o_ptMax, and o_ptMin
	   * @param[in] i_PositionVec, it is a point list with double
	   * @param[out] o_ptMax
	   * @param[out] o_ptMin
	   */
		static void GetBox(const std::vector<Ncti_Double>& i_PositionVec, NctiPosition& o_ptMax, NctiPosition& o_ptMin);
		/**
	   * @brief get box of point,include i_PositionVec, o_ptMax, and o_ptMin
	   * @param[in] i_PositionVec, it is a point list with float
	   * @param[out] o_ptMax
	   * @param[out] o_ptMin
	   */
		static void GetBox(const std::vector<Ncti_Float>& i_PositionVec, NctiPosition& o_ptMax, NctiPosition& o_ptMin);
		/**
	   * @brief get box of point list
	   * @param[in] i_st
	   * @param[in] i_ed
	   * @param[out] o_Vec
	   */
		static void GetBox(const NctiPosition& i_st, const NctiPosition& i_ed, std::vector<NctiPosition>& o_Vec);
		/**
	   * @brief intersect triangle by original and direction
	   * @param[in] i_orig
	   * @param[in] i_dir
	   * @param[in] i_v0, the triangle point
	   * @param[in] i_v1, the triangle point
	   * @param[in] i_v2, the triangle point
	   * @param[out] o_t
	   * @param[out] o_u
	   * @param[out] o_v
	   * @return Ncti_Boolean, do they intersect
	   */
		static Ncti_Boolean IntersectTriangle(const NctiPosition& i_orig, const NctiVector& i_dir,
			const NctiPosition& i_v0,
			const NctiPosition& i_v1,
			const NctiPosition& i_v2,
			Ncti_Double* o_t,
			Ncti_Double* o_u,
			Ncti_Double* o_v);
		static Ncti_Boolean IntersectLine(const NctiPosition& i_orig, const NctiVector& i_dir, const NctiPosition& i_ptS, const NctiPosition& i_ptE, Ncti_Double pickSize ,Ncti_Double& o_t, NctiPosition& o_pt);
		static Ncti_Boolean IntersectPoint(const NctiPosition& i_orig, const NctiVector& i_dir, const NctiPosition& i_ptS, Ncti_Double pickSize, Ncti_Double& o_t, NctiPosition& o_pt);
		static Ncti_Boolean RecIntersectTriangle(
			const NctiPosition& i_pt1, 
			const NctiPosition& i_pt2, 
			const NctiPosition& i_pt3,
			const NctiPosition& i_pt4,
			const NctiVector& i_dir,
			const NctiPosition& i_v0,
			const NctiPosition& i_v1,
			const NctiPosition& i_v2);
		static Ncti_Boolean RecIntersectLine(
			const NctiPosition& i_pt1,
			const NctiPosition& i_pt2,
			const NctiPosition& i_pt3,
			const NctiPosition& i_pt4,
			const NctiVector& i_dir,
			const NctiPosition& i_v0,
			const NctiPosition& i_v1);
		/**
	   * @brief determine whether the point is inside
	   * @param[in] i_ptBase
	   * @param[in] i_center, the center of box
	   * @param[in] i_vecH, the h direction of box
	   * @param[in] i_vecW, the w direction of box
	   * @param[in] i_vecL, the l direction of box
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean PointIsInBox(const NctiPosition& i_ptBase, 
			const NctiPosition& i_center, 
			const NctiVector& i_vecH, 
			const NctiVector& i_vecW, 
			const NctiVector& i_vecL);
		static Ncti_Boolean IsIntersectTwoRec(
			Ncti_Double i_Left,
			Ncti_Double i_Top,
			Ncti_Double i_Right,
			Ncti_Double i_Bottom,
			Ncti_Double i_LeftN,
			Ncti_Double i_TopN,
			Ncti_Double i_RightN,
			Ncti_Double i_BottomN);
		/**
	   * @brief Dot Product with two vectors, it is same with NctiBaseGeometryMath::DotProduct
	   * @param[in] i_vec1
	   * @param[in] i_vec2
	   * @return Ncti_Double
	   */
		static Ncti_Double DotProduct(const NctiVector& i_vec1, const NctiVector& i_vec2);
		/**
	   * @brief Cross Product with two vectors, it is same with NctiBaseGeometryMath::CrossProduct
	   * @param[in] i_vec1
	   * @param[in] i_vec2
	   * @param[in] o_VecResult, get the three direction
	   */
		static void CrossProduct(const NctiVector& i_vec1, const NctiVector& i_vec2, NctiVector& o_VecResult);
		/**
	   * @brief calculation the normal of mesh list.
	   * @param[in] i_NctiMeshDataPt
	   * @param[out] o_normals
	   */
		static void CalNormal(const NctiMeshDataPt& i_NctiMeshDataPt, std::vector<Ncti_Float>& o_normals);
		/**
	   * @brief calculation the normal of mesh list.
	   * @param[in] i_positions
	   * @param[in] i_triangles
	   * @param[out] o_normals
	   */
		static void CalNormal(const std::vector<Ncti_Float>& i_positions, const std::vector<Ncti_UInteger>& i_triangles, std::vector<Ncti_Float>& o_normals);
		/**
	   * @brief internal use
	   */
		static Ncti_Boolean CalTetrahedronFaceDir(
			const NctiPosition& i_pt1, 
			const NctiPosition& i_pt2, 
			const NctiPosition& i_pt3, 
			const NctiPosition& i_pt4, 
			Ncti_Integer i_z, 
			Ncti_Boolean i_IsOut = true);
		/**
	   * @brief internal use
	   */
		static Ncti_Boolean CalTetrahedronFaceDir(
			const NctiPosition& i_pt1,
			const NctiPosition& i_pt2,
			const NctiPosition& i_pt3, 
			const NctiPosition& i_Up, 
			Ncti_Boolean i_IsOut = true);
		/**
	   * @brief internal use
	   */
		static void CalTangentAndBiTangent(const NctiMeshDataPt& i_NctiMeshData, std::vector<Ncti_Float>& o_TangentVec, std::vector<Ncti_Float>& o_BiTangentVec);
		/**
	   * @brief internal use
	   */
		static void CalTangentAndBiTangentEx(
			const NctiPosition& i_pt1,
			const NctiPosition& i_pt2, 
			const NctiPosition& i_pt3, 
			const NctiPosition& i_ptUV1, 
			const NctiPosition& i_ptUV2,
			const NctiPosition& i_ptUV3,
			NctiVector& o_Tangent,
			NctiVector& o_BiTangent);
		/**
	   * @brief internal use
	   */
		static void generateTangents(const NctiMeshDataPt& i_NctiMeshData, std::vector<Ncti_Float>& o_TangentVec, std::vector<Ncti_Float>& o_BiTangentVec);
		/**
	   * @brief get NctiTransf by rotate
	   * @param[in] i_pt_center
	   * @param[in] i_ver_normal
	   * @param[in] i_dbAngle, angle is degree
	   * @return NctiTransf
	   */
		static NctiTransf SDRotateTrans(const NctiPosition& i_pt_center, const NctiVector& i_ver_normal, Ncti_Double i_dbAngle);
		/**
	   * @brief get NctiTransf by scale
	   * @param[in] i_pt_center
	   * @param[in] i_ver_x
	   * @param[in] i_ver_y
	   * @param[in] i_dbscalex
	   * @param[in] i_dbscaley
	   * @param[in] i_dbscalez
	   * @return NctiTransf
	   */
		static NctiTransf SDScaleTrans(const NctiPosition& i_pt_center, const NctiVector& i_ver_x, const NctiVector& i_ver_y, Ncti_Double i_dbscalex, Ncti_Double i_dbscaley, Ncti_Double i_dbscalez);
		/**
	   * @brief internal use
	   */
		static void GetVerticesUserAxis(const std::vector<std::vector<Ncti_Double>>& iPosVec, std::vector<std::vector<Ncti_Double>>& oPosVec,
			const NctiPosition& UserOrigin,
			const NctiVector& VecX,
			const NctiVector& VecY,
			const NctiVector& VecZ);
		/**
	   * @brief internal use
	   */
		static void GetNormalUserAxis(const std::vector<std::vector<Ncti_Double>>& iPosVec, std::vector<std::vector<Ncti_Double>>& oPosVec,
			const NctiPosition& UserOrigin,
			const NctiVector& VecX,
			const NctiVector& VecY,
			const NctiVector& VecZ);
		/**
	   * @brief internal use
	   */
		static Ncti_Boolean SDCalMeshAndUVAreaScale(const NCTI::NctiMeshDataPt& i_MeshData, Ncti_Double& o_scale);
		/**
	   * @brief internal use
	   */
		static Ncti_Boolean SDCalMeshAndUVAreaScale(const NCTI::NctiMeshData& i_MeshData, Ncti_Double& o_scale);
		/**
	   * @brief internal use
	   */
		static void CreateCirecleByPolyline(const NctiPosition& i_pt, Ncti_Double* i_XList, Ncti_Double* i_YList, int len,
			NctiMeshData& o_NctiMeshData);
		/**
	   * @brief internal use
	   */
		static void CreateRecByCenterWH(const NctiPosition& i_pt, Ncti_Double w, Ncti_Double h, const NctiVector& i_vecX, const NctiVector& i_vecY,
			NctiMeshData& o_NctiMeshData);
		/**
	   * @brief internal use
	   */
		static void CreateCone(const NctiPosition& i_pt, Ncti_Double radius, Ncti_Double h, int numsides, const NctiVector& i_vec, const NctiVector& i_nor,
			NctiMeshData& o_NctiMeshData);
		/**
	   * @brief internal use
	   */
		static Ncti_Boolean	GeneratePointOnCircle(NctiPosition* i_point,const NctiPosition& i_center, Ncti_Double radius, int axis, Ncti_Double angle);
		/**
	   * @brief internal use
	   */
		static Ncti_Boolean	GeneratePointsOnCircle(NctiPosition* i_points, const NctiPosition& i_center, Ncti_Double radius, int axis, int numpoints);
		/**
	   * @brief internal use
	   */
		static void CreateCircle(const NctiPosition& i_pt, int num, Ncti_Double r, const NctiVector& i_vecUp, const NctiVector& i_nor, 
			NctiMeshData& o_NctiMeshData);
		/**
	   * @brief internal use
	   */
		static void CreateArc(const NctiPosition& i_ptOne, const NctiPosition& i_ptTwo, const NctiPosition& i_ptThree, int i_numPoints,
			NctiMeshData& o_NctiMeshData);
		/**
	   * @brief internal use
	   */
		static void CreateArc(const NctiPosition& i_center, const NctiVector& i_VecH, const NctiVector& i_Nor, int i_numPoints, Ncti_Double r, Ncti_Double AngleS, Ncti_Double AngleE,
			NctiMeshData& o_NctiMeshData);
		/**
	   * @brief internal use
	   */
		static void CreateArc(const NctiPosition& i_center, const NctiVector& i_VecH, const NctiVector& i_Nor, int i_numPoints, Ncti_Double r, Ncti_Double AngleS, Ncti_Double AngleE,
			std::vector<Ncti_Float>& o_PolyLineVec);
		//三点获取平面弧信息  i_ptOne：第一个端点；i_ptTwo：另一个端点；i_ptThree：中间点
		/**
	   * @brief internal use
	   */
		static void CalcArcDate(const NctiPosition& i_ptOne, const NctiPosition& i_ptTwo, const NctiPosition& i_ptThree, NctiPosition& o_CenterPt, double& o_Radius, double& o_Startngle, double& o_EndAngle);
		/**
	   * @brief internal use
	   */
		static void CalThreeNormal(const NctiVector& i_vec, NctiVector& o_vec);
		/**
	   * @brief internal use
	   */
		static NctiVector CalNormalFromNodes(const NctiPosition& n1, const NctiPosition& n2, const NctiPosition& n3);
	};
}

#endif // !NctiBaseUtility_H
