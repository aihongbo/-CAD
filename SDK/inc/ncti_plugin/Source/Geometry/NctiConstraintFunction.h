#ifndef NctiConstraintFunction_H
#define NctiConstraintFunction_H
#include "NctiGeometryFunctionInterface.h"
#include "dcl_ncti_plugin.h"
#include "NctiDCMDef.h"
#include <vector>
namespace NCTI
{
	class NctiDisplayDCMDimSys;
	class NctiDisplayDCMGeometry;
	class NctiDisplayDCMDimension;
	class NctiDisplayDCMSpline;
	class NctiDCMVariable;
	class NctiDCMEquation;
	class NctiDCMLinearEquation;
	class NctiDCMNonLinearEquation;
	class NctiDCMLinearInequality;
	class NctiDCMCopyCurve;
	class NctiDCMOffset;
	class NctiDCMSet;
	class DECL_NCTI_PLUGIN NctiConstraintFunction
	{
	public:
		NctiConstraintFunction();
		virtual ~NctiConstraintFunction();
	public:
		static NctiGeometryResult create_dim_sys(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_DIM_SYS& o_dcm_dimsys);
		static NctiGeometryResult add_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_dmc_geometry,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult fix_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode);
		static NctiGeometryResult fix_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_P_NODE i_pnode);
		static NctiGeometryResult erase(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			void* i_node,
			Ncti_Integer i_type);
		static NctiGeometryResult add_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dcm_dimension,
			NCTI_G_NODE i_gnode1,
			NCTI_G_NODE i_gnode2,
			NCTI_G_NODE i_gnode3,
			NCTI_G_NODE i_gnode4,
			NCTI_D_NODE& o_dnode);
		static NctiGeometryResult add_dp(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dcm_dimension,
			NCTI_P_NODE i_pnode1,
			NCTI_P_NODE i_pnode2,
			NCTI_D_NODE& o_dnode);
		static NctiGeometryResult add_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dcm_dimension,
			NCTI_G_NODE i_gnode,
			NCTI_R_NODE& o_rnode);
		static NctiGeometryResult evaluate(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys);
		static NctiGeometryResult move_and_evaluate(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_G_NODE> i_gnode_vec,
			std::vector<double(*)[3]> i_matrix_vec);
		static NctiGeometryResult parameter_node(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dcm_dimension,
			NCTI_G_NODE i_gn,
			NCTI_D_NODE i_dn,
			NCTI_P_NODE& o_pn);
		static NctiGeometryResult parameter_node(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dcm_dimension,
			NCTI_D_NODE i_dn,
			Ncti_Integer i_end,
			NCTI_P_NODE& o_pn);
		static NctiGeometryResult re_evaluate(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys);
		static NctiGeometryResult help_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode,
			NCTI_D_NODE i_dnode,
			NctiPosition& o_pt);
		static NctiGeometryResult add_spline_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_dmc_geometry,
			ncti_DCM_bs_data* i_bs_data,
			Ncti_Integer i_bs_status,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult spline_parameter_limits(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_dmc_geometry,
			Ncti_Double& o_t_up,
			Ncti_Double& o_t_low);
		static NctiGeometryResult set_option(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer i_key,
			Ncti_Integer i_value,
			Ncti_Integer& o_option_return);
		static NctiGeometryResult change_chirality(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dnode,
			NCTI_G_NODE i_gnode1,
			NCTI_G_NODE i_gnode2,
			Ncti_Integer& o_status);
		static NctiGeometryResult add_conic_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_dmc_geometry,
			ncti_DCM_conic_data* i_co_data,
			Ncti_Integer i_co_status,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult add_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMVariable* i_dcm_variable,
			NCTI_V_NODE& o_vnode);
		static NctiGeometryResult add_v_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMVariable* i_dcm_variable,
			NCTI_D_NODE i_dnode,
			NCTI_V_NODE& o_vnode);
		static NctiGeometryResult add_v_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMVariable* i_dcm_variable,
			NCTI_R_NODE i_rnode,
			NCTI_V_NODE& o_vnode);
		static NctiGeometryResult changed_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode,
			Ncti_Integer i_longevity);
		static NctiGeometryResult changed_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dnode,
			Ncti_Integer i_longevity);
		static NctiGeometryResult changed_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rnode,
			Ncti_Integer i_longevity);
		static NctiGeometryResult changed_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_enode,
			Ncti_Integer i_longevity);
		static NctiGeometryResult change_pointer_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dcm_dimension,
			NCTI_D_NODE i_dnode);
		static NctiGeometryResult change_pointer_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_dcm_geom,
			NCTI_G_NODE i_gnode);
		static NctiGeometryResult change_pointer_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dcm_dimension,
			NCTI_R_NODE i_rnode);
		static NctiGeometryResult add_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMEquation * i_dcm_equation,
			NCTI_E_NODE& o_enode);
		static NctiGeometryResult add_v_to_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Double i_cf,
			NCTI_E_NODE i_enode,
			NCTI_V_NODE i_vnode,
			Ncti_Integer& o_logical);
		static NctiGeometryResult add_v_to_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Address i_ac,
			NCTI_E_NODE i_enode,
			NCTI_V_NODE i_vnode,
			Ncti_Integer& o_logical);
		static NctiGeometryResult move_to_set(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode,
			NCTI_G_NODE i_setgnode,
			Ncti_Integer& o_logical);
		static NctiGeometryResult dynamic_evaluate(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_G_NODE> i_gnode_vec,
			std::vector<double(*)[3]> i_matrix_vec,
			Ncti_Double* i_val,
			std::vector<Ncti_Integer> i_dragt_vec,
			Ncti_Integer i_opt,
			Ncti_Integer i_solving_mode,
			Ncti_Integer& o_res,
			Ncti_Integer& o_evaluation_type);
		static NctiGeometryResult value(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vnode,
			Ncti_Double& o_value);
		static NctiGeometryResult status_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode,
			Ncti_Integer& o_status);
		static NctiGeometryResult status_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dnode,
			Ncti_Integer& o_status);
		static NctiGeometryResult status_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rnode,
			Ncti_Integer& o_status);
		static NctiGeometryResult status_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_enode,
			Ncti_Integer& o_status);
		static NctiGeometryResult status_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vnode,
			Ncti_Integer& o_status);
		static NctiGeometryResult status_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_P_NODE i_pnode,
			Ncti_Integer& o_status);
		static NctiGeometryResult autodimension(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			const ncti_DCM_autodim_options* i_options,
			Ncti_Integer& o_status);
		static NctiGeometryResult add_autodimension_mask(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer i_g1t,
			Ncti_Integer i_g2t,
			Ncti_Integer i_dt,
			Ncti_Integer i_mo);
		static NctiGeometryResult constraint_balance(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer& o_degrees_of_freedom,
			Ncti_Integer& o_constraints,
			Ncti_Integer& o_rigid_body,
			Ncti_Integer& o_result);
		static NctiGeometryResult check(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_dimension,
			NCTI_G_NODE i_gnode1,
			NCTI_G_NODE i_gnode2,
			NCTI_G_NODE i_gnode3,
			NCTI_G_NODE i_gnode4,
			Ncti_Integer& o_check_result);
		static NctiGeometryResult check(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer i_dt,
			NCTI_G_NODE i_gnode1,
			NCTI_G_NODE i_gnode2,
			NCTI_G_NODE i_gnode3,
			NCTI_G_NODE i_gnode4,
			Ncti_Integer& o_check_result);
		static NctiGeometryResult help_parameters(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dnode,
			Ncti_Double o_params[2]);
		static NctiGeometryResult spline_evaluator(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_sgn,
			Ncti_Double i_param,
			Ncti_Integer i_n_der,
			Ncti_Integer i_side,
			Ncti_Double* o_array);
		static NctiGeometryResult add_pattern_2d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_geom,
			NCTI_G_NODE i_gnpat1,
			NCTI_G_NODE i_gnpat2,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult pattern_2d_value(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode,
			Ncti_Double& o_v1,
			Ncti_Double& o_v2);
		static NctiGeometryResult add_relative_transform(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_geom,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult transform(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			Ncti_Double o_mat[3][3],
			Ncti_Integer& o_transformation);
		static NctiGeometryResult add_offset_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_dcm_geom,
			NCTI_G_NODE i_parent_gn,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult add_copy_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMCopyCurve* i_copy_g,
			NCTI_G_NODE i_parent_gn,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult enquire_conic(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_cgn,
			ncti_DCM_conic_data& io_co_data,
			Ncti_Integer o_co_status);
		static NctiGeometryResult conic_evaluator(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_cgn,
			Ncti_Double i_t,
			Ncti_Integer i_n_der,
			double* o_array);
		static NctiGeometryResult update_conic(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_cgn,
			ncti_DCM_conic_data* i_co_data,
			Ncti_Integer& o_status);
		static NctiGeometryResult update_spline(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_sgn,
			ncti_DCM_bs_data* i_spline_data,
			Ncti_Integer& o_status);
		static NctiGeometryResult enquire_spline(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_sgn,
			ncti_DCM_bs_data& io_bs_data,
			Ncti_Integer& o_status);
		static NctiGeometryResult add_pattern(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMGeometry* i_dcm_geom,
			NCTI_G_NODE i_gnpat,
			NCTI_G_NODE& o_gnode);
		static NctiGeometryResult pattern_value(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			Ncti_Double& o_value);
		static NctiGeometryResult help_parameter(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			NCTI_D_NODE i_dn,
			Ncti_Double& o_value);
		static NctiGeometryResult measured_value(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			Ncti_Double& o_value);
		static NctiGeometryResult autoconstrain(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			ncti_DCM_autocon_options* i_opts);
		static NctiGeometryResult reset(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Boolean i_cancel_chirality);
		static NctiGeometryResult transform_conic(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_cgn,
			double i_mat[3][3],
			Ncti_Integer& o_status);
		static NctiGeometryResult transform_spline(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_sgn,
			double i_mat[3][3],
			Ncti_Integer& o_status);
		static NctiGeometryResult freeze(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode);
		static NctiGeometryResult reset_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn);
		static NctiGeometryResult reset_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn);
		static NctiGeometryResult reset_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rn);
		static NctiGeometryResult reset_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_en);
		static NctiGeometryResult reset_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_P_NODE i_pn);
		static NctiGeometryResult reset_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vn);
		static NctiGeometryResult equal_distance_help_point(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnthis,
			NCTI_G_NODE i_gnother,
			NCTI_D_NODE i_dn,
			Ncti_Double o_loc[2]);
		static NctiGeometryResult equal_distance_help_parameter(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnthis,
			NCTI_G_NODE i_gnother,
			NCTI_D_NODE i_dn,
			Ncti_Double& o_t);
		static NctiGeometryResult dynamic_evaluate_partitions(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_B_NODE> i_active_node_vec,
			std::vector<NCTI_G_NODE> i_gnode_vec,
			std::vector<double(*)[3]> i_matrix_vec,
			Ncti_Double* i_val,
			std::vector<Ncti_Integer> i_dragt_vec,
			Ncti_Integer i_opt,
			Ncti_Integer i_solving_mode,
			Ncti_Integer& o_res,
			Ncti_Integer& o_evaluation_type);
		static NctiGeometryResult erase_all(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys);
		static NctiGeometryResult undo_evaluation(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer i_undo_mode);
		static NctiGeometryResult add_g_to_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Address i_ac,
			NCTI_E_NODE i_en,
			NCTI_G_NODE i_gn);
		static NctiGeometryResult get_resolution(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Double& o_res_linear,
			Ncti_Double& o_res_angular);
		static NctiGeometryResult get_d_of_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			std::vector<NCTI_D_NODE>& o_dnVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult get_r_of_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			std::vector<NCTI_R_NODE>& o_rnVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult get_g_of_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);
		static NctiGeometryResult get_g_of_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rn,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);

		static NctiGeometryResult get_g_of_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);
		static NctiGeometryResult application_pointer_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			NctiDisplayDCMGeometry*& o_geom);
		static NctiGeometryResult application_pointer_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			NctiDisplayDCMDimension*& o_dimension);
		static NctiGeometryResult application_pointer_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rn,
			NctiDisplayDCMDimension*& o_dimension);
		static NctiGeometryResult application_pointer_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vn,
			NctiDCMVariable*& o_var);
		static NctiGeometryResult application_pointer_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_en,
			NctiDCMEquation*& o_equation);
		static NctiGeometryResult application_pointer_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_P_NODE i_pn,
			NctiDisplayDCMDimension*& o_dimension);
		static NctiGeometryResult add_linear_equation(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMLinearEquation* i_equation,
			NCTI_E_NODE& o_en);
		static NctiGeometryResult add_linear_inequality(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMLinearInequality* i_inequality,
			NCTI_E_NODE& o_en);
		static NctiGeometryResult add_non_linear_equation(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMNonLinearEquation* i_equation,
			NCTI_E_NODE& o_en);
		static NctiGeometryResult get_p_of_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			std::vector<NCTI_P_NODE>& o_pnVec,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);
		static NctiGeometryResult get_s_of_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			std::vector<NctiDCMSet*>& o_setVec);
		static NctiGeometryResult get_v_of_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			std::vector<NctiDCMVariable*>& o_varVec);
		static NctiGeometryResult get_p_of_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			std::vector<NCTI_P_NODE>& o_pnVec,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);
		static NctiGeometryResult get_v_of_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rn,
			std::vector<NctiDCMVariable*>& o_varVec);
		static NctiGeometryResult get_v_of_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_en,
			std::vector<NctiDCMVariable*>& o_varVec);
		static NctiGeometryResult get_r_of_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vn,
			std::vector<NCTI_R_NODE>& o_rnVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult get_d_of_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vn,
			std::vector<NCTI_D_NODE>& o_dnVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult get_e_of_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vn,
			std::vector<NctiDCMEquation*>& o_eqVec);
		static NctiGeometryResult get_d_of_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_P_NODE i_pn,
			std::vector<NCTI_D_NODE>& o_dnVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult get_g_of_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_P_NODE i_pn,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);
		static NctiGeometryResult list_g_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);
		static NctiGeometryResult list_d_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_D_NODE>& o_dnVec,
			std::vector<NctiDCMVariable*>& o_varVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult list_r_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_R_NODE>& o_rnVec,
			std::vector<NctiDCMVariable*>& o_varVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult list_e_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NctiDCMEquation*>& o_eqVec);
		static NctiGeometryResult list_v_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NctiDCMVariable*>& o_varVec);
		static NctiGeometryResult list_p_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_P_NODE>& o_pnVec,
			std::vector<NctiDisplayDCMDimension*>& o_dimensionVec);
		static NctiGeometryResult evaluate(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			const std::vector<NCTI_G_NODE>& i_gnVec,
			ncti_DCM_solving_mode i_mode,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult re_evaluate(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			const std::vector<NCTI_G_NODE>& i_gnVec,
			ncti_DCM_solving_mode i_mode,
			Ncti_Boolean i_calcStatus,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult query_offset_distance(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMOffset* i_pOffset,
			ncti_DCM_offset_side& o_side,
			Ncti_Double& o_distance);
		static NctiGeometryResult query_copy_transform(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMCopyCurve* i_pCopyCurve,
			Ncti_Double o_transMat[3][3],
			Ncti_Integer& o_transStatus);
		static NctiGeometryResult is_evaluated(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			ncti_DCM_evaluated_outcome& o_state);
		static NctiGeometryResult change_pointer_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMEquation* i_pEquation,
			NCTI_E_NODE i_en);
		static NctiGeometryResult change_pointer_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDCMVariable* i_pVar,
			NCTI_V_NODE i_vn);
		static NctiGeometryResult change_pointer_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMDimension* i_pDim,
			NCTI_P_NODE i_pn);
		static NctiGeometryResult model_satisfied(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Boolean i_checkBtweenRigid,
			Ncti_Double i_res_linear,
			Ncti_Double i_res_angular,
			ncti_DCM_satisfied_status& o_status);
		static NctiGeometryResult satisfied_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			Ncti_Double i_res_linear,
			Ncti_Double i_res_angular,
			ncti_DCM_satisfied_status& o_status);
		static NctiGeometryResult satisfied_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rn,
			Ncti_Double i_res_linear,
			Ncti_Double i_res_angular,
			ncti_DCM_satisfied_status& o_status);
		static NctiGeometryResult satisfied_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_en,
			Ncti_Double i_res_linear,
			Ncti_Double i_res_angular,
			ncti_DCM_satisfied_status& o_status);
		static NctiGeometryResult check(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gnode1,
			NCTI_G_NODE i_gnode2,
			const NctiVector& i_dir,
			Ncti_Integer& o_check_result);
		static NctiGeometryResult enquire_winding_angle(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			Ncti_Double& o_value,
			Ncti_Boolean& o_hasValue);
		static NctiGeometryResult degree_of_singularity(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer& o_dos,
			ncti_DCM_dos_status& o_status);
		static NctiGeometryResult list_singular_d_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_D_NODE>& o_dnVec,
			std::vector<NctiDisplayDCMDimension*>& o_pDimVec,
			ncti_DCM_dos_status& o_status);
		static NctiGeometryResult list_singular_r_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_R_NODE>& o_rnVec,
			std::vector<NctiDisplayDCMDimension*>& o_pDimVec,
			ncti_DCM_dos_status& o_status);
		static NctiGeometryResult list_singular_e_nodes(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NctiDCMEquation*>& o_pEquVec,
			ncti_DCM_dos_status& o_status);
		static NctiGeometryResult evaluate_partitions(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_B_NODE> i_activeNodeVec,
			std::vector<NCTI_G_NODE> i_gnVec,
			ncti_DCM_solving_mode i_mode,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult re_evaluate_partitions(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_B_NODE> i_activeNodeVec,
			std::vector<NCTI_G_NODE> i_gnVec,
			Ncti_Boolean i_calcStatus,
			ncti_DCM_solving_mode i_mode,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult undo_evaluation_partitions(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			std::vector<NCTI_B_NODE> i_activeNodeVec,
			ncti_DCM_undo_mode i_mode);
		static NctiGeometryResult deduce_constraints(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Double i_tol_linear,
			Ncti_Double i_tol_angular,
			ncti_DCM_d_type i_dt,
			NCTI_G_NODE i_gnode1,
			NCTI_G_NODE i_gnode2,
			NCTI_G_NODE i_gnode3,
			NCTI_G_NODE i_gnode4,
			Ncti_Integer& o_num);
		static NctiGeometryResult last_evaluation_type(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult last_evaluation_type_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult last_evaluation_type_d(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_D_NODE i_dn,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult last_evaluation_type_r(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_R_NODE i_rn,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult last_evaluation_type_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_en,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult last_evaluation_type_v(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_V_NODE i_vn,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult last_evaluation_type_p(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_P_NODE i_pn,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult next_re_evaluate_type(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			const std::vector<NCTI_G_NODE>& i_gnVec,
			ncti_DCM_solving_mode i_mode,
			ncti_DCM_evaluation_type& o_et);
		static NctiGeometryResult update_extensions(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			Ncti_Integer& o_status);
		static NctiGeometryResult underdefined_status(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			Ncti_Integer& o_dofs);
		static NctiGeometryResult underdefined_dof(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			Ncti_Integer& o_rotNum,
			Ncti_Integer& o_transNum,
			Ncti_Boolean& o_internal1,
			Ncti_Boolean& o_internal2,
			ncti_DCM_dof_info_type& o_infoType,
			Ncti_Double o_extraInfo[2],
			ncti_DCM_dof_info_type& o_info2Type,
			Ncti_Double o_extraInfo2[2],
			ncti_DCM_dof_result_status& o_status);
		static NctiGeometryResult transform_from_initial(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			Ncti_Double o_mat[3][3],
			Ncti_Double& o_internalOffset1,
			Ncti_Double& o_internalOffset2,
			Ncti_Double& o_scale1,
			Ncti_Double& o_scale2,
			Ncti_Integer& o_transformation);
		static NctiGeometryResult spline_discontinuities(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMSpline* i_pSpline,
			Ncti_Integer i_nthDer,
			std::vector<Ncti_Double>& o_disconsVec,
			ncti_DCM_bs_status& o_status);
		static NctiGeometryResult replace_spline(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NctiDisplayDCMSpline* i_pSpline,
			ncti_DCM_bs_data* i_bs_data,
			ncti_DCM_bs_status& o_status);
		static NctiGeometryResult get_e_of_g(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_G_NODE i_gn,
			std::vector<NctiDCMEquation*>& o_equVec);
		static NctiGeometryResult get_g_of_e(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			NCTI_E_NODE i_en,
			std::vector<NctiDisplayDCMGeometry*>& o_geomVec);
		static NctiGeometryResult get_option(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer i_key,
			Ncti_Integer& o_value,
			Ncti_Integer& o_option_return);
		static NctiGeometryResult get_default_option(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NctiDisplayDCMDimSys* i_dimsys,
			Ncti_Integer i_key,
			Ncti_Integer& o_value,
			Ncti_Integer& o_option_return);
	};
}
#endif
