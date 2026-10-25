#ifndef NctiGeoDataDef_H
#define NctiGeoDataDef_H

#include <vector>
#include "NctiPosition.h"
#include "NctiAxis.h"

enum Ncti_Geo_Create_Sphere {
	sphere_default = 0,
	sphere_angle3,
	sphere_angle1_angle2,
	sphere_angle1_angle2_angle3
};

struct Ncti_Geo_Periodic {
	//[0,1,2]代表[x,y,z]方向
	Ncti_Integer m_DirID = -1;
	Ncti_Double m_DirLength = 0.0f;
	//是否偏移
	Ncti_Boolean m_isTrim = true;
	Ncti_Double m_FirstPerioParam = 0.0f;
	Ncti_Integer m_Times = 0;
	friend std::ostream& operator<<(std::ostream& os, const Ncti_Geo_Periodic& value)
	{
		os << "Ncti_Geo_Periodic m_DirID:" << value.m_DirID;
		os << " Ncti_Geo_Periodic m_DirLength:" << value.m_DirLength;
		os << " Ncti_Geo_Periodic m_isTrim:" << value.m_isTrim;
		os << " Ncti_Geo_Periodic  m_FirstPerioParam:" << value.m_FirstPerioParam;
		os << " Ncti_Geo_Periodic  m_Times:" << value.m_Times;
		return os;
	}
};

struct Ncti_Geo_Unifysamedom {
	Ncti_Boolean anUFaces = true;
	Ncti_Boolean anUEdges = true;
	Ncti_Boolean anConBS = false;
	Ncti_Boolean isAllowInternal = false;
	Ncti_Boolean isSafeInputMode = true;
	Ncti_Double aLinTol = 1.e-7;
	Ncti_Double aAngTol = 1.e-12;
};

struct Ncti_Geo_Fixshape{
    Ncti_Double prec = 1.e-7;
    Ncti_Double tol = 1.e-7;
	Ncti_Double angleDeg = -1;
	Ncti_Double tailWidth = -1;
	Ncti_Integer LackingMode = -1;
	Ncti_Integer DegeneratedMode = -1;
	Ncti_Integer ShiftedMode = -1;
	Ncti_Integer SmallMode = -1;
	Ncti_Integer NotchedEdgesMode = -1;
	Ncti_Integer SelfIntersectionMode = -1;
	Ncti_Integer OrientationMode = -1;
	Ncti_Integer MissingSeamMode = -1;
};

struct Ncti_Geo_Extrema
{
	std::vector<Ncti_Double> m_Extrema_val;
	std::vector<NCTI::NctiPosition> m_Pnts1,m_Pnts2;
	std::vector<Ncti_Double> m_Params[4];//u1 v1 u2 v2
	Ncti_Boolean m_IsParallel = false;//是否平行
	Ncti_Boolean m_Success = false;
};
struct NctiSewwpSection
{
	NCTI_MODEL_TAG m_section_body;//截面实体
	NCTI_MODEL_TAG m_section_cell;//抽取自m_section_body，nullptr则m_section_body为输入
	NCTI_MODEL_TAG m_vectex_body;//接触点实体
	NCTI_MODEL_TAG m_vectex_cell;//抽取自m_vectex_body，nullptr则m_vectex_body为输入
	Ncti_Boolean m_to_transform;//是否进行移动
	Ncti_Boolean m_to_rotate;//是否进行旋转
	NctiSewwpSection() :m_section_body(nullptr), m_section_cell(nullptr), m_vectex_body(nullptr), m_vectex_cell(nullptr), m_to_transform(false), m_to_rotate(false) {}
};
struct Ncti_Geo_Evol_Radius
{
	NCTI_MODEL_TAG m_edge;//边
	std::vector<Ncti_Double> m_edge_parm;//边上参数
	std::vector<Ncti_Double> m_radius;//边上参数对应的半径
};
struct Ncti_Geo_Approx_Data
{
	NCTI_MODEL_TAG m_Face;//面
	NCTI_MODEL_TAG m_Edge;//面上的边
	Ncti_Integer   m_Tang;//连续性 i means constraints Gi
};
struct Ncti_RemoveInt_Item
{
	std::vector<NCTI_MODEL_TAG> LSToTake;
	std::vector<NCTI_MODEL_TAG> LSToAvoid;
	Ncti_Integer Material;
};

struct Ncti_Sewing_Params {
	Ncti_Boolean m_SewingMode = true;
	Ncti_Boolean m_AnalysisMode = true;
	Ncti_Boolean m_CuttingMode = true;
	Ncti_Boolean m_NonManifoldMode = false;
	Ncti_Boolean m_SameParameterMode = true;
	Ncti_Boolean m_FloatingEdgesMode = false;
	Ncti_Boolean m_FaceMode = true;
};
//OCC shapeType
enum Ncti_Geo_Shape_Type {
	NCTI_COMPOUND,
	NCTI_COMPSOLID,
	NCTI_SOLID,
	NCTI_SHELL,
	NCTI_FACE,
	NCTI_WIRE,
	NCTI_EDGE,
	NCTI_VERTEX,
	NCTI_SHAPE
};

enum Ncti_Geo_Continue_Type {
    NCTI_C0 = 0,
    NCTI_G1,
    NCTI_C1,
    NCTI_G2,
    NCTI_C2,
    NCTI_C3,
    NCTI_CN
};

struct Ncti_Geo_Project_Point
{
	NCTI::NctiPosition m_Position;
	std::vector<Ncti_Double> m_Params;
};

struct Ncti_Geo_Circle_Property
{
	NCTI::NctiPosition m_Pt;
	NCTI::NctiVector m_Normal;
	NCTI::NctiVector m_XDir;
	Ncti_Double m_Radius;
};
struct Ncti_Geo_Ellipse_Property
{
	NCTI::NctiPosition m_Pt;
	NCTI::NctiVector m_Normal;
	NCTI::NctiVector m_XDir;
	Ncti_Double m_MajorRadius;
	Ncti_Double m_MinorRadius;
};
struct Ncti_Geo_Edge_Property
{
	NCTI::NctiPosition m_FirstPt;
	NCTI::NctiPosition m_LastPt;
	Ncti_Double m_Length;
	Ncti_Double m_first;
	Ncti_Double m_last;
};
struct Ncti_Geo_Cylinder_Property
{
	NCTI::NctiPosition m_Pt;
	NCTI::NctiVector m_Normal;
	NCTI::NctiVector m_XDir;
	Ncti_Double m_Height;
	Ncti_Double m_Radius;
};

enum Ncti_Attrib_Type
{
    ATTRIB_Double = 0,
    ATTRIB_Int,
    ATTRIB_String,
    ATTRIB_Pointer,
    ATTRIB_UString,
    ATTRIB_Vector,
    ATTRIB_Coord,
    ATTRIB_Dir,
    ATTRIB_Axes,
};

//拓补对象相对于其底层几何对象的方向
enum Ncti_Topol_Orientation
{
	Topol_FORWARD,
	Topol_REVERSED,
	Topol_INTERNAL,
	Topol_EXTERNAL
};

//异常Cell类型
enum Ncti_AbnormalCell_Type
{
	Mini_AbnormalCell_Type = 0,

	//游离的Vertex、Edge、Face：指的是一些孤立的点、线、面等
	//建议的处理方式：移除特征（目前还没有适合的测试模型）
	Free_Cell = 1,

	//冗余的拓扑对象：指的是一些多余的点、线等
	//建议的处理方式：移除冗余的拓扑对象
	Redundant_Cell = Free_Cell << 1,

	//重叠边：指的是一些有重叠区域的边
	//建议的处理方式：切除
	Overlap_Edge = Redundant_Cell << 1,

	//折叠的Face：指的是两个有共同边的面片，在共边处两个面的法向近似反向
	//建议的处理方式：移除特征
	Collapse_Face = Overlap_Edge << 1,

	//非流型的Vertex、Edge、Face：
	//建议的处理方式：移除特征（目前还没有适合的测试模型）
	NonManifold_Cell = Collapse_Face << 1,

	//小间隙边：指的是sheet中有小的缝隙，导致模型不能形成实体
	//建议的处理方式：缝合
	Wounds_Edge = NonManifold_Cell << 1,

	//面积极小的面片：指的是模型存在的一些零碎面片，以至于影响到网格剖分
	//建议的处理方式：移除特征
	SmallArea_Face = Wounds_Edge << 1,

	//细长的面片：指的是模型中存在一些宽度方向尺寸极小的面片，以至于影响网格剖分
	//建议的处理方式：移除特征
	Slot_Face = SmallArea_Face << 1,

	//两面片相交形成尖角：指的是两个面片在相交处的法向近似反向，以至于影响网格剖分
	//建议的处理方式：倒圆角
	Sharp_IntersectFace = Slot_Face << 1,

	Max_AbnormalCell_Type
};

//异常Cell临界值
struct AbnormalCellCriticalValue
{
	//重叠边之间的最大距离
	double _maxOverlapEdgeDistance = 1.0e-2;

	//两个面片在共边处的夹角如果小于_maxCollapseAngle，被认定为是折叠的必要条件
	double _maxCollapseAngle = 5.0;

	//如果被折叠面片上有测试点到基础面片的距离大于_maxCollapseDistance，被认定为是不满足折叠的条件
	double _maxCollapseDistance = 1.0e-2;

	//被认定为是缝隙的最大间隙
	double _maxWoundsEdgeGap = 1.0e-1;

	//被认定为面积极小面片的最大面积
	double _maxSmallFaceAreaValue = 2.0e-3;

	//被认定为细长面片的最大宽度
	double _maxSlotFaceWidth = 1.0e-2;

	//两个面片在共边处的夹角如果小于_maxSharpIntersectFaceAngle，被认定为两面片相交形成尖角
	double _maxSharpIntersectFaceAngle = 5.0;
};

class meshgems_clamped_data
{
public:
	virtual ~meshgems_clamped_data() {}

private:

};

struct Meshgems_Vertex_Data
{
	Ncti_Integer _ncti_id = -1;
	NCTI::NctiPosition _position;
};

struct Meshgems_Edge_Data
{
	Ncti_Integer _ncti_id = -1;
	Ncti_Integer _ncti_uvids[2] = { -1 };
	Ncti_Topol_Orientation _orientation = Topol_FORWARD;		//Edge相对于底层curve的方向
	Ncti_Double _miniParam = 0.0;
	Ncti_Double _maxParam = 0.0;
	Meshgems_Vertex_Data _startVertex;
	Meshgems_Vertex_Data _endVertex;
	NCTI_MODEL_TAG _pCurve = nullptr;
};

struct Meshgems_Face_data
{
	Ncti_Integer _ncti_id = -1;
	Ncti_Topol_Orientation _orientation = Topol_FORWARD;		//Face相对于底层surface的方向
	std::vector<Meshgems_Edge_Data> _vtEdges;					//边集合
	NCTI_MODEL_TAG _pSurface = nullptr;

	double _u_range[2] = { 0.0 };								//surface的U参数范围
	double _v_range[2] = { 0.0 };								//surface的V参数范围
	bool _u_periodic = false;									//U方向是否是周期性的
	bool _v_periodic = false;									//V方向是否是周期性的

	Ncti_Integer _nKernel = 0;									//0 : OCC;	1 : Parasolid
	bool _bClosed = false;										//面片是否闭合
};

struct Helical_Geometry_Data
{
	NCTI::NctiAxis _rotateAxis;									//旋转轴
	int _nHand = 0;											//1 : 左手法则;		0 : 右手法则
	double _fTurnsRange[2] = { 0.0, 360.0 };				//扫掠范围
	double _fHelicalPitch = 0.0;							//每扫掠一周，在_rotateAxis.GetNormal()上的提升高度
	double _fSpiralPitch = 0.0;								//每扫掠一周，旋转半径的变化量
	double _fTolerance = 0.01;								//拟合精度
};

struct BodyHollowOption
{
	std::vector<std::pair<NCTI_MODEL_TAG, double> > _vtOffsetFaces;			//面片及其对应的局部抽壳厚度
	std::vector<NCTI_MODEL_TAG> _vtPierceFaces;								//开放的面片
	int _nOffsetStep;		//创建台阶面;	0 : 不创建台阶面
							//1 : 只在偏移面与不偏移面之间，或者是偏移面与开放面之间，创建台阶面
							//2 : 所有的平滑边界都创建台阶面;
							//3 : 除了那些可以创建生长面以外的平滑边界都创建台阶面

	int _nGrow;				//修复冲突的方式	0 : 兼容之前的版本;
							//1 : 由内核确定生长哪些面片；
							//2 : 生长那些在偏移过程中移动的面片；
							//3 : 生长那些在偏移过程中固定不变的面片；
							//4 : 不生长，在破损处采用加盖的方式进行修复
							//5 : 不采取任何措施进行修复，如果出现这种情况，镂空功能将失败

	int _nEdgeOffsetBlend;	//凸边处是否倒圆角 0 : 不倒圆角		1 : 倒圆角
};

enum NCTIFaultCode
{
	NCTI_BODY_state_corrupt = 0,
	NCTI_BODY_state_invalid_ident,
	NCTI_BODY_state_inside_out,
	NCTI_BODY_state_bad_regions,
	NCTI_EDGE_state_open,
	NCTI_EDGE_state_bad_vertex,
	NCTI_EDGE_state_reversed,
	NCTI_EDGE_state_bad_spcurve,
	NCTI_EDGE_state_vertices_touch,
	NCTI_EDGE_state_bad_face_order,
	NCTI_EDGE_state_bad_wire_ed_ed,
	NCTI_EDGE_state_open_nmnl,
	NCTI_EDGE_state_bad_vertex_nmnl,
	NCTI_EDGE_state_bad_sp_nmnl,
	NCTI_EDGE_state_reversed_nmnl,
	NCTI_ENTITY_state_invalid,
	NCTI_FACE_state_bad_vertex,
	NCTI_FACE_state_bad_edge,
	NCTI_FACE_state_bad_edge_order,
	NCTI_FACE_state_no_vtx_at_sing,
	NCTI_FACE_state_bad_loops,
	NCTI_FACE_state_self_int,
	NCTI_FACE_state_bad_wire_fa_ed,
	NCTI_FACE_state_check_fail,
	NCTI_FACE_state_bad_face_face,
	NCTI_GEOM_state_self_int,
	NCTI_GEOM_state_degenerate,
	NCTI_REGION_state_bad_shells,
	NCTI_SHELL_state_bad_topol_geom,
	NCTI_SHELL_state_bad_sh_sh,
	NCTI_TOPOL_state_not_G1,
	NCTI_TOPOL_state_size_box,
	NCTI_TOPOL_state_check_fail,
	NCTI_TOPOL_state_no_geom,
	NCTI_BODY_state_ok,
	NCTI_FACE_state_redundant,
	NCTI_CURVE_state_inconsistent,
	NCTI_LOOP_state_invalid,
	NCTI_EDGE_state_bad_order,
	NCTI_ATTDEF_state_bad_name,
	NCTI_ATTRIB_state_bad_string,
	NCTI_ATTRIB_state_invalid_att,
	NCTI_ATTRIB_state_bad_data_len,
	NCTI_ATTRIB_state_bad_ustring,
	NCTI_ATTRIB_state_byte_oor,
	NCTI_ATTRIB_state_empty_field,
	NCTI_ATTRIB_state_int_oor,
	NCTI_ATTRIB_state_non_unit_vec,
	NCTI_ATTRIB_state_real_oor,
	NCTI_ATTRIB_state_short_oor,
	NCTI_SESSION_state_corrupt_c,
	NCTI_BB_state_corrupt_c,
	NCTI_KI_LIST_state_corrupt_c,
	NCTI_GEOM_state_corrupt_c,
	NCTI_TRANSF_state_corrupt_c,
	NCTI_ASSEMBLY_state_corrupt_c,
	NCTI_PARTITION_state_corrupt_c,
	NCTI_PARTITION_state_xref_c,
	NCTI_ITEM_state_unattached_c,
	NCTI_BCURVE_state_close_knots_c,
	NCTI_BSURF_state_close_u_knots_c,
	NCTI_BSURF_state_close_v_knots_c,
	NCTI_EDGE_state_touch_edge_c,
	NCTI_TOPOL_state_bad_closed_c,
	NCTI_TOPOL_state_u_parm_degen_c,
	NCTI_TOPOL_state_v_parm_degen_c,
	NCTI_TOPOL_state_parm_degen_c,
	NCTI_TOPOL_state_u_phys_degen_c,
	NCTI_TOPOL_state_v_phys_degen_cc,
	NCTI_TOPOL_state_phys_degen_c
};

//对象检查错误结果
struct BodyCheckFaultResult
{
	NCTIFaultCode _nFaultCode;					//错误码
	Ncti_Integer _entity_1 = 0;					//发生错误的对象1
	Ncti_Integer _entity_2 = 0;					//发生错误的对象2
};

enum NCTISelfIntDegensType
{
	NCTI_self_int_degen_none = 0,
	//...............

	NCTI_self_int_type_general,
	NCTI_self_int_type_sing,
	NCTI_self_int_type_mixed,
	//...............
	//以上为自交类型

	NCTI_CURVE_degen_type_param,
	NCTI_CURVE_degen_type_phys,
	NCTI_CURVE_degen_type_on_surf,
	//...............
	//以上为曲线退化类型

	NCTI_SURF_degen_type_param,
	NCTI_SURF_degen_type_phys_cvx,
	NCTI_SURF_degen_type_phys_ccv,
	NCTI_SURF_degen_type_phys_mixed,
	NCTI_SURF_degen_type_phys_undef
	//...............
	//以上为曲面退化类型
};

//对象自交、退化信息
struct CellSelfIntDegensInfo
{
	NCTISelfIntDegensType _nType;			//类别
	std::vector<NCTI::NctiPosition> _vtPosition;	//自交点，或者退化点集合
	std::vector<Ncti_Double> _vtRange;		//自交或者退化区域
};

struct NCTIBodyExtendOption
{
	NCTI_MODEL_TAG i_pBodyToExtend;  //需要延申的BODY
	std::vector<NCTI_MODEL_TAG> edgesOfBody;   //延申的边，必须属于需要延申的BODY
	double extendDistance;        //延申距离，仅isExtendDistance=true时有效
	NCTI_MODEL_TAG i_pFenceBody;  //延申截止对象BODY,仅isExtendDistance=false时有效
	int extendShapeType;          //延申类型      0：线性延申；1：柔和延申；2反射延申；3内部延申；4圆弧延申
	int extensionSmoothnessType;  //延申时光滑类型：0：g0 不产生光滑效果;1:g1 产生光滑效果
};

struct NCTIFaceTransformOption
{
	bool _bMergeFace = true;
	int _nGrow = 0;						//修复冲突的方式	0 : 兼容之前的版本;
										//1 : 由内核确定生长哪些面片；
										//2 : 生长那些在变换过程中移动的面片；
										//3 : 生长那些在变换过程中固定不变的面片；
										//4 : 不生长，在破损处采用加盖的方式进行修复
										//5 : 不采取任何措施进行修复，如果出现这种情况，变换功能将失败

	int _nTransformStep = 0;			//创建台阶面;	0 : 不创建台阶面
										//1 : 在平滑的边界处，创建台阶面
										//2 : 在所有的边界处，创建台阶面
										//3 : 在侧面与相邻面不一致的情况下，创建台阶面
										//4 : 除非可以通过生长相关面的方式，解决问题，否则在平滑的边界处，创建台阶面;

	int _nPreferAdjacency = 0;			//控制变换面与相邻面相交的方式	0 : 尽量保持或者延伸相邻面;
										//1 : 尽量选择新的相邻面

	double _fTolerance = 0.01;			//变换精度
};

struct NCTITopolFacetOption
{
	int _nMatch = 1;					//相邻面片离散过程中的匹配方式		0 : 不匹配
										// 1 : 几何匹配，相邻面片在相交处，离散后的网格几何上精确相交，但拓补上是分离的
										// 2 : 拓补匹配，相邻面片在相交处，离散后的网格几何上精确相交，并且具有一致的拓补关系，也就是网格顶点也能够匹配上
										// 3 : 裁剪，网格剖分时，不考虑相邻面片，结果是，网格在面片相交处有可能重叠，或者会有间隙

	double _fSurfacePlaneTol = 1.0e-2;	//离散化后网格与原面片之间的容差，如果为0，采用内部计算的方式确定

	double _fCurveChordTol = 1.0e-2;	//在边缘区域，离散化后网格边与原面片边之间的容差，如果为0，采用内部计算的方式确定

	bool _bOutputNormal = false;		//是否输出网格顶点处的法向
};

enum NCTIGeneralType
{
	NCTI_General_nm_edge_c=23770,        //边非流形
	NCTI_General_nm_vertex_c,            //顶点非流形
	NCTI_General_opposed_faces_c,        //边有反向面
	NCTI_General_solid_internal_c,       //实体包含内部实体
	NCTI_General_mixed_dimension_c,      //多维混合
	NCTI_General_wire_in_solid_c,        //实体包含线框
	NCTI_General_frame_c,                //出现frame
	NCTI_General_OK
};
struct NCTIBodyGeneralResult
{
	NCTIGeneralType _generalType;      //见枚举说明
	Ncti_Integer _pTopol;              //有错误的topol
};

enum NCTIBbClass
{
	NCTI_Class_null=0,
	NCTI_Class_point = 2001,
	NCTI_Class_curve,
	NCTI_Class_surf,
	NCTI_Class_transf,
	NCTI_Class_vertex=5001,
	NCTI_Class_edge,
	NCTI_Class_loop,
	NCTI_Class_face,
	NCTI_Class_shell,
	NCTI_Class_body,  
	NCTI_Class_instance,
	NCTI_Class_assembly,
	NCTI_Class_region=5011,
	NCTI_Class_attdef = 6003,
	NCTI_Class_group=6005
};

struct NCTIBbParam
{
	std::vector<NCTIBbClass> create;
	std::vector<NCTIBbClass> deleet;
	std::vector<NCTIBbClass> copy;
	std::vector<NCTIBbClass> transfer;
	std::vector<NCTIBbClass> merge;
	std::vector<NCTIBbClass> split;
	std::vector<NCTIBbClass> transform;
	std::vector<NCTIBbClass> change_attrib;
	std::vector<NCTIBbClass> change;

};

enum NCTIBbStatus
{
	NCTI_BB_status_off_c=14501,        // bb 关并清楚数据
	NCTI_BB_status_on_c,         // bb 开并记录实体数据
	NCTI_BB_status_user_field_c  // bb 开并记录实体数据和用户数据
};
enum NCTIParamConsistent
{
	NCTI_PARAM_consistent_set_c,
	NCTI_PARAM_consistent_unset_c
};
enum NCTIKeepAsFacet
{
	NCTI_BODY_keep_as_facet_yes_c,
	NCTI_BODY_keep_as_facet_no_c
};
enum NCTIBoundType
{
	NCTI_bound_distance_c=21850,   //到拉伸面的距离
	NCTI_bound_sheet_c,            //sheet类型边界
	NCTI_bound_surf_c,             //surf类型边界
	NCTI_bound_face_c,             //face类型边界
	NCTI_bound_body_c,			   //body类型边界
	NCTI_bound_none_c,             //空边界
};
enum NCTIBoundSide
{
	NCTI_bound_side_both_c=22980,  //结果为拉伸的整个，包含内外
	NCTI_bound_side_out_c,         //结果取边界交的外部部分
	NCTI_bound_side_in_c           //结果取边界交的内部部分
};
struct NCTIBoundDef
{
	NCTIBoundType _boundType;      //边界类型，详见枚举说明
	bool _forward;                 //true:在拉伸路径的方向；false：反拉伸路径的方向
	double _distance;              //拉伸距离值 必须大于等于0
	NCTI_MODEL_TAG _boundEntity;   //边界实体，可以是body、face 、surface
	bool _nearest;                 //true:多次相交时使用最近的区域；false：选择第一个区域
	int _nthDivision;              //特定区域索引
	NCTIBoundSide _side;           //如果被边界实体切割的话，选择结果取哪部分，详见枚举说明

};
struct NCTIBodyExtrudeOption
{
	NCTIBoundDef _startBound;                  //起始边界，详见结构说明
	NCTIBoundDef _endBound;                    //终止边界，详见结构说明
	NCTI_MODEL_TAG _extrudedBody;              //取代拉伸截面的被边界处理的体
	bool _allowDisjoint;                       //是否容许有孤立的组件
	NCTIParamConsistent _paramConsistent;      //是否总是保持拉伸方向上一致
	bool _havePlineAngle;                      //是否支持多段线角度
	double _plineAngle;                        //多段线角度值
	NCTIKeepAsFacet _keepAsFacet;              //是否结果实体三角化
	std::vector< NCTI_MODEL_TAG> _subObj;   //子物体，比如某个体的面或者边等
};

struct NCTIBodyExtrudeParam
{
	NCTI_MODEL_TAG _profile;                   //待拉伸的截面
	NCTI::NctiVector _pathVector;              //拉伸的矢量
	NCTIBodyExtrudeOption _extrudeOption;      //拉伸设置，详见结构说明
};

enum NCTILatticeCmdType
{
	NCTI_LATTICE_create_by_graph=0,
	NCTI_LATTICE_make_patterned,
	NCTI_LATTICE_offset,
	NCTI_LATTICE_clip,
	NCTI_LATTICE_make_bodies,
	NCTI_LATTICE_disjoin,
	NCTI_LATTICE_combine,
	NCTI_LATTICE_inBox
};

struct NCTILatticeCreateParam
{
	std::vector<NCTI::NctiPosition> _ballPositions;
	std::vector<Ncti_Double> _ballRadii;
	std::vector<Ncti_Integer> _rodStartIndex;
	std::vector<Ncti_Integer> _rodEndIndex;
	std::vector<Ncti_Double> _rodRadii;
	NCTILatticeCmdType _cmdType;
};

enum class NCTIMeshCmdType
{
	NCTI_MESH_create_from_facets = 0,
	NCTI_MESH_fill_holes,
	NCTI_MESH_fix_defects,
	NCTI_MESH_imprint_vectors,
	NCTI_MESH_make_bodies,
	NCTI_MESH_make_surf_trimmed
};
struct NCTIMeshCreateParam
{
	std::vector<NCTI::NctiPosition> _Positions;
	std::vector<Ncti_Integer> _Index;
	NCTIMeshCmdType _cmdType;
};

enum class NCTIBsurfCmdType
{
	NCTI_Bsurf_project_point = 0,
	NCTI_Bsurf_extend_trim,
	NCTI_Bsurf_fill_hole,
	NCTI_Bsurf_create_face_by_curves,
	NCTI_Bsurf_edge_loft_face,
	NCTI_Bsurf_edge_join,
	NCTI_Bsurf_sew_surf,
	NCTI_Bsurf_face_blend,
	NCTI_Bsurf_fetch_faces,
	NCTI_Bsurf_create_sheet
};
struct NCTIBsurfEditParam
{
	std::vector< NCTI_MODEL_TAG> _iModels;
	std::vector< NCTI::NctiPosition>_iPosition;
	std::vector<Ncti_Integer> _Index;
	std::vector<Ncti_Double> _value;
	NCTIBsurfCmdType _iCmd;
	Ncti_Boolean _iIsSide;
}; 

//曲面参数重参化选项
struct NCTISurfReparameteriseOption
{
	Ncti_Boolean _bUVSwap = false;					//是否U、V交换
	Ncti_Boolean _bUReverse = false;				//U方向是否反向
	Ncti_Boolean _bVReverse = false;				//V方向是否反向
	Ncti_Boolean _bUReparameterise = false;			//U方向是否重参化
	Ncti_Boolean _bVReparameterise = false;			//V方向是否重参化
	Ncti_Double _fParamValue[4] = { 0.0 };			//重参化后U、V参数值，参数值排列如：{ miniU, maxU, miniV, maxV }
};

enum class NCTILoftPeriodic
{
	NCTI_PARAM_periodic_no_c=18020,
	NCTI_PARAM_periodic_yes_c,
	NCTI_PARAM_periodic_seamed_c
};
enum class NCTILoftCurvatureCondition
{
	NCTI_BODY_loft_natural_c=21530,
	NCTI_BODY_loft_unconstrained_c,
	NCTI_BODY_loft_clamped_c
};
enum class NCTILoftClampType
{
	NCTI_BODY_loft_clamp_no_c=21540,
	NCTI_BODY_loft_clamp_vector_c,
	NCTI_BODY_loft_clamp_face_c,
	NCTI_BODY_loft_clamp_planar_c,
	NCTI_BODY_loft_clamp_vec_face_c,
	NCTI_BODY_loft_clamp_vec_planar_c
};
struct NCTILoftVertexClamp
{
	std::vector< NCTI::NctiVector>_iTangents;                //切线方向
	std::vector< NCTI_MODEL_TAG> _iVertexes;             //顶点
	std::vector< Ncti_Double> _iMagnitudes;                  //长度
};
struct NCTILoftFaceClamp
{
	std::vector<NCTI_MODEL_TAG> _iowningNctiBodies;		//所属NctiBody
	std::vector< NCTI_MODEL_TAG> _iFaces;             //面
	std::vector< NCTI_MODEL_TAG> _iEdges;            //边
	std::vector< NCTI_MODEL_TAG> _iVertexes;        //顶点
	std::vector< Ncti_Double> _iMagnitudes;             //长度
};
struct NCTILoftPlanarClamp
{
	NCTI::NctiVector  _iNormal;                         //法向量
	Ncti_Double          i_Magnitude;                  //长度
};
struct NCTILoftDerivConds
{
	NCTILoftCurvatureCondition _iCurvatureCondition;
	NCTILoftClampType _iClampTpe;
	NCTILoftVertexClamp _iVertexClamp;
	NCTILoftFaceClamp _iFaceClamp;
	NCTILoftPlanarClamp _iPlanarClamp;
};
enum class NCTILoftSimplifyType
{
	NCTI_BODY_simplify_analytic_c=21520,
	NCTI_BODY_simplify_swept_spun_c,
	NCTI_BODY_simplify_no_c
};
enum class NCTILoftTopologyType
{
	NCTI_BODY_topology_minimal_c=21830,
	NCTI_BODY_topology_columns_c,
	NCTI_BODY_topology_grid_c
};
struct NCTIBodyVertexMatch
{
	NCTI_MODEL_TAG _iProfileVertex;
	NCTI_MODEL_TAG _iMatchVertex;
};
struct NCTIBodyProfileMatch
{
	NCTI_MODEL_TAG _iProfile;
	std::vector< NCTIBodyVertexMatch> _iMatches;
};
enum class NCTILoftUpdateType
{
	NCTI_BODY_loft_update_0_c=22520,          //for updating v13.2 and earlier models
	NCTI_BODY_loft_update_1_c,          //for updating v14.0 and v14.1 models
	NCTI_BODY_loft_update_2_c ,         //for updating v15.0 models
	NCTI_BODY_loft_update_3_c ,         //for updating v15.1 to v24.1 models
	NCTI_BODY_loft_update_4_c ,         //for updating v25.0 to v26.0 models
	NCTI_BODY_loft_update_v261_c,       //for updating v26.1 models
	NCTI_BODY_loft_update_v270_c ,      //for updating v27.0 models
	NCTI_BODY_loft_update_v271_c,       //for updating v27.1 models
	NCTI_BODY_loft_update_v280_c ,      //for updating v28.0 models
	NCTI_BODY_loft_update_default_c    //activate latest functionality
};
enum class NCTILoftDerivMag
{
	NCTI_BODY_loft_deriv_mag_single_c= 22770,
	NCTI_BODY_loft_deriv_mag_smooth_c,
	NCTI_BODY_loft_deriv_mag_round_c
};
enum class NCTILoftSmoothness
{
	NCTI_BODY_smoothness_exact_c=23020,
	NCTI_BODY_smoothness_relax_c
};
struct NCTIBodyLoftParam
{
	void IniData()
	{
		_iPeriodic = NCTILoftPeriodic::NCTI_PARAM_periodic_no_c;
		_iSimplify = NCTILoftSimplifyType::NCTI_BODY_simplify_analytic_c;
		_iTopology = NCTILoftTopologyType::NCTI_BODY_topology_minimal_c;
		_iTolerance = 1e-2;
		_iMinimiseTolerance = false;
		_iUpdateType = NCTILoftUpdateType::NCTI_BODY_loft_update_default_c;
		_iDerivMag = NCTILoftDerivMag::NCTI_BODY_loft_deriv_mag_single_c;
		_iWantEdgeTracking = false;
		_iSmoothness = NCTILoftSmoothness::NCTI_BODY_smoothness_exact_c;
		_iCreateConstructionTopol = false;
		_iReturnEdgeTracking = false;
	}
	std::vector< NCTI_MODEL_TAG> _iProfiles;             //放样截面
	std::vector< NCTI_MODEL_TAG>_iVertexes;             //用于对齐的顶点
	std::vector< NCTI_MODEL_TAG> _iguideLines;       //引导线
	//end_conditions
	NCTILoftPeriodic _iPeriodic;                                     //终点截面处周期性
	NCTILoftDerivConds _iStart;                                     //终点截面处开始位置放样方向的继承
	NCTILoftDerivConds _iEnd;                                      //终点截面处结束位置放样方向的继承
	NCTILoftSimplifyType _iSimplify;                             //简化水平
	NCTILoftTopologyType _iTopology;                        //拓扑格式
	std::vector< NCTIBodyProfileMatch> _iProfileMatches;        //顶点匹配信息集合
	std::vector<NCTILoftDerivConds> _iIntermediateDerivs;      //中间截面的派生继承
	std::vector< Ncti_Integer> _iProfileIndices;                          //中间截面的派生继承索引
	std::vector <NCTILoftDerivConds> _iGuideDerivs;      //引导线的派生
	std::vector< Ncti_Integer> _iGuideIndices;                 //引导指标
	Ncti_Double _iTolerance;                                             //公差
	Ncti_Boolean _iMinimiseTolerance;                            //是否最小公差
	NCTILoftUpdateType _iUpdateType;                          //更新标识
	NCTILoftDerivMag _iDerivMag;                                  //继承度
	Ncti_Boolean _iWantEdgeTracking;                            //是否需要边的跟踪信息
	NCTILoftSmoothness _iSmoothness;                         //光滑度类型
	Ncti_Boolean _iCreateConstructionTopol;                 //是否创建构造拓扑
	Ncti_Boolean _iReturnEdgeTracking;                         //是否返回边的有序跟踪信息
};
enum class NCTISweptAlignment
{
	NCTI_BODY_sweep_align_normal_c = 21560,
	NCTI_BODY_sweep_align_parallel_c,
	NCTI_BODY_sweep_align_parm_c,
	NCTI_BODY_sweep_align_arclength_c
};
enum class NCTISimplifyType
{
	NCTI_BODY_simplify_analytic_c=21520,
	NCTI_BODY_simplify_no_c,
	NCTI_BODY_simplify_swept_spun_c,
	NCTI_BODY_simplify_yes_c
};
enum class NCTISweepLawType
{
	NCTI_BODY_sweep_law_none_c=21570,
	NCTI_BODY_sweep_law_discrete_c,
	NCTI_BODY_sweep_law_curve_c,
	NCTI_BODY_sweep_law_curve_inv_c
};
enum class NCTISweepKnotType
{
	NCTI_knot_unset_c=8500,
	NCTI_knot_non_uniform_c,
	NCTI_knot_uniform_c,
	NCTI_knot_quasi_uniform_c,
	NCTI_knot_piecewise_bezier_c,
	NCTI_knot_bezier_ends_c,
	NCTI_knot_smooth_seam_c
};
struct NCTIBodySweptLawCurve
{
	Ncti_Integer _iDegree;
	std::vector< Ncti_Double> _iVertices;
	std::vector< Ncti_Double> _iKnots;
	std::vector< Ncti_Integer> _iKnotsMult;
	Ncti_Integer _iVertexDim;
	Ncti_Boolean _iIsRational;
	NCTISweepKnotType _iKnotType;
	Ncti_Boolean _iIsPeriodic;
	Ncti_Boolean _iIsClosed;
};
struct NCTIBodySweptLaw
{
	NCTISweepLawType _iLawType;
	std::vector< NCTI_MODEL_TAG>_iLawDiscreteVertexes;    
	std::vector< Ncti_Double> _iLawDiscreteValues;
	NCTIBodySweptLawCurve _iLawCurve;
};
enum class NCTISweepScaleType
{
	NCTI_BODY_sweep_scale_posn_c=22540,
	NCTI_BODY_sweep_scale_size_c,
	NCTI_BODY_sweep_scale_both_c
};
enum class NCTISweepProfileLaw
{
	NCTI_sweep_profile_law_no_c = 24310,
	NCTI_sweep_profile_law_yes_c
};
enum class NCTISweepLockType
{
	NCTI_sweep_lock_path_and_dir_c=23600,
	NCTI_sweep_lock_path_c,
	NCTI_sweep_lock_rotation_c
};
enum class NCTISweepPreferredContinuity
{
	NCTI_scontinuity_c1_c=23150,
	NCTI_scontinuity_c2_c,
	NCTI_scontinuity_c3_c,
	NCTI_scontinuity_g1_c,
	NCTI_scontinuity_g2_c,
	NCTI_scontinuity_g3_c,
	NCTI_scontinuity_g0_c
};
enum class NCTIContinuity
{
	NCT_continuity_c1_c=23150,
	NCT_continuity_c2_c,
	NCT_continuity_c3_c,
	NCT_continuity_g1_c,
	NCT_continuity_g2_c,
	NCT_continuity_g3_c,
	NCT_continuity_g0_c
};
enum class NCTISweepGuideClampType
{
	NCTI_sweep_guide_clamp_none_c=23260,
	NCTI_sweep_guide_clamp_dirn_c,
	NCTI_sweep_guide_clamp_fixed_c
};
struct NCTISweepGuideControl
{
	std::vector< NCTI_MODEL_TAG>_iProfileMatchVertexes;
	NCTISweepGuideClampType   _iGuideClampType;
	std::vector< NCTI::NctiVector> _iDirection;
	std::vector< NCTI_MODEL_TAG>_iGuideClampVertices;
	std::vector< NCTI_MODEL_TAG>_iGuideMatchVertexes;
};
enum class NCTISweepGuideMethod
{
	NCTI_sweep_guide_point_c=23250,
	NCTI_sweep_guide_chord_c,
	NCTI_sweep_guide_curve_c,
	NCTI_sweep_guide_project_c
};
enum class NCTISweepGuideScale
{
	NCTI_sweep_guide_uniform_c = 23290,
	NCTI_sweep_guide_lateral_c
};
enum class NCTISweepGuideScope
{
	NCTI_sweep_guide_scope_global_c = 26400,
	NCTI_sweep_guide_scope_local_c
};
enum class NCTISweepOutputXsect
{
	NCTI_sweep_output_xsect_no_c=23700,
	NCTI_sweep_output_xsect_yes_c,
	NCTI_sweep_output_xsect_on_fail_c
};
enum class NCTISweepGroupXsect
{
	NCTI_sweep_group_xsect_per_vx_c = 23710,
	NCTI_sweep_group_xsect_per_edge_c,
	NCTI_sweep_group_xsect_no_c
};
enum class NCTISweepRepair
{
	NCTI_sweep_repair_no_c=23970,
	NCTI_sweep_repair_yes_c,
	NCTI_sweep_repair_report_c
};
enum class NCTISweepCornerType
{
	NCTI_sweep_corner_type_mitre_c=25700,
	NCTI_sweep_corner_type_spin_c
};
enum class NCTISweepDerivMag
{
	NCTI_sweep_deriv_mag_smooth_c=26760,
	NCTI_sweep_deriv_mag_round_c
};
enum class NCTISweepUpdate
{
	NCTI_BODY_sweep_update_0_c = 24450,         //for updating v22.0 and earlier models
	NCTI_BODY_sweep_update_1_c,         //for updating v22.1 - v24.0 models
	NCTI_BODY_sweep_update_2_c,         //for updating v24.1 models
	NCTI_BODY_sweep_update_3_c,         // for updating v25.0 - v26.0 models
	NCTI_BODY_sweep_update_v261_c,    //  for updating v26.1 models
	NCTI_BODY_sweep_update_v270_c,     //  for updating v27.0 models
	NCTI_BODY_sweep_update_v271_c,     //for updating v27.1 models
	NCTI_BODY_sweep_update_v280_c,      // for updating v28.0 models
	NCTI_BODY_sweep_update_default_c    //activate latest functionality
};
enum class NCTISweepClampType
{
	NCTI_sweep_clamp_none_c=23300,
	NCTI_sweep_clamp_const_profile_c,
	NCTI_sweep_clamp_face_c
};
struct NCTISweepFaceClamp
{
	std::vector< NCTI_MODEL_TAG> _iEdges;             //边集合
	std::vector< NCTI_MODEL_TAG> _iFaces;             //边集合
	std::vector< NCTI_MODEL_TAG> _iVertexes;             //边集合
	std::vector< Ncti_Double> _iMagnitudes;
}; 
struct  NCTISweepDerivConds
{
	NCTISweepClampType _iClampType;
	Ncti_Double _iProfileClampMagnitude;
	NCTISweepFaceClamp _iFaceClamp;
};
struct NCTIBodySweptParam
{
	std::vector<NCTI_MODEL_TAG> _iProfiles;             //扫略截面
	NCTI_MODEL_TAG  _iPath;                                        //扫略路径
	std::vector<NCTI_MODEL_TAG>_iPathVertexes;      //用于对齐路径顶点
	NCTISweptAlignment _iProfileAlignment;                 //截面对齐方式
	NCTISimplifyType _iSimplify;                                     //简化方式
	NCTILoftTopologyType _iTopology;                         //拓扑格式
	std::vector<NCTI_MODEL_TAG>_iIgnorableVertices; //忽略的顶点
	std::vector< NCTIBodyProfileMatch> _iProfileMatches;        //顶点匹配信息集合
	NCTIBodySweptLaw _iTwist;                                          //扭转截面数据
	Ncti_Boolean  _iHaveTwistDirection;
	NCTI::NctiVector _iTwistDirection;
	NCTIBodySweptLaw _iScalePath;
	NCTISweepScaleType _iScaleType;
	NCTI::NctiPosition  _iScalePoint;
	NCTISweepProfileLaw _iProfileLaw;
	Ncti_Double _iTolerance;
	Ncti_Boolean _iMinimiseTolerance;
	Ncti_Boolean _iAllowRationals;
	Ncti_Boolean _iWantEdgeTracking;
	Ncti_Boolean _iHaveLockDirection;
	NCTI::NctiVector _ILockDirection;
	NCTISweepLockType  _iLockType;
	std::vector<NCTI_MODEL_TAG>_iLockFaces;
	NCTISweepPreferredContinuity _iPreferredContinuity;
	std::vector<NCTI_MODEL_TAG> _iGuides;
	std::vector <NCTISweepGuideControl>  _iGuideControls;
	NCTISweepGuideMethod _iGuideMethod;
	NCTISweepGuideScale _iGuideScale;
	NCTISweepGuideScope _iGuideScope;
	NCTIContinuity _iProfileContinuty;
	Ncti_Integer _iFixedGuideIndex;
	Ncti_Boolean _iTrimToGuides;
	Ncti_Boolean _iHaveTrimPoint;
	NCTI::NctiPosition  _iTrimPoint;
	std::vector<NCTISweepDerivConds> _iProfileDerivs;
	std::vector<Ncti_Integer> _iProfileDerivsIndices;
	NCTISweepOutputXsect _iOutputXsect;
	NCTISweepGroupXsect  _iGroupXsect;
	Ncti_Integer _iXsectsCount;
	NCTISweepRepair _iRepair;
	NCTISweepCornerType _iCornerType;
	NCTISweepDerivMag _iDerivMag;
	NCTISweepUpdate _iUpdate;
};
struct NCTIPyBodyLoftParam
{
	std::vector <Ncti_Long> m_alignVertexIdVec;          //截面开始点id集合
	std::vector<std::string> m_guideLinesNameVec;     //引导线实体名
	std::vector <Ncti_Long> m_mappingVertexIdVec;          //截面匹配点id集合
	std::vector <Ncti_Long> m_startClampVertexIndex;
	std::vector <NCTI::NctiVector> m_startClampTangents;     //起点约束点切线方向
	std::vector <Ncti_Double> m_startClampMagnitudes;     //起点约束点切线方向
	std::vector <Ncti_Long> m_endClampVertexIndex;
	std::vector <NCTI::NctiVector> m_endClampTangents;      //终点约束点的切线方向
	std::vector <Ncti_Double> m_endClampMagnitudes;     //起点约束点切线方向
	Ncti_Boolean m_isSmoothnessgRelax;                                  //是否G1连续

	std::vector<std::string> m_vtStartClampFaceNames;		//起始约束面片所在的Body名称
	std::vector<Ncti_Long> m_vtStartClampFaceIndices;		//起始约束面片的序号
	double m_fStartClampFaceMagnitude = 1.0;				//起始约束比例
	std::vector<std::string> m_vtEndClampFaceNames;			//终止约束面片所在的Body名称
	std::vector<Ncti_Long> m_vtEndClampFaceIndices;			//终止约束面片的序号
	double m_fEndClampFaceMagnitude = 1.0;					//终止约束比例
};
struct NCTIExtrudeBoundParam
{
	Ncti_Integer _iBound;                                                     //边界类型
	Ncti_Boolean _iForward;                                        //是否向前
	Ncti_Double  _iDistance;                                            //拉伸距离
	std::vector <std::string> _iEntity;                             //边界实体
	Ncti_Boolean _iNearest;                                        //是否取最近截面
	Ncti_Integer _iNthDivision;                                        //多区域时选取的区域索引
	Ncti_Integer _iSide;                                          //截面交拉伸结果时修剪哪一边
};

enum class NCTIFaceGrowType
{
	NCTI_FACE_grow_update_c=24120,
	NCTI_FACE_grow_auto_c,
	NCTI_FACE_grow_moving_c,
	NCTI_FACE_grow_fixed_c,
	NCTI_FACE_grow_no_c,
	NCTI_FACE_grow_fail_c
}; 
enum class NCTIOffsetStep
{
	NCTI_offset_step_no_c = 22310,
	NCTI_offset_step_pierce_c,
	NCTI_offset_step_yes_c,
	NCTI_offset_step_all_c,
	NCTI_offset_step_site_c
};
struct NCTIBodyThickenParam
{
	NCTI_MODEL_TAG _iBody;                                                        //待加厚的sheet体
	Ncti_Double _iFrontOffset;                                                        //向前加厚厚度
	Ncti_Double _iBackOffset;                                                         //向后加厚厚度
	Ncti_Double _iTol;                                                                     //公差
	NCTI::NctiVector _iPunchDirection;                                          //加厚方向
	std::vector <NCTI_MODEL_TAG> _iNonDefaultFaces;             //加厚特殊厚度值的面
	std::vector <Ncti_Double> _iFrontOffsetValues;                     //加厚特殊厚度值的面的向前加厚厚度
	std::vector <Ncti_Double> _iBackOffsetValues;                      //加厚特殊厚度值的面的向后加厚厚度
	std::vector <NCTI_MODEL_TAG> _iSideEdges;                       //侧面边
	std::vector <NCTI_MODEL_TAG> _iSideSurfaces;                   //侧曲面
	Ncti_Integer _iBlendType;                                                       //混合类型
	Ncti_Double _iBlendRadius;                                                    //混合半径
	std::vector <NCTI_MODEL_TAG> _iPierceFaces;                    //穿透面
	NCTIFaceGrowType _iGrowType;                                           //增长类型
	NCTIOffsetStep _iOffsetStep;                                                //偏移选择类型
};
enum class NCTITaperCornerType
{
	NCTI_taper_corner_extend_c=22400,
	NCTI_taper_corner_plane_c
};
enum class NCTITaperMiterType
{
	NCTI_taper_miter_on_ref_c = 22530,
	NCTI_taper_miter_to_face_c,
	NCTI_taper_miter_at_open_c
}; 
enum class NCTITaperUndercutType
{
	NCTI_taper_undercut_ref_no_c = 22860,
	NCTI_taper_undercut_ref_yes_c
};
enum class NCTITaperConcaveType
{
	NCTI_taper_concave_none_c = 23010,
	NCTI_taper_concave_radius_c,
	NCTI_taper_concave_plane_c,
	NCTI_taper_concave_mix_c
};
enum class NCTITaperKeepMaterial
{
	NCTI_taper_keep_material_no_c = 23520,
	NCTI_taper_keep_material_yes_c
};

struct NCTIBodyTaperParam
{
	NCTI_MODEL_TAG _iBody;                                                        //待拔模的体
	std::vector <NCTI_MODEL_TAG> _iRefsAbove;                        //上部参考实体
	std::vector <NCTI_MODEL_TAG> _iRefsBelow;                        //下部参考实体
	NCTI_MODEL_TAG _iPartingBody;                                           //分割体
	NCTI::NctiVector _iDrawDirection;                                           //拔模方向
	Ncti_Double _iAngleAbove;                                                     //上部拔模角
	Ncti_Double _iAngleBelow;                                                     //下部拔模角
	std::vector <NCTI_MODEL_TAG> _iPartingEdges;                  //分割面处的边
	NCTITaperCornerType _iCornerType;                                     //拐角类型
	Ncti_Boolean _iMiterAtParting;                                              //
	Ncti_Boolean _iMergeFace;
	NCTITaperMiterType _iMiterType;
	std::vector <NCTI_MODEL_TAG> _iMiterEdges;                  //侧部的边
	std::vector <NCTI_MODEL_TAG> _iReplaceEdges;              //改变边
	NCTITaperUndercutType _iUndercutType;
	std::vector <NCTI_MODEL_TAG> _iUpperFaces;                  //上部的面
	std::vector <NCTI_MODEL_TAG> _iLowerFaces;                  //下部的面
	NCTITaperConcaveType _iConcaveType;
	Ncti_Double _iConcaveRadius;
	NCTITaperKeepMaterial _iKeepMaterial;
};
enum class NCTICurveProjectMethod
{
	NCTI_proj_method_normal_c = 26520,
	NCTI_proj_method_vector_c,
	NCTI_proj_method_perspective_c,
	NCTI_proj_method_unset_c
};
enum class NCTIMaxProjectDist
{
	NCTI_proj_max_dist_no_c = 25160,
	NCTI_proj_max_dist_whole_c
};
enum class NCTIProjectHideFaceType
{
	NCTI_proj_face_hidden_no_c = 25150,
	NCTI_proj_face_hidden_array_c,
	NCTI_proj_face_hidden_body_c
};
enum class NCTIProjectConnectType
{
	NCTI_proj_connect_none_c = 25140,
	NCTI_proj_connect_side_c,
	NCTI_proj_connect_all_c,
	NCTI_proj_connect_side_all_c,
	NCTI_proj_connect_hidden_all_c
};
enum class NCTIProjectSplitClash
{
	NCTI_proj_split_clash_no_c = 25170,
	NCTI_proj_split_clash_self_c,
	NCTI_proj_split_clash_all_c
};
enum class NCTIProjectCurveToPoint
{
	NCTI_proj_to_points_no_c = 25180,
	NCTI_proj_to_points_tol_c,
	NCTI_proj_to_points_end_on_c,
	NCTI_proj_to_points_all_c
};
enum class NCTIProjectImprintType
{
	NCTI_proj_function_project_c = 25360,
	NCTI_proj_function_imprint_c,
	NCTI_proj_function_both_c
};

enum class NCTIProjectPrecisionType
{
	NCTI_imprint_precision_auto_c = 25380,
	NCTI_imprint_precision_accurate_c
};
enum class NCTIProjectNominalType
{
	NCTI_proj_nominal_yes_c = 25350,
	NCTI_proj_nominal_no_c
};
enum class NCTIProjectImprintComplete
{
	NCTI_proj_complete_no_c=25340,
	NCTI_proj_complete_edge_c,
	NCTI_proj_complete_laminar_c,
	NCTI_proj_complete_faceset_c
};
enum class NCTIProjectCompleteBound
{
	NCTI_complete_bound_none_c = 26210,
	NCTI_complete_bound_if_within_c
};
struct NCTICurveProjectParam
{
	NCTICurveProjectMethod _iMethod;                           //投影方式
	Ncti_Boolean _iHaveDirection;                                     //是否指定投影方向
	NCTI::NctiVector _iProjectDirection;                             //投影方向
	NCTI::NctiPosition _iEyePosition;                                  //眼睛位置
	Ncti_Boolean _iBidirectionalProjection;                        //是否双向投影
	NCTIMaxProjectDist _iMaxProjectDistType;                  //最大投影距离类型
	Ncti_Double _iMaxProjectDist;                                      //最大投影距离值
	NCTIProjectHideFaceType _iHideFaceType;                  //隐藏面类型
	NCTIProjectConnectType _iConnectType;                     //连接类型
	std::vector <Ncti_Integer> _iBannedResultCurveClasses;      //禁用的结果曲线类型
	NCTIProjectSplitClash _iSplitClash;                                  //切割碰撞类型
	NCTIProjectCurveToPoint _iCurveToPoint;                      //曲线投影成点类型
	Ncti_Boolean _iIsAddAsConstruction;                              //是否构造添加
	Ncti_Double _iTolerance;                                                  //公差
	NCTIProjectImprintType _iProjectImprintType;                //投影压印类型
	NCTIProjectPrecisionType _iProjectPrecisionType;           //投影精度类型
	NCTIProjectNominalType _iProjectNominalType;
	NCTIProjectImprintComplete _iProjectImprintComplete;
	NCTIProjectCompleteBound _iProjectCompleteBound;
	Ncti_Double _iCompleteBoundDistance;
	std::vector <NCTI_MODEL_TAG> _iSubObj;

};
enum class NCTIOffsetMethod
{
	NCTI_offset_method_sx_trim_c=22150,
	NCTI_offset_method_sx_repair_1_c,
	NCTI_offset_method_sx_repair_2_c,
	NCTI_offset_method_accurate_c,
	NCTI_offset_method_approximate_c
};
enum class NCTIOffsetCheckFace
{
	NCTI_check_fa_fa_no_c=18340,
	NCTI_check_fa_fa_yes_c
};
enum class NCTIOffsetFixDegens
{
	NCTI_fix_degens_no_c=24850,
	NCTI_fix_degens_offset_c,
	NCTI_fix_degens_all_c
};
enum class NCTIOffsetGrow
{
	NCTI_FACE_grow_update_c=24120,
	NCTI_FACE_grow_auto_c,
	NCTI_FACE_grow_moving_c,
	NCTI_FACE_grow_fixed_c,
	NCTI_FACE_grow_no_c,
	NCTI_FACE_grow_fail_c
};
enum class NCTIOffsetBlendEdges
{
	NCTI_EDGE_offset_blend_no_c=22640,
	NCTI_EDGE_offset_blend_convex_c
};
struct NCTIBodyOffsetParam
{
	std::vector <NCTI_MODEL_TAG> _iFaceObj;           //待偏移的子拓扑，比如面、边、实体等
	std::vector < Ncti_Double> _iOffsetDist;                 //偏移的距离，与上面对应
	Ncti_Double _iTol;                                                    //公差
	Ncti_Boolean _iAllowDisjoint;                                  //容许断连
	NCTIOffsetCheckFace _iCheckFace;                        //检查面
	NCTIOffsetMethod _iOffsetMethod;                      //偏移方法                             
	NCTIOffsetFixDegens _iFixDegens;                        //修复退化
	NCTIOffsetStep _iOffsetStep;                                 //台阶偏移类型
	Ncti_Boolean _iSplitLaminarVertices;                     //切割共面顶点
	NCTIOffsetGrow _iGrow;                                        //增长类型
	NCTIOffsetBlendEdges _iBlendEdges;                    //混合边
	Ncti_Double _iBlendRadius;                                   //混合半径
};
enum class NCTIBodyScale
{
	NCTI_scale_factor_1x_c = 26960,
	NCTI_scale_factor_10x_c,
	NCTI_scale_factor_100x_c,
	NCTI_scale_factor_1000x_c
};
struct NCTIBodyEnlargeParam
{
	NCTI_MODEL_TAG _iModel;      //待扩大的body
	Ncti_Long _iscaleFactor;            //缩放因子,取值见上面枚举值：NCTIBodyScale
	Ncti_Double _itolerance;           //公差
};

struct NCTIFillHoleOption
{
	std::vector<NCTI_MODEL_TAG> _vtSupportBodies;
	bool _bImpritSupportBodies = false;
};

struct NCTIIdentifyFeatureOption
{
	int _nType = -1;
	double critical_value[2] = { 0.0 };
};

struct NCTIIdentifyFeatureResult
{
	int _nType;
	double _fFeatureValue;
	std::vector<NCTI_MODEL_TAG> _vtFeatureFaces;
};

struct NCTI3FaceBlendOption
{
	Ncti_Integer _left_orientation = 2;				//0 : before;		1 : behind;		2 : unknown
	Ncti_Integer _right_orientation = 2;
	Ncti_Integer _centre_orientation = 2;
};

struct NCTIFaceBlendOption
{
	Ncti_Integer _walls = 2;					//0 : 不裁剪；	1 : 裁剪但不合并；	2 : 裁剪且合并；	3 : 裁剪合并，且形成实体；	4 : 预览模式
	Ncti_Double _blendRadius = 0.0;
};

struct NCTIEdgeBlendOption
{
	Ncti_Double _startMagnitude = 1.0;				//起始导数值
	Ncti_Double _endMagnitude = 1.0;				//终止导数值
};

struct NCTIEdgeOffsetOnBody
{
	double _offset_distance = 0.0;
};


#endif // !NctiGeoDataDef_H

