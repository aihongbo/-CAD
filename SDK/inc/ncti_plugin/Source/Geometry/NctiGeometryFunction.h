#ifndef NctiGeometryFunction_H
#define NctiGeometryFunction_H
#include "ncti_base.h"
#include "dcl_ncti_plugin.h"
#include "NctiModelFunctionResult.h"
#include "NctiGeometryFunctionInterface.h"
namespace NCTI
{
	class NctiDisplayDocCustomContainer;
	class NctiBaseModel;
	class NctiVector;
	class DECL_NCTI_PLUGIN NctiGeometryFunction
	{
	public:
		NctiGeometryFunction();
		virtual ~NctiGeometryFunction();
	public:
		static NctiGeometryResult import_file(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec, 
			int i_nUniteMode = 1);
		static NctiGeometryResult export_file(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);

		static NctiGeometryResult create_box(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiPosition& i_pos,
			Ncti_Double i_len,
			Ncti_Double i_width,
			Ncti_Double i_height,
			NCTI_MODEL_TAG& o_ModelBody);

        static NctiGeometryResult isos(
            NctiDisplayDocCustomContainer *i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Integer i_geom,
            NCTI_MODEL_TAG &o_ModelBody);

        static NctiGeometryResult tclean(
            NctiDisplayDocCustomContainer *i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Boolean i_geom,
            Ncti_Boolean i_force,
            NCTI_MODEL_TAG &o_ModelBody);

		static NctiGeometryResult boolean_unit(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_FModelBody,
			NCTI_MODEL_TAG i_SModelBody,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult fillet_body(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG& o_ResultBody,
			const std::vector<NCTI_MODEL_TAG>& i_EdgeVec,
			const std::vector<Ncti_Double>& i_raduis);
		static NctiGeometryResult create_line(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiPosition& i_pos, 
			const NctiPosition& i_pos2,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult get_edge_mid_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_ModelEdge,
			NctiPosition& o_MidPoint);
		static NctiGeometryResult get_edge_point_from_u(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_ModelEdge,
			Ncti_Double i_u,
			NctiPosition& o_Point);
		static NctiGeometryResult find_nearest_edge_by_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NctiPosition>& i_PointVec,
			std::vector<NCTI_MODEL_TAG>& o_ModelEdgeVec);
        static NctiGeometryResult find_all_edge(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			std::vector<NCTI_MODEL_TAG>& o_ModelEdgeVec);
        static NctiGeometryResult find_all_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            std::vector<NCTI_MODEL_TAG>& o_ModelEdgeVec);
        static NctiGeometryResult find_all_vertex(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            std::vector<NCTI_MODEL_TAG>& o_ModelEdgeVec);
		static NctiGeometryResult middle_path(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG i_start,
            NCTI_MODEL_TAG i_end,
            NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult chfi2d(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_source, Ncti_Integer mode,
			const std::vector<NCTI_MODEL_TAG>& i_eid,
			const std::vector <Ncti_Double> i_len,
            NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult cal_distance_edge_and_pt(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_ModelEdge,
			const NctiPosition& i_Point,
			Ncti_Double& o_Distance);
		static NctiGeometryResult create_sphere(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			Ncti_Double i_Radius,
			Ncti_Double i_angle1,
			Ncti_Double i_angle2,
			Ncti_Double i_angle3,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult create_cylinder(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Double i_Radius,
			Ncti_Double i_Height,
			const NctiAxis& i_Axis,
			Ncti_Double i_Angle,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult create_cone(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Double i_BottomRadius,
			Ncti_Double i_TopRadius,
			Ncti_Double i_Height,
			const NctiAxis& i_Axis,
			Ncti_Double i_Angle,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult boolean_cut(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_FModelBody,
			NCTI_MODEL_TAG i_SModelBody,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult boolean_common(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_FModelBody,
			NCTI_MODEL_TAG i_SModelBody,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult pan_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Double i_panx,
			Ncti_Double i_pany,
			Ncti_Double i_panz,
			NCTI_MODEL_TAG& io_SModelBody);
		static  NctiGeometryResult scale_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiPosition OringePt,
			NctiVector i_scale,
			NCTI_MODEL_TAG& io_SModelBody);
		static  NctiGeometryResult scale_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiPosition OringePt,
			Ncti_Double i_scale,
			NCTI_MODEL_TAG& io_SModelBody);
		static NctiGeometryResult create_bezier_curve(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NctiPosition>& i_ControlPts,
			const std::vector<Ncti_Double>& i_WeightPts,
			NCTI_MODEL_TAG& o_bezierCurve);
		static NctiGeometryResult create_model_doc(
			EnumModelDoc i_modelDoc,
			NctiBaseModel* i_pBaseModel,
			NctiDisplayDocCustomContainer*& o_pCustomContainer);
		static  NctiGeometryResult create_circle(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			Ncti_Double i_radius,
			NCTI_MODEL_TAG& o_modelBody);
		static  NctiGeometryResult create_wire(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_EdgesBody,
			NCTI_MODEL_TAG& o_modelBody);
		static  NctiGeometryResult revolve_operate(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSrcModelBody,
			const NctiPosition& i_pntRotateCenter,
			const NctiVector& i_vRotateAxis,
			Ncti_Double i_fRotateAngle,
			NCTI_MODEL_TAG& o_modelBody);
        static  NctiGeometryResult fix_small_edges(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSrcModelBody,
			Ncti_Double i_tolrence,
			Ncti_Double i_limitAngle,
            NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult fix_small_faces(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_tol,
            NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult fix_shape(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
			Ncti_Geo_Fixshape i_config,
            NCTI_MODEL_TAG& o_ModelBody);
        static NctiGeometryResult fix_continuity(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
			Ncti_Double i_tol,
            NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult fix_tolerance(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            NCTI_MODEL_TAG& o_ModelBody);
        static NctiGeometryResult fix_gaps(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
            Ncti_Double i_precision,
            NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult fix_small_solids(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
			Ncti_Double i_volume,
            Ncti_Double i_width,
			Ncti_Boolean i_merge,
            NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult extract_prop(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			NctiGeomProp& o_geomProp);
		static NctiGeometryResult rotate_body(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiPosition& i_pntBase,
			const NctiVector& i_vector,
			Ncti_Double i_Angle,
			std::vector<NCTI_MODEL_TAG>& io_pModelBodyVec);
		static NctiGeometryResult prism(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			const NctiVector& i_vector,
			NCTI_MODEL_TAG& o_pModelBody);
		static NctiGeometryResult mirror_body(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			const NctiPosition& i_pntBase,
			const NctiVector& i_vector,
			NCTI_MODEL_TAG& o_pModelBody);
		static NctiGeometryResult sewing_bodies(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pSewiedBodyVec,
			Ncti_Double i_tolerance, Ncti_Sewing_Params i_Params,
			NCTI_MODEL_TAG& o_pSewingBody);
		static NctiGeometryResult create_wedge(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			Ncti_Double i_dx,
			Ncti_Double i_dy,
			Ncti_Double i_dz,
			Ncti_Double i_xMin,
			Ncti_Double i_zMin,
			Ncti_Double i_xMax,
			Ncti_Double i_zMax,
			NCTI_MODEL_TAG& o_pSewingBody);
		static NctiGeometryResult create_pipe(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSpineBody,
			NCTI_MODEL_TAG i_pProfileBody, 
			NCTI_MODEL_TAG& o_pModelBody);
		static NctiGeometryResult create_torus(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			Ncti_Double i_rotateRadius,
			Ncti_Double i_sectionRadius,
			Ncti_Double i_sectionAngle1,
			Ncti_Double i_sectionAngle2,
			Ncti_Double i_rotateAngle,
			NCTI_MODEL_TAG& o_pModelBody);
		static NctiGeometryResult nurbs_convert(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG& o_pTargetBody);

		static NctiGeometryResult reverse_normal(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG& io_pModelBody);

		static NctiGeometryResult create_plane(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceWire, 
			const NctiAxis& i_Axis,
			NCTI_MODEL_TAG& o_pModelBody);

		static NctiGeometryResult create_polyline(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NctiPosition>& i_vtPoints,
			NCTI_MODEL_TAG& o_pModelBody);

		static NctiGeometryResult bspline_curve(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_degree,
			const std::vector<Ncti_Double>& i_Knots,
			const std::vector<Ncti_Integer>& i_Multiplicities,
			const std::vector<NctiPosition>& i_ControlPts,
			const std::vector<Ncti_Double>& i_Weights,
			Ncti_Boolean i_Period,
			NCTI_MODEL_TAG& o_pModelBody);

		static NctiGeometryResult create_vertex(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiPosition& i_Vertex,
			NCTI_MODEL_TAG& o_pModelBody);

		static NctiGeometryResult create_uviso(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			Ncti_Integer i_isoType,
			Ncti_Double i_paramValue,
			NCTI_MODEL_TAG& o_pTargetBody
			);

		static NctiGeometryResult depouille(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG& io_pBody,
			const NctiVector& i_vector,
			const std::vector<NCTI_MODEL_TAG>& i_pFaces,
			const std::vector<Ncti_Double>& i_dAngles,
			const std::vector<NctiPosition>& i_LeanCenterPts,
			const std::vector<NctiVector>& i_Normals);

		static NctiGeometryResult create_sub_edge(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			Ncti_Double i_paramFirstValue,
			Ncti_Double i_paramSecondValue,
			NCTI_MODEL_TAG& o_pTargetBody
		);
		static NctiGeometryResult create_sub_face(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			Ncti_Double i_u_paramFValue,
			Ncti_Double i_u_paramLValue,
			Ncti_Double i_v_paramFValue,
			Ncti_Double i_v_paramLValue,
			Ncti_Boolean i_LimitFace,
			NCTI_MODEL_TAG& o_pTargetBody
		);
		static NctiGeometryResult create_intersect_curve(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody1,
			NCTI_MODEL_TAG i_pSourceBody2,
			Ncti_Boolean i_bPCurveOnObj1,
			Ncti_Boolean i_bPCurveOnObj2,
			Ncti_Boolean i_bAppro,
			NCTI_MODEL_TAG& o_pTargetBody
		);
		static NctiGeometryResult create_half_space(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NctiPosition i_halfSpaceRef,
			NCTI_MODEL_TAG& o_pTargetBody);
		static  NctiGeometryResult create_make_face(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG i_pWire,
			NCTI_MODEL_TAG& o_pTargetBody
		);
		static NctiGeometryResult find_nearest_face_by_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NctiPosition>& i_PointVec,
			std::vector<NCTI_MODEL_TAG>& o_ModelFaceVec);
		static NctiGeometryResult get_point_on_face_by_uv(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_ModelFace,
			Ncti_Double i_u_value,
			Ncti_Double i_v_value,
			NctiPosition& o_Point);
		static NctiGeometryResult create_arc(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			Ncti_Double i_radius,
			Ncti_Double i_startAngle,
			Ncti_Double i_endAngle,
			NCTI_MODEL_TAG& o_pTargetBody
		);
		static NctiGeometryResult create_profile(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_EdgesVec,
			NCTI_MODEL_TAG i_ProfileBody,
			NCTI_MODEL_TAG i_ProfileFace,
			Ncti_Boolean i_onlyWire,
			NCTI_MODEL_TAG& o_modelBody
		);
		static  NctiGeometryResult transform_body(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Double i_mat[3][3],
			NCTI_MODEL_TAG& io_modelBody
		);
		static NctiGeometryResult get_closet_point_and_tangent(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Edge,
			const NctiPosition& i_point,
			NctiPosition& o_closetPoint,
			NctiVector& o_tangent
		);
		static NctiGeometryResult offset_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			const NctiVector& i_OffsetVector,
			double i_Distance,
			NCTI_MODEL_TAG& i_TargetBody
		);
		static NctiGeometryResult get_edge_point_and_tangent(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Edge,
			Ncti_Double i_param,
			NctiPosition& o_closetPoint,
			NctiVector& o_tangent,
			Ncti_Boolean i_isTangentNormalize = true
		);
		static NctiGeometryResult trim_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			Ncti_Double i_fU1,
			Ncti_Double i_fU2,
			Ncti_Double i_fV1,
			Ncti_Double i_fV2,
			Ncti_Boolean i_bUSense,
			Ncti_Boolean i_bVSense,
			NCTI_MODEL_TAG& o_TargetBody
		);
		static NctiGeometryResult split(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_FModelBodyVec,
			const std::vector<NCTI_MODEL_TAG>& i_SModelBodyVec,
			NCTI_MODEL_TAG& o_ModelBody
		); 
		static NctiGeometryResult periodic(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SrcBody,
			const std::vector<Ncti_Geo_Periodic>& i_PeriodicVec,
			NCTI_MODEL_TAG& o_TarBody
		);
		static NctiGeometryResult create_ellipse(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			const Ncti_Double& i_majorRadius,
			const Ncti_Double& i_minorRadius,
			NCTI_MODEL_TAG& o_TargetBody
		);
		static NctiGeometryResult create_compound(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			std::vector<NCTI_MODEL_TAG> i_SourceBodys,
			NCTI_MODEL_TAG& o_TargetBody
		);
		static NctiGeometryResult add_object(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SModelBody,
			NCTI_MODEL_TAG i_TModelBody,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult feat_dprism(
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
			NCTI_MODEL_TAG& o_pReturnBody
		);
		static NctiGeometryResult create_tangent(
			NctiDisplayDocCustomContainer* pSDDisplayDocCustomContainer,
			NCTI_MODEL_TAG i_EdgeTag1,
			NCTI_MODEL_TAG i_EdgeTag2,
			Ncti_Double i_Angle,
			std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec);
		static NctiGeometryResult feat_prism(
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
			NCTI_MODEL_TAG& o_pReturnBody
		);
		static NctiGeometryResult offset_face(
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
			Ncti_Boolean i_removeIntEdge
		);
		static NctiGeometryResult feat_Revol(
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
			NCTI_MODEL_TAG& o_pReturnBody
		);
		static NctiGeometryResult get_vertex_pnt(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSrcTargetBody,
			NCTI_MODEL_TAG i_vertexTag,
			NctiPosition& o_pnt
		);
		static  NctiGeometryResult get_edge_end_points(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSrcTargetBody,
			NCTI_MODEL_TAG i_edge_tag,
			NctiPosition& o_pnt_start,
			NctiPosition& o_pnt_end,
			NctiVector& o_tangent_start,
			NctiVector& o_tangent_end
		);
		static NctiGeometryResult feat_lienarform(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSrcTargetBody,
			NCTI_MODEL_TAG i_pSrcProfileWireObject,
			NCTI_MODEL_TAG i_pSrcPlaneObject,
			const NctiVector& i_vThicken1,
			const NctiVector& i_vThicken2,
			Ncti_Long i_nBooleanMode,
			Ncti_Long i_nOption,
			NCTI_MODEL_TAG& o_pReturnBody
		);
		static NctiGeometryResult feat_revolutionform(
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
			NCTI_MODEL_TAG& o_pReturnBody
		);
		static NctiGeometryResult make_sweep(
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
			NCTI_MODEL_TAG& o_Target
		);
		static NctiGeometryResult unifysamedom(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec, const Ncti_Geo_Unifysamedom& i_Config,
			NCTI_MODEL_TAG& o_Tag);
		static  NctiGeometryResult extract_cell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG i_pSourceCell,
			NCTI_MODEL_TAG& o_pTarget
		);
        static  NctiGeometryResult extract_solid(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
			std::vector<NCTI_MODEL_TAG>& i_pSourceCell,
            NCTI_MODEL_TAG& o_pTarget
        );
        static  NctiGeometryResult extract_wire(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            std::vector<NCTI_MODEL_TAG>& i_pSourceCell,
            NCTI_MODEL_TAG& o_pTarget
        );
		static NctiGeometryResult extract_bounds(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NctiGeomBounds& o_bounds);
		static  NctiGeometryResult extract_section(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody1,
			NCTI_MODEL_TAG i_SourceBody2,
			NCTI_MODEL_TAG& o_SectionBody);
		static NctiGeometryResult dump_topology(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			Ncti_Boolean i_LocDifferent,
			std::map<int, int>& o_Type_Nb
		);
		static NctiGeometryResult get_edge_value_by_param(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Edge,
			Ncti_Double i_param,
			NctiPosition& o_closetPoint,
			NctiVector& o_tangent,
			NctiVector& o_secDer,
			Ncti_Boolean i_isTangentNormalize = true
		);
		static NctiGeometryResult get_section_alone_vertex(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Cell,
			Ncti_Integer& o_alone
		);
		static NctiGeometryResult chamfer_body(NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG i_SourceBody,
			const std::vector<NCTI_MODEL_TAG>& i_EdgeVec,
			const std::vector<NCTI_MODEL_TAG>& i_FaceVec,
			const std::vector<Ncti_Double>& i_DistanceVec,
			const std::vector<Ncti_Double>& i_AngleVec,
			NCTI_MODEL_TAG& o_pTarget
			);
		static NctiGeometryResult fillet_evol_radius(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			const std::vector<Ncti_Geo_Evol_Radius>& i_EdgeParamVec,
			Ncti_Integer i_FilletMode,
			NCTI_MODEL_TAG& o_pTarget
		);
        static NctiGeometryResult same_parameter(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            Ncti_Double i_tol,Ncti_Boolean i_force,
            NCTI_MODEL_TAG& o_pTarget
        );
        static NctiGeometryResult split_number(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            Ncti_Integer i_num1, Ncti_Integer i_num2,
            NCTI_MODEL_TAG& o_pTarget
        );
        static NctiGeometryResult to_bspline(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            Ncti_Double i_tol3d, Ncti_Double i_tol2d,
			Ncti_Geo_Continue_Type i_continue3d, 
			Ncti_Geo_Continue_Type i_continue2d,
			Ncti_Integer i_degree,Ncti_Integer i_segment,
            NCTI_MODEL_TAG& o_pTarget
        );
        static NctiGeometryResult to_bezier(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_SourceBody,
            Ncti_Boolean i_3d, Ncti_Boolean i_2d,
            NCTI_MODEL_TAG& o_pTarget
        );
		static  NctiGeometryResult set_orientation(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Cell,
			Ncti_Integer i_Orientation,
			NCTI_MODEL_TAG& o_pTarget
		);
		static NctiGeometryResult make_approx_face(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<Ncti_Geo_Approx_Data>& i_approx_data,
			Ncti_Integer i_NPt,
			Ncti_Double i_tol3d,
			Ncti_Integer i_Nbmax,
			Ncti_Integer i_degmax,
			Ncti_Integer i_CritOrder,
			NCTI_MODEL_TAG& o_pTarget
		);
		static NctiGeometryResult make_face_by_surface(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			NCTI_MODEL_TAG i_Cell,
			NCTI_MODEL_TAG& o_pTarget
		);
		static NctiGeometryResult create_parabola(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			const Ncti_Double& i_focal,
			const Ncti_Double& i_firstParm,
			const Ncti_Double& i_lastParm,
			NCTI_MODEL_TAG& o_TargetBody
		);
		static NctiGeometryResult create_bspline_surf(
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
			NCTI_MODEL_TAG& o_Target
		);
		static NctiGeometryResult create_bezier_surf(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<std::vector<NctiPosition>>& i_ctrl_points,
			const std::vector<std::vector<Ncti_Double>>& i_weight,
			NCTI_MODEL_TAG& o_Target
		);
		static NctiGeometryResult create_hyperbola(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			const Ncti_Double& i_majorRadius,
			const Ncti_Double& i_minorRadius,
			const Ncti_Double& i_firstParm,
			const Ncti_Double& i_lastParm,
			NCTI_MODEL_TAG& o_TargetBody
		);
		static NctiGeometryResult thrusections(NctiDisplayDocCustomContainer*  pContainer,
			const std::vector<NCTI_MODEL_TAG>& i_Bodies,
			Ncti_Boolean isSolid,
			Ncti_Boolean isRuled, 
			Ncti_Boolean isNoCheckWires,
			Ncti_Boolean isSafe,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult create_circle3Tangent(NctiDisplayDocCustomContainer* pContainer,
			const std::vector<NCTI_MODEL_TAG>& i_Bodies,
			std::vector<NCTI_MODEL_TAG>& o_Bodies);
		static NctiGeometryResult extend_face(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pModelBody,
			const NctiVector& i_vector,
			NCTI_MODEL_TAG& o_pModelBody);
		static NctiGeometryResult get_boungding_box(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pModelBody,
			NctiPosition& o_ptMin,
			NctiPosition& o_ptMax);
		static NctiGeometryResult edges_project(NctiDisplayDocCustomContainer* pContainer,
			const std::vector<NCTI_MODEL_TAG>& i_Bodies,
			Ncti_Boolean i_LimitFace,
			Ncti_Double i_MaxDistance,
			Ncti_Double i_Tolerance,
			Ncti_Integer i_Continuity,
			Ncti_Integer i_MaxDeg,
			Ncti_Integer i_MaxSeg,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult modify_circle(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_modelBody,
			Ncti_Double i_radius,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult modify_ellipse(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_modelBody,
			Ncti_Double i_majorRadius,
			Ncti_Double i_minRadius,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult transform_body(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Double i_mat[4][4],
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult extend_curve(
			NctiDisplayDocCustomContainer* i_pContainer,
			NctiPosition i_pt,
			Ncti_Integer i_Continuity,
			Ncti_Boolean i_After,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult extend_surface(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Double i_Length,
			Ncti_Integer i_Continuity,
			Ncti_Boolean i_isU,
			Ncti_Boolean i_After,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult modify_bspline_curve(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_modelBody,
			const std::vector<NctiPosition>& i_ControlPts,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult get_normal_by_uv(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_ModelFace,
			Ncti_Double i_u_value,
			Ncti_Double i_v_value,
			NctiVector& o_Normal);
		static NctiGeometryResult find_nearest_vertex_by_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NctiPosition>& i_PointVec,
			std::vector<NCTI_MODEL_TAG>& o_ModelVertexVec);

		static NctiGeometryResult increase_bezier_bspline_curve_degree(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Long i_degree,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult increase_bezier_bspline_surf_degree(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Long i_udegree,
			Ncti_Long i_vdegree,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult insert_bspline_curve_knot(
			NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<Ncti_Double>& i_knotVec,
			const std::vector<Ncti_Long>& i_multVec,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult insert_bspline_surf_knot(
			NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<Ncti_Double>& i_uKnotVec,
			const std::vector<Ncti_Long>& i_uMultVec,
			const std::vector<Ncti_Double>& i_vKnotVec,
			const std::vector<Ncti_Long>& i_vMultVec,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult remove_bspline_curve_knot(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Long i_index,
			Ncti_Long i_mult,
			Ncti_Double i_tolerance,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult remove_bspline_surf_knot(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Long i_uIndex,
			Ncti_Long i_uMult,
			Ncti_Long i_vIndex,
			Ncti_Long i_vMult,
			Ncti_Double i_tolerance,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult move_bspline_curve_tangent(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Double i_u,
			const NctiPosition& i_point,
			const NctiVector& i_tangent,
			Ncti_Long i_constraint,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult move_bspline_curve_point(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Double i_u,
			const NctiVector& i_direct,
			Ncti_Long i_index1,
			Ncti_Long i_index2,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult move_bezier_bspline_surf_pole(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Long i_row,
			Ncti_Long i_col,
			const NctiVector& i_direct,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult convert_to_nurbs(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_modelBody,
			Ncti_Long i_convertMode,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult project_point(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_modelBody,
			const NctiPosition& i_point,
			Ncti_Long i_algo,
			std::vector<NCTI_MODEL_TAG>& o_modelBodyVec);
		static NctiGeometryResult extract_nearest_cell_by_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			const std::vector<NctiPosition>& i_PointVec,
			Ncti_Geo_Shape_Type i_FindType,
			std::vector<NCTI_MODEL_TAG>& o_ModelTagVec);

		static NctiGeometryResult make_tuyau(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_pPath,
			NCTI_MODEL_TAG i_pFirstCurve,
			NCTI_MODEL_TAG i_pLastCurve,
			Ncti_Double i_Radius,
			Ncti_Boolean i_NS,
			std::vector<NCTI_MODEL_TAG> i_vSequenceOfCurve,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult make_volume(
			NctiDisplayDocCustomContainer* i_pContainer,
			std::vector<NCTI_MODEL_TAG> i_pBodies,
			Ncti_Boolean i_bCompounds,
			Ncti_Boolean i_bToIntersect,
			Ncti_Boolean i_bAvoidInternal,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult make_faces_by_edges(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_modelBody,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult set_tolerance(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_modelBody,
			Ncti_Double i_value,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult multi_boolean_cut(
			NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<NCTI_MODEL_TAG> &i_FModelBodyVec,
			const std::vector<NCTI_MODEL_TAG> &i_SModelBodyVec,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult multi_boolean_common(
			NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<NCTI_MODEL_TAG> &i_FModelBodyVec,
			const std::vector<NCTI_MODEL_TAG> &i_SModelBodyVec,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult multi_boolean_unit(
			NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<NCTI_MODEL_TAG> &i_ModelBodyVec,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult create_multi_intersect_curve(
			NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
			NCTI_MODEL_TAG& o_modelBody);

		static  NctiGeometryResult create_empty_shape(
			NctiDisplayDocCustomContainer* i_pContainer,
			Ncti_Integer i_ShapeType,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult general_boolean_unit(
			NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult invert(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_ModelBody,
			NCTI_MODEL_TAG& o_modelBody);

		static NctiGeometryResult direct_faces(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody, NCTI_MODEL_TAG& o_ModelBody);

        static NctiGeometryResult split_angle(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
			Ncti_Double i_angle,
			Ncti_Double i_tol,
			NCTI_MODEL_TAG& o_ModelBody);

        static NctiGeometryResult split_closed(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody,
			Ncti_Integer i_nbPoints,
            Ncti_Double i_closeTol,
            Ncti_Double i_maxTol,
            NCTI_MODEL_TAG& o_ModelBody);

        static NctiGeometryResult to_revolution(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult remove_internal_boundaries(
			NctiDisplayDocCustomContainer* i_pContainer,
			std::vector<Ncti_RemoveInt_Item> &i_RemoveIntItemVec,
			NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult evolved_operate(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_SplineModelBody,
			NCTI_MODEL_TAG i_ProfileModelBody,
			Ncti_Boolean i_CloseSolid,
			Ncti_Boolean i_UseAlternativeAlgorithm,
			Ncti_Boolean i_HasToComputeAxes,
			NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult make_offset(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_SrcBody,
			Ncti_Integer i_NbOffset,
			Ncti_Double i_StepOffsetVal,
			Ncti_Boolean i_Approx,
			Ncti_Integer i_ConnectType,
			Ncti_Double i_Altitude,
			std::vector<NCTI_MODEL_TAG>& o_ModelTagVec);
		static NctiGeometryResult create_box(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis,
			Ncti_Double i_len,
			Ncti_Double i_width,
			Ncti_Double i_height,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult mini_distance(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_BodiesTagVec,
			Ncti_Double i_deflection,
			Ncti_Boolean i_multiThread,
			Ncti_Double& o_dist);
		static NctiGeometryResult cal_extrema(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_BodiesTagVec,
			Ncti_Geo_Extrema& o_ExtremaOutput);
		static NctiGeometryResult thick_shell(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			Ncti_Double dOffset,
			Ncti_Integer joinType,
			Ncti_Double dTol,
			NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult get_project_point(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_modelBody,
			const NctiPosition& i_point,
			Ncti_Long i_algo,
			std::vector<Ncti_Geo_Project_Point>& o_projectPointVec);
		static NctiGeometryResult extract_outwire(
			NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult fillet2d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pSourceBodyVec,
			Ncti_Integer i_mode,
			const std::vector<Ncti_Double> i_radiusOrLenVec,
			std::vector<NCTI_MODEL_TAG>& o_modelBodyVec);

		static NctiGeometryResult set_bezier_bspline_weight(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_uindex,
			Ncti_Integer i_vindex,
			Ncti_Double i_weight,
			NCTI_MODEL_TAG& io_modelBody);

        static NctiGeometryResult bsurf_create_fitted(
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
        static NctiGeometryResult bsurf_create_piecewise(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Integer i_u_degree,
            Ncti_Integer i_u_segments,
            Ncti_Integer i_v_degree,
            Ncti_Integer i_v_segments,
            Ncti_Boolean i_is_rational,
            Ncti_Integer i_rep,
            const std::vector<Ncti_Double>& i_coeffs,
            NCTI_MODEL_TAG& o_modelBody);
        static NctiGeometryResult bsurf_create_splinewise(
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
        static NctiGeometryResult bsurf_clamp_knots(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG& io_modelBody);
        static NctiGeometryResult create_trimmed_surf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceSurf,
            Ncti_Double i_u,
            Ncti_Double i_U,
            Ncti_Double i_v,
            Ncti_Double i_V,
            NCTI_MODEL_TAG& io_modelBody);

		static NctiGeometryResult repairShape(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			Ncti_Integer i_nMode,
			Ncti_Double i_dTol,
			NCTI_MODEL_TAG i_pSampleBody,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult create_null_shape(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult remove_features(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_SourceBody,
			std::vector<NCTI_MODEL_TAG> i_Faces,
			NCTI_MODEL_TAG& i_TargetBody);
        static NctiGeometryResult transform_face(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pFace,
            const Ncti_Double i_matrix[4][4],
            Ncti_Boolean i_flag,
            NCTI_MODEL_TAG& o_ModelBody);
        static NctiGeometryResult create_and_check_transf(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Boolean i_HasRotation,
            const NctiVector& i_axis,
            Ncti_Double i_angle,
            Ncti_Double i_scale,
            Ncti_Boolean i_HasMirror,
            const NctiPosition& i_planePos,
            const NctiVector& i_PlaneNormal,
            Ncti_Double o_matrix[4][4]);
        static NctiGeometryResult transform_direction(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const NctiVector& i_vec,
            const Ncti_Double i_matrix[4][4],
            NctiVector& o_vec);
        static NctiGeometryResult transform_equal(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            const Ncti_Double i_matrix[4][4],
            const Ncti_Double i_matrix2[4][4],
            Ncti_Boolean& o_equal);
        static NctiGeometryResult check_entity(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            NCTI_MODEL_TAG i_pFace,
            Ncti_Boolean& o_valid);

        static NctiGeometryResult create_view_outline(
            NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_pSourceBody,
            const NctiPosition& i_pos,
            const NctiVector& i_direction,
            NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult create_assemble(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_assembly_template,
			NCTI_MODEL_TAG& o_pAssemble);
		static NctiGeometryResult assemble_objects(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pAssemble,
			const std::vector<NCTI_MODEL_TAG>& i_vtDirectChildren);
		static  NctiGeometryResult remove_objects_from_assemble(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pAssemble,
			const std::vector<NCTI_MODEL_TAG>& i_vtObjectsToRemove);
		static  NctiGeometryResult export_assemble(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pAssemble,
			NCTI_MODEL_TAG& o_pExportBody);
        static NctiGeometryResult ask_shell_by_edge(
            NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_pSourceEdge,
            Ncti_Integer& o_num);
        static NctiGeometryResult create_body_by_vert(NctiDisplayDocCustomContainer* i_pContainer,
            NCTI_MODEL_TAG i_pTarget, NCTI_MODEL_TAG i_vert, NCTI_MODEL_TAG& io_modelBody);
        static NctiGeometryResult find_nearest_geom_by_point(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody, const std::vector<NctiPosition>& i_PointVec, std::vector<NCTI_MODEL_TAG>& o_ModelGeomVec);
        static NctiGeometryResult body_pick_topols(NctiDisplayDocCustomContainer* i_pCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_pSourceSurf,
            const NctiVector& i_ray, Ncti_Integer i_pickType, Ncti_Double i_dMaxDist, Ncti_Integer i_pickMethod, Ncti_Double i_ratio,
            Ncti_Boolean i_approximateCurve, NCTI_MODEL_TAG& io_modelBody);
        static NctiGeometryResult ask_attrib(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody, NCTI_MODEL_TAG i_entity, Ncti_Attrib_Type i_type, std::map<std::string, std::vector<std::string>>& o_attibs);
        static NctiGeometryResult set_attrib(NctiDisplayDocCustomContainer* i_pCustomContainer,
            NCTI_MODEL_TAG i_TargeBody, NCTI_MODEL_TAG i_entity, const Ncti_WChar* i_attribName,
            const std::vector<std::string>& i_value, Ncti_Attrib_Type i_type);
		static NctiGeometryResult create_sheet_polygon(NctiDisplayDocCustomContainer* i_pCustomContainer, 
			const NctiAxis& i_Axis, Ncti_Integer i_sides, Ncti_Double i_radius, NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult create_sheet_rectangle(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis, Ncti_Double i_length, Ncti_Double i_width, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult create_solid_cone(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis, Ncti_Double i_radius, Ncti_Double i_height, Ncti_Double i_semi_angle, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult create_solid_cylinder(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis, Ncti_Double i_Radius, Ncti_Double i_Height, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult create_solid_prism(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis, Ncti_Integer i_sides, Ncti_Double i_radius, Ncti_Double i_height, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult create_solid_sphere(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiAxis& i_Axis, Ncti_Double i_radius, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult create_copy_topology(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult delete_interior_loop(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult reverse_face(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult attach_points(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NctiPosition>& i_vtPosition, NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult find_face_interior_point(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody, NctiPosition& o_point);

		static NctiGeometryResult find_face_outer_loop(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody, NCTI_MODEL_TAG& o_outerWire);
		static NctiGeometryResult create_curve_by_common_edge(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG i_pFace,
			NCTI_MODEL_TAG i_pFace2,
			NCTI_MODEL_TAG& o_ModelBody);
		static NctiGeometryResult find_inter_btw_face(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_pTarget,
			NCTI_MODEL_TAG i_pFaceBody,
			NCTI_MODEL_TAG i_pFaceBody2,
			Ncti_Boolean i_flag,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult offset_surf(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_pSurfBody,
			Ncti_Double i_offset,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult create_section_with_sheet(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_pTarget,
			NCTI_MODEL_TAG i_sheetBody,
			NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult simplify_object(NctiDisplayDocCustomContainer* i_pContainer, NCTI_MODEL_TAG& io_modelBody);
		static NctiGeometryResult topol_clash(NctiDisplayDocCustomContainer* i_pContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pTargets,
			const std::vector<NCTI_MODEL_TAG>& i_pTools,
			std::vector<unsigned int>& clash_type,
			std::vector<std::pair<unsigned int, unsigned int>>& clash_pairs);
		static NctiGeometryResult find_curve_box(
			NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_pSouceBody,
			NCTI_MODEL_TAG i_pSouceCurve,
			Ncti_Double o_box[6]);

		static NctiGeometryResult spcurve_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG i_pSourceCell,
			NCTI_MODEL_TAG& o_pCurve);

		static NctiGeometryResult swept_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pCurveBody,
			const NctiVector& i_Dir,
			NCTI_MODEL_TAG& o_pBody);

		static NctiGeometryResult bcurve_create_splinewise(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NctiPosition>& i_ControlPts,
			Ncti_Integer i_Degree,
			NCTI_MODEL_TAG& o_pCurve);

		static NctiGeometryResult bcurve_clamp_knots(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pCurveBody,
			NCTI_MODEL_TAG& o_pBody);

		static NctiGeometryResult bcurve_join(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pCurveBodyVec,
			NCTI_MODEL_TAG& o_pCurve);

		static NctiGeometryResult geom_copy(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pBody,
			NCTI_MODEL_TAG& o_pBody);

		static NctiGeometryResult curve_make_curve_reversed(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pCurveBody,
			NCTI_MODEL_TAG& o_pCurve);

		static NctiGeometryResult curve_make_spcurves_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSurfaceBody,
			NCTI_MODEL_TAG i_pCurveBody,
			NCTI_MODEL_TAG& o_pCurve);

		static NctiGeometryResult edge_make_curve(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_pSurfaceCellVec,
			NCTI_MODEL_TAG& o_pCurve);

		static NctiGeometryResult create_solid_torus(NctiDisplayDocCustomContainer* i_pCustomContainer, 
			const NctiAxis& i_Axis, 
			Ncti_Double i_major_radius, 
			Ncti_Double i_minor_radius, 
			NCTI_MODEL_TAG& o_ModelBody);

		static NctiGeometryResult delete_face_from_general_body(NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG i_pFaceToDelete,
			NCTI_MODEL_TAG& o_pResultBody);

		static NctiGeometryResult transform_assemble(NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG& io_pSourceAsm,
			Ncti_Double i_mat[4][4]);

		static NctiGeometryResult create_offset_surface(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSurfaceBody,
			Ncti_Double i_offset_distance,
			NCTI_MODEL_TAG& o_pResultBody);

		static NctiGeometryResult make_isocline_surf(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pCurveBody,
			const NctiVector& i_direction,
			Ncti_Double i_angle,
			Ncti_Integer i_side,
			NCTI_MODEL_TAG& o_pResultBody);

		static NctiGeometryResult remove_edge_by_vertex(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pWireBody,
			NCTI_MODEL_TAG i_pEdgeToRemove,
			Ncti_Integer i_position,
			NCTI_MODEL_TAG& o_pResultBody);

		static NctiGeometryResult body_entity_categorize(NctiDisplayDocCustomContainer* i_pCustomContainer, 
			NCTI_MODEL_TAG i_pBody, Ncti_Integer i_method);

		static NctiGeometryResult find_all_partitions(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pBody, std::vector<Ncti_Integer>& o_vtPartitions);

		static NctiGeometryResult body_change_partition(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG& io_pBody, Ncti_Integer i_toPartition);

		static NctiGeometryResult find_assembly_instances(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pAssembly, std::vector<Ncti_Integer>& o_vtInstances);

		static NctiGeometryResult instance_change_part(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG& io_pSrcAssembly, Ncti_Integer i_srcInstanceTag, NCTI_MODEL_TAG i_pNewPart);

		static NctiGeometryResult instance_replace_transf(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_instanceTag, Ncti_Double i_mat[4][4], NCTI_MODEL_TAG& io_pAssembly);

		static NctiGeometryResult instance_transform(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_instanceTag, Ncti_Double i_mat[4][4], NCTI_MODEL_TAG& io_pAssembly);

		static NctiGeometryResult find_shells_by_vertex(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pBody, NCTI_MODEL_TAG i_pVertexCell, std::vector<Ncti_Integer>& o_vtShells);

		static NctiGeometryResult find_face_loops(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pFaceBody, std::vector<Ncti_Integer>& o_vtLoops);

		static NctiGeometryResult delete_loop_from_sheet(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG& io_pFaceBody, Ncti_Integer i_loop);
        static NctiGeometryResult decrease_bezier_bspline_curve_degree(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_degree, NCTI_MODEL_TAG& io_modelBody);
        static NctiGeometryResult decrease_bezier_bspline_surf_degree(NctiDisplayDocCustomContainer* i_pCustomContainer,
            Ncti_Long i_udegree, Ncti_Long i_vdegree,
            NCTI_MODEL_TAG& io_modelBody);

		static NctiGeometryResult euler_edge_zip(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_ring_face(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_ring_loop(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_edge_face(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_edge_loop(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_merge_vertice(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_vert, Ncti_Integer i_index, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_edge_slit(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_left, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_edge_split(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, Ncti_Boolean i_forward, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_make_loop(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_edge, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_merge_loop(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_face, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_merge_edge_loop(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_targetBody, NCTI_MODEL_TAG i_face, NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult euler_transfer_loop(NctiDisplayDocCustomContainer* i_pContainer,
			NCTI_MODEL_TAG i_from, NCTI_MODEL_TAG i_to, NCTI_MODEL_TAG& io_modelBody);


		static NctiGeometryResult bcurve_create_fitted(NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceCurve,
			Ncti_Double i_t_from,
			Ncti_Double i_t_to,
			Ncti_Double i_distTol,
			Ncti_Double i_dAngleTol,
			const std::vector<Ncti_Double>& i_interpolated_params,
			Ncti_Boolean i_preserve_parameterisation,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult bcurve_create_by_fitting(NctiDisplayDocCustomContainer* i_pCustomContainer,
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
		static NctiGeometryResult bcurve_create_spline_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
			std::vector<NctiPosition> i_positions,
			std::vector<Ncti_Double> i_parameters,
			std::vector<Ncti_Integer> i_param_indices,
			Ncti_Integer i_spline_method,
			Ncti_Double i_fit_tol,
			NCTI_MODEL_TAG& o_modelBody);
		static NctiGeometryResult partition_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer& o_partitionTag);
		static NctiGeometryResult partition_set_current(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partitionCurrent);
		static NctiGeometryResult session_ask_curr_partition(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer& o_partitionCurrent);
		static NctiGeometryResult partition_make_pmark_2(NctiDisplayDocCustomContainer * i_pCustomContainer,
			Ncti_Integer i_partition, Ncti_Integer & o_pmark);
		static NctiGeometryResult partition_advance_pmark(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partition, Ncti_Integer& o_pmark);
		static NctiGeometryResult pmark_goto_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_pmark);
		static NctiGeometryResult partition_merge(NctiDisplayDocCustomContainer* i_pCustomContainer,
			std::vector<Ncti_Integer> i_partitions, std::vector<Ncti_Integer> i_pmarks);
		static NctiGeometryResult partition_delete(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partition);
		static NctiGeometryResult face_imprint_curves(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_pSourceBody,
			NCTI_MODEL_TAG i_pWire,
			NCTI_MODEL_TAG& o_pTargetBody);
		static NctiGeometryResult partition_copy(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partition, Ncti_Integer& o_partitioncopy);
		static NctiGeometryResult pmark_ask_identifier(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_pmark, Ncti_Integer& o_identifier);
		static NctiGeometryResult partition_transmit(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partition, const Ncti_Char* i_FullFileName, Ncti_Integer i_transmit_deltas);
		static NctiGeometryResult partition_transmit_delta(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partition);
		static NctiGeometryResult partition_receive(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName, Ncti_Integer i_receive_deltas, Ncti_Integer& o_partition);
		static NctiGeometryResult partition_receive_deltas_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partition);
		static NctiGeometryResult partition_find_pmark_by_id(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_partition, Ncti_Integer i_identifier, Ncti_Integer& o_pmark);
		static NctiGeometryResult mark_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer& o_mark);
		static NctiGeometryResult mark_ask_pmarks(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_mark, std::vector<Ncti_Integer>& o_pmarksVec);
		static NctiGeometryResult pmark_is_used_by_mark(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_pmark, Ncti_Boolean& o_is_used);
		static NctiGeometryResult mark_goto_2(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Integer i_mark);
		static NctiGeometryResult session_transmit(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName);
		static NctiGeometryResult session_receive(NctiDisplayDocCustomContainer* i_pCustomContainer,
			const Ncti_Char* i_FullFileName);

		static NctiGeometryResult bb_create(NctiDisplayDocCustomContainer* i_pCustomContainer,
			std::vector<Ncti_Integer> i_create,std::vector<Ncti_Integer> i_deleet,std::vector<Ncti_Integer> i_copy,std::vector<Ncti_Integer> i_transfer,std::vector<Ncti_Integer> i_merge,std::vector<Ncti_Integer> i_split,std::vector<Ncti_Integer> i_transform,std::vector<Ncti_Integer> i_change_attrib,std::vector<Ncti_Integer> i_change);
		static NctiGeometryResult bb_set_status(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Boolean i_status);
		static NctiGeometryResult bb_output_events(NctiDisplayDocCustomContainer* i_pCustomContainer,
			Ncti_Boolean i_empty,std::vector< Ncti_Integer>& o_events,std::vector< Ncti_Integer>& o_entities,std::vector< Ncti_Integer>& o_event_types,std::vector< Ncti_Integer>& o_classes);
		static NctiGeometryResult mark_delete_all(NctiDisplayDocCustomContainer* i_pCustomContainer);

		static NctiGeometryResult make_helical_curve_by_point(NctiDisplayDocCustomContainer* i_pCustomContainer, const NctiPosition& i_position, const Helical_Geometry_Data& i_helicalData, NCTI_MODEL_TAG& o_pWireBody);
		static NctiGeometryResult make_helical_surface_by_curve(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pWire, const Helical_Geometry_Data& i_helicalData, NCTI_MODEL_TAG& o_pSheetBody);
		static NctiGeometryResult hollow_out_solid_body(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSolidBody, Ncti_Double i_offsetValue, Ncti_Double i_tolerance, const BodyHollowOption& i_hollowOpt, NCTI_MODEL_TAG& o_pResultBody);
		static NctiGeometryResult find_point_on_curve(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pWireBody, NCTI_MODEL_TAG i_pEdge, Ncti_Double i_fMeasureValue, Ncti_Integer i_nMeasureMode, std::vector<NctiPosition>& o_vtPoint);
		static NctiGeometryResult remove_face_to_new_body(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, const std::vector<NCTI_MODEL_TAG>& i_vtFaceToRemove, Ncti_Integer i_nParentHealMethod, Ncti_Integer i_nChildHealMethod, std::vector<NCTI_MODEL_TAG>& o_vtBodies);
		static NctiGeometryResult face_replace_surface(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, const std::vector<NCTI_MODEL_TAG>& i_vtFaceToReplace, const std::vector<NCTI_MODEL_TAG>& i_vtNewFaceBody, double i_tolerance, NCTI_MODEL_TAG& o_pNewBody);
        static NctiGeometryResult get_obb_boungding_box(NctiDisplayDocCustomContainer* i_pCustomContainer,const std::vector<NCTI_MODEL_TAG>& i_pModelBody,const std::vector<NctiPosition>& paraData,std::vector<NctiPosition>& boxData);
		static NctiGeometryResult make_neutral_sheet(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, const std::vector<NCTI_MODEL_TAG>& i_vtLeftFaces, const std::vector<NCTI_MODEL_TAG>& i_vtRightFaces, int i_nMethods, double i_fPlacement, NCTI_MODEL_TAG& o_pNeutralSheet);
		static NctiGeometryResult delete_redundant_topol(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, NCTI_MODEL_TAG& o_pNewBody);
		static NctiGeometryResult body_fault_check(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, std::vector<BodyCheckFaultResult>& o_vtFault);
		static NctiGeometryResult find_cell_self_int(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, NCTI_MODEL_TAG i_pCell, std::vector<CellSelfIntDegensInfo>& o_vtSelfIntInfo);
		static NctiGeometryResult find_cell_degens(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, NCTI_MODEL_TAG i_pCell, std::vector<CellSelfIntDegensInfo>& o_vtDegensInfo);
		static NctiGeometryResult trim_face_by_wire(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, NCTI_MODEL_TAG i_pToolBody, Ncti_Boolean i_ReserveInternal, NCTI_MODEL_TAG& o_pNewBody);
		static NctiGeometryResult body_extend(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyExtendOption& extendOption, NCTI_MODEL_TAG& resultData);
		static NctiGeometryResult filling(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, const std::vector<NCTI_MODEL_TAG>& i_EdgeVec, int iType, NCTI_MODEL_TAG& o_pBody);
		static NctiGeometryResult face_transform(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, const std::vector<NCTI_MODEL_TAG>& i_vtFaceToTransform, const std::vector<NctiTransf>& i_vtTransf, const NCTIFaceTransformOption& i_option, NCTI_MODEL_TAG& o_pNewBody);
		static NctiGeometryResult surface_intersect_surface(NctiDisplayDocCustomContainer* i_pCustomContainer,NCTI_MODEL_TAG i_pSurface1, NCTI_MODEL_TAG i_pSurface2, std::vector<NctiPosition>& o_resultPoints, std::vector<NCTI_MODEL_TAG>& o_resultCurves);
		static NctiGeometryResult edge_repair(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG& io_pBody, const std::vector<NCTI_MODEL_TAG>& i_vtEdgeToRepair, bool i_bEnsureOnSurfs, bool i_bIntersect, double i_fMaxTolerance);
		static NctiGeometryResult topol_render_facet(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, const std::vector<NCTI_MODEL_TAG>& i_vtFacesToFacet, const NCTITopolFacetOption& i_option, std::vector<NctiMeshData>& o_vtNctiMeshData);
		static NctiGeometryResult face_repair(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_faceBodyModel, NCTI_MODEL_TAG i_faceModel, bool i_g1Discontinuities, bool i_selfIntersections, NCTI_MODEL_TAG& o_resultBody);
		static NctiGeometryResult identify_general(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, std::vector<NCTIBodyGeneralResult>& o_checkResult);
		static NctiGeometryResult bb_ask(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTIBbParam& o_bbParamResult);
		static NctiGeometryResult bb_ask_status(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTIBbStatus& o_bbStatusResult);
		static NctiGeometryResult body_extrude(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyExtrudeParam& i_extrudeParam, NCTI_MODEL_TAG& o_resultBody);
		static NctiGeometryResult lattice_create(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTILatticeCreateParam& i_latticeParam, std::vector<NCTI_MODEL_TAG>& o_resultLattices);
		static NctiGeometryResult output_topol_info_with_geom(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pModelBody, const std::vector<NCTI_MODEL_TAG>& i_vtModelCells, int i_nLevel, const char* const i_pFileName);
		static NctiGeometryResult ask_entity_param(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_entity, const std::vector<Ncti_Integer>& i_paramType, std::vector<std::string>& o_paramValueStr);
		static NctiGeometryResult mesh_create(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIMeshCreateParam& i_meshParam, std::vector<NCTI_MODEL_TAG>& o_resultMeshes);
		static NctiGeometryResult bsurf_edit(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBsurfEditParam& i_BsurfEditParam, std::vector<NCTI_MODEL_TAG>& o_resultModels);
		static NctiGeometryResult bcurve_reparameterise(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, NCTI_MODEL_TAG i_pEdge, double i_fMiniParam, double i_fMaxParam, NCTI_MODEL_TAG& o_pNewBody);
		static NctiGeometryResult face_reparameterise_surf(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, const std::vector<NCTI_MODEL_TAG>& i_vtFaces, const NCTISurfReparameteriseOption& i_option, NCTI_MODEL_TAG& o_pNewBody);
		static NctiGeometryResult input_pk_xt_xb_file(NctiDisplayDocCustomContainer* i_pCustomContainer, const Ncti_Char* const i_FullFileName, std::vector<NCTI_MODEL_TAG>& o_vtModelBody);
		static NctiGeometryResult output_pk_xt_xb_file(NctiDisplayDocCustomContainer* i_pCustomContainer, const Ncti_Char* const i_FullFileName, const std::vector<NCTI_MODEL_TAG>& i_vtModelBody);
		static NctiGeometryResult body_loft(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyLoftParam& i_bodyLoftParam, NCTI_MODEL_TAG& o_resultModel);
		static NctiGeometryResult body_swept(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodySweptParam& i_bodySweptParam, NCTI_MODEL_TAG& o_resultModel);
		static NctiGeometryResult body_thicken(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyThickenParam& i_bodyThickenParam, NCTI_MODEL_TAG& o_resultModel);
		static NctiGeometryResult body_taper(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyTaperParam& i_bodyTaperParam, NCTI_MODEL_TAG& o_resultModel);
		static NctiGeometryResult section_with_surface(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_target, NCTI_MODEL_TAG i_surface,  Ncti_Integer i_resultType, std::vector<NCTI_MODEL_TAG>& o_resultModels);
		static NctiGeometryResult curve_project(NctiDisplayDocCustomContainer* i_pCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_curves, const std::vector<NCTI_MODEL_TAG>& i_targets, const NCTICurveProjectParam& i_curveProjectParam, std::vector<NCTI_MODEL_TAG>& o_resultModels);
		static NctiGeometryResult body_offset(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_targetBody, const Ncti_Double i_offsetDist, const NCTIBodyOffsetParam& i_bodyOffsetParam, NCTI_MODEL_TAG& o_resultModel);
		static NctiGeometryResult body_enlarge(NctiDisplayDocCustomContainer* i_pCustomContainer, const NCTIBodyEnlargeParam& i_bodyEnlargeParam, std::vector<NCTI_MODEL_TAG>& o_resultModels);
		static NctiGeometryResult divide_body(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, std::vector<NCTI_MODEL_TAG>& o_vtDisconnectedBodies);
		static NctiGeometryResult set_topol_precision(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, NCTI_MODEL_TAG i_pTopol, Ncti_Integer i_method, double i_precision, NCTI_MODEL_TAG& o_pBody);
		static NctiGeometryResult filling(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, const std::vector<NCTI_MODEL_TAG>& i_EdgeVec, int iType, const NCTIFillHoleOption& i_fillOpt, NCTI_MODEL_TAG& o_pBody);
		static NctiGeometryResult identify_feature(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, const NCTIIdentifyFeatureOption& i_opt, std::vector<NCTIIdentifyFeatureResult>& o_vtFeatureFaces);
		static NctiGeometryResult make_3_face_blend(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pLeftBody, const std::vector<NCTI_MODEL_TAG>& i_vtLeftFaces, NCTI_MODEL_TAG i_pRightBody, const std::vector<NCTI_MODEL_TAG>& i_vtRightFaces, NCTI_MODEL_TAG i_pCentreBody, const std::vector<NCTI_MODEL_TAG>& i_vtCentreFaces, NCTI_MODEL_TAG i_pGuideWire, const NCTI3FaceBlendOption& i_opt, NCTI_MODEL_TAG& o_resultBody);
		static NctiGeometryResult set_curve_parameter_range(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, NCTI_MODEL_TAG i_Edge, Ncti_Double dFirst, Ncti_Double dLast, NCTI_MODEL_TAG& o_pBody);
		static NctiGeometryResult get_curve_parameter_range(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pBody, NCTI_MODEL_TAG i_Edge, Ncti_Double& dFirst, Ncti_Double& dLast);
		static NctiGeometryResult face_make_blend(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pLeftBody, const std::vector<NCTI_MODEL_TAG>& i_vtLeftFaces, NCTI_MODEL_TAG i_pRightBody, const std::vector<NCTI_MODEL_TAG>& i_vtRightFaces, Ncti_Boolean i_bLeftSense, Ncti_Boolean i_bRightSense, const NCTIFaceBlendOption& i_opt, NCTI_MODEL_TAG& o_resultBody);
		static NctiGeometryResult edge_make_blend(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pStartBody, NCTI_MODEL_TAG i_pStartEdge, NCTI_MODEL_TAG i_pStartVertex, Ncti_Double i_startOffsetRatio, NCTI_MODEL_TAG i_pEndBody, NCTI_MODEL_TAG i_pEndEdge, NCTI_MODEL_TAG i_pEndVertex, Ncti_Double i_endOffsetRatio, const NCTIEdgeBlendOption& i_opt, NCTI_MODEL_TAG& o_resultBody);
		static NctiGeometryResult edge_offset_on_body(NctiDisplayDocCustomContainer* i_pCustomContainer, NCTI_MODEL_TAG i_pSrcBody, const std::vector<NCTI_MODEL_TAG>& i_vtEdgesToOffset, int i_direction, const NCTIEdgeOffsetOnBody& i_opt, NCTI_MODEL_TAG& o_resultBody);
	};
}

#endif										
