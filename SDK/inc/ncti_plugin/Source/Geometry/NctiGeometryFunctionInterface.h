#ifndef NctiGeometryFunctionInterface_H
#define NctiGeometryFunctionInterface_H
#include "ncti_base.h"
#include "NctiFunctionInterface.h"
#include "dcl_ncti_plugin.h"
#include "NctiModelFunctionResult.h"
#include "NctiGPropDef.h"
#include "NctiGBoundsDef.h"
#include "NctiGeoDataDef.h"
#include "chrono"
#include <map>
#include "ncti_include.h"
namespace NCTI
{
    class NctiDisplayDocCustomContainer;
    class NctiBaseModel;
    class NctiVector;
    class NctiAxis;
    class DECL_NCTI_PLUGIN NctiGeometryResult : public NctiModelFunctionResult
    {
    public:
        NctiGeometryResult();
        NctiGeometryResult(bool i_result);
        NctiGeometryResult(NctiModelFunctionResult const &p);
        ~NctiGeometryResult();

    private:
        std::chrono::high_resolution_clock::time_point m_tStart;
        std::chrono::high_resolution_clock::time_point m_tEnd;
        Ncti_LongLong m_UsedPhysicalMemoryS;
        Ncti_LongLong m_UsedPhysicalMemoryE;
        Ncti_Double m_cpuUsageS;
        Ncti_Double m_cpuUsageE;

    public:
        void SetTime(std::chrono::high_resolution_clock::time_point i_s,
                     std::chrono::high_resolution_clock::time_point i_e)
        {
            m_tStart = i_s;
            m_tEnd = i_e;
        }
        void SetUsedPhysicalMemory(Ncti_LongLong i_UsedPhysicalMemoryS, Ncti_LongLong i_UsedPhysicalMemoryE)
        {
            m_UsedPhysicalMemoryS = i_UsedPhysicalMemoryS;
            m_UsedPhysicalMemoryE = i_UsedPhysicalMemoryE;
        }
        void SetcpuUsage(Ncti_Double i_cpuUsageS, Ncti_Double i_cpuUsageE)
        {
            m_cpuUsageS = i_cpuUsageS;
            m_cpuUsageE = i_cpuUsageE;
        }
        Ncti_Double GetTime();
        Ncti_LongLong GetUsedPhysicalMemory()
        {
            return (m_UsedPhysicalMemoryE - m_UsedPhysicalMemoryS);
        }
        Ncti_Double GetcpuUsage() { return m_cpuUsageE - m_cpuUsageS; }
    };
    class DECL_NCTI_PLUGIN NctiGeometryFunctionInterface : public NctiFunctionInterface
    {
        NCTI_PLUGIN_FUNCTIONS(NctiGeometryFunctionInterface)
    public:
        NctiGeometryFunctionInterface();
        virtual ~NctiGeometryFunctionInterface();

    public:
        /*
         * @brief 导入文件 order 1
         * @param i_pCustomContainer
         * @param i_FullFileName 文件全路径
         * @param o_ModelBodyVec 导入的模型对象集合
         * @param i_nUniteMode 合并模式， 0 : 不合并;       1 : 同类型合并;      2 : 全部合并
         */
        virtual NctiGeometryResult import_file(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Char* i_FullFileName,
            std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec, 
            int i_nUniteMode = 1);
        /*
         * @brief 导出文件 order 2
         * @param i_pCustomContainer
         * @param i_FullFileName 文件全路径
         * @param i_ModelBodyVec 导出的模型对象集合
         */
        virtual NctiGeometryResult export_file(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Char* i_FullFileName,
            const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);

    public:
        /*
         * @brief 创建长方体 order 3
         * @param i_pCustomContainer
         * @param i_pos 基准点
         * @param i_len 长度
         * @param i_width 宽度
         * @param i_height 高度
         * @param o_ModelBody: 长方体对象
         */
        virtual NctiGeometryResult create_box(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiPosition& i_pos,
            Ncti_Double i_len,
            Ncti_Double i_width,
            Ncti_Double i_height,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 布尔并集 order 4
         * @param i_pCustomContainer
         * @param i_FModelBody 并集对象1
         * @param i_SModelBody 并集对象2
         * @param o_ModelBody  并集对象
         */
        virtual NctiGeometryResult boolean_unit(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_FModelBody,
            NCTI_MODEL_TAG i_SModelBody,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 倒角 order 5
         * @param i_pCustomContainer
         * @param i_TargeBody 倒角对象
         * @param o_ResultBody 倒角结果
         * @param i_EdgeVec 倒角的边ID集合
         * @param i_raduis 倒角的半径集合
         */
        virtual NctiGeometryResult fillet_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG& o_ResultBody,
            const std::vector<NCTI_MODEL_TAG>& i_EdgeVec,
            const std::vector<Ncti_Double>& i_raduis);
        /*
         * @brief 创建直线 order 6
         * @param i_pCustomContainer
         * @param i_pos_start 起点
         * @param i_pos_end 终点
         * @param o_ModelBody 直线对象
         */
        virtual NctiGeometryResult create_line(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiPosition& i_pos_start,
            const NctiPosition& i_pos_end,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 获取边的中点 order 7
         * @param i_pCustomContainer
         * @param i_TargeBody 目标对象
         * @param i_ModelEdge 边的ID
         * @param o_MidPoint 中点坐标
         */
        virtual NctiGeometryResult get_edge_mid_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG i_ModelEdge,
            NctiPosition& o_MidPoint);
        /*
         * @brief 寻找点的最近边 order 8
         * @param i_pCustomContainer
         * @param i_TargeBody 目标对象
         * @param i_PointVec 点坐标集合
         * @param o_ModelEdgeVec 最近边集合
         */
        virtual NctiGeometryResult find_nearest_edge_by_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            const std::vector<NctiPosition>& i_PointVec,
            std::vector<NCTI_MODEL_TAG>& o_ModelEdgeVec);
        /*
         * @brief 计算点到边的距离 order 9
         * @param i_pCustomContainer
         * @param i_ModelEdge 边对象
         * @param i_Point 点坐标
         * @param o_Distance 距离
         */
        virtual NctiGeometryResult cal_distance_edge_and_pt(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_ModelEdge,
            const NctiPosition& i_Point,
            Ncti_Double& o_Distance);
        /*
         * @brief 创建球体 order 10
         * @param i_pCustomContainer
         * @param NctiAxis 球的参考坐标系
         * @param i_Radius 半径
         * @param i_angle1 最小角度
         * @param i_angle2 最大角度
         * @param i_angle3 球体完成角度
         * @param o_ModelBody 球体对象
         */
        virtual NctiGeometryResult create_sphere(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_Radius,
            Ncti_Double i_angle1,
            Ncti_Double i_angle2,
            Ncti_Double i_angle3,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 创建圆柱体 order 11
         * @param i_pCustomContainer
         * @param i_Radius 圆心
         * @param i_Height 高
         * @param i_Axis 圆柱体坐标系
         * @param i_Angle 圆柱体完成角度
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_cylinder(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_Radius,
            Ncti_Double i_Height,
            const NctiAxis& i_Axis,
            Ncti_Double i_Angle,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 创建圆锥体 order 12
         * @param i_pCustomContainer
         * @param i_BottomRadius 底部圆心
         * @param i_TopRadius 顶部圆心
         * @param i_Height 高度
         * @param i_Axis 圆锥体坐标系
         * @param i_Angle 圆锥体完成角度
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_cone(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_BottomRadius,
            Ncti_Double i_TopRadius,
            Ncti_Double i_Height,
            const NctiAxis& i_Axis,
            Ncti_Double i_Angle,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 布尔差集 order 13
         * @param i_pCustomContainer
         * @param i_FModelBody 被减对象
         * @param i_SModelBody 切割对象
         * @param o_ModelBody 被减对象剩余部分
         */
        virtual NctiGeometryResult boolean_cut(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_FModelBody,
            NCTI_MODEL_TAG i_SModelBody,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 布尔交集 order 14
         * @param i_pCustomContainer
         * @param i_FModelBody 交集对象
         * @param i_SModelBody 交集对象
         * @param o_ModelBody 输出对象
         * @param
         */
        virtual NctiGeometryResult boolean_common(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_FModelBody,
            NCTI_MODEL_TAG i_SModelBody,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 平移 order 15
         * @param i_pCustomContainer
         * @param i_panx 平移x坐标
         * @param i_pany 平移y坐标
         * @param i_panz 平移z坐标
         * @param io_SModelBody 平移对象
         */
        virtual NctiGeometryResult pan_object(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_panx,
            Ncti_Double i_pany,
            Ncti_Double i_panz,
            NCTI_MODEL_TAG& io_SModelBody);
        /*
         * @brief 缩放	order 16
         * @param i_pCustomContainer
         * @param OringePt 缩放基准点
         * @param i_scale 缩放比例
         * @param io_SModelBody 缩放对象
         */
        virtual NctiGeometryResult scale_object(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiPosition& OringePt,
            Ncti_Double i_scale,
            NCTI_MODEL_TAG& io_SModelBody);
        /*
         * @brief 创建贝塞尔曲线	order 17
         * @param i_pCustomContainer
         * @param i_ControlPts 控制点集
         * @param i_WeightPts  权重集
         * @param o_bezierCurve 输出曲线
         */
        virtual NctiGeometryResult create_bezier_curve(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NctiPosition>& i_ControlPts,
            const std::vector<Ncti_Double>& i_WeightPts,
            NCTI_MODEL_TAG& o_bezierCurve);
        /*
         * @brief 创建文档	order 18
         * @param i_modelDoc 文档类型
         * @param i_pBaseModel  基础模块
         * @param o_pCustomContainer  容器
         */
        virtual NctiGeometryResult create_model_doc(
            EnumModelDoc i_modelDoc,
            NctiBaseModel* i_pBaseModel,
            NctiDisplayDocCustomContainer*& o_pCustomContainer);
        /*
         * @brief 创建圆	order 19
         * @param i_pCustomContainer 文档类型
         * @param i_Axis		坐标系
         * @param i_radius  半径
         * @param o_modelBody  输出圆
         */
        virtual NctiGeometryResult create_circle(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_radius,
            NCTI_MODEL_TAG& o_modelBody);

        /*
         * @brief 旋转操作	order 20
         * @param i_pCustomContainer 文档类型
         * @param i_pSrcModelBody 待旋转的对象
         * @param i_pntRotateCenter  旋转中心点
         * @param i_vRotateAxis  旋转轴的方向
         * @param i_fRotateAngle  旋转角度
         * @param o_modelBody  旋转结果对象
         */
        virtual NctiGeometryResult revolve_operate(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcModelBody,
            const NctiPosition& i_pntRotateCenter,
            const NctiVector& i_vRotateAxis,
            Ncti_Double i_fRotateAngle,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 创建Wire线	order 21
         * @param i_pCustomContainer 文档类型
         * @param i_EdgesVec  边集合
         * @param o_modelBody  输出wire
         */
        virtual NctiGeometryResult create_wire(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_EdgesVec,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 提取属性	order 22
         * @param i_pCustomContainer 文档类型
         * @param i_pModelBody 提取属性的对象
         * @param o_geomProp  输出的属性值
         */
        virtual NctiGeometryResult extract_prop(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pModelBody,
            NctiGeomProp& o_geomProp);
        /*
         * @brief 旋转对象	order 23
         * @param i_pCustomContainer 文档类型
         * @param i_pntBase 旋转轴心
         * @param i_vector  旋转轴线方向
         * @param i_Angle   旋转角度
         * @param io_pModelBodyVec 旋转对象
         */
        virtual NctiGeometryResult rotate_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiPosition& i_pntBase,
            const NctiVector& i_vector,
            Ncti_Double i_Angle,
            std::vector<NCTI_MODEL_TAG>& io_pModelBodyVec);
        /*
         * @brief 线性扫掠	order 24
         * @param i_pCustomContainer 文档类型
         * @param i_pModelBody 操作对象
         * @param i_vector  矢量
         * @param o_pModelBody 输出对象
         */
        virtual NctiGeometryResult prism(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pModelBody,
            const NctiVector& i_vector,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief 镜像	order 25
         * @param i_pCustomContainer 文档类型
         * @param i_pModelBody 操作对象
         * @param i_pntBase  镜像源点
         * @param i_vector   镜像方向
         * @param o_pModelBody 输出对象
         */
        virtual NctiGeometryResult mirror_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pModelBody,
            const NctiPosition& i_pntBase,
            const NctiVector& i_vector,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief 缝合	order 26
         * @param i_pCustomContainer 文档类型
         * @param i_pSewiedBodyVec 被缝合对象
         * @param i_tolerance  容差
         * @param o_pSewingBody 输出对象
         */
        virtual NctiGeometryResult sewing_bodies(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_pSewiedBodyVec,
            Ncti_Double i_tolerance, Ncti_Sewing_Params i_Params,
            NCTI_MODEL_TAG& o_pSewingBody);
        /*
         * @brief 创建楔形	order 27
         * @param i_pCustomContainer 文档类型
         * @param i_Axis 坐标系
         * @param i_dx X长度
         * @param i_dy Y长度
         * @param i_dz Z长度
         * @param i_xMin X最小值
         * @param i_zMin Z最小值
         * @param i_xMax X最大值
         * @param i_zMax Z最大值
         * @param o_pSewingBody 输出对象
         */
        virtual NctiGeometryResult create_wedge(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_dx,
            Ncti_Double i_dy,
            Ncti_Double i_dz,
            Ncti_Double i_xMin,
            Ncti_Double i_zMin,
            Ncti_Double i_xMax,
            Ncti_Double i_zMax,
            NCTI_MODEL_TAG& o_pSewingBody);
        /*
         * @brief 沿曲线扫掠轮廓	order 28
         * @param i_pCustomContainer 文档类型
         * @param i_pSpineBody 曲线
         * @param i_pProfileBody 轮廓
         * @param o_pModelBody 扫掠结果
         */
        virtual NctiGeometryResult create_pipe(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSpineBody,
            NCTI_MODEL_TAG i_pProfileBody,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief 圆环	order 29
         * @param i_pCustomContainer 文档类型
         * @param i_Axis 坐标系
         * @param i_rotateRadius 圆环半径
         * @param i_sectionRadius 截面半径
         * @param i_sectionAngle1 截面起始角度
         * @param i_sectionAngle2 截面终止角度
         * @param i_rotateAngle 圆环旋转角度
         * @param o_pModelBody 输出对象
         */
        virtual NctiGeometryResult create_torus(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_rotateRadius,
            Ncti_Double i_sectionRadius,
            Ncti_Double i_sectionAngle1,
            Ncti_Double i_sectionAngle2,
            Ncti_Double i_rotateAngle,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief Nurbs对象转化为B样条曲线, order 30
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody Nurbs Body
         * @param o_pTargetBody 输出对象
         */
        virtual NctiGeometryResult nurbs_convert(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 翻转法向	order 31
         * @param i_pCustomContainer 文档类型
         * @param o_pModelBody 翻转对象
         */
        virtual NctiGeometryResult reverse_normal(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_pModelBody);

        /*
         * @brief 创建无限大平面	order 32
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceWire	源线对象
         * @param i_Axis 坐标系
         * @param o_pModelBody 输出对象
         */
        virtual NctiGeometryResult create_plane(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceWire,
            const NctiAxis& i_Axis,
            NCTI_MODEL_TAG& o_pModelBody);

        /*
         * @brief 创建polyline	order 33
         * @param i_pCustomContainer 文档类型
         * @param i_vtPoints 点的数组
         * @param o_pModelBody 输出对象
         */
        virtual NctiGeometryResult create_polyline(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NctiPosition>& i_vtPoints,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief 创建B样条曲线	order 34
         * @param i_pCustomContainer 文档类型
         * @param i_degree 次数
         * @param i_Knots 节点集
         * @param i_Multiplicities 重复数
         * @param i_ControlPts 控制点集
         * @param i_Weights 权重
         * @param i_Period 是否启用周期性
         * @param o_pModelBody 输出对象
         */
        virtual NctiGeometryResult bspline_curve(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_degree,
            const std::vector<Ncti_Double>& i_Knots,
            const std::vector<Ncti_Integer>& i_Multiplicities,
            const std::vector<NctiPosition>& i_ControlPts,
            const std::vector<Ncti_Double>& i_Weights,
            Ncti_Boolean i_Period,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief 创建顶点	order 35
         * @param i_pCustomContainer 文档类型
         * @param i_Vertex 顶点
         * @param o_pModelBody 输出对象
         */
        virtual NctiGeometryResult create_vertex(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiPosition& i_Vertex,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief 创建等参线	order 36
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入对象
         * @param i_isoType 等参线类型，0为 u  1为 v
         * @param i_paramValue 对应类型uv值
         * @param o_pTargetBody 输出对象
         */
        virtual NctiGeometryResult create_uviso(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            Ncti_Integer i_isoType,
            Ncti_Double i_paramValue,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 拔模	order 37
         * @param i_pCustomContainer 文档类型
         * @param i_pBody 拔模对象
         * @param i_vector 方向向量
         * @param i_pFace 拔模面
         * @param i_dAngle 拔模角度
         * @param i_LeanCenterPt 中性面的倾斜中心点
         * @param i_Normal 中性面的法向
         */
        virtual NctiGeometryResult depouille(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_pBody,
            const NctiVector& i_vector,
            const std::vector<NCTI_MODEL_TAG>& i_pFaces,
            const std::vector<Ncti_Double>& i_dAngles,
            const std::vector<NctiPosition>& i_LeanCenterPts,
            const std::vector<NctiVector>& i_Normals);
        /*
         * @brief 根据已有Edge及始末参数值创建新Edge	order 38
         * @note  当时始末参数相等时，自动修改为原curve始末参数
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 原有的Edge
         * @param i_paramFirstValue 新Edge起始参数
         * @param i_paramSecondValue 新Edge结束参数
         * @param o_pTargetBody 返回结果
         */
        virtual NctiGeometryResult create_sub_edge(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            Ncti_Double i_paramFirstValue,
            Ncti_Double i_paramSecondValue,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 根据已有Face及始末uv参数值创建新Face	order 39
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 原有的Face
         * @param i_u_paramFValue 新Face的u起始参数
         * @param i_u_paramLValue 新Face的u结束参数
         * @param i_v_paramFValue 新Face的v起始参数
         * @param i_v_paramLValue 新Face的v结束参数
         * @param i_LimitFace     是否受face边界约束
         * @param o_pTargetBody 返回结果
         */
        virtual NctiGeometryResult create_sub_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            Ncti_Double i_u_paramFValue,
            Ncti_Double i_u_paramLValue,
            Ncti_Double i_v_paramFValue,
            Ncti_Double i_v_paramLValue,
            Ncti_Boolean i_LimitFace,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 对象1和对象2求交线	order 40
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody1 求交对象1
         * @param i_pSourceBody2 求交对象2
         * @param i_bPCurveOnObj1 是否计算交线在Object2的PCurve
         * @param i_bPCurveOnObj2 是否计算交线在Object2的PCurve
         * @param i_bAppro 是否允许拟合
         * @param o_pTargetBody 返回结果
         */
        virtual NctiGeometryResult create_intersect_curve(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody1,
            NCTI_MODEL_TAG i_pSourceBody2,
            Ncti_Boolean i_bPCurveOnObj1,
            Ncti_Boolean i_bPCurveOnObj2,
            Ncti_Boolean i_bAppro,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 创建半平面空间	order 41
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入的face或shell
         * @param i_halfSpaceRef 参考点
         * @param o_pTargetBody 返回结果
         */
        virtual NctiGeometryResult create_half_space(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NctiPosition i_halfSpaceRef,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 根据已有的Face及新的Face边界创建面	order 42
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 原有的Face
         * @param i_pWire 新Face的边界
         * @param o_pTargetBody 返回结果
         */
        virtual NctiGeometryResult create_make_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pWire,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 寻找点的最近面	order 43
         * @param i_pCustomContainer 文档类型
         * @param i_TargeBody 目标对象
         * @param i_PointVec 点
         * @param o_ModelFaceVec 输出最近面
         */
        virtual NctiGeometryResult find_nearest_face_by_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            const std::vector<NctiPosition>& i_PointVec,
            std::vector<NCTI_MODEL_TAG>& o_ModelFaceVec);

        /*
         * @brief 通过uv值获取面上的点	order 44
         * @param i_pCustomContainer 文档类型
         * @param i_TargeBody 目标对象
         * @param i_ModelFace 输入目标对象上的面
         * @param i_u_value 面上u值(归一化)
         * @param i_v_value 面上v值（归一化）
         * @param o_Point 输出点
         */
        virtual NctiGeometryResult get_point_on_face_by_uv(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG i_ModelFace,
            Ncti_Double i_u_value,
            Ncti_Double i_v_value,
            NctiPosition& o_Point);
        /*
         * @brief 创建圆弧	order 45
         * @param i_pCustomContainer 文档类型
         * @param i_Axis 坐标系
         * @param i_radius 半径
         * @param i_startAngle 开始角度(弧度)
         * @param i_endAngle 结束角度(弧度)
         * @param o_pTargetBody 输出结果
         */
        virtual NctiGeometryResult create_arc(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_radius,
            Ncti_Double i_startAngle,
            Ncti_Double i_endAngle,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 创建轮廓	order 46
         * @param i_pCustomContainer 文档类型
         * @param i_EdgesVec      平面线条(uv域上的线条)
         * @param i_ProfileBody   创建轮廓的曲面所属实体
         * @param i_ProfileFace   轮廓的曲面,i_ProfileBody为Face或只有一个Face，则此参数可为nullptr
         * @param i_onlyWire      生成曲线，true则生成结果为wire，false则生成结果为face
         * @param o_modelBody     输出结果
         */
        virtual NctiGeometryResult create_profile(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_EdgesVec,
            NCTI_MODEL_TAG i_ProfileBody,
            NCTI_MODEL_TAG i_ProfileFace,
            Ncti_Boolean i_onlyWire,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 对象的矩阵变化	order 47
         * @param i_pCustomContainer 文档类型
         * @param i_mat			变换矩阵（二维变换矩阵）
         * @param io_modelBody     输入输出实体
         */
        virtual NctiGeometryResult transform_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_mat[3][3],
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 获取边上最近点的位置和切向	order 48
         * @param i_pCustomContainer 文档类型
         * @param i_SourceBody		输入几何对象
         * @param i_Edge             指定几何对象的边，若为nullptr，则从i_SourceBody的边中查找最近的点
         * @param i_point			输入查找的点
         * @param o_closetPoint      输出最近点
         * @param o_tangent          输出点的切向
         */
        virtual NctiGeometryResult get_closet_point_and_tangent(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            NCTI_MODEL_TAG i_Edge,
            const NctiPosition& i_point,
            NctiPosition& o_closetPoint,
            NctiVector& o_tangent);
        /*
         * @brief 偏移	order 49
         * @param i_pCustomContainer 文档类型
         * @param i_SourceBody 源对象
         * @param i_OffsetVector 偏移方向
         * @param i_Distance 偏移距离
         * @param o_pTargetBody 输出对象
         */
        virtual NctiGeometryResult offset_object(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            const NctiVector& i_OffsetVector,
            double i_Distance,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 通过参数获取边上点的位置和切向	order 50
         * @param i_pCustomContainer 文档类型
         * @param i_SourceBody		输入实体对象
         * @param i_Edge             指定实体对象的边，若为nullptr，则视为实体对象为只有一条边
         * @param i_param			输入查找边的参数
         * @param o_closetPoint      输出点
         * @param o_tangent          输出点的切向
         * @param i_isTangentNormalize		输出点的切向是否单位化
         */
        virtual NctiGeometryResult get_edge_point_and_tangent(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            NCTI_MODEL_TAG i_Edge,
            Ncti_Double i_param,
            NctiPosition& o_closetPoint,
            NctiVector& o_tangent,
            Ncti_Boolean i_isTangentNormalize);
        /*
         * @brief 裁剪对象（线条或者面片）	order 51
         * @param i_pCustomContainer 文档类型
         * @param i_SourceBody		输入实体对象
         * @param i_fU1				输入的曲线起始参数，或者是曲面U方向的起始参数
         * @param i_fU2				输入的曲线终止参数，或者是曲面U方向的终止参数
         * @param i_fV1				输入曲面V方向的起始参数
         * @param i_fV2				输入曲面V方向的终止参数
         * i_bUSense				输入曲线参数方向，或者曲面U方向的参数方向
         * i_bVSense				输入曲面V方向的参数方向
         * @param o_TargetBody      返回结果
         */
        virtual NctiGeometryResult trim_object(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            Ncti_Double i_fU1,
            Ncti_Double i_fU2,
            Ncti_Double i_fV1,
            Ncti_Double i_fV2,
            Ncti_Boolean i_bUSense,
            Ncti_Boolean i_bVSense,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 多模型布尔分割，只取集合1和集合2的交集部分 order 52
         * @param i_pCustomContainer
         * @param i_FModelBodyVec 分割对象集合1(集合内取并集）
         * @param i_SModelBodyVec 分割对象集合2(集合内取并集）
         * @param o_ModelBody 输出对象
         * @param
         */
        virtual NctiGeometryResult split(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_FModelBodyVec,
            const std::vector<NCTI_MODEL_TAG>& i_SModelBodyVec,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 阵列	order 53
         * @param i_pCustomContainer 文档类型
         * @param i_SrcBody		输入实体对象
         * @param i_PeriodicVec		阵列数据
         * @param o_TarBody		输出阵列对象
         */
        virtual NctiGeometryResult periodic(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SrcBody,
            const std::vector<Ncti_Geo_Periodic>& i_PeriodicVec,
            NCTI_MODEL_TAG& o_TarBody);
        /*
         * @brief 创建椭圆	order 54
         * @param i_pCustomContainer 文档类型
         * @param i_Axis		椭圆坐标系
         * @param i_majorRadius		长轴半径
         * @param i_minorRadius		短轴半径
         * @param o_TargetBody		输出实体对象
         */
        virtual NctiGeometryResult create_ellipse(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            const Ncti_Double& i_majorRadius,
            const Ncti_Double& i_minorRadius,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 创建组合体	order 55
         * @param i_pCustomContainer 文档类型
         * @param i_SourceBodys		源对象数组
         * @param o_TargetBody		输出组合对象
         */
        virtual NctiGeometryResult create_compound(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::vector<NCTI_MODEL_TAG> i_SourceBodys,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 添加Body	order 56
         * @param i_pCustomContainer 文档类型
         * @param i_SModelBody		源对象
         * @param i_TModelBody		目标对象
         * @param o_ModelBody		输出对象
         */
        virtual NctiGeometryResult add_object(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SModelBody,
            NCTI_MODEL_TAG i_TModelBody,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 根据参数创建一个棱柱并根据后续命令与现有的模型进行不同特征	order 57
         * @param i_pCustomContainer 文档类型
         * @param i_pSrcTargetBody			用于与Prism后的对象，进行布尔操作的目标对象
         * @param i_pSrcProfileFaceObject	用于定义Prism的基础轮廓对象
         * @param i_pSrcSkewFaceObject		用于定义Prism方向的参考对象
         * @param i_pPrismFromObject		Prism操作的起始位置
         * @param i_pPrismUntilObject		Prism操作的终止位置
         * @param i_pPrismHeight			Prism操作的高度
         * @param i_fDraftAngle				Prism操作的拔模角度，＋为向外拔模，-为向内拔模
         * @param i_nBooleanMode			拉伸后的对象与i_pSrcTargetBody的融合方式 参数可选为0,1,2	0 代表创建的棱柱用于布尔减除	1 - 代表创建的棱柱用于布尔增加	2 - 未知
         * @param i_nOption					可选参数
         * @param o_pReturnBody				返回结果
         */
        virtual NctiGeometryResult feat_dprism(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcTargetBody,
            NCTI_MODEL_TAG i_pSrcProfileFaceObject,
            NCTI_MODEL_TAG i_pSrcSkewFaceObject,
            NCTI_MODEL_TAG i_pPrismFromObject,
            NCTI_MODEL_TAG i_pPrismUntilObject,
            const Ncti_Double* i_pPrismHeight,
            Ncti_Double i_fDraftAngle,
            Ncti_Long i_nBooleanMode,
            Ncti_Long i_nOption,
            NCTI_MODEL_TAG& o_pReturnBody);
        /*
         * @brief 创建公切线	order 58
         * @param i_pCustomContainer 文档类型
         * @param i_EdgeTag1		对象1
         * @param i_EdgeTag2		对象2
         * @param i_Angle		    角度
         * @param o_ModelBodyVec	输出对象集合
         */
        virtual NctiGeometryResult create_tangent(
            NctiDisplayDocCustomContainer* pSDDisplayDocCustomContainer,
            NCTI_MODEL_TAG i_EdgeTag1,
            NCTI_MODEL_TAG i_EdgeTag2,
            Ncti_Double i_Angle,
            std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec);

        /*
         * @brief 根据参数创建一个棱柱并根据后续命令与现有的模型进行不同特征	order 59
         * @param i_pCustomContainer 文档类型
         * @param i_pSrcTargetBody			用于与Prism后的对象，进行布尔操作的目标对象
         * @param i_pSrcProfileFaceObject	用于定义Prism的基础轮廓对象
         * @param i_pSrcSkewFaceObject		用于定义Prism方向的参考对象
         * @param i_pPrismFromObject		Prism操作的起始位置
         * @param i_pPrismUntilObject		Prism操作的终止位置
         * @param i_vDirection				Prism操作的拉伸方向
         * @param i_pPrismHeight			Prism操作的高度
         * @param i_nBooleanMode			拉伸后的对象与i_pSrcTargetBody的融合方式 参数可选为0,1,2	0 代表创建的棱柱用于布尔减除	1 - 代表创建的棱柱用于布尔增加	2 - 未知
         * @param i_nOption					可选参数
         * @param o_pReturnBody				返回结果
         */
        virtual NctiGeometryResult feat_prism(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcTargetBody,
            NCTI_MODEL_TAG i_pSrcProfileFaceObject,
            NCTI_MODEL_TAG i_pSrcSkewFaceObject,
            NCTI_MODEL_TAG i_pPrismFromObject,
            NCTI_MODEL_TAG i_pPrismUntilObject,
            const NctiVector& i_vDirection,
            const Ncti_Double* i_pPrismHeight,
            Ncti_Long i_nBooleanMode,
            Ncti_Long i_nOption,
            NCTI_MODEL_TAG& o_pReturnBody);
        /*
         * @brief 偏移实体上的面形成新的实体	order 60
         * @param i_pCustomContainer  文档类型
         * @param i_sourceBody        输入的实体
         * @param i_pFaces            指定要偏移的面，为空则全部面偏移
         * @param i_InitOffsetValue   初始化指定的偏移值
         * @param i_offsetValue       面的偏移量，或与面数组一一对应，或为空
         * @param i_connectType       连接方式 0-GeomAbs_Arc 1-GeomAbs_Tangent,2-GeomAbs_Intersection
         * @param o_targetBody        输出生成的实体
         * @param i_tol               设置误差
         * @param i_inter             是否完全相交模式
         * @param i_selfInter         是否允许自交
         * @param i_thickening        是否为加厚
         * @param i_removeIntEdge     是否去除内部的边
         * */
        virtual NctiGeometryResult offset_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_sourceBody,
            NCTI_MODEL_TAG& o_targetBody,
            Ncti_Double i_InitOffsetValue,
            std::vector<NCTI_MODEL_TAG> i_pFaces,
            std::vector<Ncti_Double> i_offsetValue,
            Ncti_Long i_connectType,
            Ncti_Double i_tol,
            Ncti_Boolean i_inter,
            Ncti_Boolean i_selfInter,
            Ncti_Boolean i_thickening,
            Ncti_Boolean i_removeIntEdge);
        /*
         * @brief 根据参数创建一个旋转体，并根据后续命令与现有的模型进行不同特征	order 61
         * @param i_pCustomContainer		文档类型
         * @param i_pSrcTargetBody			用于与Revol后的对象，进行布尔操作的目标对象
         * @param i_pSrcProfileFaceObject	用于定义Revol的基础轮廓对象
         * @param i_pSrcSkewFaceObject		用于定义Revol方向的参考对象
         * @param i_pRevolFromObject		Revol操作的起始位置
         * @param i_pRevolUntilObject		Revol操作的终止位置
         * @param i_pntLocation				旋转中心轴通过的点
         * @param i_vDirection				旋转中心轴方向
         * @param i_pRevolAngle				旋转角度
         * @param i_nBooleanMode			旋转后的对象与i_pSrcTargetBody的融合方式 参数可选为0,1,2	0 代表创建的棱柱用于布尔减除	1 - 代表创建的棱柱用于布尔增加	2 - 未知
         * @param i_nOption					可选参数
         * @param o_pReturnBody				返回结果
         */
        virtual NctiGeometryResult feat_Revol(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcTargetBody,
            NCTI_MODEL_TAG i_pSrcProfileFaceObject,
            NCTI_MODEL_TAG i_pSrcSkewFaceObject,
            NCTI_MODEL_TAG i_pRevolFromObject,
            NCTI_MODEL_TAG i_pRevolUntilObject,
            const NctiPosition& i_pntLocation,
            const NctiVector& i_vDirection,
            const Ncti_Double* i_pRevolAngle,
            Ncti_Long i_nBooleanMode,
            Ncti_Long i_nOption,
            NCTI_MODEL_TAG& o_pReturnBody);
        /*
         * @brief 获取点坐标	order 62
         * @param i_pCustomContainer	文档类型
         * @param i_pSrcTargetBody	输入的实体对象
         * @param i_vertexTag	    点元素，若为空则判断i_pSrcTargetBody是否为点类型
         * @param o_pnt	            输出点坐标
         */
        virtual NctiGeometryResult get_vertex_pnt(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcTargetBody,
            NCTI_MODEL_TAG i_vertexTag,
            NctiPosition& o_pnt);
        /*
         * @brief 获取边的始末点及切向	order 63
         * @param i_pCustomContainer	文档类型
         * @param i_pSrcTargetBody	输入的实体对象
         * @param i_edge_tag	        边，若为空则判断i_pSrcTargetBody是否为边类型
         * @param o_pnt_start        起点
         * @param o_pnt_end          终点
         * @param o_tangent_start    起点法向
         * @param o_tangent_end	    终点法向
         */
        virtual NctiGeometryResult get_edge_end_points(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcTargetBody,
            NCTI_MODEL_TAG i_edge_tag,
            NctiPosition& o_pnt_start,
            NctiPosition& o_pnt_end,
            NctiVector& o_tangent_start,
            NctiVector& o_tangent_end);

        /*
         * @brief 根据参数创建一个线性加厚特征，并根据后续命令与现有的模型进行不同特征	order 64
         * @param i_pCustomContainer			文档类型
         * @param i_pSrcTargetBody			用于与LienarForm后的对象，进行布尔操作的目标对象
         * @param i_pSrcProfileWireObject	用于定义LienarForm的基础轮廓对象
         * @param i_pSrcPlaneObject			用于定义LienarForm方向的参考对象
         * @param i_vThicken1				方向1上的加厚
         * @param i_vThicken2				方向2上的加厚
         * @param i_nBooleanMode			LienarForm后的对象与i_pSrcTargetBody的融合方式 参数可选为0,1,2	0 代表创建的棱柱用于布尔减除	1 - 代表创建的棱柱用于布尔增加	2 - 未知
         * @param i_nOption					可选参数
         * @param o_pReturnBody				返回结果
         */
        virtual NctiGeometryResult feat_lienarform(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcTargetBody,
            NCTI_MODEL_TAG i_pSrcProfileWireObject,
            NCTI_MODEL_TAG i_pSrcPlaneObject,
            const NctiVector& i_vThicken1,
            const NctiVector& i_vThicken2,
            Ncti_Long i_nBooleanMode,
            Ncti_Long i_nOption,
            NCTI_MODEL_TAG& o_pReturnBody);

        /*
         * @brief 根据参数为指定模型使用旋转命令增加筋条/槽	order 65
         * @param i_pCustomContainer			文档类型
         * @param i_pSrcTargetBody			用于与LienarForm后的对象，进行布尔操作的目标对象
         * @param i_pSrcProfileWireObject	用于定义LienarForm的基础轮廓对象
         * @param i_pSrcPlaneObject			用于定义LienarForm方向的参考对象
         * @param i_pntRevolveAxis			旋转轴通过的点
         * @param i_vRevolveAxis			旋转轴的方向
         * @param i_fHeight1				高度限制1
         * @param i_fHeight2				高度限制2
         * @param i_nBooleanMode			LienarForm后的对象与i_pSrcTargetBody的融合方式 参数可选为0,1,2	0 代表创建的棱柱用于布尔减除	1 - 代表创建的棱柱用于布尔增加	2 - 未知
         * @param i_nOption					可选参数
         * @param o_pReturnBody				返回结果
         */
        virtual NctiGeometryResult feat_revolutionform(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcTargetBody,
            NCTI_MODEL_TAG i_pSrcProfileWireObject,
            NCTI_MODEL_TAG i_pSrcPlaneObject,
            const NctiPosition& i_pntRevolveAxis,
            const NctiVector& i_vRevolveAxis,
            Ncti_Double i_fHeight1,
            Ncti_Double i_fHeight2,
            Ncti_Long i_nBooleanMode,
            Ncti_Long i_nOption,
            NCTI_MODEL_TAG& o_pReturnBody);
        /*
        * @brief 根据设置的参数进行扫掠	order 66
        * @param i_pCustomContainer			 文档类型
        * @param i_pWireSpine                脊线
        * @param i_Unif		                 脊线是否合并域处理
        * @param i_SweepMode                 设置不同的标架方法
                                                 0--"-FR" 标架由曲线局部坐标系给出
                                                 1--"-CF" 标架由曲线切向和法线计算最小化扭率得出
                                                 2--"-DT" 离散的正交标架
                                                 3--"-DX" 由一个曲面(或壳)给出标架，切线和法线由Darboux标架（另一种沿曲线的标架）定义
                                                 4--"-CN" 由一个方向定义了副法向以确定标架
                                                 5--"-FX" 标架由固定的切向和法向确定
                                                 6--"-G"  选定引导线，并定义该引导线的接触类型
        * @param i_DX_Shape                  指定Face或Shell（DX模式下)
        * @param i_DX_Cell                   指定的Face或Shell为i_DX_Shape上的元素（DX模式下)
        * @param i_CN_Dir                    指定方向定义副法向（CN模式下）
        * @param i_FX_DVec                   指定标架固定的切向（FX模式下）
        * @param i_FX_DNVec                  指定标架固定的法向（FX模式下）
        * @param i_G_Wire_Guide              指定引导线（G模式下）
        * @param i_G_CurvilinearEquivalence  曲率参数  0|1(Plan|ACR)（G模式下）
        * @param i_G_KeepContact             接触参数  0|1|2(不接触|接触|边界接触)（G模式下）(no contact|contact|contact on border)
        * @param i_MaxDegree                 近似的最大度数，参数值必须大于0，默认为100
        * @param i_MaxSeg                    近似的最大跨度数，参数值应在1到14之间，默认11
        * @param i_Sections                  截面设置
        * @param i_AngleTol                  角度容差
        * @param i_LinearTol                 线性容差
        * @param i_TransitionMode            过渡方式 0-默认 1-直角 2-圆角
        * @param i_BuildSolid                生成为实体
        * @param o_Target                    输出结果
        */
        virtual NctiGeometryResult make_sweep(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pWireSpine,
            Ncti_Boolean i_Unif,
            Ncti_Long i_SweepMode,
            NCTI_MODEL_TAG i_DX_Shape,
            NCTI_MODEL_TAG i_DX_Cell,
            NctiVector i_CN_Dir,
            NctiVector i_FX_DVec,
            NctiVector i_FX_DNVec,
            NCTI_MODEL_TAG i_G_Wire_Guide,
            Ncti_Boolean i_G_CurvilinearEquivalence,
            Ncti_Integer i_G_KeepContact,
            Ncti_Integer i_MaxDegree,
            Ncti_Integer i_MaxSeg,
            std::vector<NctiSewwpSection> i_Sections,
            Ncti_Double i_AngleTol,
            Ncti_Double i_LinearTol,
            Ncti_Integer i_TransitionMode,
            Ncti_Boolean i_BuildSolid,
            NCTI_MODEL_TAG& o_Target);
        /*@brief 合并具有相同域的形状	order 67
         * @param i_pCustomContainer	文档类型
         * @param i_ModelBodyVec	输入的实体对象
         *	i_ModelBodyVec[0]:待简化的对象
         *   i_ModelBodyVec[1~n-1]:需要保留的对象
         * @param i_Config	       配置项
         * @param o_Tag        输出对象
         */
        virtual NctiGeometryResult unifysamedom(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
            const Ncti_Geo_Unifysamedom& i_Config,
            NCTI_MODEL_TAG& o_Tag);
        /*@brief 抽取对象的子元素	order 68
         * @param i_pCustomContainer	文档类型
         * @param i_pSourceBody		输入的实体对象
         * @param i_pSourceCell	    点边面
         * @param o_pTarget          输出对象
         */
        virtual NctiGeometryResult extract_cell(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pSourceCell,
            NCTI_MODEL_TAG& o_pTarget);
        /*
         * @brief 抽取对象的UV	order 69
         * @param i_pCustomContainer	文档类型
         * @param i_pSourceBody		输入的实体对象
         * @param o_bounds          输出边界UV对象
         */
        virtual NctiGeometryResult extract_bounds(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NctiGeomBounds& o_bounds);
        /*
         * @brief 求交点或交线	order 70
         * @param i_pCustomContainer		文档类型
         * @param i_pSourceBody1		 输入的实体对象1
         * @param i_SourceBody2          输入的实体对象2
         * @param o_SectionBody          输出相交对象
         */
        virtual NctiGeometryResult extract_section(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody1,
            NCTI_MODEL_TAG i_SourceBody2,
            NCTI_MODEL_TAG& o_SectionBody);
        /*
         * @brief 输出对象的各个类型的拓扑数量及总数量	order 71
         * @param i_pCustomContainer	文档类型
         * @param i_pSourceBody		输入的实体对象
         * @param i_LocDifferent     不同location是否作为不同拓扑
         * @param o_Type_Nb          输出对应类型及数量，0-Vertex 1-edge 2-wire 3-face 4-shell 5-solid 6-compsolid 7-compound 8-shape
         *                          v2.0: 20-fin; 21-edge; 22-内存使用
         */
        virtual NctiGeometryResult dump_topology(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            Ncti_Boolean i_LocDifferent,
            std::map<int, int>& o_Type_Nb);
        /*
         * @brief 通过参数获取边上点的位置、一阶导和二阶导	order 72
         * @param i_pCustomContainer 文档类型
         * @param i_SourceBody		输入实体对象
         * @param i_Edge             指定实体对象的边，若为nullptr，则视为实体对象为只有一条边
         * @param i_param			输入查找边的参数
         * @param o_closetPoint      输出点位置
         * @param o_tangent          输出曲线在参数的一阶导
         * @param o_secDer           输出曲线在参数的二阶导
         * @param i_isTangentNormalize	输出曲线在参数的一阶导是否单位化
         */
        virtual NctiGeometryResult get_edge_value_by_param(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            NCTI_MODEL_TAG i_Edge,
            Ncti_Double i_param,
            NctiPosition& o_closetPoint,
            NctiVector& o_tangent,
            NctiVector& o_secDer,
            Ncti_Boolean i_isTangentNormalize);
        /*
         * @brief 轮廓的不闭合点个数	order 73
         * @param i_pCustomContainer 文档类型
         * @param i_SourceBody		输入实体对象
         * @param i_Cell           指定实体对象的子元素，若为nullptr，则检查实体对象
         * @param o_alone			    输出不闭合点个数
         */
        virtual NctiGeometryResult get_section_alone_vertex(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            NCTI_MODEL_TAG i_Cell,
            Ncti_Integer& o_alone);
        /*
         * @brief 倒角	order 74
         * @param i_pCustomContainer		文档类型
         * @param i_SourceBody			输入实体对象
         * @param i_EdgeVec				边对象
         * @param i_FaceVec			    面对象
         * @param i_DistanceVec			距离参数
         * @param i_AngleVec			    角度参数
         * @param o_pTarget			    输出对象
         */
        virtual NctiGeometryResult chamfer_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            const std::vector<NCTI_MODEL_TAG>& i_EdgeVec,
            const std::vector<NCTI_MODEL_TAG>& i_FaceVec,
            const std::vector<Ncti_Double>& i_DistanceVec,
            const std::vector<Ncti_Double>& i_AngleVec,
            NCTI_MODEL_TAG& o_pTarget);
        /*
         * @brief 变径倒圆角	order 75
         * @param i_pCustomContainer	文档类型
         * @param i_SourceBody			输入实体对象
         * @param i_EdgeParamVec		边对象参数，包括边和曲线参数及半径
         * @param i_FilletMode			圆角的设置 0 - ChFi3d_Rational(默认) 1-ChFi3d_QuasiAngular 2-ChFi3d_Polynomial
         * @param o_pTarget			    输出对象
         */
        virtual NctiGeometryResult fillet_evol_radius(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            const std::vector<Ncti_Geo_Evol_Radius>& i_EdgeParamVec,
            Ncti_Integer i_FilletMode,
            NCTI_MODEL_TAG& o_pTarget);
        /*
         * @brief 定义方向	order 76
         * @param i_pCustomContainer		文档类型
         * @param i_SourceBody			输入实体对象
         * @param i_Cell				输入子元素，若为空则操作i_SourceBody
         * @param i_Orientation			方向参数 0 - TopAbs_FORWARD, 1 - TopAbs_REVERSED, 2 - TopAbs_INTERNAL, 3 - TopAbs_EXTERNAL
         * @param o_pTarget			    输出对象
         */
        virtual NctiGeometryResult set_orientation(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            NCTI_MODEL_TAG i_Cell,
            Ncti_Integer i_Orientation,
            NCTI_MODEL_TAG& o_pTarget);
        /*
         * @brief 拟合面片	order 77
         * @param i_pCustomContainer		文档类型
         * @param i_approx_data			输入参与拟合的面片和边
         * @param i_NPt					与约束相关联的点的数量
         * @param i_tol3d				拟合精度
         * @param i_Nbmax			    Bezier面片最大数量
         * @param i_degmax			    Bezier面片最大阶数
         * @param i_CritOrder			使用评价准则，-1不使用任何准则 0使用使用PlateG0Criterion 1使用PlateG1Criterion
         * @param o_pTarget			    输出对象
         */
        virtual NctiGeometryResult make_approx_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<Ncti_Geo_Approx_Data>& i_approx_data,
            Ncti_Integer i_NPt,
            Ncti_Double i_tol3d,
            Ncti_Integer i_Nbmax,
            Ncti_Integer i_degmax,
            Ncti_Integer i_CritOrder,
            NCTI_MODEL_TAG& o_pTarget);
        /*
         * @brief 通过几何面创建面片	order 78
         * @param i_pCustomContainer		文档类型
         * @param i_SourceBody			输入的实体，i_Cell为null则该实体的几何面作为输入对象
         * @param i_Cell                 实体子元素，指定面
         * @param o_pTarget			    输出对象
         */
        virtual NctiGeometryResult make_face_by_surface(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            NCTI_MODEL_TAG i_Cell,
            NCTI_MODEL_TAG& o_pTarget);
        /*
         * @brief 创建抛物线	order 79
         * @param i_pCustomContainer 文档类型
         * @param i_Axis				抛物线坐标系
         * @param i_focal			焦点距离
         * @param i_firstParm		抛物线的起始参数
         * @param i_lastParm			抛物线的终止参数
         * @param o_TargetBody		输出实体对象
         */
        virtual NctiGeometryResult create_parabola(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            const Ncti_Double& i_focal,
            const Ncti_Double& i_firstParm,
            const Ncti_Double& i_lastParm,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 创建Bspline曲面	order 80
         * @param i_pCustomContainer 文档类型
         * @param i_u_degree			曲面U方向阶数
         * @param i_v_degree			曲面V方向阶数
         * @param i_u_periodic		U方向是否周期性
         * @param i_v_periodic		V方向是否周期性
         * @param i_u_knotVec		曲面U方向的节点向量
         * @param i_umult_knot		U方向的节点重复度
         * @param i_v_knotVec		曲面V方向的节点向量
         * @param i_vmult_knot		V方向的节点重复度
         * @param i_ctrl_points		曲面的控制点,<u1_pts,u2_pts...>
         * @param i_weight		    控制点的权重
         * @param o_TargetBody		输出实体对象
         */
        virtual NctiGeometryResult create_bspline_surf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Long& i_u_degree,
            const Ncti_Long& i_v_degree,
            const Ncti_Boolean& i_u_periodic,
            const Ncti_Boolean& i_v_periodic,
            const std::vector<Ncti_Double>& i_u_knotVec,
            const std::vector<Ncti_Integer>& i_umult_knot,
            const std::vector<Ncti_Double>& i_v_knotVec,
            const std::vector<Ncti_Integer>& i_vmult_knot,
            const std::vector<NctiPosition>& i_ctrl_points,
            const std::vector<Ncti_Double>& i_weight,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 创建Bezier曲面	order 81
         * @param i_pCustomContainer 文档类型
         * @param i_ctrl_points		曲面的控制点,v_size<u_size>
         * @param i_weight		    控制点的权重
         * @param o_TargetBody		输出实体对象
         */
        virtual NctiGeometryResult create_bezier_surf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<std::vector<NctiPosition>>& i_ctrl_points,
            const std::vector<std::vector<Ncti_Double>>& i_weight,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 创建双曲线	order 82
         * @param i_pCustomContainer 文档类型
         * @param i_Axis		        双曲线坐标系
         * @param i_majorRadius		长轴半径
         * @param i_minorRadius		短轴半径
         * @param i_firstParm		双曲线的起始参数
         * @param i_lastParm			双曲线的终止参数
         * @param o_TargetBody		输出实体对象
         */
        virtual NctiGeometryResult create_hyperbola(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            const Ncti_Double& i_majorRadius,
            const Ncti_Double& i_minorRadius,
            const Ncti_Double& i_firstParm,
            const Ncti_Double& i_lastParm,
            NCTI_MODEL_TAG& o_TargetBody);
        /*
         * @brief 放样	order 83
         * @param i_pCustomContainer 文档类型
         * @param i_Bodies			输入对象
         * @param i_isSolid			是否实体
         * @param i_isRuled			是否规则
         * @param i_isNoCheckWires		是否不检验Wires
         * @param i_isSafe				是否锁定
         * @param o_ModelBody		输出实体对象
         */
        virtual NctiGeometryResult thrusections(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_Bodies,
            Ncti_Boolean i_isSolid,
            Ncti_Boolean i_isRuled,
            Ncti_Boolean i_isNoCheckWires,
            Ncti_Boolean i_isSafe,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 创建圆切线	order 84
         * @param i_pCustomContainer 文档类型
         * @param i_Bodies			输入对象
         * @param o_Bodies			输出对象
         */
        virtual NctiGeometryResult create_circle3Tangent(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_Bodies,
            std::vector<NCTI_MODEL_TAG>& o_Bodies);
        /*
         * @brief 线拉伸面	order 85
         * @param i_pCustomContainer 文档类型
         * @param i_pModelBody			输入对象
         * @param i_vector				方向
         * @param o_pModelBody			输出对象
         */
        virtual NctiGeometryResult extend_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pModelBody,
            const NctiVector& i_vector,
            NCTI_MODEL_TAG& o_pModelBody);
        /*
         * @brief 获取对象的包围盒	order 86
         * @param i_pCustomContainer 文档类型
         * @param i_pModelBody		输入对象
         * @param o_ptMin            输出包围盒最小点
         * @param o_ptMax            输出包围盒最大点
         */
        virtual NctiGeometryResult get_boungding_box(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_pModelBody,
            NctiPosition& o_ptMin,
            NctiPosition& o_ptMax);
        /*
         * @brief 边投影到面	order 87
         * @param i_pCustomContainer 文档类型
         * @param i_Bodies		输入对象，最后一个为面
         * @param i_LimitFace    是否限制投影到面范围
         * @param i_MaxDistance  最大距离
         * @param i_Tolerance    容差
         * @param i_Continuity   曲线连续性
         * @param i_MaxDeg		最大阶数
         * @param i_MaxSeg		最大线段数
         * @param o_ModelBody	输出对象
         */
        virtual NctiGeometryResult edges_project(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_Bodies,
            Ncti_Boolean i_LimitFace,
            Ncti_Double i_MaxDistance,
            Ncti_Double i_Tolerance,
            Ncti_Integer i_Continuity,
            Ncti_Integer i_MaxDeg,
            Ncti_Integer i_MaxSeg,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 修改圆半径	order 88
         * @param i_pCustomContainer   文档类型
         * @param i_modelBody		  输入对象
         * @param i_radius             输入半径
         * @param o_modelBody          输出对象
         */
        virtual NctiGeometryResult modify_circle(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_modelBody,
            Ncti_Double i_radius,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 修改椭圆半径	order 89
         * @param i_pCustomContainer   文档类型
         * @param i_modelBody		  输入对象
         * @param i_majorRadius        输入长轴半径
         * @param i_minRadius          输入短轴半径
         * @param o_modelBody          输出对象
         */
        virtual NctiGeometryResult modify_ellipse(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_modelBody,
            Ncti_Double i_majorRadius,
            Ncti_Double i_minRadius,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 对象的矩阵变化	order 90
         * @param i_pCustomContainer 文档类型
         * @param i_mat			变换矩阵（三维变换矩阵）
         * @param io_modelBody     输入输出实体
         */
        virtual NctiGeometryResult transform_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_mat[4][4],
            NCTI_MODEL_TAG& io_modelBody);

        /*
         * @brief 曲线延伸	order 91
         * @param i_pCustomContainer 文档类型
         * @param i_pt			延伸目标点
         * @param i_Continuity	曲线连续性
         * @param i_After		从曲线末端/首端延伸
         * @param io_modelBody  输入输出实体
         */
        virtual NctiGeometryResult extend_curve(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NctiPosition i_pt,
            Ncti_Integer i_Continuity,
            Ncti_Boolean i_After,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 曲面延伸	order 92
         * @param i_pCustomContainer 文档类型
         * @param i_Length			延伸长度
         * @param i_Continuity		曲面连续性
         * @param i_isU				从U/V方向延伸
         * @param i_After			从末端/首端延伸
         * @param io_modelBody		输入输出实体
         */
        virtual NctiGeometryResult extend_surface(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_Length,
            Ncti_Integer i_Continuity,
            Ncti_Boolean i_isU,
            Ncti_Boolean i_After,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 修改B样条曲线	order 93
         * @param i_pCustomContainer 文档类型
         * @param i_modelBody		输入对象
         * @param i_ControlPts		输入控制点集
         * @param o_modelBody		输出对象
         */
        virtual NctiGeometryResult modify_bspline_curve(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_modelBody,
            const std::vector<NctiPosition>& i_ControlPts,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 获取曲面上UV的法向	order 94
         * @param i_pCustomContainer 文档类型
         * @param i_TargeBody		输入对象
         * @param i_ModelFace		输入对象的面
         * @param i_u_value			输入U值
         * @param i_v_value			输入V值
         * @param o_Normal			输出法向
         */
        virtual NctiGeometryResult get_normal_by_uv(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG i_ModelFace,
            Ncti_Double i_u_value,
            Ncti_Double i_v_value,
            NctiVector& o_Normal);
        /*
         * @brief 寻找点的最近Vertex order 95
         * @param i_pCustomContainer
         * @param i_TargeBody 目标对象
         * @param i_PointVec 点坐标
         * @param o_ModelVertexVec 输出最近点集合
         */
        virtual NctiGeometryResult find_nearest_vertex_by_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            const std::vector<NctiPosition>& i_PointVec,
            std::vector<NCTI_MODEL_TAG>& o_ModelVertexVec);
        /*
         * @brief B样条或贝塞尔曲线升阶	order 96
         * @param i_pCustomContainer		文档类型
         * @param i_degree			增加度数到该值，>=0
         * @param io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult increase_bezier_bspline_curve_degree(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_degree,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief B样条或贝塞尔曲面升阶	order 97
         * @param i_pCustomContainer		文档类型
         * @param i_udegree			增加u向度数到该值，0且i_udegree有效，只增加u向阶数
         * @param i_vdegree			增加v向度数到该值，0且i_vdegree有效，只增加v向阶数
         * @param io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult increase_bezier_bspline_surf_degree(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_udegree,
            Ncti_Long i_vdegree,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 增加B样条曲线节点	order 98
         * @param i_pCustomContainer		文档类型
         * @param i_knotVec			节点
         * @param i_multVec			重复度
         * @param io_modelBody	    输入输出对象
         */
        virtual NctiGeometryResult insert_bspline_curve_knot(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<Ncti_Double>& i_knotVec,
            const std::vector<Ncti_Long>& i_multVec,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 增加B样条曲面节点	order 99
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_uKnotVec			u节点
         * @param[in] i_uMultVec			u重复度
         * @param[in] i_vKnotVec			v节点
         * @param[in] i_vMultVec			v重复度
         * @param[in out] io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult insert_bspline_surf_knot(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<Ncti_Double>& i_uKnotVec,
            const std::vector<Ncti_Long>& i_uMultVec,
            const std::vector<Ncti_Double>& i_vKnotVec,
            const std::vector<Ncti_Long>& i_vMultVec,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 减少B样条曲线节点	order 100
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_index			节点序号，从0开始
         * @param[in] i_mult				减少的重复度，0表示删除节点
         * @param[in] i_tolerance		容差
         * @param[in out] io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult remove_bspline_curve_knot(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_index,
            Ncti_Long i_mult,
            Ncti_Double i_tolerance,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 减少B样条曲面节点	order 101
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_uIndex			u节点序号，从0开始，-1且v有效，仅修改v
         * @param[in] i_uMult			u减少的重复度，0表示删除节点
         * @param[in] i_vIndex			v节点序号，从0开始，-1且u有效，仅修改u
         * @param[in] i_vMult			v减少的重复度，0表示删除节点
         * @param[in] i_tolerance		容差
         * @param[in out] io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult remove_bspline_surf_knot(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_uIndex,
            Ncti_Long i_uMult,
            Ncti_Long i_vIndex,
            Ncti_Long i_vMult,
            Ncti_Double i_tolerance,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 将B样条曲线u值对应点移动到point并与tangent相切	order 102
         * @param[in] i_pCustomContainer			文档类型
         * @param[in] i_u					曲线u值
         * @param[in] i_point				切点
         * @param[in] i_tangent				切向
         * @param[in] i_constraint			起始和结束控制点约束 -1:可移动 0:点不可移动 1:点及其切向不可移动
         * @param[in out] io_modelBody		输入输出对象
         */
        virtual NctiGeometryResult move_bspline_curve_tangent(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_u,
            const NctiPosition& i_point,
            const NctiVector& i_tangent,
            Ncti_Long i_constraint,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 将B样条曲线u值对应点向指定向量移动	order 103
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_u				曲线u值
         * @param[in] i_direct			移动的向量
         * @param[in] i_index1			起始可移动的控制点编号，从0开始，-1时，index1取1，index2取控制点数量-2
         * @param[in] i_index2			结束可移动的控制点编号，从0开始
         * @param[in out] io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult move_bspline_curve_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Double i_u,
            const NctiVector& i_direct,
            Ncti_Long i_index1,
            Ncti_Long i_index2,
            NCTI_MODEL_TAG& io_modelBody);

        /*
         * @brief 移动B样条曲面或Bezier曲面控制点 order 104
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_row				行编号，从0开始，-1且col有效，移动整列
         * @param[in] i_col				列编号，从0开始，-1且row有效，移动整行
         * @param[in] i_direct			移动的向量
         * @param[in out] io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult move_bezier_bspline_surf_pole(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_row,
            Ncti_Long i_col,
            const NctiVector& i_direct,
            NCTI_MODEL_TAG& io_modelBody);

        /*
         * @brief 二维曲线、三维曲线或曲面创建二维或三维NURBS曲线或NURBS曲面 order 105
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_pSourceBody		输入对象
         * @param[in] i_convertMode		转换模式，仅在曲线为圆或椭圆时适用
         *	0			使用num_spans=[（ULast-UFirst）/1.2]+1计算跨度数
         *	s[N]		强制N个跨度，如果（ULast-UFirst）>=PI且N=1，ULast-UFirst>=2 PI且N=2，则将产生错误
         *	1--"s1"
         *	2--"s2"
         *	3--"s3"
         *	4--"s4"
         *	5--"qa"
         *	6--"c1"		确保了与生成的B样条曲线相关的方程，具有C1连续，增强了曲线不同跨度连接点的连续性
         *	7--"po"		生成多项式（即非有理），对得到的具有8个控制点（即多项式次数等于7）的B样条曲线进行参数化
         * @param[out] o_modelBody		输出对象
         */
        virtual NctiGeometryResult convert_to_nurbs(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            Ncti_Long i_convertMode,
            NCTI_MODEL_TAG& o_modelBody);

        /*
         * @brief 点投影到线或面中 order 106
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_modelBody		输入对象，线或者面
         * @param[in] i_point			投影的点
         * @param[in] i_algo				极值算法
         *		0--"Extrema_ExtAlgo_Grad" 梯度下降
         *		1--"Extrema_ExtAlgo_Tree" 搜索树
         * @param[out] o_modelBodyVec	输出对象
         */
        virtual NctiGeometryResult project_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_modelBody,
            const NctiPosition& i_point,
            Ncti_Long i_algo,
            std::vector<NCTI_MODEL_TAG>& o_modelBodyVec);

        /*
        * @brief 寻找点的最近子实体 order 107
        * @param i_pCustomContainer
        * @param i_TargeBody 目标对象
        * @param i_PointVec  点坐标
        * @param i_FindType  抽取类型，0：compound
                                      1:compsolid
                                      2:solid
                                      3:shell
                                      4:face
                                      5:wire
                                      6:edge
                                      7:vertex
                                      8:shape
        * @param o_ModelTagVec 输出最近子元素为实体
        */
        virtual NctiGeometryResult extract_nearest_cell_by_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            const std::vector<NctiPosition>& i_PointVec,
            Ncti_Geo_Shape_Type i_FindType,
            std::vector<NCTI_MODEL_TAG>& o_ModelTagVec);

        /*
         * @brief 生成管道	order 108
         * @param[in] i_pCustomContainer	文档类型
         * @param[in] i_pPath		曲线路径
         * @param[in] i_pFirstCurve  首部截面
         * @param[in] i_pLastCurve	尾部截面
         * @param[in] i_Radius		截面的半径
         * @param[in] i_NS			表示是否使用 -NS 选项
         * @param[in] i_vSequenceOfCurve 截面列表
         * @param[out] o_modelBody 输出管道曲面
         */
        virtual NctiGeometryResult make_tuyau(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pPath,
            NCTI_MODEL_TAG i_pFirstCurve,
            NCTI_MODEL_TAG i_pLastCurve,
            Ncti_Double i_Radius,
            Ncti_Boolean i_NS,
            std::vector<NCTI_MODEL_TAG> i_vSequenceOfCurve,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 通过一组连接、相交或嵌套的形状构建基础的实体	order 109
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_pBodies			输入模型集合
         * @param[in] i_bCompounds		表示是否使用 -c 选项
         * @param[in] i_bToIntersect		表示是否使用 -ni 选项
         * @param[in] i_bAvoidInternal	表示是否使用 -ai 选项
         * @param[out] o_modelBody		输出新构建的实体
         */
        virtual NctiGeometryResult make_volume(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::vector<NCTI_MODEL_TAG> i_pBodies,
            Ncti_Boolean i_bCompounds,
            Ncti_Boolean i_bToIntersect,
            Ncti_Boolean i_bAvoidInternal,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 使用传入对象的边构成对应的面 order 110
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_modelBody		输入对象
         * @param[out] o_modelBody		输出对象
         */
        virtual NctiGeometryResult make_faces_by_edges(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_modelBody,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 设置模型的容差值 order 111
         * @param[in] i_pCustomContainer		文档类型
         * @param[in] i_modelBody		输入对象
         * @param[in] i_tolerance		容差值
         * @param[out] o_modelBody		输出对象
         */
        virtual NctiGeometryResult set_tolerance(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_modelBody,
            Ncti_Double i_tolerance,
            NCTI_MODEL_TAG& o_modelBody);
        /*
         * @brief 多模型布尔差集 order 112
         * @param i_pCustomContainer
         * @param i_FModelBodyVec 被减对象集合(集合内取并集）
         * @param i_SModelBodyVec 切割对象集合(集合内取并集）
         * @param o_ModelBody 被减对象剩余部分
         */
        virtual NctiGeometryResult multi_boolean_cut(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_FModelBodyVec,
            const std::vector<NCTI_MODEL_TAG>& i_SModelBodyVec,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 多模型布尔交集 order 113
         * @param i_pCustomContainer
         * @param i_FModelBodyVec 交集对象集合1(集合内取并集）
         * @param i_SModelBodyVec 交集对象集合2(集合内取并集）
         * @param o_ModelBody 输出对象
         * @param
         */
        virtual NctiGeometryResult multi_boolean_common(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_FModelBodyVec,
            const std::vector<NCTI_MODEL_TAG>& i_SModelBodyVec,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 多模型布尔并集 order 114
         * @param i_pCustomContainer
         * @param i_ModelBodyVec 并集对象集合
         * @param o_ModelBody  并集对象
         */
        virtual NctiGeometryResult multi_boolean_unit(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 多模型求交线	order 115
         * @param i_pCustomContainer 文档类型
         * @param i_ModelBodyVec 求交对象集合
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_multi_intersect_curve(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
        * @brief 创建空模型	order 116
        * @param i_pCustomContainer 文档类型
        * @param i_ShapeType shape类型，0:compound
                                        1:compsolid
                                        2:solid
                                        3:shell
                                        4:face
                                        5:wire
                                        6:edge
                                        7:vertex
                                        8:shape
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult create_empty_shape(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_ShapeType,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 通用布尔并集 order 117
         * @param i_pCustomContainer
         * @param i_ModelBodyVec 并集对象集合
         * @param o_ModelBody  并集对象
         */
        virtual NctiGeometryResult general_boolean_unit(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 将一个shape的所有子shape的方向倒转 order 118
         * @param i_pCustomContainer
         * @param i_ModelBody: 被倒转对象
         * @param o_ModelBody: 倒转后的对象
         */
        virtual NctiGeometryResult invert(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_ModelBody,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 基础表面转化旋转表面 order 119
         * @param i_pCustomContainer
         * @param i_TargeBody 输入的模型
         * @param o_ModelBody 输出的模型
         */
        virtual NctiGeometryResult to_revolution(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 删除模型内部边界 order 120
         * @param i_pCustomContainer
         * @param i_RemoveIntItemVec 输入的模型
         * @param o_ModelBody 输出的模型
         */
        virtual NctiGeometryResult remove_internal_boundaries(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::vector<Ncti_RemoveInt_Item>& i_RemoveIntItemVec,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 通过样条曲线和轮廓演化出新的实体 order 121
         * @param i_pCustomContainer
         * @param i_SplineModelBody 样条曲线对象
         * @param i_ProfileModelBody 轮廓对象
         * @param i_CloseSolid 是否创建闭合的实体
         * @param i_UseAlternativeAlgorithm 是否使用交替算法
         * @param i_HasToComputeAxes 是否自动计算参考坐标系
         * @param o_ModelBody 演化后的实体
         */
        virtual NctiGeometryResult evolved_operate(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SplineModelBody,
            NCTI_MODEL_TAG i_ProfileModelBody,
            Ncti_Boolean i_CloseSolid,
            Ncti_Boolean i_UseAlternativeAlgorithm,
            Ncti_Boolean i_HasToComputeAxes,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 转化间接曲面 order 122
         * @param i_pCustomContainer
         * @param i_TargeBody 输入的模型
         * @param o_ModelBody 输出的模型
         */
        virtual NctiGeometryResult direct_faces(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody, 
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 分割周期曲面 order 123
         * @detail 将给定形状中的旋转体、圆柱形、环形、圆锥形、球形曲面分割
         *         以便每个结果段覆盖不超过定义的角度数。
         * @param i_pCustomContainer
         * @param i_TargeBody 输入的模型
         * @param i_angle 最大分割角度
         * @param i_tol 容差
         * @param o_ModelBody 输出的模型
         */
        virtual NctiGeometryResult split_angle(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_angle,
            Ncti_Double i_tol,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 分割闭合曲面 order 124
         * @param i_pCustomContainer
         * @param i_TargeBody 输入的模型
         * @param i_nbPoints 分割点数
         * @param i_closeTol 闭合容差
         * @param i_maxTol 最大容差
         * @param o_ModelBody 输出的模型
         */
        virtual NctiGeometryResult split_closed(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Integer i_nbPoints,
            Ncti_Double i_closeTol,
            Ncti_Double i_maxTol,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 修复小实体 order 125
         * @param i_pCustomContainer
         * @param i_TargeBody 输入的模型
         * @param i_volume 体积容差
         * @param i_width 宽度容差
         * @param i_merge true:合并,false:移除
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult fix_small_solids(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_volume,
            Ncti_Double i_width,
            Ncti_Boolean i_merge,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 移除小曲面 order 126
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @param i_tol: 小于此数值的face将被移除
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult fix_small_faces(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_tol,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
        * @brief 修复小边线 order 127
        * @param i_pCustomContainer
        * @param i_TargeBody: 输入的模型
        * @param i_tolerance: 小边线修复容差
        * @param i_limitAngle: 小边线修复最大修边角度
        * @param o_ModelBody: 输出的模型
        */
        virtual NctiGeometryResult fix_small_edges(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_tolerance,
            Ncti_Double i_limitAngle,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 修复间隙 order 128
         * @detail 用wires修复edges之间的间隙，使用曲面修复算法修复Faces之间的间隙
         * @note 操作fix_small_faces / fix_small_edges 之后，需要fix_gaps
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @param i_precision: 修复精度
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult fix_gaps(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_precision,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief  使不同方式的表达一致 order 129
         * @detail 确保每个边的各种表示对于相同的参数给出相同的3D点
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @param i_tol: 容差。负数表示不设置统一容差，使用每一条edge自身的容差
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult same_parameter(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_tol, Ncti_Boolean i_force,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief  将曲面、曲线转换为具有指定阶数和指定段数的 BSpline 曲面。 order 130
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @param i_tol3d: 3d容差
         * @param i_tol2d: 2d容差
         * @param i_continue3d: 3d连续性
         * @param i_continue2d: 2d连续性
         * @param i_degree: 指定阶数
         * @param i_segment: 最小段数
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult to_bspline(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            Ncti_Double i_tol3d, Ncti_Double i_tol2d,
            Ncti_Geo_Continue_Type i_continue3d,
            Ncti_Geo_Continue_Type i_continue2d,
            Ncti_Integer i_degree, Ncti_Integer i_segment,
            NCTI_MODEL_TAG& o_pTarget);

        /*
         * @brief  修复给定对象所有子几何 order 131
         * @detail 修复face/edge/solid
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @param i_config: 配置
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult fix_shape(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Geo_Fixshape i_config,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief  将曲面、曲线转换为贝塞尔曲线曲面。 order 132
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @param i_3d: 是否转化3d
         * @param i_2d: 是否转化2d
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult to_bezier(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            Ncti_Boolean i_3d, Ncti_Boolean i_2d,
            NCTI_MODEL_TAG& o_pTarget);

        /*
         * @brief  修复给定对象所有容差 order 133
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult fix_tolerance(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief  偏移（Wires or Face） order 134
         * @param i_pCustomContainer
         * @param i_SrcBody: 输入的模型
         * @param i_NbOffset: 偏移次数
         * @param i_StepOffsetVal: 单位偏移量
         * @param i_Approx: 设置近似标志，将输入轮廓转换为仅由二维圆弧和二维线段组成的轮廓
         * @param i_ConnectType: Wire之间的连接类型，Arc或相交
         * @param i_Altitude: 偏移高度
         * @param o_ModelTagVec: 输出的模型
         */
        virtual NctiGeometryResult make_offset(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SrcBody,
            Ncti_Integer i_NbOffset,
            Ncti_Double i_StepOffsetVal,
            Ncti_Boolean i_Approx,
            Ncti_Integer i_ConnectType,
            Ncti_Double i_Altitude,
            std::vector<NCTI_MODEL_TAG>& o_ModelTagVec);

        /*
         * @brief  修复连续性 order 135
         * @detail 尝试修复C1连续性，无法修复物体的被分割开为多个C1连续的物体
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入的模型
         * @paran i_tolorance：容差
         * @param o_ModelBody: 输出的模型
         */
        virtual NctiGeometryResult fix_continuity(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_tolorance,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
        * @brief 创建Box order 136
        * @param i_pCustomContainer
        * @param i_Axis     坐标系
        * @param i_len:     长
        * @param i_width:   宽
        * @param i_height:  高
        * @param o_ModelBody: Box对象
        */
        virtual NctiGeometryResult create_box(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_len,
            Ncti_Double i_width,
            Ncti_Double i_height,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
        * @brief 计算两实体最小距离 order 137
        * @param i_pCustomContainer
        * @param i_BodiesTagVec		实体，数量为2
        * @param i_deflection:		偏差
        * @param i_multiThread:		是否多线程
        * @param o_dist:			输出距离
        */
        virtual NctiGeometryResult mini_distance(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_BodiesTagVec,
            Ncti_Double i_deflection,
            Ncti_Boolean i_multiThread,
            Ncti_Double& o_dist);

        /*
         * @brief 清理几何或三角剖分 order 138
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入对象
         * @param i_geom: 删除几何。否则删除三角剖分
         * @param i_force:强制删除所有不相关的表达
         * @param o_ModelBody: 输出对象
         */
        virtual NctiGeometryResult tclean(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Boolean i_geom,
            Ncti_Boolean i_force,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 生成等参数线 139
         * @param i_pCustomContainer
         * @param i_TargeBody: 输入对象
         * @param i_nvnum: 等参数线数量
         * @param o_ModelBody: 输出等参线
         */
        virtual NctiGeometryResult isos(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Integer i_nvnum,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 查找对象内所有edge 140
         * @param i_pCustomContainer
         * @param i_TargeBody: 目标
         * @param o_ModelEdgeVec: 输出
         */
        virtual NctiGeometryResult find_all_edge(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            std::vector<NCTI_MODEL_TAG>& o_ModelEdgeVec);
        /*
         * @brief 查找对象内所有face 141
         * @param i_pCustomContainer
         * @param i_TargeBody: 目标
         * @param o_ModelEdgeVec: 输出
         */
        virtual NctiGeometryResult find_all_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            std::vector<NCTI_MODEL_TAG>& o_ModelFaceVec);
        /*
         * @brief 计算极值 142
         * @param i_pCustomContainer
         * @param i_BodiesTagVec: 输入2个对象
         * @param o_ExtremaOutput: 输出极值
         */
        virtual NctiGeometryResult cal_extrema(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_BodiesTagVec,
            Ncti_Geo_Extrema& o_ExtremaOutput);
        /*
         * @brief 2D倒角和圆角 143
         * @param i_pCustomContainer
         * @param i_source: 倒角和圆角对象
         * @param i_mode:   0 圆角模式
         *                  1 两长度倒角
         *                  2 长度角度倒角
         * @param i_eid: 倒角对象两条边id
         * @param i_len: mode0 [圆角半径]
         *               mode1 [第一倒角长度,第二倒角长度]
         *               mode2 [倒角长度,倒角角度]
         * @param o_ModelBody: 输出对象
         */
        virtual NctiGeometryResult chfi2d(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_source, Ncti_Integer i_mode,
            const std::vector<NCTI_MODEL_TAG>& i_eid,
            const std::vector <Ncti_Double> i_len,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
        * @brief 抽壳 order 144
        * @param i_pCustomContainer
        * @param i_TargeBody: 输入对象
        * @param dOffset: 偏移距离
        * @param joinType: 连接类型 1圆弧 2相交 3相切
        * @param dTol: 容差
        * @param o_ModelBody: 输出对象
        */
        virtual NctiGeometryResult thick_shell(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double dOffset,
            Ncti_Integer joinType,
            Ncti_Double dTol,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
         * @brief 缩放	order 145. order18的重载
         * @param i_pCustomContainer
         * @param OringePt 缩放基准点
         * @param i_scale 缩放比例
         * @param io_SModelBody 缩放对象
         */
        virtual NctiGeometryResult scale_object(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiPosition& OringePt,
            const NctiVector& i_scale,
            NCTI_MODEL_TAG& io_SModelBody);
        /*
         * @brief 查找对象内所有vertex 146
         * @param i_pCustomContainer
         * @param i_TargeBody: 目标
         * @param o_ModelVertexVec: 输出
         */
        virtual NctiGeometryResult find_all_vertex(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            std::vector<NCTI_MODEL_TAG>& o_ModelVertexVec);

        /*
         * @brief 点投影到线或面中 order 147
         * @param[in] i_pContainer		文档类型
         * @param[in] i_modelBody		输入对象，线或者面
         * @param[in] i_point			投影的点
         * @param[in] i_algo				极值算法
         *		0--"Extrema_ExtAlgo_Grad" 梯度下降
         *		1--"Extrema_ExtAlgo_Tree" 搜索树
         * @param[out] o_projectPointVec    输出的投影点
         */
        virtual NctiGeometryResult get_project_point(
            NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_modelBody,
            const NctiPosition& i_point,
            Ncti_Long i_algo,
            std::vector<Ncti_Geo_Project_Point>& o_projectPointVec);

        /*
        * @brief 抽中间路径 order 148
        * @param i_pCustomContainer
        * @param i_TargeBody:路径经过对象
        * @param i_start: 路径起始对象
        * @param i_end: 路径终止对象
        * @param dTol: 容差
        * @param o_ModelBody: 输出对象
        */
        virtual NctiGeometryResult middle_path(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG i_start,
            NCTI_MODEL_TAG i_end,
            NCTI_MODEL_TAG& o_ModelBody);

        /*@brief 抽取对象的face组成solid	order 149
         * @param i_pCustomContainer	文档类型
         * @param i_pSourceBody		输入的实体对象
         * @param i_pSourceFace	    face 列表
         * @param i_pTarget         输出solid对象
         */
        virtual NctiGeometryResult extract_solid(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            const std::vector<NCTI_MODEL_TAG>& i_pSourceCell,
            NCTI_MODEL_TAG& o_pTarget);

        /*@brief 抽取对象的edge组成wire	order 150
         * @param i_pCustomContainer	文档类型
         * @param i_pSourceBody		输入的实体对象
         * @param i_pSourceFace	    edge 列表
         * @param i_pTarget         输出wire对象
         */
        virtual NctiGeometryResult extract_wire(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            const std::vector<NCTI_MODEL_TAG>& i_pSourceCell,
            NCTI_MODEL_TAG& o_pTarget);
        /*
        * @brief 提取一个面的外轮廓 order 151
        * @param i_pCustomContainer
        * @param i_TargeBody: 输入对象
        * @param o_ModelBody: 输出对象
        */
        virtual NctiGeometryResult extract_outwire(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG& o_ModelBody);

        /*@brief 两个不平行的曲线之间创建一个圆滑的过渡或一个尖锐的过渡	order 152
         * @param i_pCustomContainer	文档类型
         * @param i_pSourceBodyVec		输入的实体对象数组(一个线或两个边)
         * @param i_mode:   0 圆滑的过渡
         *                  1 尖锐的过渡
         * @param i_radiusOrLenVec	    半径或两个边上的距离
         * @param o_modelBodyVec        输出对象
         */
        virtual NctiGeometryResult fillet2d(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_pSourceBodyVec,
            Ncti_Integer i_mode,
            const std::vector<Ncti_Double> i_radiusOrLenVec,
            std::vector<NCTI_MODEL_TAG>& o_modelBodyVec);

        /* @brief 按数量分割曲面	order 153
         * @detail 尽量按照方形分割曲面，模式一指定分割数，模式二分别指定uv方向分割数
         * @param i_face		输入face对象
         * @param i_num1	    分割数量。当i_num2>0时，表示u方向分割数量
         * @param i_num2        v方向分割数量。<=0表示仅按i_num1分割
         * @param o_shell       输出shell对象
         */
        virtual NctiGeometryResult split_number(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_face, 
            Ncti_Integer i_num1, 
            Ncti_Integer i_num2,
            NCTI_MODEL_TAG& o_shell);

        /*
        * @brief 设置bspline曲线或者面控制点权重 order 154
        * @param i_pCustomContainer	文档类型
        * @param i_uindex			u序号，从0开始
        * @param i_vIndex			v序号，从0开始（面有效）
        * @param i_weight           权重值
        * @param io_modelBody       输入输出对象
        */
        virtual NctiGeometryResult set_bezier_bspline_weight(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_uindex,
            Ncti_Integer i_vindex,
            Ncti_Double i_weight,
            NCTI_MODEL_TAG& io_modelBody);

        /*
       * @brief 修复面、线、边(平面、圆柱面、圆锥面、球面、直线、圆、椭圆) order 155
       * @param i_pCustomContainer	文档类型
       * @param i_pSourceBody	    传入的要修复的实体对象(面、线、边),除了球、圆、椭圆其他的实体修复后是无限大的
       * @param i_nMode			    修复对象的类型(可选,默认0) 0:pln 1:cyl 2:con 3:sph 4:lin 5:cir 6:ell
       * @param i_dTol              容差(可选,默认1.e-7)
       * @param i_pSampleBody       样例模型(可选,样例模型类型需要与i_nMode保持一致,4:lin 5:cir 6:ell不需要样例模型)
       * @param o_modelBody         输出面或边对象
       */
        virtual NctiGeometryResult repairShape(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            Ncti_Integer i_nMode,
            Ncti_Double i_dTol,
            NCTI_MODEL_TAG i_pSampleBody,
            NCTI_MODEL_TAG& o_modelBody);

        /*
        * @brief 创建拟合的b样条曲面 order 156
        * @param i_pCustomContainer	文档类型
        * @param i_pSourceSurf	    传入的要拟合的曲面实体
        * @param i_u_from			U方向的参数空间起始值
        * @param i_u_to			U方向的参数空间终止值
        * @param i_v_from			V方向的参数空间起始值
        * @param i_v_to             V方向的参数空间终止值
        * @param i_dTol              容差(可选,默认1.e-7)
        * @param i_dAngleTol              角度容差(可选,默认0.0)
        * @param i_u_interpolated_params              U方向的插值参数数组
        * @param i_v_interpolated_params              V方向的插值参数数组
        * @param o_modelBody         输出面对象
        */
        virtual NctiGeometryResult bsurf_create_fitted(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceSurf,
            Ncti_Double i_u_from,
            Ncti_Double i_u_to,
            Ncti_Double i_v_from,
            Ncti_Double i_v_to,
            Ncti_Double i_dTol,
            Ncti_Double i_dAngleTol,
            const std::vector<Ncti_Double>& i_u_interpolated_params,
            const std::vector<Ncti_Double>& i_v_interpolated_params,
            NCTI_MODEL_TAG& o_modelBody);
    
        /*
        * @brief 按分段方式创建b样条曲面 order 157
        * @param i_pCustomContainer	文档类型
        * @param i_u_degree			U方向的度数(阶次-1）
        * @param i_u_segments			U方向的分段
        * @param i_v_degree			U方向的度数(阶次-1）
        * @param i_v_segments             V方向的分段
        * @param i_is_rational       是否有理样条(TRUE)
        * @param i_rep              表示方法，0- Bezier；1-多边形；2-hermite;3-泰勒
        * @param i_coeffs              系数向量
        * @param o_modelBody         输出面对象
        */
        virtual NctiGeometryResult bsurf_create_piecewise(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_u_degree,
            Ncti_Integer i_u_segments,
            Ncti_Integer i_v_degree,
            Ncti_Integer i_v_segments,
            Ncti_Boolean i_is_rational,
            Ncti_Integer i_rep,
            const std::vector<Ncti_Double>& i_coeffs,
            NCTI_MODEL_TAG& o_modelBody); 

        /*
        * @brief 按样条标准式创建b样条曲面 order 158
        * @param i_pCustomContainer	文档类型
        * @param i_u_degree			U方向的度数
        * @param i_u_positions			U方向的控制点数目
        * @param i_v_degree			V方向的度数
        * @param i_v_positions             V方向的控制点数目
        * @param i_positions              控制点数组，U方向优先排列
        * @param i_u_end              U方向的低端点条件
        * @param i_u_drivs              U方向的低端点导数
        * @param i_U_end              U方向的高端点条件
        * @param i_U_drivs              U方向的高端点导数
        * @param i_v_end              V方向的低v端点条件
        * @param i_v_drivs              V方向的低端点导数
        * @param i_V_end              V高方向的高端点条件
        * @param i_V_drivs              V方向的高端点导数
        * @param i_u_knot_auto              U方向的节点是否自动定义
        * @param i_v_knot_auto              V方向的节点是否自动定义
        * @param i_u_knots              U方向的节点
        * @param i_v_knots              V方向的节点
        * @param i_how_twist              U、V方向的扭转设置（分别是：U低/V低、U低/V高、U高/V低、U高/V高）
        * @param i_twist              U、V方向的扭转向量
        * @param o_modelBody         输出面或边对象
        */
        virtual NctiGeometryResult bsurf_create_splinewise(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_u_degree,
            Ncti_Integer i_u_positions,
            Ncti_Integer i_v_degree,
            Ncti_Integer i_v_positions,
            const std::vector<NctiPosition>& i_positions,
            Ncti_Boolean i_u_knot_auto,
            Ncti_Boolean i_v_knot_auto,
            const std::vector<Ncti_Double>& i_u_knots,
            const std::vector<Ncti_Double>& i_v_knots,
            const Ncti_Boolean i_how_twist[4],
            const NctiPosition i_twist[4],
            NCTI_MODEL_TAG& o_modelBody);

        /*
        * @brief 夹住节点使之具有bezier端点条件 order 159
        * @param i_pCustomContainer	文档类型
        * @param io_modelBody         传入/输出面或边对象
        */      
        virtual NctiGeometryResult bsurf_clamp_knots(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_modelBody);

        /*
        * @brief 设定U/V方向参数空间的比例，生成裁剪的曲面实体    order 160
        * @param i_pCustomContainer	文档类型
        * @param i_pSourceSurf	    传入的要拟合的曲面实体
        * @param i_u            U方向的低端参数比例
        * @param i_U              U方向的高端参数比例
        * @param i_v            V方向的低端参数比例
        * @param i_V              V方向的高端参数比例
        * @param io_modelBody         传入/输出面或边对象
        */
        virtual NctiGeometryResult create_trimmed_surf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceSurf,
            Ncti_Double i_u,
            Ncti_Double i_U,
            Ncti_Double i_v,
            Ncti_Double i_V,
            NCTI_MODEL_TAG& io_modelBody);

        /*
        * @brief 射线获取实体的子实体 order 161
        * @param i_pCustomContainer	文档类型
        * @param i_pSourceSurf	    传入的要拟合的曲面实体
        * @param i_ray            射线向量
        * @param i_pickType              拾取的对象类型（0-面，1-边，2-点）
        * @param i_dMaxDist            拾取边或点的时候，的最大辐射距离
        * @param i_pickMethod              拾取的方法
        * @param i_ratio              拾取距离（轴向和辐射）的计算比例
        * @param i_approximateCurve              V方向的高端参数比例
        * @param io_modelBody         传入/输出面或边对象
        */
        virtual NctiGeometryResult body_pick_topols(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_pSourceSurf,
            const NctiVector& i_ray,
            Ncti_Integer i_pickType,
            Ncti_Double i_dMaxDist,
            Ncti_Integer i_pickMethod,
            Ncti_Double i_ratio,
            Ncti_Boolean i_approximateCurve,
            NCTI_MODEL_TAG& io_modelBody);

        /*
        * @brief 创建用于测试的空对象	order 162
        * @param i_pCustomContainer 文档类型
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult create_null_shape(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
        * @brief 移除特征	order 163
        * @param i_pCustomContainer 文档类型
        * @param i_SourceBody 输入对象
        * @param i_Faces 输入子对象面
        * @param i_TargetBody 输出对象
        */
        virtual NctiGeometryResult remove_features(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            std::vector<NCTI_MODEL_TAG> i_Faces,
            NCTI_MODEL_TAG& i_TargetBody
        );

        /* 变换子对象面，并生成实体对象
        * @param i_pCustomContainer 文档类型
        * @param i_SourceBody 输入对象
        * @param[in] i_pFace    - 输入子对象面，或者几何对象      165
        * @param i_matrix       输入变换矩阵
        * @param i_flag       0 - 使用topol体，1-使用几何体
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult transform_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pFace, 
            const Ncti_Double i_matrix[4][4],
            Ncti_Boolean i_flag,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
        创建transf并查询，检查          166
        * @param i_pCustomContainer 文档类型
        * @param i_HasRotation 布尔值，是否旋转
        * @param i_axis         旋转轴
        * @param i_angle    旋转角度
        * @param i_scale    缩放比例
        * @param i_HasMirror     布尔值，是否镜像
        * @param i_planePos 镜像平面的位置点
        * @param i_PlaneNormal 镜像平面的法向
        * @param o_matrix 输出的变换矩阵
        */
        virtual NctiGeometryResult create_and_check_transf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Boolean i_HasRotation,
            const NctiVector& i_axis,
            Ncti_Double i_angle,
            Ncti_Double i_scale,
            Ncti_Boolean i_HasMirror,
            const NctiPosition& i_planePos,
            const NctiVector& i_PlaneNormal,
            Ncti_Double o_matrix[4][4]);
        /*
        * 变换矩阵应用于向量               167
        * @param i_pCustomContainer 文档类型
        * @param i_vec 输入的向量
        * @param i_matrix 输入的变换矩阵
        * @param o_vec 输出的向量
        */
        virtual NctiGeometryResult transform_direction(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiVector& i_vec,
            const Ncti_Double i_matrix[4][4],
            NctiVector& o_vec);
        /*
        * 判断两个变换矩阵是否相同      168
        * @param i_pCustomContainer 文档类型
        * @param i_matrix 输入的变换矩阵
        * @param i_matrix2 输入的变换矩阵2
        * @param o_equal 输出的布尔值，表示是否相等
        */
        virtual NctiGeometryResult transform_equal(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Double i_matrix[4][4],
            const Ncti_Double i_matrix2[4][4],
            Ncti_Boolean& o_equal);
        /*
        * 检查assembly, edge, face            169
        * @param i_pCustomContainer 文档类型
        * @param i_SourceBody 输入对象
        * @param[in] i_pFace    - 输入子对象面，或者几何对象      
        * @param o_valid 输出的布尔值，表示是否合法
        */
        virtual NctiGeometryResult check_entity(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pFace,
            Ncti_Boolean& o_valid);
        /*
        * 按照指定的面（子实体），创建公共边（曲线）       170
        * @param i_pCustomContainer 文档类型
        * @param i_SourceBody 输入对象
        * @param[in] i_pFace    - 输入面对象          
        * @param[in] i_pFace2    - 输入面对象2
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult create_curve_by_common_edge(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pFace,
            NCTI_MODEL_TAG i_pFace2,
            NCTI_MODEL_TAG& o_ModelBody);
        /*
        * 按照指定的顶点，创建与之相关的body（实体）       171
        * @param i_pCustomContainer 文档类型
        * @param i_SourceBody 输入对象
        * @param[in] i_pVert    - 输入顶点对象
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult create_body_by_vert(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pVert,
            NCTI_MODEL_TAG& o_ModelBody);        

        /*
       * @brief 创建装配体	order 172
       * @param i_pCustomContainer 文档类型
       * @param i_assembly_template 输入的装配体对象，如果为空，创建一个空的装配体
       * @param o_pAssemble 输出的装配体对象
       */
        virtual NctiGeometryResult create_assemble(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_assembly_template,
            NCTI_MODEL_TAG& o_pAssemble);

        /*
        * @brief 添加对象到装配体	order 173
        * @param i_pCustomContainer 文档类型
        * @param i_pAssemble 输入的装配体对象
        * @param i_vtDirectChildren 加入到装配体的子对象
        */
        virtual NctiGeometryResult assemble_objects(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pAssemble,
            const std::vector<NCTI_MODEL_TAG>& i_vtDirectChildren);

        /*
        * @brief 从装配体中移除对象	order 174
        * @param i_pCustomContainer 文档类型
        * @param i_pAssemble 输入的装配体对象
        * @param i_vtObjectsToRemove 从装配体中移除的子对象
        */
        virtual NctiGeometryResult remove_objects_from_assemble(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pAssemble,
            const std::vector<NCTI_MODEL_TAG>& i_vtObjectsToRemove);
        /*
       * @brief 导出装配体	order 175
       * @param i_pCustomContainer 文档类型
       * @param i_pAssemble 输入的装配体对象
       * @param o_pExportBody 输出的导出对象
       */
        virtual NctiGeometryResult export_assemble(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pAssemble,
            NCTI_MODEL_TAG& o_pExportBody);
        /*
        * 按照view的方向，生成轮廓线实体 176
        * @param i_pCustomContainer 文档类型
        * @param i_SourceBody 输入对象
        * @param i_pos      view的起始位置
        * @param i_direction    view的方向
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult create_view_outline(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            const NctiPosition& i_pos,
            const NctiVector& i_direction,
            NCTI_MODEL_TAG& o_ModelBody);        
        /*
        * 按照edge获取shell的个数          order-177
        * @param i_pContainer 文档类型
        * @param i_pSourceEdge 输入对象
        * @param o_num      输出个数
        */
        virtual NctiGeometryResult ask_shell_by_edge(
            NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_pSourceEdge,
            Ncti_Integer& o_num);
        /*
        * @brief 计算曲线对象的包围盒	order 178
        * @param i_pContainer 文档类型
        * @param i_pSouceBody       输入的目标实体
        * @param i_pSouceCurve      输入的子对象曲线
        * @param o_box      - 输出结果
        */
        virtual NctiGeometryResult find_curve_box(
            NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_pSouceBody,
            NCTI_MODEL_TAG i_pSouceCurve,
            Ncti_Double o_box[6]);

        /*
        * 简化几何实体或子对象面         order 179
        * @param i_pContainer 文档类型
        * @param io_modelBody       输入/输出的实体
        */
        virtual NctiGeometryResult simplify_object(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG& io_modelBody);
        /*
        * 求两个面实体的相交，返回结果            order 180
        * @param i_pContainer 文档类型
        * @param i_pTargets       输入的拓扑对象
        * @param i_pFaceBody       输入的实体
        * @param i_pFaceBody2       输入的实体2
        * @param i_flag       标记，采用face求交，还是surf求交
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult find_inter_btw_face(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_pTarget, 
            NCTI_MODEL_TAG i_pFaceBody,
            NCTI_MODEL_TAG i_pFaceBody2,
            Ncti_Boolean i_flag,
            NCTI_MODEL_TAG& o_modelBody);
        /*
        * 偏移曲面并生成offset对象           order 181
        * @param i_pContainer 文档类型
        * @param i_pSurfBody       输入的曲面实体
        * @param i_offset       输入的偏移距离
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult offset_surf(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_pSurfBody,
            Ncti_Double i_offset,
            NCTI_MODEL_TAG& io_modelBody);        
        /*
        * 检查拓扑对象的碰撞         order 182
        * @param i_pContainer 文档类型
        * @param i_pTargets       输入的拓扑对象
        * @param i_pTools       输入的拓扑对象2
        * @param clash_type       输出的碰撞类型
        * @param clash_pairs       输出的碰撞对
        */
        virtual NctiGeometryResult topol_clash(NctiDisplayDocCustomContainer* i_pContainer,
            const std::vector<NCTI_MODEL_TAG>& i_pTargets,
            const std::vector<NCTI_MODEL_TAG>& i_pTools,
            std::vector<unsigned int>& clash_type,
            std::vector<std::pair<unsigned int, unsigned int>>& clash_pairs);
        /*
        * 使用sheet实体生成剖切面，并返回            order 183
        * @param i_pContainer 文档类型
        * @param i_pTarget       输入的实体
        * @param i_sheetBody       输入的面实体
        * @param io_modelBody    -输出对象
        */
        virtual NctiGeometryResult create_section_with_sheet(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_pTarget,
            NCTI_MODEL_TAG i_sheetBody,
            NCTI_MODEL_TAG& io_modelBody);
        /*
         * @brief 寻找点的最近几何体（面、边、点）      order 184
         * @param i_pCustomContainer 文档类型
         * @param i_TargeBody 目标对象
         * @param i_PointVec 点
         * @param o_ModelGeomVec 输出最近几何体（面、边、点）
         */
        virtual NctiGeometryResult find_nearest_geom_by_point(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            const std::vector<NctiPosition>& i_PointVec,
            std::vector<NCTI_MODEL_TAG>& o_ModelGeomVec);

        /*
         * @brief 查询实体的属性集      order 185
         * @param i_pCustomContainer 文档类型
         * @param i_TargeBody 目标对象
         * @param i_entity 子实体
         * @param o_attibs   输出有名属性集
         */
        virtual NctiGeometryResult ask_attrib(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody, NCTI_MODEL_TAG i_entity, Ncti_Attrib_Type i_type, std::map<std::string, std::vector<std::string>>& o_attibs);
        /*
         * @brief 设置实体的属性集      order 186
         * @param i_pCustomContainer 文档类型
         * @param i_TargeBody 目标对象
         * @param i_entity 子实体
         * @param i_attribName 属性域名称
         * @param i_value 属性值
         * @param i_type   属性类型
         */
        virtual NctiGeometryResult set_attrib(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody, NCTI_MODEL_TAG i_entity, const Ncti_WChar* i_attribName,
            const std::vector<std::string>& i_value, Ncti_Attrib_Type i_type);

        /*
         * @brief 创建正多边形面片      order 187
         * @param i_pCustomContainer 文档类型
         * @param i_Axis 输入坐标系
         * @param i_sides 多边形边数
         * @param i_radius 圆半径
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_sheet_polygon(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Integer i_sides,
            Ncti_Double i_radius,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
        * @brief 创建矩形面片      order 188
        * @param i_pCustomContainer 文档类型
        * @param i_Axis 输入坐标系
        * @param i_length 矩形长度
        * @param i_width 矩形宽度
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult create_sheet_rectangle(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_length,
            Ncti_Double i_width,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
        * @brief 创建圆锥实体      order 189
        * @param i_pCustomContainer 文档类型
        * @param i_Axis 输入坐标系
        * @param i_radius 圆锥底面半径
        * @param i_height 圆锥高度
        * @param i_semi_angle 圆锥斜度
        * @param o_ModelBody 输出对象
        */
        virtual NctiGeometryResult create_solid_cone(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_radius,
            Ncti_Double i_height,
            Ncti_Double i_semi_angle,
            NCTI_MODEL_TAG& o_ModelBody);

       /*
       * @brief 创建圆柱实体      order 190
       * @param i_pCustomContainer 文档类型
       * @param i_Axis 输入坐标系
       * @param i_radius 圆柱底面半径
       * @param i_height 圆柱高度
       * @param o_ModelBody 输出对象
       */
        virtual NctiGeometryResult create_solid_cylinder(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_Radius,
            Ncti_Double i_Height,
            NCTI_MODEL_TAG& o_ModelBody);

         /*
         * @brief 创建正多边实体      order 191
         * @param i_pCustomContainer 文档类型
         * @param i_Axis 输入坐标系
         * @param i_sides 多边实体的边数
         * @param i_radius 圆半径
         * @param i_height 圆柱高度
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_solid_prism(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Integer i_sides,
            Ncti_Double i_radius,
            Ncti_Double i_height,
            NCTI_MODEL_TAG& o_ModelBody);

         /*
         * @brief 创建球实体      order 192
         * @param i_pCustomContainer 文档类型
         * @param i_Axis 输入坐标系
         * @param i_radius 球半径
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_solid_sphere(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_radius,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 复制拓补      order 193
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入对象
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_copy_topology(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 删除面片的内部loop      order 194
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入对象
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult delete_interior_loop(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 反向面片方向      order 195
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入对象
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult reverse_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 附加坐标值      order 196
         * @param i_pCustomContainer 文档类型
         * @param i_vtPosition 输入坐标值数组
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult attach_points(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NctiPosition>& i_vtPosition,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 提取面片中的任一点      order 197
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入对象
         * @param o_ModelBody 输出点对象
         */
        virtual NctiGeometryResult find_face_interior_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NctiPosition& o_point);

        /*
         * @brief 提取面片中最外面的轮廓      order 198
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入对象
         * @param o_outerWire 输出最外面轮廓
         */
        virtual NctiGeometryResult find_face_outer_loop(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG& o_outerWire);
		/*
		 * @brief 提取spcurve曲线      order 199
		 * @param i_pCustomContainer 文档类型
		 * @param i_pSourceBody 输入对象
		 * @param i_pSourceCell edge
		 * @param o_pCurve 输出spcurve曲线
		 */
		virtual NctiGeometryResult spcurve_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG i_pSourceCell,
			NCTI_MODEL_TAG& o_pCurve);

		/*
		 * @brief 扫掠曲面      order 200
		 * @param i_pCustomContainer 文档类型
		 * @param i_pCurveBody 截面曲线
		 * @param i_Dir 扫掠方向
		 * @param o_pBody 输出扫掠面
		 */
		virtual NctiGeometryResult swept_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pCurveBody,
			const NctiVector& i_Dir,
			NCTI_MODEL_TAG& o_pBody);

		/*
		 * @brief 创建一个b样条曲线      order 201
		 * @param i_ControlPts 控制点集
		 * @param i_Degree 次数
		 * @param o_pCurve 输出b样条曲线
		 */
		virtual NctiGeometryResult bcurve_create_splinewise(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NctiPosition>& i_ControlPts,
			Ncti_Integer i_Degree,
			NCTI_MODEL_TAG& o_pCurve);

		/*
		 * @brief 夹住节点使之具有bezier端点条件    order 202
		 * @param i_pCustomContainer 文档类型
		 * @param io_pBody 传入/输出曲线
		 */
		virtual NctiGeometryResult bcurve_clamp_knots(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pCurveBody,
			NCTI_MODEL_TAG& o_pBody);

		/*
		 * @brief 夹住节点使之具有bezier端点条件    order 203
		 * @param i_pCustomContainer 文档类型
		 * @param i_pCurveBodyVec 曲线数组
		 * @param o_pCurve 输出曲线
		 */
		virtual NctiGeometryResult bcurve_join(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pCurveBodyVec,
			NCTI_MODEL_TAG& o_pCurve);

		/*
		 * @brief 对象拷贝    order 204
		 * @param i_pCustomContainer 文档类型
		 * @param i_pBody 输入对象
		 * @param o_pBody 输出对象
		 */
		virtual NctiGeometryResult geom_copy(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pBody,
			NCTI_MODEL_TAG& o_pBody);

		/*
		 * @brief 曲线首尾逆转    order 205
		 * @param i_pCustomContainer 文档类型
		 * @param i_pCurveBody 输入对象
		 * @param o_pCurve 输出对象
		 */
		virtual NctiGeometryResult curve_make_curve_reversed(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pCurveBody,
			NCTI_MODEL_TAG& o_pCurve);

		/*
		 * @brief 创建SPcurve  order 206
		 * @param i_pCustomContainer 文档类型
		 * @param i_pSurfaceBody 输入曲面
		 * @param i_pCurveBody 输入曲线
		 * @param o_pCurve 输出对象
		 */
		virtual NctiGeometryResult curve_make_spcurves_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSurfaceBody,
			NCTI_MODEL_TAG i_pCurveBody,
			NCTI_MODEL_TAG& o_pCurve);

		/*
		 * @brief edge生成曲线  order 207
		 * @param i_pCustomContainer 文档类型
		 * @param i_pSurfaceCellVec 输入edge数组
		 * @param o_pCurve 输出对象
		 */
		virtual NctiGeometryResult edge_make_curve(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pSurfaceCellVec,
			NCTI_MODEL_TAG& o_pCurve);

        /*
         * @brief 创建圆环实体      order 208
         * @param i_pCustomContainer 文档类型
         * @param i_Axis 输入坐标系
         * @param i_major_radius 圆环半径
         * @param i_minor_radius 圆环截面半径
         * @param o_ModelBody 输出对象
         */
        virtual NctiGeometryResult create_solid_torus(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiAxis& i_Axis,
            Ncti_Double i_major_radius,
            Ncti_Double i_minor_radius,
            NCTI_MODEL_TAG& o_ModelBody);

        /*
         * @brief 从general body中删除面片    order 209
         * @param i_pCustomContainer 文档类型
         * @param i_pSourceBody 输入对象
         * @param i_pFaceToDelete 待删除的面片
         * @param o_pResultBody 输出对象
         */
        virtual NctiGeometryResult delete_face_from_general_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pFaceToDelete,
            NCTI_MODEL_TAG& o_pResultBody);

        /*
         * @brief 对组件进行矩阵变换      order 210
         * @param i_pCustomContainer 文档类型
         * @param io_pSourceAsm 输入输出组件
         * @param i_mat 变换矩阵
         */
        virtual NctiGeometryResult transform_assemble(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_pSourceAsm,
            Ncti_Double i_mat[4][4]);

        /*
         * @brief 创建偏移面      order 211
         * @param i_pCustomContainer 文档类型
         * @param i_pSurfaceBody 输入面片
         * @param i_offset_distance 偏移距离
         * @param o_pResultBody 偏移后的对象
         */
        virtual NctiGeometryResult create_offset_surface(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSurfaceBody,
            Ncti_Double i_offset_distance,
            NCTI_MODEL_TAG& o_pResultBody);

        /*
         * @brief 创建等斜面      order 212
         * @param i_pCustomContainer 文档类型
         * @param i_pCurveBody 输入线体
         * @param i_direction 倾斜方向
         * @param i_angle 倾斜角度
         * @param i_side 选择方向           0: 选取左边;    1: 选取右边
         * @param o_pResultBody 偏移后的对象
         */
        virtual NctiGeometryResult make_isocline_surf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pCurveBody,
            const NctiVector& i_direction,
            Ncti_Double i_angle,
            Ncti_Integer i_side,
            NCTI_MODEL_TAG& o_pResultBody);

        /*
         * @brief 在指定位置打断边      order 213
         * @param i_pCustomContainer 文档类型
         * @param i_pWireBody 输入线体
         * @param i_pEdgeToRemove 输入被打断的边
         * @param i_position 打断位置           0 : 起点位置    1 : 终点位置
         * @param o_pResultBody 打断后的对象
         */
        virtual NctiGeometryResult remove_edge_by_vertex(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pWireBody,
            NCTI_MODEL_TAG i_pEdgeToRemove,
            Ncti_Integer i_position,
            NCTI_MODEL_TAG& o_pResultBody);

        /*
         * @brief 对Body中的点、线、面对象进行归类      order 214
         * @param i_pCustomContainer 文档类型
         * @param i_pBody 输入Body
         * @param i_method 归类方法     0 : 对vertex归类;   1 : 对edge归类;    2 : 对face归类;
         * @param o_pResultBody 偏移后的对象
         */
        virtual NctiGeometryResult body_entity_categorize(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            Ncti_Integer i_method);

        /*
         * @brief 获取当前会话中的所有partition对象的tag      order 215
         * @param i_pCustomContainer 文档类型
         * @param i_pBody 输入对象
         * @param o_vtPartitions 输出partition对象的tag数组
         */
        virtual NctiGeometryResult find_all_partitions(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            std::vector<Ncti_Integer>& o_vtPartitions);

        /*
         * @brief 改变BODY所在的partition      order 216
         * @param i_pCustomContainer 文档类型
         * @param io_pBody 输入输出对象
         * @param i_toPartition 目标partition     如果i_toPartition为0，将新建一个partition，并把i_pBody移动到该partition中
         */
        virtual NctiGeometryResult body_change_partition(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_pBody,
            Ncti_Integer i_toPartition);

        /*
         * @brief 获取装配体中的所有instances      order 217
         * @param i_pCustomContainer 文档类型
         * @param i_pAssembly 输入装配件对象
         * @param o_vtInstances 输出的Instance Tag数组
         */
        virtual NctiGeometryResult find_assembly_instances(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pAssembly,
            std::vector<Ncti_Integer>& o_vtInstances);

        /*
         * @brief 改变装配体中instance指向的对象       order 218
         * @param i_pCustomContainer 文档类型
         * @param io_pSrcAssembly 源装配体
         * @param i_srcInstanceTag 源Instance Tag
         * @param i_pNewPart 新的Part对象
         */
        virtual NctiGeometryResult instance_change_part(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_pSrcAssembly,
            Ncti_Integer i_srcInstanceTag,
            NCTI_MODEL_TAG i_pNewPart);

        /*
         * @brief 改变装配体中instance的变换矩阵      order 219
         * @param i_pCustomContainer 文档类型
         * @param i_instanceTag 输入Instance Tage
         * @param i_mat 变换矩阵
         * @param io_pAssembly 目标装配体对象
         */
        virtual NctiGeometryResult instance_replace_transf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_instanceTag,
            Ncti_Double i_mat[4][4],
            NCTI_MODEL_TAG& io_pAssembly);

        /*
         * @brief 对装配体中instance应用变换矩阵      order 220
         * @param i_pCustomContainer 文档类型
         * @param i_instanceTag 输入Instance Tage
         * @param i_mat 变换矩阵
         * @param io_pAssembly 目标装配体对象
         */
        virtual NctiGeometryResult instance_transform(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_instanceTag,
            Ncti_Double i_mat[4][4],
            NCTI_MODEL_TAG& io_pAssembly);

        /*
         * @brief 获取与指定vertex有关的所有shell对象      order 221
         * @param i_pCustomContainer 文档类型
         * @param i_pBody 输入对象
         * @param i_pVertexCell 输入Vertex对象
         * @param o_vtShells 输出shell对象的Tag数组
         */
        virtual NctiGeometryResult find_shells_by_vertex(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            NCTI_MODEL_TAG i_pVertexCell,
            std::vector<Ncti_Integer>& o_vtShells);

        /*
         * @brief 获取face中的所有loop对象      order 222
         * @param i_pCustomContainer 文档类型
         * @param i_pFaceBody 输入对象
         * @param o_vtLoops 输出loop对象的Tag数组，其中第一个为外部loop
         */
        virtual NctiGeometryResult find_face_loops(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pFaceBody,
            std::vector<Ncti_Integer>& o_vtLoops);

        /*
         * @brief 从sheet中删除指定的loop      order 223
         * @param i_pCustomContainer 文档类型
         * @param io_pFaceBody 输入输出对象
         * @param i_loop 输出待删除的loop Tag
         */
        virtual NctiGeometryResult delete_loop_from_sheet(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_pFaceBody,
            Ncti_Integer i_loop);

        /*
         * @brief B样条或贝塞尔曲线降阶	order 224
         * @param i_pCustomContainer		文档类型
         * @param i_degree			减少度数到该值，>=0
         * @param io_modelBody	输入输出对象
         */
        virtual NctiGeometryResult decrease_bezier_bspline_curve_degree(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_degree, NCTI_MODEL_TAG& io_modelBody);
        /*
        * @brief B样条或贝塞尔曲面降阶	order 225
        * @param i_pCustomContainer		文档类型
        * @param i_udegree			减少u向度数到该值，0且i_udegree有效，只减低u向阶数
        * @param i_vdegree			减少v向度数到该值，0且i_vdegree有效，只减低v向阶数
        * @param io_modelBody	输入输出对象
        */
        virtual NctiGeometryResult decrease_bezier_bspline_surf_degree(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_udegree, Ncti_Long i_vdegree,
            NCTI_MODEL_TAG& io_modelBody);

        /*
        * @brief 边的zip开口（欧拉操作）	order 226
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_edge			传入的边（子实体）
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_edge_zip(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 添加/删除环面的欧拉操作	order 227
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_face			传入的面（子实体）
        * @param i_left			左侧(true)或者右侧(false)
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_ring_face(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 添加/删除bi-wire环的欧拉操作	order 228
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_edge			传入的顶点（子实体）
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_ring_loop(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 添加/删除边和面的欧拉操作	order 229
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_edge			传入的边（子实体）
        * @param i_left			左侧(true)或者右侧(false)
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_edge_face(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 添加/删除边和环的欧拉操作	order 230
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_edge			传入的边（子实体）
        * @param i_left			左侧(true)或者右侧(false)
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_edge_loop(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);

        /*
        * @brief 添加/删除边和顶点的欧拉操作	order 231
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_vert			传入的顶点（子实体）
        * @param i_index			fin的序号
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_merge_vertice(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_vert, Ncti_Integer i_index, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 添加/删除双边组成的面的欧拉操作	order 232
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_edge			传入的边（子实体）
        * @param i_left			左侧(true)或者右侧(false)
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_edge_slit(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 分割边的欧拉操作	order 233
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_edge			传入的边（子实体）
        * @param i_forward			向前(true)或者向后(false)
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_edge_split(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_forward, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 添加/删除环的欧拉操作	order 234
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_edge			传入的边（子实体）
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_make_loop(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, NCTI_MODEL_TAG& o_modelBody);

        /*
        * @brief 拆分/合并离散环的欧拉操作	order 235
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_face			传入的面（子实体）
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_merge_loop(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_face, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 拆分/合并边到环的欧拉操作	order 236
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_face			传入的面（子实体）
        * @param o_modelBody	输出对象
        */
        virtual NctiGeometryResult euler_merge_edge_loop(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_face, NCTI_MODEL_TAG& o_modelBody);
        /*
        * @brief 将环从一个面移到另一个面的欧拉操作	order 237
        * @param i_pCustomContainer		文档类型
        * @param i_pBody        输入i_targetBody
        * @param i_from			传入的面（子实体）
        * @param i_to		传入的面（子实体）
        * @param io_modelBody	输入输出对象
        */
        virtual NctiGeometryResult euler_transfer_loop(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_from, NCTI_MODEL_TAG i_to, NCTI_MODEL_TAG& io_modelBody);

        /*
        * @brief 用一条bcurve拟合一条曲线	order 238
        * @param i_pCustomContainer		文档类型
        * @param i_pSourceCurve        输入的曲线
        * @param i_t_from，i_t_to		输入曲线的起始末尾参数
        * @param i_distTol，i_dAngleTol		距离和角度拟合容差
        * @param i_interpolated_params   插值点
        * @param i_preserve_parameterisation   是否将原曲线的参数化方法应用到拟合bcurve上
        * @param o_modelBody	输出的对象
        */
        virtual NctiGeometryResult bcurve_create_fitted(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceCurve,
            Ncti_Double i_t_from,
            Ncti_Double i_t_to,
            Ncti_Double i_distTol,
            Ncti_Double i_dAngleTol,
            const std::vector<Ncti_Double>& i_interpolated_params,
            Ncti_Boolean i_preserve_parameterisation,
            NCTI_MODEL_TAG& o_modelBody);

        /*
        * @brief 用一条bcurve拟合多条曲线	order 239
        * @param i_pCustomContainer		文档类型
        * @param i_pSourceCurves       输入的多条曲线
        * @param fit_parameters        生成的bcurves在每条曲线端点处的参数值
        * @param i_t_from，i_t_to		输入生成曲线的起始末尾参数
        * @param i_distTol，i_dAngleTol		距离和角度拟合容差
        * @param i_break_parms      bcurve的切割点（需要在输入的多个curves的端点处取若干值）(暂时不用）
        * @param o_modelBody    输出的对象
        */
        virtual NctiGeometryResult bcurve_create_by_fitting(NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::vector<NCTI_MODEL_TAG> i_pSourceCurves,
            std::vector<std::vector<Ncti_Double>> i_curve_intervals,
            std::vector<Ncti_Double> fit_parameters,
            Ncti_Boolean i_rational,
            Ncti_Double i_t_from,
            Ncti_Double i_t_to,
            Ncti_Double i_distTol,
            Ncti_Double i_dAngleTol,
            const std::vector<Ncti_Double>& i_break_parms,
            NCTI_MODEL_TAG& o_modelBody);

        /*
        * @brief 创建一条b样条曲线	order 240
        * @param i_pCustomContainer		文档类型
        * @param i_positions       输入多个拟合点
        * @param i_parameters        生成的bcurves在每个拟合点处的参数值
        * @param i_param_indices		i_parameters应该对应哪些i_positions
        * @param i_spline_method    拟合方法（插值/逼近）
        * @param fit_tol		点距离拟合容差
        * @param o_modelBody    输出的对象
        */

        virtual NctiGeometryResult bcurve_create_spline_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::vector<NctiPosition> i_positions,
            std::vector<Ncti_Double> i_parameters,
            std::vector<Ncti_Integer> i_param_indices,
            Ncti_Integer i_spline_method,
            Ncti_Double i_fit_tol,
            NCTI_MODEL_TAG& o_modelBody);

        /*
        * @brief 创建一个新的partition	order 241
        * @param i_pCustomContainer		文档类型
        * @param o_partitionID    输出partition在session中的顺序(这个顺序和PK_SESSION_ask_partitions后，partitions数组的顺序相反），即第几个partition，将o_partitionID这个代表第几个partition的变量
        * 存到python脚本开辟出的内存空间中（或者叫做python文档中）。这是不改变中间层的临时解决方法，最好的解决方法还是在中间层
        * 的文档中创建可以储存parasolid的partition的指针变量。
        */
        virtual NctiGeometryResult partition_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer& o_partitionTag);

        /*
        * @brief 设置当前partition	order 242
        * @param i_pCustomContainer		文档类型
        * @param i_partitionCurrent    要设置为当前partition的partition的tag。
        */
        virtual NctiGeometryResult partition_set_current(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partitionCurrent);

        /*
        * @brief 设置当前partition	order 243
        * @param i_pCustomContainer		文档类型
        * @param o_partitionCurrent    当前partition的tag。
        */
        virtual NctiGeometryResult session_ask_curr_partition(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer& o_partitionCurrent);

        /*
        * @brief 在partition中创建新的pmark	order 244
        * @param i_pCustomContainer		文档类型
        * @param i_partition    在这个partition创建
        * @param o_pmark    新创建的pmark
        */
        virtual NctiGeometryResult partition_make_pmark_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition, Ncti_Integer& o_pmark);

        /*
        * @brief 更新partition中的pmark，并删除原来的currentpmark	order 245
        * @param i_pCustomContainer		文档类型
        * @param i_partition    在这个partition更新
        * @param o_pmark   更新后的pmark
        */
        virtual NctiGeometryResult partition_advance_pmark(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition, Ncti_Integer& o_pmark);

        /*
        * @brief 跳回指定pmark  order 245
        * @param i_pCustomContainer		文档类型
        * @param i_pmark    跳回这个pmark
        */
        virtual NctiGeometryResult pmark_goto_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_pmark);

        /*
        * @brief 将几个partition中的pmarks合并到第一个partition，并删除其他partition	order 246
        * @param i_pCustomContainer		文档类型
        * @param i_partitions    需要合并的partitions
        * @param i_pmarks   每个需要合并partition中的pmarks
        */
        virtual NctiGeometryResult partition_merge(NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::vector<Ncti_Integer> i_partitions, std::vector<Ncti_Integer> i_pmarks);
        
        /*
        * @brief 删除指定的partition	order 247
        * @param i_pCustomContainer		文档类型
        * @param i_partition    需要删除的partition
        */
        virtual NctiGeometryResult partition_delete(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition);

        /*
        * @brief 复制指定的partition	order 248
        * @param i_pCustomContainer		文档类型
        * @param i_partition    需要复制的partition
        * @param o_partitioncopy    复制出来的partition
        */
        virtual NctiGeometryResult partition_copy(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition, Ncti_Integer& o_partitioncopy);
        
        /*
        * @brief 查询pmark在其partition的ID	order 249
        * @param i_pCustomContainer		文档类型
        * @param i_pmark    需要查询的pmark
        * @param o_identifier    查询出来的identifier
        */
        virtual NctiGeometryResult pmark_ask_identifier(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_pmark, Ncti_Integer& o_identifier);

        /*
        * @brief 输出partition	order 250
        * @param i_pCustomContainer		文档类型
        * @param i_partition    需要输出的partition
        * @param i_FullFileName    输出路径
        * @param i_transmit_deltas    需要输出的哪些delta内容
        */
        virtual NctiGeometryResult partition_transmit(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition, const Ncti_Char* i_FullFileName, Ncti_Integer i_transmit_deltas) ;
        
        /*
        * @brief 输出partition的delta	order 251
        * @param i_pCustomContainer		文档类型
        * @param i_partition    需要输出的partition，与前面partition_transmit的i_partition相同
        * @param i_FullFileName    输出路径
        * @param i_transmit_deltas    需要输出的哪些delta内容
        */
        virtual NctiGeometryResult partition_transmit_delta(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition);

        /*
        * @brief 输入partition	order 252
        * @param i_pCustomContainer		文档类型
        * @param i_FullFileName    输入路径
        * @param i_receive_deltas   需要输入delta内容
        * @param o_partition    输入后新生成的partition
        */
        virtual NctiGeometryResult partition_receive(NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Char* i_FullFileName, Ncti_Integer i_receive_deltas, Ncti_Integer& o_partition);
        
        /*
        * @brief 输入partition的delta	order 253
        * @param i_pCustomContainer		文档类型
        * @param i_partition    与前面相邻的partition_receive输入的i_partition相同
        */
        virtual NctiGeometryResult partition_receive_deltas_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition);

        /*
        * @brief 根据ID查找partition中的pmark	order 254
        * @param i_pCustomContainer		文档类型
        * @param i_partition    查找这个partition中的pmark
        * @param i_identifier    ID
        * @param o_pmark    查找出来的pmark
        */
        virtual NctiGeometryResult partition_find_pmark_by_id(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_partition, Ncti_Integer i_identifier, Ncti_Integer& o_pmark);
        
        /*
        * @brief 创建sessionmark	order 255
        * @param o_pmark    创建的mark
        */
        virtual NctiGeometryResult mark_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer& o_mark);

        /*
        * @brief 查找pmarks	order 256
        * @param i_mark    在这个mark中查找
        * @param o_pmarksVec    查出的pmarks
        */
        virtual NctiGeometryResult mark_ask_pmarks(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_mark, std::vector<Ncti_Integer>& o_pmarksVec);

        /*
        * @brief 查询pmark是否被某个mark用了	order 257
        * @param i_pmark    查这个pmark
        * @param o_is_used    是否被使用
        */
        virtual NctiGeometryResult pmark_is_used_by_mark(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_pmark, Ncti_Boolean& o_is_used);

        /*
        * @brief 跳到哪个mark上	order 258
        * @param i_mark    跳到这个mark上
        */
        virtual NctiGeometryResult mark_goto_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_mark);

        /*
        * @brief 输出session	order 259
        * @param i_FullFileName    文件路径
        */
        virtual NctiGeometryResult session_transmit(NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Char* i_FullFileName);

        /*
        * @brief 输入session	order 260
        * @param i_FullFileName    文件路径
        */
        virtual NctiGeometryResult session_receive(NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Char* i_FullFileName);

        /*
        * @brief 创建Bulletin board   	order 231
        * @param create——change     共9种行为类型，每种行为类型规定了其记录的entity类型（entity类型在这里有15种，从0到14）
        */
        virtual NctiGeometryResult bb_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::vector<Ncti_Integer> i_create,
            std::vector<Ncti_Integer> i_deleet,
            std::vector<Ncti_Integer> i_copy,
            std::vector<Ncti_Integer> i_transfer,
            std::vector<Ncti_Integer> i_merge,
            std::vector<Ncti_Integer> i_split,
            std::vector<Ncti_Integer> i_transform,
            std::vector<Ncti_Integer> i_change_attrib,
            std::vector<Ncti_Integer> i_change);

        
        /*
        * @brief 设置Bulletin board状态   	order 231
        * @param status
        */
        virtual NctiGeometryResult bb_set_status(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Boolean i_status);

        /*
        * @brief 输出Bulletin board   	order 231
        * @param i_empty    是否清空BB
        * @param o_events    事件号数组
        * @param o_entities    对应的entity的tag数组
        * @param o_event_types    事件类型数组
        * @param o_classes    entity类型数组
        */
        virtual NctiGeometryResult bb_output_events(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Boolean i_empty,
            std::vector< Ncti_Integer>& o_events,
            std::vector< Ncti_Integer>& o_entities,
            std::vector< Ncti_Integer>& o_event_types,
            std::vector< Ncti_Integer>& o_classes);

        /*
        * @brief 删除所有mark   	order 231
        */
         virtual NctiGeometryResult mark_delete_all(NctiDisplayDocCustomContainer* i_pCustomContainer);

		/*
        * @brief 面上压印曲线	order 261
        * @param i_pCustomContainer 文档类型
        * @param i_pSourceBody 压印使用的Face
        * @param i_pWire 压印使用的曲线
        * @param o_pTargetBody 返回结果
        */
        virtual NctiGeometryResult face_imprint_curves(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pWire,
            NCTI_MODEL_TAG& o_pTargetBody);
        /*
         * @brief 获取边上任意一点坐标 order 262
         * @param i_pCustomContainer
         * @param i_TargeBody 目标对象
         * @param i_ModelEdge 边的ID
		 * @param i_u 边上参数值
		 * @param o_Point 输出边上点的坐标
         */
        virtual NctiGeometryResult get_edge_point_from_u(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG i_ModelEdge,
			Ncti_Double i_u,
            NctiPosition& o_Point);
        
        /*
         * @brief 通过点扫掠生成螺旋线 order 263
         * @param i_pCustomContainer
         * @param i_position 扫掠点
         * @param i_helicalData 螺旋几何的定义数据
         * @param o_pWireBody 螺旋线对象
         */
        virtual NctiGeometryResult make_helical_curve_by_point(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiPosition& i_position,
            const Helical_Geometry_Data& i_helicalData,
            NCTI_MODEL_TAG& o_pWireBody);

        /*
         * @brief 通过边扫掠生成螺旋曲面 order 264
         * @param i_pCustomContainer
         * @param i_pWire 扫掠边
         * @param i_helicalData 螺旋几何的定义数据
         * @param o_pSheetBody 螺旋曲面对象
         */
        virtual NctiGeometryResult make_helical_surface_by_curve(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pWire,
            const Helical_Geometry_Data& i_helicalData,
            NCTI_MODEL_TAG& o_pSheetBody);

        /*
         * @brief 抽壳 order 265
         * @param i_pCustomContainer
         * @param i_pSolidBody 实体对象
         * @param i_offsetValue 全局抽壳厚度
         * @param i_tolerance   偏差
         * @param i_hollowOpt   抽壳功能的可选项
         * @param o_pResultBody 抽壳结果对象
         */
        virtual NctiGeometryResult hollow_out_solid_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSolidBody,
            Ncti_Double i_offsetValue,
            Ncti_Double i_tolerance,
            const BodyHollowOption& i_hollowOpt,
            NCTI_MODEL_TAG& o_pResultBody);

        /*
         * @brief 查找曲线上的点 order 266
         * @param i_pCustomContainer
         * @param i_pWireBody 输入的wire对象
         * @param i_pEdge edge对象
         * @param i_fMeasureValue 测量值
         * @param i_nMeasureMode   测量方式 0 : 弧长; 1 : 弧长比例; 2 : 弦长; 3 : 弦长比例; 4 : 分段弦长比例
         * @param o_vtPoint 查找到的点
         */
        virtual NctiGeometryResult find_point_on_curve(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pWireBody,
            NCTI_MODEL_TAG i_pEdge,
            Ncti_Double i_fMeasureValue,
            Ncti_Integer i_nMeasureMode,
            std::vector<NctiPosition>& o_vtPoint);

        /*
         * @brief 从一个body移除一些面片，并由这些面片创建新的body order 267
         * @param i_pCustomContainer
         * @param i_pSrcBody 输入的原对象
         * @param i_vtFaceToRemove 须要从原对象中移除的面片
         * 
         * @param i_nParentHealMethod 父对象的修复方式  0 : 不采取任何修复方式;  
         * 1 : 在缺口处加盖;  2 : 延伸缺口处的面片，直至把缺口封闭;
         * 3 : 生长父对象中孔周边的面片，直至把缺口封闭;    4 : 如果采用延伸的方式不能修复缺口，尝试采用裁剪的方式进行修复;
         * 5 : 采用任何可能的方式进行修复
         * 
         * @param i_nChildHealMethod 子对象的修复方式   0 : 不采取任何修复方式;  
         * 1 : 在缺口处加盖;  2 : 延伸缺口处的面片，直至把缺口封闭;
         * 3 : 生长父对象中孔周边的面片，直至把缺口封闭;    4 : 如果采用延伸的方式不能修复缺口，尝试采用裁剪的方式进行修复;
         * 5 : 采用任何可能的方式进行修复
         * 
         * @param o_vtBodies 运行后的结果集合
         */
        virtual NctiGeometryResult remove_face_to_new_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtFaceToRemove,
            Ncti_Integer i_nParentHealMethod,
            Ncti_Integer i_nChildHealMethod,
            std::vector<NCTI_MODEL_TAG>& o_vtBodies);

        /*
         * @brief 面片几何替换 order 268
         * @param i_pCustomContainer
         * @param i_pSrcBody 输入的原对象
         * @param i_vtFaceToReplace 需要被替换的面片
         * @param i_vtNewFaceBody 提供的新的面片
         * @param i_tolerance 精度
         * @param o_pNewBody 替换后的生成的对象
         */
        virtual NctiGeometryResult face_replace_surface(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtFaceToReplace,
            const std::vector<NCTI_MODEL_TAG>& i_vtNewFaceBody,
            double i_tolerance,
            NCTI_MODEL_TAG& o_pNewBody);
         /* @brief 获取对象的OBB包围盒	 order 269
         * @param i_pCustomContainer 文档类型
         * @param i_pModelBody		输入对象集合
         * @param paraData           输入参数集合
         * 轴1的原点
         * 轴1的方向
         * 轴2的原点
         * 轴2的方向
         * @param boxData           输出OBB包围盒参数，5个点依次如下
         * 索引0:box的最小点坐标；
         * 索引1：box的最大点坐标；
         * 轴的原点坐标
         * 轴的X轴
         * 轴的Z轴
         */
        virtual NctiGeometryResult get_obb_boungding_box(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const std::vector<NCTI_MODEL_TAG>& i_pModelBody,
            const std::vector<NctiPosition>& paraData,
            std::vector<NctiPosition>& boxData);

        /*
        * @brief 中面抽取 order 270
        * @param i_pCustomContainer
        * @param i_pSrcBody 输入的原对象
        * @param i_vtLeftFaces 输入的左面片集
        * @param i_vtRightFaces 输入的右面片集
        * @param i_nMethods 生成中面的方式， 0 : 适用于i_vtRightFaces由i_vtLeftFaces偏移而来的情况，中面由其中的i_vtLeftFaces或者i_vtRightFaces偏移所得
                                             1 : 中面由i_vtLeftFaces偏移所得；      2 : 中面由i_vtLeftFaces和i_vtRightFaces的平均中间面所得

        * @param i_fPlacement   放置参数
        * @param o_pNeutralSheet 生成的中面对象
        */
        virtual NctiGeometryResult make_neutral_sheet(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtLeftFaces,
            const std::vector<NCTI_MODEL_TAG>& i_vtRightFaces,
            int i_nMethods,
            double i_fPlacement,
            NCTI_MODEL_TAG& o_pNeutralSheet);

        /*
        * @brief 冗余拓扑删除 order 271
        * @param i_pCustomContainer
        * @param i_pSrcBody 输入的原对象
        * @param o_pNewBody 删除冗余拓扑后的新对象
        */
        virtual NctiGeometryResult delete_redundant_topol(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            NCTI_MODEL_TAG& o_pNewBody);

        /*
        * @brief 对象错误检查 order 272
        * @param i_pCustomContainer
        * @param i_pSrcBody 输入的原对象
        * @param o_vtFault 输出的错误信息
        */
        virtual NctiGeometryResult body_fault_check(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            std::vector<BodyCheckFaultResult>& o_vtFault);

/*
        * @brief 查找曲线、曲面自交区域 order 273
        * @param i_pCustomContainer
        * @param i_pSrcBody 输入的原对象
        * @param i_pCell 输入edge或者face对象
        * @param o_vtSelfIntInfo 输出的自交信息
        */
        virtual NctiGeometryResult find_cell_self_int(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            NCTI_MODEL_TAG i_pCell, 
            std::vector<CellSelfIntDegensInfo>& o_vtSelfIntInfo);

        /*
        * @brief 查找曲线、曲面上退化区域 order 274
        * @param i_pCustomContainer
        * @param i_pSrcBody 输入的原对象
        * @param i_pCell 输入edge或者face对象
        * @param o_vtDegensInfo 输出的退化信息
        */
        virtual NctiGeometryResult find_cell_degens(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            NCTI_MODEL_TAG i_pCell,
            std::vector<CellSelfIntDegensInfo>& o_vtDegensInfo);

        /*
        * @brief 线裁剪面 order 275
        * @param i_pCustomContainer
        * @param i_pSrcBody 输入的原对象
        * @param i_pToolBody 输入的线对象
		* @param i_ReserveInternal 裁剪后保留内部
		* @param o_pNewBody 裁剪后的新对象
        */
        virtual NctiGeometryResult trim_face_by_wire(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            NCTI_MODEL_TAG i_pToolBody,
            Ncti_Boolean i_ReserveInternal,
            NCTI_MODEL_TAG& o_pNewBody);
            
        /*  @brief 延申BODY order 276
        * @param i_pCustomContainer 文档类型
        * @param extendOption		输入延申参数
        * @param resultData         延伸产生的新对象集合
        */
        virtual NctiGeometryResult body_extend(NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NCTIBodyExtendOption& extendOption, NCTI_MODEL_TAG& resultData);

        /*
        * @brief 填充 order 277
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入对象
        * @param i_EdgeVec i_pBody的填充边界
        * @param iType 曲面填充类型 2:G2，3:G3，4:G4.....
        * @param o_pBody 填充后新对象
        */
        virtual NctiGeometryResult filling(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            const std::vector<NCTI_MODEL_TAG>& i_EdgeVec,
            int iType,
            NCTI_MODEL_TAG& o_pBody);

        /*
        * @brief 面片变换 order 278
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入对象
        * @param i_vtFaceToTransform i_pBody中待变换的面片集合
        * @param i_vtTransf i_vtFaceToTransform中面片相应的变换矩阵
        * @param i_option 可选项
        * @param o_pNewBody 变换后后的新对象
        */
        virtual NctiGeometryResult face_transform(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtFaceToTransform,
            const std::vector<NctiTransf>& i_vtTransf,
            const NCTIFaceTransformOption& i_option,
            NCTI_MODEL_TAG& o_pNewBody);
        
        /*  @brief 曲面求交 order 279
        * @param i_pCustomContainer 文档类型
        * @param pSurface1		曲面1
        * @param pSurface2      曲面2
        * @param resultPoints   返回交点集合
        * @param resultCurves   返回交曲线（polyline）集合
        */
        virtual NctiGeometryResult surface_intersect_surface(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSurface1, NCTI_MODEL_TAG i_pSurface2, std::vector<NctiPosition>& o_resultPoints, std::vector<NCTI_MODEL_TAG>& o_resultCurves);

        /*
        * @brief edge修复 order 280
        * @param i_pCustomContainer 文档
        * @param io_pBody 输入输出对象
        * @param i_vtEdgeToRepair i_pBody中待修复的edge集合
        * @param i_bEnsureOnSurfs 是否保证Edge正好在面片的surface上
        * @param i_bIntersect 是否保证edge正好是相邻face的交线
        * @param i_fMaxTolerance 允许的最大偏差
        */
        virtual NctiGeometryResult edge_repair(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_pBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtEdgeToRepair,
            bool i_bEnsureOnSurfs,
            bool i_bIntersect,
            double i_fMaxTolerance);

        /*
        * @brief BODY离散化 order 281
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入的BODY对象
        * @param i_vtFacesToFacet i_pBody中对应的需要被离散化的面片，如果为空，则离散i_pBody中所有的面片
        * @param i_option 输入的离散化选项
        * @param o_vtNctiMeshData 面片离散后的Mesh数据
        */
        virtual NctiGeometryResult topol_render_facet(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtFacesToFacet,
            const NCTITopolFacetOption& i_option,
            std::vector<NctiMeshData>& o_vtNctiMeshData);
            
        /*  @brief 修复topol  order 282
        * @param i_pCustomContainer 文档类型
        * @param i_faceBodyModel 待修复的Face的body
        * @param i_faceModel 待修复的Face
        * @param i_g1Discontinuities     值：true 开启G1连续修复; false 不修复
        * @param i_selfIntersections     值：true 开启自相交修复; false 不修复自相交
        * @param o_resultBody   返回修复后的body
        */
        virtual NctiGeometryResult face_repair(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_faceBodyModel, NCTI_MODEL_TAG i_faceModel,bool i_g1Discontinuities,bool i_selfIntersections,NCTI_MODEL_TAG& o_resultBody);

		/*@brief Body确认     order 283
        * @param i_pCustomContainer 文档类型
        * @param i_pBody            输入参数：待确认的Body
        * @param o_checkResult      返回结果集合
        */
        virtual NctiGeometryResult identify_general(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody, std::vector<NCTIBodyGeneralResult>& o_checkResult);

        /*  @brief 获取布告板参数      order 284
        * @param i_pCustomContainer 输入参数：文档类型
        * @param o_bbParamResult    输出参数：布告板参数
        */
        virtual NctiGeometryResult bb_ask(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTIBbParam& o_bbParamResult);

        /*  @brief 获取布告板状态  order 285
        * @param i_pCustomContainer 输入参数：文档类型
        * @param o_bbStatusResult    输出参数：布告板状态
        */
        virtual NctiGeometryResult bb_ask_status(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTIBbStatus& o_bbStatusResult);

        /*  @brief 拉伸实体     order 286
        * @param i_pCustomContainer 输入参数：文档类型
        * @param i_profile  输入参数：被拉伸的截面
        * @param i_path     输入参数：拉伸的矢量
        * @param i_extrudeOption  输入参数：拉伸设置
        * @param o_resultBody    输出参数：拉伸后的结果实体
        */
        virtual NctiGeometryResult body_extrude(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyExtrudeParam& i_extrudeParam, NCTI_MODEL_TAG& o_resultBody);

        /*  @brief 创建晶格实体       order 287
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_latticeParam      输入参数：晶格数据参数
        * @param o_resultLattices    输出参数：创建的晶格实体(暂时是三角化body)
        */
        virtual NctiGeometryResult lattice_create(NctiDisplayDocCustomContainer* i_pCustomContainer,const NCTILatticeCreateParam& i_latticeParam, std::vector<NCTI_MODEL_TAG>& o_resultLattices);

        /*  @brief 输出拓补、几何信息    order 288
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_pModelBody        输入参数：Body对象
        * @param i_vtModelCells      输入参数：要输出信息的CELL对象列表(如果为空，则输出整个BODY的信息)
        * @param i_nLevel            输入参数：表示输出信息的等级，
                                     0 : 在输出整个BODY信息的情况下（即i_vtModelCells为空的情况下），
                                     只输出与BODY相关的最基本的全局信息，在i_vtModelCells不为空的情况下，等同于i_nLevel == 1
                                     1 : 只输出拓扑信息
                                     2 : 输出拓扑和几何信息
        * @param i_pFileName         输入参数：文件名字（后缀为xml）
        */
        virtual NctiGeometryResult output_topol_info_with_geom(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pModelBody, const std::vector<NCTI_MODEL_TAG>& i_vtModelCells, int i_nLevel, const char* const i_pFileName);
        
        /*  @brief 获取实体参数值      order 289
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_entity            输入参数：获取参数的实体
        * @param i_paramType         输入参数：参数类型值集合
        * @param o_paramValueStr     输出参数：参数值的字符集合
        */
        virtual NctiGeometryResult ask_entity_param(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_entity, const std::vector<Ncti_Integer>& i_paramType, std::vector<std::string>& o_paramValueStr);

        /*  @brief 创建mesh           order 290
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_latticeParam      输入参数：mesh数据参数
        * @param o_resultLattices    输出参数：创建的mesh
        */
        virtual NctiGeometryResult mesh_create(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIMeshCreateParam& i_meshParam, std::vector<NCTI_MODEL_TAG>& o_resultMeshes);

        /*  @brief 曲面编辑操作       order 291
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_BsurfEditParam      输入参数：曲面数据参数
        * @param o_resultModels    输出参数：创建的模型
        */
        virtual NctiGeometryResult bsurf_edit(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBsurfEditParam& i_BsurfEditParam, std::vector<NCTI_MODEL_TAG>& o_resultModels);

        /*
        * @brief bcurve对象参数重参化 order 292
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入的BODY对象
        * @param i_pEdge i_pBody中须进行参数重参化曲线对应的edge
        * @param i_fMiniParam 输入的参数最小值
        * @param i_fMaxParam 输入的参数最大值
        * @param o_pNewBody 输出的BODY对象
        */
        virtual NctiGeometryResult bcurve_reparameterise(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            NCTI_MODEL_TAG i_pEdge,
            double i_fMiniParam,
            double i_fMaxParam, 
            NCTI_MODEL_TAG& o_pNewBody);

        /*
        * @brief 曲面对象参数重参化 order 293
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入的BODY对象
        * @param i_vtFaces i_pBody中须进行参数重参化曲面对应的face数组
        * @param i_option 选项
        * @param o_pNewBody 输出的BODY对象
        */
        virtual NctiGeometryResult face_reparameterise_surf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtFaces,
            const NCTISurfReparameteriseOption& i_option,
            NCTI_MODEL_TAG& o_pNewBody);

        /*
        * @brief 读取Parasolid文件格式文件，X_T、X_B、或者xmt_txt、xmt_bin文件 order 294
        * @param i_pCustomContainer 文档
        * @param i_FullFileName 输入参数 全路径文件名
        * @param o_vtModelBody  输出参数 输出的BODY列表
        */
        virtual NctiGeometryResult input_pk_xt_xb_file(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Char* const i_FullFileName,
            std::vector<NCTI_MODEL_TAG>& o_vtModelBody);

        /*
        * @brief 输出Parasolid文件格式文件，X_T、X_B、或者xmt_txt、xmt_bin文件 order 295
        * @param i_pCustomContainer 文档
        * @param i_FullFileName 输入参数 全路径文件名
        * @param i_vtModelBody  输入参数 模型列表
        */
        virtual NctiGeometryResult output_pk_xt_xb_file(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Char* const i_FullFileName,
            const std::vector<NCTI_MODEL_TAG>& i_vtModelBody);

        /*  @brief 放样           order  296
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_bodyLoftParam      输入参数：loft参数数据
        * @param o_resultLattices    输出参数：放样创建的体
        */
        virtual NctiGeometryResult body_loft(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyLoftParam& i_bodyLoftParam, NCTI_MODEL_TAG& o_resultModel);

        /*  @brief 扫略           order  297
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_bodySweptParam      输入参数  扫略参数数据
        * @param o_resultModel    输出参数：放样创建的体
        */
        virtual NctiGeometryResult body_swept(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodySweptParam& i_bodySweptParam, NCTI_MODEL_TAG& o_resultModel);

        /*  @brief 加厚           order 298
       * @param i_pCustomContainer  输入参数：文档类型
       * @param i_bodyThickenParam      输入参数  加厚参数数据
       * @param o_resultModel    输出参数：加厚创建的体
       */
        virtual NctiGeometryResult body_thicken(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyThickenParam& i_bodyThickenParam, NCTI_MODEL_TAG& o_resultModel);


        /*  @brief 拔模           order    299
       * @param i_pCustomContainer  输入参数：文档类型
       * @param i_bodyTaperParam      输入参数  taper参数数据
       * @param o_resultModel    输出参数：taper创建的体
       */
        virtual NctiGeometryResult body_taper(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyTaperParam& i_bodyTaperParam, NCTI_MODEL_TAG& o_resultModel);

        /*  @brief 拔模           order 300
      * @param i_pCustomContainer  输入参数：文档类型
      * @param i_target      输入参数  被分割的体
      * @param i_surface      输入参数  用来分割体的surface
      * @param i_resultType      输入参数  返回结果类型：
      * @param o_resultModels    输出参数：返回分割后的体集合   0：返回surface法向同侧；1：返回surface法向异侧；2全部返回
      */
        virtual NctiGeometryResult section_with_surface(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_target, NCTI_MODEL_TAG i_surface,  Ncti_Integer i_resultType, std::vector<NCTI_MODEL_TAG>& o_resultModels);

        /*  @brief 曲线投影           order    301
      * @param i_pCustomContainer  输入参数：文档类型
      *@param i_curves        需要投影的曲线，不能自相交
      *@param i_targets       曲线投影的目标，可以是实心体，面片、面
      * @param i_curveProjectParam      输入参数  NCTICurveProjectParam参数数据
      * @param o_resultModels    输出参数：投影结果，可能单个也可能多个
      */
        virtual NctiGeometryResult curve_project(NctiDisplayDocCustomContainer* i_pCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_curves, const std::vector<NCTI_MODEL_TAG>& i_targets, const NCTICurveProjectParam& i_curveProjectParam, std::vector<NCTI_MODEL_TAG>& o_resultModels);
      
        /*  @brief 偏移           order  302
    * @param i_pCustomContainer  输入参数：文档类型
    * @param i_targetBody      输入参数  待偏移的体或面
    * @param i_offsetDist      输入参数 偏移距离
    * @param i_bodyOffsetParam      输入参数  偏移参数：
    * @param o_resultModel    输出参数： 返回偏移后的结果
    */
        virtual NctiGeometryResult body_offset(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_targetBody,  Ncti_Double i_offsetDist, const NCTIBodyOffsetParam& i_bodyOffsetParam, NCTI_MODEL_TAG& o_resultModel);
    
    /*  @brief 扩大体  order 303
        * @param i_pCustomContainer  输入参数：文档类型
        * @param i_bodyEnlargeParam  输入参数：扩大体参数，详见该结构说明
        * @param o_resultLattices    输出参数：扩大后的体集合o_resultModels
        */
        virtual NctiGeometryResult body_enlarge(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyEnlargeParam& i_bodyEnlargeParam, std::vector<NCTI_MODEL_TAG>& o_resultModels);

        /*
        * @brief 分拆模型中不相连的部分 order 304
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入的BODY对象
        * @param o_vtDisconnectedBodies 输出的非连接的对象
        */
        virtual NctiGeometryResult divide_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            std::vector<NCTI_MODEL_TAG>& o_vtDisconnectedBodies);

        /*
        * @brief 设置拓扑对象的精度 order 305
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入的BODY对象
        * @param i_pTopol 输入的要设置精度的拓扑对象(Vertex或者Edge)
        * @param i_method 设置方式       0 : 修改精度值(适用于Vertex和Edge);     1 : 重置精度(适用于Edge);      2 : 优化(适用于Vertex)
        * @param i_precision 输入的精度值
        * @param o_pBody 输出的BODY对象
        */
        virtual NctiGeometryResult set_topol_precision(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            NCTI_MODEL_TAG i_pTopol, 
            Ncti_Integer i_method,
            double i_precision,
            NCTI_MODEL_TAG& o_pBody);

        /*
        * @brief 填充
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入对象
        * @param i_EdgeVec i_pBody的填充边界
        * @param iType 曲面填充类型 2:G2，3:G3，4:G4.....
        * i_fillOpt 填充选项
        * @param o_pBody 填充后新对象
        */
        virtual NctiGeometryResult filling(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            const std::vector<NCTI_MODEL_TAG>& i_EdgeVec,
            int iType,
            const NCTIFillHoleOption& i_fillOpt,
            NCTI_MODEL_TAG& o_pBody);

        /*
        * @brief 特征识别
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入对象
        * @param i_opt 特征识别选项
        * @param o_vtFeatureFaces 输出的特征面
        */
        virtual NctiGeometryResult identify_feature(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            const NCTIIdentifyFeatureOption& i_opt,
            std::vector<NCTIIdentifyFeatureResult>& o_vtFeatureFaces);

        /*
        * @brief 三面倒角
        * @param i_pCustomContainer 文档
        * @param i_pLeftBody 左边面所在的BODY
        * @param i_vtLeftFaces 左边面
        * @param i_pRightBody 右边面所在的BODY
        * @param i_vtRightFaces 右边面
        * @param i_pCentreBody 中间面所在的BODY
        * @param i_vtCentreFaces 中间面
        * @param i_pGuideWire   定义横截面的Wire对象
        * @param i_opt 三面倒角选项
        * @param o_resultBody 输出的倒角对象
        */
        virtual NctiGeometryResult make_3_face_blend(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pLeftBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtLeftFaces,
            NCTI_MODEL_TAG i_pRightBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtRightFaces,
            NCTI_MODEL_TAG i_pCentreBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtCentreFaces,
            NCTI_MODEL_TAG i_pGuideWire,
            const NCTI3FaceBlendOption& i_opt,
            NCTI_MODEL_TAG& o_resultBody);

        /*
        * @brief 获取曲线的参数范围
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入Curve
        * @param i_Edge 边界
        * @param dFirst 输出第一个参数范围值
        * @param dLast 输出最后一个参数范围值
        */
        virtual NctiGeometryResult get_curve_parameter_range(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            NCTI_MODEL_TAG i_Edge,
            Ncti_Double& dFirst,
            Ncti_Double& dLast);
        /*
        * @brief 设置曲线的参数范围
        * @param i_pCustomContainer 文档
        * @param i_pBody 输入Curve
        * @param i_Edge 边界
        * @param dFirst 第一个参数范围值
        * @param dLast 最后一个参数范围值
        * @param o_pBody 输出对象
        */
        virtual NctiGeometryResult set_curve_parameter_range(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pBody,
            NCTI_MODEL_TAG i_Edge,
            Ncti_Double dFirst,
            Ncti_Double dLast,
            NCTI_MODEL_TAG& o_pBody);

        /*
        * @brief 面组与面组之间倒角
        * @param i_pCustomContainer 文档
        * @param i_pLeftBody 左边面所在的BODY
        * @param i_vtLeftFaces 左边面
        * @param i_pRightBody 右边面所在的BODY
        * @param i_vtRightFaces 右边面
        * @param i_bLeftSense 左边面是否与法向一致
        * @param i_bRightSense 右边面是否与法向一致
        * @param i_opt 面倒角选项
        * @param o_resultBody 输出的倒角对象
        */
        virtual NctiGeometryResult face_make_blend(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pLeftBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtLeftFaces,
            NCTI_MODEL_TAG i_pRightBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtRightFaces,
            Ncti_Boolean i_bLeftSense,
            Ncti_Boolean i_bRightSense,
            const NCTIFaceBlendOption& i_opt,
            NCTI_MODEL_TAG& o_resultBody);

        /*
        * @brief 边与边之间的混接
        * @param i_pCustomContainer 文档
        * @param i_pStartBody 起始边所在的BODY
        * @param i_pStartEdge 起始边
        * @param i_pStartVertex 起始参考点
        * @param i_startOffsetRatio 起始偏移比例
        * @param i_pEndBody 终止边所在的BODY
        * @param i_pEndEdge 终止边
        * @param i_pEndVertex 终止参考点
        * @param i_endOffsetRatio 终止偏移比例
        * @param i_opt 选项
        * @param o_resultBody 输出的混接对象
        */
        virtual NctiGeometryResult edge_make_blend(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pStartBody,
            NCTI_MODEL_TAG i_pStartEdge,
            NCTI_MODEL_TAG i_pStartVertex,
            Ncti_Double i_startOffsetRatio,
            NCTI_MODEL_TAG i_pEndBody,
            NCTI_MODEL_TAG i_pEndEdge,
            NCTI_MODEL_TAG i_pEndVertex,
            Ncti_Double i_endOffsetRatio,
            const NCTIEdgeBlendOption& i_opt,
            NCTI_MODEL_TAG& o_resultBody);

        /*
        * @brief 面上边的偏移
        * @param i_pCustomContainer 文档
        * @param i_pSrcBody 原实体或者sheet BODY
        * @param i_vtEdgesToOffset 待偏移的边
        * @param i_direction 偏移方向       0 : 左偏;   1 : 右偏
        * @param i_opt 选项
        * @param o_resultBody 输出的对象
        */
        virtual NctiGeometryResult edge_offset_on_body(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcBody,
            const std::vector<NCTI_MODEL_TAG>& i_vtEdgesToOffset,
            int i_direction,
            const NCTIEdgeOffsetOnBody& i_opt,
            NCTI_MODEL_TAG& o_resultBody);
    };
}
#endif
