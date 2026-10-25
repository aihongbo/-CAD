#include "OCCInterfaceDemo.h"
#include "NctiDisplayDocCustomContainer.h"
#include "NctiFile.h"
#include "NctiString.h"
#include "NctiPosition.h"
#include "NctiBaseUtility.h"

#include <gp_Pnt.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include "TopExp_Explorer.hxx"
#include <Geom_BezierCurve.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <GeomFill_Trihedron.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepBuilderAPI_NurbsConvert.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Geom_OffsetSurface.hxx>
#include "BOPAlgo_BOP.hxx"
#include "BOPTest_Objects.hxx"
#include "BRepTest_Objects.hxx"
#include "BOPTest.hxx"
#include "BOPAlgo_Splitter.hxx"
#include "BOPAlgo_MakePeriodic.hxx"
#include "BRep_Builder.hxx"
#include "ShapeAnalysis_Curve.hxx"
#include "GeomAPI.hxx"
#include "Geom2dGcc_Lin2d2Tan.hxx"
#include "Geom2dGcc_QualifiedCurve.hxx"
#include "Geom2dGcc_Lin2dTanObl.hxx"
#include "Geom2dGcc.hxx"
#include "Geom2d_Line.hxx"
#include "Geom_Plane.hxx"
#include "Geom2d_Circle.hxx"
#include "Geom_Line.hxx"
#include "TopoDS.hxx"
#include "NctiOCCBody.h"
#include "GCPnts_AbscissaPoint.hxx"
#include "ShapeUpgrade_UnifySameDomain.hxx"
#include "BOPAlgo_Section.hxx"
#include "BRepFilletAPI_MakeChamfer.hxx"
#include "BRepTools.hxx"
#include "BRepOffsetAPI_ThruSections.hxx"
#include "GccAna_Circ2d3Tan.hxx"
#include "GccEnt_QualifiedCirc.hxx"
#include "GeometryTest_DrawableQualifiedCurve2d.hxx"
#include "GccEnt_QualifiedLin.hxx"
#include "GccEnt_Position.hxx"
#include "BRepOffsetAPI_NormalProjection.hxx"
#include "BRepAdaptor_Curve.hxx"
#include "Geom_Circle.hxx"
#include "Geom_Ellipse.hxx"
#include "GeomLib.hxx"
#include "Geom_TrimmedCurve.hxx"
#include "Geom_BSplineCurve.hxx"
#include "GProp_GProps.hxx"
#include "BRepGProp.hxx"
#include "GeomLProp_SLProps.hxx"
#include "BRepExtrema_DistShapeShape.hxx"
#include "BRepOffsetAPI_MakeOffset.hxx"
#include "GeomAPI_ExtremaCurveCurve.hxx"
#include "GeomAPI_ExtremaSurfaceSurface.hxx"
#include "GeomAPI_ExtremaCurveSurface.hxx"
#include "BRepBuilderAPI_GTransform.hxx"
#include "BRepAlgoAPI_Defeaturing.hxx"
//#include <BRepTest_Objects.hxx>
//#include <TopTools_ListOfShape.hxx>
//#include <BOPAlgo_BOP.hxx>
//#include <BOPTest_Objects.hxx>
//#include <BOPTest.hxx>
//#include <Draw_ProgressIndicator.hxx>
#include "NctiGeometryFunctionInterface.h"

using namespace NCTI;
#define NCTI_OBJ_NAME "OCCInterfaceDemo"

NCTI_PLUGIN_DEF(OCCInterfaceDemo, GeometryFunctionInterfaceDemo, "ncti_occ_plugin_demo", NCTI_OBJ_NAME)

/**
 * @brief 检查OCC文档容器是否为空
 * @details 检查给定的文档容器指针是否为空或不是OCC文档容器类型
 * @param DOC_OCC_VALUE 文档容器指针
 */
#define NCTI_DOC_OCC_EMPTY(DOC_OCC_VALUE)                                                                              \
    if (DOC_OCC_VALUE == nullptr) {                                                                                    \
        return NctiModelFunctionResult();                                                                              \
    }                                                                                                                  \
    if (DOC_OCC_VALUE->IsTypeName(NctiDisplayOCCDocCustomContainer::ID) == false) {                                    \
        return NctiModelFunctionResult();                                                                              \
    }

/**
 * @brief 检查OCC文档容器是否为空(新版本)
 * @details 检查给定的文档容器指针是否为空或不是OCC文档容器类型
 * @param DOC_OCC_VALUE 文档容器指针
 */
#define NCTI_DOC_OCC_EMPTY_NEW(DOC_OCC_VALUE)                                                                          \
    if (DOC_OCC_VALUE == nullptr) {                                                                                    \
        return NctiGeometryResult();                                                                                   \
    }                                                                                                                  \
    if (DOC_OCC_VALUE->IsTypeName(NctiDisplayOCCDocCustomContainer::ID) == false) {                                    \
        return NctiGeometryResult();                                                                                   \
    }

/**
 * @brief 添加OCC错误代码
 */
#define NCTI_OCC_ADD_ERRORCODE()

//检查参数Point有效性
/**
 * @brief 检查参数点有效性
 * @details 检查两个点是否满足指定的相同/不同条件
 * @param i_ARGPOINT1 第一个点参数
 * @param i_ARGPOINT2 第二个点参数
 * @param i_BSAME 是否应该相同
 * @param i_RESULT 结果对象
 */
#define CHECK_FUNC_POINT_VALID(i_ARGPOINT1, i_ARGPOINT2, i_BSAME, i_RESULT)                                            \
    {                                                                                                                  \
        if (NctiBaseUtility::same_point(i_ARGPOINT1, i_ARGPOINT2, NCTI_RESABS) != i_BSAME) {                           \
            i_RESULT.SetErrorInfoByCode(FUNC_GENERAL_PARAMETER_ERROR);                                                 \
            if (i_BSAME) {                                                                                             \
                i_RESULT.AddErrorInfo("Two points are not same.");                                                     \
            }                                                                                                          \
            else {                                                                                                     \
                i_RESULT.AddErrorInfo("Two points are same.");                                                         \
            }                                                                                                          \
            i_RESULT.SetErrorArgument(#i_ARGPOINT1, ncti_error_to_string(i_ARGPOINT1));                                \
            i_RESULT.SetResult(false);                                                                                 \
            return i_RESULT;                                                                                           \
        }                                                                                                              \
    }

OCCInterfaceDemo* g_NctiOCCInterface = NCTI_NEW OCCInterfaceDemo();

NCTI::OCCInterfaceDemo::OCCInterfaceDemo()
{
}

NCTI::OCCInterfaceDemo::~OCCInterfaceDemo()
{
}

/**
 * @brief 创建长方体的演示函数实现
 * @details 使用OpenCASCADE库创建一个长方体，并将其添加到文档容器中
 * 
 * @param i_pCustomContainer 文档容器指针
 * @param i_pos 长方体的坐标点位置
 * @param i_len 长度
 * @param i_width 宽度
 * @param i_height 高度
 * @param o_ModelBody 输出的模型体对象
 * @return 几何操作结果
 */

bool IsTypeNameOcc(const char* sTypeName)
{
    if ((NctiDisplayDocCustomContainer::ID)[2] != sTypeName[2])
    {
        return false; 
    }
    if (strcmp("doc_occ_custom_container", sTypeName) == 0)
    {
        return true;
    }
    return false;
}

NctiGeometryResult NCTI::OCCInterfaceDemo::create_box_demo(NctiDisplayDocCustomContainer* i_pCustomContainer,
                                                           const NctiPosition& i_pos,
                                                           Ncti_Double i_len,
                                                           Ncti_Double i_width,
                                                           Ncti_Double i_height,
                                                           NCTI_MODEL_TAG& o_ModelBody)
{
    //NCTI_DOC_OCC_EMPTY_NEW(DOC_OCC_CUSTOM_CONTAINER_DEMO)
    if (!IsTypeNameOcc(i_pCustomContainer->TypeName()))
    {
        return NctiGeometryResult();
    }
    
    NctiGeometryResult result(true);

    CHECK_FUNC_ARGUMENT_RANGE(fabs(i_len), >, Precision::Confusion(), result)
    CHECK_FUNC_ARGUMENT_RANGE(fabs(i_width), >, Precision::Confusion(), result)
    CHECK_FUNC_ARGUMENT_RANGE(fabs(i_height), >, Precision::Confusion(), result)
    BEGIN_TRY
    gp_Pnt corner(i_pos.x(), i_pos.y(), i_pos.z());
    BRepPrimAPI_MakeBox box(corner, i_len, i_width, i_height);
    TopoDS_Shape shape = box.Shape();
    if (shape.IsNull()) {
        result.SetErrorInfoByCode(FUNC_KERNEL_ERROR);
        result.SetResult(false);
        return result;
    }
    TopoDS_Shape* pTopoDS_Shape = NCTI_NEW TopoDS_Shape(shape);
    NctiOCCBody* pBody          = NCTI_NEW NctiOCCBody(pTopoDS_Shape);
    o_ModelBody                 = pBody;
    END_CATCH_EXCEPTION(result)
    return result;
}
