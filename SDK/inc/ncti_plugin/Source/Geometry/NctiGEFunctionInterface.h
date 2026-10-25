#ifndef NctiGEFunctionInterface_H
#define NctiGEFunctionInterface_H
#include "NctiGeometryFunctionInterface.h"
#include <memory>
namespace NCTI
{
	class NctiRenderSegmentItem;
	class NctiAssembly;
	class DECL_NCTI_PLUGIN NctiGEFunctionInterface : public NctiFunctionInterface
	{
		NCTI_PLUGIN_FUNCTIONS(NctiGEFunctionInterface)
	public:
		NctiGEFunctionInterface();
		virtual ~NctiGEFunctionInterface();
	public:
		virtual NctiGeometryResult uv_position_perform(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell,
			Ncti_Double i_u,
			Ncti_Double i_v,
			Ncti_Integer& o_result,
			Ncti_Boolean i_reverse);
		virtual NctiGeometryResult uvs_find(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody, 
			NCTI_MODEL_TAG i_edge,
			NCTI_MODEL_TAG i_face,
			const std::vector<Ncti_Double>& i_params,
			std::vector<NctiPosition>& o_pts,
			Ncti_Boolean i_reverse);
		virtual NctiGeometryResult is_close(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_cell,
			Ncti_Boolean& o_isClose,
			Ncti_Boolean i_reverse);
		virtual NctiGeometryResult get_faces_same_radius(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Cell,
			std::vector<NCTI_MODEL_TAG>& o_Cells
		);
		virtual NctiGeometryResult find_nearest_face_by_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NCTI_MODEL_TAG>& i_ModelFaceVec,
			const std::vector<NctiPosition>& i_PointVec,
			std::vector<NCTI_MODEL_TAG>& o_ModelFaceVec
		);
		virtual NctiGeometryResult get_face_cell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			std::vector<NCTI_MODEL_TAG>& o_CellVec);
		virtual NctiGeometryResult remove_face(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NCTI_MODEL_TAG>& i_FaceCellVec,
			NCTI_MODEL_TAG& o_ResultBody);
		virtual NctiGeometryResult split_face(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NCTI_MODEL_TAG>& i_FaceCellVec,
			std::vector<NCTI_MODEL_TAG>& o_FaceVec,
			NCTI_MODEL_TAG& o_ResultBody);
		virtual NctiGeometryResult fill_loop(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody, 
			const std::vector<NCTI_MODEL_TAG>& i_EdgeCellVec,
			NCTI_MODEL_TAG& o_ResultBody);
		virtual NctiGeometryResult explode(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			std::vector<NCTI_MODEL_TAG>& o_ResultBodyVec);
		virtual NctiGeometryResult extract_bounds(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_Cell,
			NctiGeomBounds& o_bounds);
		virtual NctiGeometryResult extract_prop(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell,
			NctiGeomProp& o_geomProp);
		virtual NctiGeometryResult pick_ray(
			NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell, 
			const NctiPosition& i_posRay,
			const NctiVector& i_uvecRay,
			Ncti_Double& o_u,
			Ncti_Double& o_v);
		virtual NctiGeometryResult IsEnclosed(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_TargeBodyTool);
		virtual NctiGeometryResult add_attribute_cell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody, 
			NctiRenderSegmentItem* i_pSegment);
		virtual NctiGeometryResult get_attribute_cell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_Cell,
			NctiRenderSegmentItem*& o_pSegment);
		virtual NctiGeometryResult import_file(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec,
			int i_nUniteMode = 1);
		/*
		* @brief 分组方式导入装配数据
		* @param i_pCustomContainer 文档
		* @param i_FullFileName 导入文件
		* @param o_ModelBodyVec 几何
		* @param strLayerName 分组名称
		* @param LayerIndexVec 分组包含关系
		* @param LayerTpye 组类型
		*/
		virtual NctiGeometryResult import_file_assemble(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			std::vector<std::vector<NCTI_MODEL_TAG>>& o_ModelBodyVec,
			std::vector<std::string>& strLayerName,
			std::vector<std::vector<int>>& LayerIndexVec,
			std::vector<int >& LayerTpye);
		/*
		* @brief 导入装配数据
		* @param i_pCustomContainer 文档
		* @param i_FullFileName 导入文件
		* @param container 装配数据
		*/
		virtual NctiGeometryResult import_file_assemble(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			std::shared_ptr<NctiAssembly>& container);
		 /*
         * @brief 
         * @param i_pCustomContainer
         * @param i_FModelBody 被切割对象
         * @param i_SModelBodyVec 切割对象
		 * @param o_ModelBodyVec 切割后所有剩余部分
		 */
		virtual NctiGeometryResult object_cut(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_FModelBody,
			const std::vector <NCTI_MODEL_TAG>& i_SModelBodyVec,
			std::vector <NCTI_MODEL_TAG>& o_ModelBodyVec);

		/*
		* @brief 获取面上点、法向数据
		* @param i_pCustomContainer
		* @param i_TargeBody 对象
		* @param i_FaceCell 子对象面
		* @param  i_num_u U方向数量
		* @param  i_num_v V方向数量
		* @param  o_resultVec 输出是否在面上
		* @param  i_reverse 是否反转
		* @param  o_ptVec 输出点
		* @param  o_vecVec 输出法向
		*/
		virtual NctiGeometryResult uv_position_perform_pt_normal(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell,
			Ncti_Integer i_num_u,
			Ncti_Integer i_num_v,
			std::vector<std::vector < Ncti_Boolean>>& o_resultVec,
			Ncti_Boolean i_reverse,
			std::vector < std::vector < NctiPosition>>& o_ptVec,
			std::vector < std::vector < NctiVector>>& o_vecVec);
		virtual NctiGeometryResult edge_ai(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_Edge,
			NCTI_MODEL_TAG i_FFaceCell, 
			NCTI_MODEL_TAG i_SFaceCell, 
			Ncti_Boolean i_reverse,
			const std::vector<Ncti_Double>& i_abVec,
			std::vector<NctiPosition>& o_EdgePtVec,
			std::vector<NctiVector>& o_EdgeTangentVec,
			std::vector<NctiVector>& o_FFaceNormalVec,
			std::vector<NctiVector>& o_SFaceNoramlaVec);
		/*
		* @brief 文件格式转换
		* @param i_pCustomContainer PK文档
		* @param i_FullFileName 需要转换个文件
		* @param o_FullFileName 转换后的文件
		*/
		virtual NctiGeometryResult convert_file(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			const Ncti_Char* o_FullFileName);

		/*
		* @brief 寻找模型正面法向
		* @param i_pCustomContainer 文档
		* @param i_faces 输入面
		* @param o_norm 正面法向
		*/
		virtual NctiGeometryResult calc_front_norm(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            std::map<NCTI_MODEL_TAG, std::vector<NCTI_MODEL_TAG>>i_faces,
            NctiVector& o_norm);
		/*
		* @brief 点在模型内判断
		* @param i_pCustomContainer 文档
		* @param i_pBody 输入对象
		* @param i_Pts 判断点
		* @param o_Pts 输出内部点
		*/
		virtual NctiGeometryResult check_point_in_model(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody, 
			const std::vector<NctiPosition>& i_Pts,
			const Ncti_Double& dTol,
			std::vector<NctiPosition>& o_Pts);
		/*
	   * @brief 获取实体的方向外包盒
	   * @param i_pCustomContainer 文档类型
	   * @param i_pModelBodyVec 实体数组
	   * @param io_axis 包围盒坐标轴
	   * @param o_XSize 包围盒X轴方向尺寸
	   * @param o_YSize 包围盒Z轴方向尺寸
	   * @param o_ZSize 包围盒Z轴方向尺寸
	   */
		virtual NctiGeometryResult get_oriented_bounding_box(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pModelBodyVec,
			NctiAxis& o_axis,
			Ncti_Double& o_XSize,
			Ncti_Double& o_YSize,
			Ncti_Double& o_ZSize);
		/*
		* @brief 获取单元的方向外包盒
		* @param i_pCustomContainer 文档类型
		* @param i_pModelBodyVec 实体数组
		* @param i_CellVec 单元的ID
		* @param io_axis 包围盒坐标轴
		* @param o_XSize 包围盒X轴方向尺寸
		* @param o_YSize 包围盒Z轴方向尺寸
		* @param o_ZSize 包围盒Z轴方向尺寸
		*/
		virtual NctiGeometryResult get_cell_oriented_bounding_box(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			std::vector<NCTI_MODEL_TAG>& i_CellVec,
			NctiAxis& o_axis,
			Ncti_Double& o_XSize,
			Ncti_Double& o_YSize,
			Ncti_Double& o_ZSize);
		/*
		* @brief 获取面在指定位置的最大最小曲率
		* @param i_pCustomContainer 文档类型
		* @param i_pModelBody 实体
		* @param i_FaceCell 面的ID
		* @param i_U U值
		* @param i_V V值
		* @param o_MinCurvature 返回在指定UV位置的最小曲率
		* @param o_MaxCurvature 返回在指定UV位置的最大曲率
		*/
		virtual NctiGeometryResult get_face_curvature(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_FaceCell,
			Ncti_Double& i_U,
			Ncti_Double& i_V,
			Ncti_Double& o_MinCurvature,
			Ncti_Double& o_MaxCurvature);
		/*
		* @brief 获取边的长度
		* @param i_pCustomContainer 文档类型
		* @param i_pModelBody 实体
		* @param i_EdgeCell 边的ID
		* @param o_Length 长度
		*/
		virtual NctiGeometryResult get_edge_length(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_EdgeCell,
			Ncti_Double& o_Length);
		/*
		* @brief 获取指定点的UV值
		* @param i_pCustomContainer 文档类型
		* @param i_pModelBody 实体
		* @param i_Cell 单元ID
		* @param i_pos 点坐标
		* @param o_U u值
		* @param o_V v值
		*/
		virtual NctiGeometryResult get_uv_at_point(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_Cell,
			NctiPosition& i_pos,
			Ncti_Double& o_U,
			Ncti_Double& o_V);

		/*
		* @brief meshgems中曲面定义的回调函数
		* @param i_pCustomContainer 文档
		* @param i_pSurface 输入的surface对象
		* @param i_pUV 输入的U、V参数值
		* @param o_pXYZ 输出i_pUV对应的坐标值
		* @param o_pDU 输出U方向的偏导
		* @param o_pDV 输出V方向的偏导
		* @param o_pDUU 输出U方向的二阶偏导
		* @param o_pDUV 输出U、V方向的二阶偏导
		* @param o_pDVV 输出V方向的二阶偏导
		*/
		virtual NctiGeometryResult meshgems_surf_definition_callback(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSurface,
			double* i_pUV,
			double* o_pXYZ,
			double* o_pDU,
			double* o_pDV,
			double* o_pDUU,
			double* o_pDUV,
			double* o_pDVV);

		/*
		* @brief meshgems中曲线定义的回调函数
		* @param i_pCustomContainer 文档
		* @param i_pSurface 输入的surface对象，如果不为nullptr时，定义曲面上的spcurve，如果为nullptr时，定义3D曲线
		* @param i_pCurve 输入的curve对象
		* @param i_t 参数值
		* @param o_pCoord 如果是2d曲线，输出是U、V值；如果是3d曲线，输出是X、Y、Z值
		* @param o_pDT 一阶导数
		* @param o_pDTT 二阶导数
		*/
		virtual NctiGeometryResult meshgems_curve_definition_callback(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSurface,
			NCTI_MODEL_TAG i_pCurve,
			double i_t,
			double* o_pCoord,
			double* o_pDT,
			double* o_pDTT);

		/*
		* @brief meshgems中获取face对象数据
		* @param i_pCustomContainer 文档
		* @param i_pOwningBody 输入的BODY对象
		* @param i_vtFaces 输入的Face对象数组
		* @param o_vtFaceData 输出的Face数据数组
		* @param o_pClampedData 输出的被钳住的数据
		*/
		virtual NctiGeometryResult meshgems_get_faces_data(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pOwningBody,
			const std::vector<NCTI_MODEL_TAG>& i_vtFaces,
			std::vector<Meshgems_Face_data>& o_vtFaceData,
			meshgems_clamped_data*& o_pClampedData
		);
		/*
		* @brief 导出文件时增加配置导出选项
		* @param i_pCustomContainer 文档
		* @param i_FullFileName 导出文件路径
		* @param i_ModelBodyVec 输入的ModelBody对象数组
		* @param i_opt 输出文件配置，默认无配置为-1，1为支持non_manifold非流形
		*/
		virtual NctiGeometryResult export_file_with_opt(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
			const Ncti_Integer& i_opt);
		/*
		* @brief 导出对象时，简化拓扑结构
		* @param i_pCustomContainer 文档
		* @param i_ModelBody， 输入对象
		* @param o_ModelBody， 输出对象
		*/
		virtual NctiGeometryResult simplify_topo(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_ModelBody,
			NCTI_MODEL_TAG& o_ModelBody
			);

		/*
		* @brief 通过输入BODY中的两组指定边线或者面片，缝合其中的缝隙
		* @param i_pCustomContainer		文档
		* @param i_vtCells				输入对象中的cell集合
		* @param i_vtMatchedCells		输入对象中匹配的的cell集合
		* @param i_fSewTolerance		输入缝合容差
		* @param o_pModelBody，			输出的BODY对象
		*/
		virtual NctiGeometryResult body_sew_or_knit_cells(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_vtCells,
			const std::vector<NCTI_MODEL_TAG>& i_vtMatchedCells,
			double i_fSewTolerance,
			NCTI_MODEL_TAG& o_pModelBody
		);

		/*
		* @brief 搜索BODY中异常的对象
		* @param i_pCustomContainer		文档
		* @param i_pModelBody			输入对象
		* @param i_vtAbnormalCellType	输入的异常类型
		* @param i_critical_value		输入异常Cell临界值
		* @param o_vtAbnormalCells		输出相应的对象集合
		*/
		virtual NctiGeometryResult search_abnormal_cells(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			const std::vector<Ncti_AbnormalCell_Type>& i_vtAbnormalCellType,
			const AbnormalCellCriticalValue& i_critical_value,
			std::vector<std::vector<NCTI_MODEL_TAG> >& o_vtAbnormalCells
		);
		/*
		* @brief 对BODY中闭合的面进行分割
		* @param i_pCustomContainer		文档
		* @param i_pModelBody			输入对象集合
		* @param i_splitPointNum		面分割增加的分割点个数，需要>=1
		* @param o_vtModelBody			输出相应的对象集合
		*/
		virtual NctiGeometryResult divide_closed_face(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pModelBody,
			Ncti_Integer i_splitPointNum,
			std::vector<NCTI_MODEL_TAG>& o_vtModelBody);
		/*
		* @brief 各body间共面face的edge映射
		* @param i_pCustomContainer		文档
		* @param i_ModelBodyVec			输入对象集合
		* @param o_ModelBodyVec		    输出相应的对象集合
		*/
		virtual NctiGeometryResult mapping_edge(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector <NCTI_MODEL_TAG>& i_sModelBodyVec, 
			std::vector <NCTI_MODEL_TAG>& o_ModelBodyVec);
		/*
		* @brief 移除曲面的裁剪边界，返回一个没有裁剪的完整曲面
		* @param i_pCustomContainer		文档
		* @param i_ModelBody			输入对象
		* @param i_vtFace				输入的Face对象
		* @param o_ModelBody		    输出相应的对象
		*/
		virtual NctiGeometryResult remove_trimmed_surface(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pOwningBody,
			NCTI_MODEL_TAG i_vtFace,
			NCTI_MODEL_TAG& o_ModelBody);

		/*
		* @brief 放置基本图形，如：圆、矩形等等
		* 放置平面局部坐标系的计算原则：1、计算i_pReferenceEdge的起点及其对应的切向，并以该起点处作为局部坐标系的原点，
										   局部坐标系的Z轴为该切向；
		*								2、如果i_pReferenceFace1、i_pReferenceFace2都不为空，则计算i_pReferenceFace1、i_pReferenceFace2在
										   局部坐标系原点处的法向，计算这两个法向的夹角的角平分线向量，并以该向量作为局部坐标系的Y轴方向
		*								3、如果i_pReferenceFace1、i_pReferenceFace2只有其中一个不为空，则计算这个Face在
										   局部坐标系原点处的法向，并以该向量作为局部坐标系的X轴方向
										4、如果i_pReferenceFace1、i_pReferenceFace2都为空，则获取i_pReferenceEdge所对应的Face，再按照2、3的
										   方法计算局部坐标系的X轴方向。如果i_pReferenceEdge没有对应的Face，则局部坐标系的X轴方向不确定
		* @param i_pCustomContainer		文档
		* @param i_pReferenceEdge		参考Edge
		* @param i_pReferenceFace1		参考Face
		* @param i_pReferenceFace2		参考Face
		* @param i_nShapeType			图形类型	0 : 圆形	1 : 矩形
		* @param i_vtDimension			尺寸列表	比如圆只有一个半径，矩形X、Y轴方向的尺寸依次输入
		* @param i_vCenterOffset		中心点偏移	只考虑在局部坐标系的X、Y方向上的偏移
		* @param i_fRotateAngle			绕过局部坐标系原点Z轴方向的旋转角度
		* @param o_pShape				输出的基本图形BODY
		*/
		virtual NctiGeometryResult place_primitive_shape(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_pReferenceEdge,
			NCTI_MODEL_TAG i_pReferenceFace1,
			NCTI_MODEL_TAG i_pReferenceFace2,
			int i_nShapeType,
			const std::vector<Ncti_Double>& i_vtDimension,
			const NctiVector& i_vCenterOffset,
			double i_fRotateAngle,
			NCTI_MODEL_TAG& o_pShape);

		/*
		 * @brief 通过uv值获取面上的点、法向数据
		 * @param i_pCustomContainer 文档类型
		 * @param i_TargeBody 目标对象
		 * @param i_ModelFace 输入目标对象上的面
		 * @param i_u_value 面上u值(归一化)
		 * @param i_v_value 面上v值（归一化）
		 * @param o_Point 输出点
		 * @param o_Vector 输出法向
		 * @param o_bRes 输出点是否在面上
		 */
		virtual NctiGeometryResult get_position_normal_on_face_by_uv(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_ModelFace,
			Ncti_Double i_u_value,
			Ncti_Double i_v_value,
			NctiPosition& o_Point,
			NctiVector& o_Vector,
			Ncti_Boolean& o_bRes);

		/*
		 * @brief 实体加厚函数：返回加厚后的新实体(面加厚对象)
		 * @param i_pCustomContainer 文档类型
		 * @param i_sourceBody 输入对象
		 * @param i_ModelFaceVec 输入对象面，可以为空
		 * @param i_OffsetDistance 厚度
		 * @param i_Tolerance 精度
		 * @param o_targetBody 返回加厚后的新实体
		 */
		virtual NctiGeometryResult thicken_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_sourceBody,
			const std::vector<NCTI_MODEL_TAG>& i_ModelFaceVec,
			Ncti_Double i_offsetDistance,
			Ncti_Double i_tolerance,
			NCTI_MODEL_TAG& o_targetBody);
		/*
		 * @brief 获取曲线交点
		 * @param i_pCustomContainer 文档类型
		 * @param i_ModelBody1 输入曲线对象1
		 * @param i_ModelBody2 输入曲线对象2
		 * @param o_intersectionPoint 返回交点
		 */
		virtual NctiGeometryResult is_curve_intersection(
			NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG  i_ModelBody1, 
			NCTI_MODEL_TAG  i_ModelBody2, 
			std::vector<NctiPosition>& o_intersectionPoint);

		/*
		 * @brief 反转几何体中指定多个面的法向（其余面完全不变）
		 * @param i_pCustomContainer 文档类型
		 * @param i_sourceBody 输入对象
		 * @param i_ModelFaceVec 输入对象面
		 * @param o_targetBody 返回加厚后的新实体
		 */
		virtual NctiGeometryResult reverse_specified_faces(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_sourceBody,
			const std::vector<NCTI_MODEL_TAG>& i_ModelFaceVec,
			NCTI_MODEL_TAG& o_targetBody);

		/*
		 * @brief 创建等斜度曲线
		 * @param i_pCustomContainer 文档类型
		 * @param i_pSourceBody 输入对象
		 * @param i_vtSourceFace 输入对象面
		 * @param i_vDirection	方向
		 * @param i_fAngle	等斜角度（以角度计算）
		 * @param i_fAngleWidth	等斜度线宽度(以角度值度量)，可以为0
		 * @param i_fTolerance	偏差
		 * @param o_vtIsoClineCurves 返回的等斜度曲线集合
		 */
		virtual NctiGeometryResult make_isocline_curve(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			const std::vector<NCTI_MODEL_TAG>& i_vtSourceFace,
			const NctiVector& i_vDirection,
			double i_fAngle,
			double i_fAngleWidth,
			double i_fTolerance,
			std::vector<std::vector<NCTI_MODEL_TAG> >& o_vtIsoClineCurves);
	};
}
#endif
