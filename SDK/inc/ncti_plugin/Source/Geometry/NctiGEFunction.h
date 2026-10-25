#ifndef NctiGEFunction_H
#define NctiGEFunction_H
#include "NctiGEFunctionInterface.h"
namespace NCTI
{
	class DECL_NCTI_PLUGIN NctiGEFunction
	{
	public:
		NctiGEFunction();
		virtual ~NctiGEFunction();
	public:
		static NctiGeometryResult uv_position_perform(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell,
			Ncti_Double i_u,
			Ncti_Double i_v,
			Ncti_Integer& o_result,
			Ncti_Boolean i_reverse);
		static NctiGeometryResult uvs_find(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_edge,
			NCTI_MODEL_TAG i_face,
			const std::vector<Ncti_Double>& i_params,
			std::vector<NctiPosition>& o_pts,
			Ncti_Boolean i_reverse);
		static NctiGeometryResult is_close(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_cell,
			Ncti_Boolean& o_isClose,
			Ncti_Boolean i_reverse);
		static NctiGeometryResult get_faces_same_radius(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Cell,
			std::vector<NCTI_MODEL_TAG>& o_Cells
		);
		static NctiGeometryResult find_nearest_face_by_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NCTI_MODEL_TAG>& i_ModelFaceVec,
			const std::vector<NctiPosition>& i_PointVec,
			std::vector<NCTI_MODEL_TAG>& o_ModelFaceVec
		);
		static NctiGeometryResult get_face_cell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			std::vector<NCTI_MODEL_TAG>& o_CellVec);
		static NctiGeometryResult remove_face(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NCTI_MODEL_TAG>& i_FaceCellVec,
			NCTI_MODEL_TAG& o_ResultBody);
		static NctiGeometryResult split_face(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NCTI_MODEL_TAG>& i_FaceCellVec,
			std::vector<NCTI_MODEL_TAG>& o_FaceVec,
			NCTI_MODEL_TAG& o_ResultBody);
		static NctiGeometryResult fill_loop(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NCTI_MODEL_TAG>& i_EdgeCellVec,
			NCTI_MODEL_TAG& o_ResultBody);
		static NctiGeometryResult explode(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			std::vector<NCTI_MODEL_TAG>& o_ResultBodyVec);
		static NctiGeometryResult extract_bounds(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_Cell,
			NctiGeomBounds& o_bounds);
		static NctiGeometryResult extract_prop(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell,
			NctiGeomProp& o_geomProp);
		static NctiGeometryResult pick_ray(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell,
			const NctiPosition& i_posRay,
			const NctiVector& i_uvecRay,
			Ncti_Double& o_u,
			Ncti_Double& o_v);
		static NctiGeometryResult IsEnclosed(
			NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG i_TargeBody, 
			NCTI_MODEL_TAG i_TargeBodyTool);
		static NctiGeometryResult add_attribute_cell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NctiRenderSegmentItem* i_pSegment);
		static NctiGeometryResult get_attribute_cell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_Cell,
			NctiRenderSegmentItem*& o_pSegment);
		static NctiGeometryResult import_file(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec,
			int i_nUniteMode = 1);
		static NctiGeometryResult import_file_assemble(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			std::vector<std::vector<NCTI_MODEL_TAG>>& o_ModelBodyVec,
			std::vector<std::string>& strLayerName,
			std::vector<std::vector<int>>& LayerIndexVec,
			std::vector<int >& LayerTpye);
		static NctiGeometryResult import_file_assemble(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			std::shared_ptr<NctiAssembly>& container);
		static NctiGeometryResult object_cut(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_FModelBody,
			const std::vector <NCTI_MODEL_TAG>& i_SModelBodyVec,
			std::vector <NCTI_MODEL_TAG>& o_ModelBodyVec);
		static NctiGeometryResult uv_position_perform_pt_normal(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_FaceCell,
			Ncti_Integer i_num_u,
			Ncti_Integer i_num_v,
			std::vector<std::vector < Ncti_Boolean>>& o_resultVec,
			Ncti_Boolean i_reverse,
			std::vector < std::vector < NctiPosition>>& o_ptVec,
			std::vector < std::vector < NctiVector>>& o_vecVec);
		static NctiGeometryResult edge_ai(
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
		static NctiGeometryResult convert_file(
				NctiDisplayDocCustomContainer* i_pCustomContainer,
				const Ncti_Char* i_FullFileName,
				const Ncti_Char* o_FullFileName);
        static NctiGeometryResult calc_front_norm(
			NctiDisplayDocCustomContainer* pCusDoc,
            std::map<NCTI_MODEL_TAG,std::vector<NCTI_MODEL_TAG>>faces,
            NctiVector& o_norm);
		static NctiGeometryResult check_point_in_model(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NctiPosition>& i_Pts,
			const Ncti_Double& dTol,
			std::vector<NctiPosition>& o_Pts);
		static NctiGeometryResult get_oriented_bounding_box(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pModelBodyVec,
			NctiAxis& o_axis,
			Ncti_Double& o_XSize,
			Ncti_Double& o_YSize,
			Ncti_Double& o_ZSize);
		static NctiGeometryResult get_cell_oriented_bounding_box(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			std::vector<NCTI_MODEL_TAG>& i_CellVec,
			NctiAxis& o_axis,
			Ncti_Double& o_XSize,
			Ncti_Double& o_YSize,
			Ncti_Double& o_ZSize);
		static NctiGeometryResult get_face_curvature(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_FaceCell,
			Ncti_Double& i_U,
			Ncti_Double& i_V,
			Ncti_Double& o_MinCurvature,
			Ncti_Double& o_MaxCurvature);
		static NctiGeometryResult get_edge_length(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_EdgeCell,
			Ncti_Double& o_Length);
		static NctiGeometryResult get_uv_at_point(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_Cell,
			NctiPosition& i_pos,
			Ncti_Double& o_U,
			Ncti_Double& o_V);
		static NctiGeometryResult meshgems_surf_definition_callback(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSurface,
			double* i_pUV,
			double* o_pXYZ,
			double* o_pDU,
			double* o_pDV,
			double* o_pDUU,
			double* o_pDUV,
			double* o_pDVV);

		static NctiGeometryResult meshgems_curve_definition_callback(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSurface,
			NCTI_MODEL_TAG i_pCurve,
			double i_t,
			double* o_pCoord,
			double* o_pDT,
			double* o_pDTT);

		static NctiGeometryResult meshgems_get_faces_data(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pOwningBody,
			const std::vector<NCTI_MODEL_TAG>& i_vtFaces,
			std::vector<Meshgems_Face_data>& o_vtFaceData,
			meshgems_clamped_data*& o_pClampedData);
		static NctiGeometryResult export_file_with_opt(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
			const Ncti_Integer& i_opt);
		static NctiGeometryResult simplify_topo(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_ModelBody,
			NCTI_MODEL_TAG& o_ModelBody
		);

		static NctiGeometryResult body_sew_or_knit_cells(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_vtCells,
			const std::vector<NCTI_MODEL_TAG>& i_vtMatchedCells,
			double i_fSewTolerance,
			NCTI_MODEL_TAG& o_pModelBody
		);

		static NctiGeometryResult search_abnormal_cells(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			const std::vector<Ncti_AbnormalCell_Type>& i_vtAbnormalCellType,
			const AbnormalCellCriticalValue& i_critical_value,
			std::vector<std::vector<NCTI_MODEL_TAG> >& o_vtAbnormalCells
		);
		static NctiGeometryResult divide_closed_face(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pModelBody,
			Ncti_Integer i_splitPointNum,
			std::vector<NCTI_MODEL_TAG>& o_vtModelBody);

		static NctiGeometryResult mapping_edge(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector <NCTI_MODEL_TAG>& i_sModelBodyVec,
			std::vector <NCTI_MODEL_TAG>& o_ModelBodyVec);

		static NctiGeometryResult remove_trimmed_surface(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pOwningBody,
			NCTI_MODEL_TAG i_vtFace,
			NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult place_primitive_shape(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NCTI_MODEL_TAG i_pReferenceEdge,
			NCTI_MODEL_TAG i_pReferenceFace1,
			NCTI_MODEL_TAG i_pReferenceFace2,
			int i_nShapeType,
			const std::vector<Ncti_Double>& i_vtDimension,
			const NctiVector& i_vCenterOffset,
			double i_fRotateAngle,
			NCTI_MODEL_TAG& o_pShape);

		static NctiGeometryResult get_position_normal_on_face_by_uv(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_ModelFace,
			Ncti_Double i_u_value,
			Ncti_Double i_v_value,
			NctiPosition& o_Point,
			NctiVector& o_Vector,
			Ncti_Boolean& o_bRes);

		static NctiGeometryResult thicken_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_sourceBody,
			const std::vector<NCTI_MODEL_TAG>& i_ModelFaceVec,
			Ncti_Double i_offsetDistance,
			Ncti_Double i_tolerance,
			NCTI_MODEL_TAG& o_targetBody);

		static NctiGeometryResult is_curve_intersection(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG  i_ModelBody1,
			NCTI_MODEL_TAG  i_ModelBody2,
			std::vector<NctiPosition>& o_intersectionPoint);

		static NctiGeometryResult reverse_specified_faces(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_sourceBody,
			const std::vector<NCTI_MODEL_TAG>& i_ModelFaceVec,
			NCTI_MODEL_TAG& o_targetBody);

		static NctiGeometryResult make_isocline_curve(
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
