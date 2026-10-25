#ifndef NctiDCM3Def_H
#define NctiDCM3Def_H
#ifndef NCTI_DCM3_logical
#define NCTI_DCM3_logical int
#define NCTI_DCM3_TRUE 1
#define NCTI_DCM3_FALSE 0
#endif
#include "ncti_base.h"
#include <vector>
#include <map>

typedef double(*ARRAY_4x4)[4];
namespace NCTI
{
	class NctiDisplayDCM3Dimension;
	class NctiDisplayDCM3Geometry;
	class NctiDisplayObject;
	class NctiPosition;


	typedef enum ncti_DCM3_g_type {
		NCTI_DCM3_POINT = 0,
		NCTI_DCM3_LINE = 1,
		NCTI_DCM3_CIRCLE = 2,
		NCTI_DCM3_PLANE = 3,
		NCTI_DCM3_CYLINDER = 4,
		NCTI_DCM3_SPHERE = 5,
		NCTI_DCM3_SWEEP_SURFACE = 6,
		NCTI_DCM3_PARAMETRIC_SURFACE = 7,
		NCTI_DCM3_PARAMETRIC_CURVE = 8,
		NCTI_DCM3_SPLINE_CURVE = 9,
		NCTI_DCM3_SET = 10,
		NCTI_DCM3_TORUS = 11,
		NCTI_DCM3_CONE = 12,
		NCTI_DCM3_ELLIPSE = 13,
		NCTI_DCM3_SPLINE_SURFACE = 14,
		NCTI_DCM3_SPIN_SURFACE = 15,
		NCTI_DCM3_LINEAR_PATTERN = 16,
		NCTI_DCM3_PATTERN_ARRAY = 17,
		NCTI_DCM3_CIRCULAR_PATTERN = 18,
		NCTI_DCM3_SWEEP_SPLINE_SURFACE = 19,
		NCTI_DCM3_EQUAL_DISTANCE = 20,
		NCTI_DCM3_SPIN_SPLINE_SURFACE = 21,
		NCTI_DCM3_UNKNOWN
	} ncti_DCM3_g_type;

	typedef enum ncti_DCM3_d_type {
		NCTI_DCM3_DISTANCE = 0,
		NCTI_DCM3_ANGLE = 1,
		NCTI_DCM3_CONCENTRIC = 2,
		NCTI_DCM3_RADIUS = 3,
		NCTI_DCM3_PARALLEL = 4,
		NCTI_DCM3_PERPENDICULAR = 5,
		NCTI_DCM3_COINCIDENT = 6,
		NCTI_DCM3_TANGENT = 7,
		NCTI_DCM3_MAJOR_RADIUS = 10,
		NCTI_DCM3_MINOR_RADIUS = 11,
		NCTI_DCM3_EQUAL_RADIUS = 12,
		NCTI_DCM3_MIDPOINT = 14,
		NCTI_DCM3_DEPENDENCE = 15,
		NCTI_DCM3_EQUAL_PARAMETER = 17,
		NCTI_DCM3_EQUAL_DIRECTION = 19,
		NCTI_DCM3_EQUAL_CURVATURE = 20,
		NCTI_DCM3_EQUAL_FIRST_DERIVATIVE = 21,
		NCTI_DCM3_EQUAL_SECOND_DERIVATIVE = 22,
		NCTI_DCM3_CURVE_LENGTH = 25,
		NCTI_DCM3_SYMMETRIC = 50,
		NCTI_DCM3_HALF_ANGLE = 51,
		NCTI_DCM3_COINCIDENT_AROUND_SPINE = 52,
		NCTI_DCM3_COINCIDENT_WITH_SPINE = 53,
		NCTI_DCM3_EQUAL_HALF_ANGLE = 56,
		NCTI_DCM3_EQUAL_CURVATURE_VECTOR = 59,
		NCTI_DCM3_ANGLE_PLANAR = 60,
		NCTI_DCM3_SURFACE_NORMAL = 61,
		NCTI_DCM3_PATTERNED = 62,
		NCTI_DCM3_PATTERN_VALUE = 63,
		NCTI_DCM3_EQUAL_DISTANCED = 64,
		NCTI_DCM3_EQUAL_DISTANCE_VALUE = 65
	} ncti_DCM3_d_type;

	typedef enum ncti_DCM3_parametric_type {
		NCTI_DCM3_PARAMETRIC_PERIODIC = 0,
		NCTI_DCM3_PARAMETRIC_BOUNDED = 1
	} ncti_DCM3_parametric_type;

	typedef enum ncti_DCM3_e_type {
		NCTI_DCM3_LINEAR_EQUATION = 0,
		NCTI_DCM3_NON_LINEAR_EQUATION = 1,
		NCTI_DCM3_LINEAR_INEQUALITY = 2,
		NCTI_DCM3_UNKNOWN_EQUATION = 3
	} ncti_DCM3_e_type;

	typedef enum ncti_DCM3_discontinuity_side {
		NCTI_DCM3_DS_LOWER = 0,
		NCTI_DCM3_DS_UPPER = 1,
		NCTI_DCM3_DS_NO_DISCONTINUITY = 2
	} ncti_DCM3_discontinuity_side;

	typedef enum ncti_DCM3_torus_type {
		NCTI_DCM3_WHOLE_TORUS,
		NCTI_DCM3_APPLE_TORUS,
		NCTI_DCM3_LEMON_TORUS
	} ncti_DCM3_torus_type;

	typedef enum ncti_DCM3_pcurve_type {
		NCTI_DCM3_PCURVE_NON_PLANAR,
		NCTI_DCM3_PCURVE_PLANAR
	} ncti_DCM3_pcurve_type;

	typedef enum ncti_DCM3_g_rigidity {
		NCTI_DCM3_GEOMETRY_NON_RIGID,
		NCTI_DCM3_GEOMETRY_RIGID
	} ncti_DCM3_g_rigidity;

	typedef enum ncti_DCM3_d_rigidity {
		NCTI_DCM3_DIMENSION_NON_RIGID,
		NCTI_DCM3_DIMENSION_RIGID
	} ncti_DCM3_d_rigidity;

	typedef enum ncti_DCM3_variable_angle_return {
		NCTI_DCM3_VARIABLE_ANGLE_KEEP,
		NCTI_DCM3_VARIABLE_ANGLE_VALUE
	} ncti_DCM3_variable_angle_return;

	typedef enum ncti_DCM3_g_node_status {
		NCTI_DCM3_G_UNKNOWN,		/* unknown status (newly added to system)*/
		NCTI_DCM3_G_FIXED,		/* geometry has been declared fixed */
		NCTI_DCM3_G_OVER_DEFINED,	/* geometry is over defined by dimensions */
		NCTI_DCM3_G_NOT_CONSISTENT,	/* geometry inconsistently defined by dimensions */
		NCTI_DCM3_G_NOT_CONSISTENT_DIMENSIONS,	/* geometry inconsistently defined by
							dimensions - change model */
		NCTI_DCM3_G_NOT_CONSISTENT_OTHER,	/* geometry inconsistently defined by
						dimensions - try changing solving mode */
		NCTI_DCM3_G_NOT_CONSISTENT_UNKNOWN,	/* geometry inconsistently defined by
						dimensions - cannot ascertain what to recommend */
		NCTI_DCM3_G_NOT_CHANGED,	/* geometry was not changed */
		NCTI_DCM3_G_WELL_DEFINED,	/* geometry is well defined by dimensions */
		NCTI_DCM3_G_UNDER_DEFINED,	/* geometry is underdefined by dimensions */
		NCTI_DCM3_G_WITHIN_BOUNDS    /* geometry is underdefined but only due to */
								   /* a bounded dimension */
	} ncti_DCM3_g_node_status;

	typedef enum ncti_DCM3_d_node_status {
		NCTI_DCM3_D_UNKNOWN,		/* unknown status (newly added to system) */
		NCTI_DCM3_D_OVER_DEFINED,	/* dimension specification is over-defined */
		/* or too complex to solve */
		NCTI_DCM3_D_NOT_CONSISTENT,	/* given dimension value is inconsistent */
		NCTI_DCM3_D_NOT_CONSISTENT_DIMENSIONS,	/* given dimension value is
							inconsistent - change model */
		NCTI_DCM3_D_NOT_CONSISTENT_OTHER,	/* given dimension value is
						inconsistent - try changing solving mode */
		NCTI_DCM3_D_NOT_CONSISTENT_UNKNOWN,	/* given dimension value is inconsistent -
						cannot ascertain what to recommend */
		NCTI_DCM3_D_NOT_CHANGED,	/* given dimension not changed */
		NCTI_DCM3_D_BETWEEN_SET_MEMBERS,	/* given dimension between set members -
						has not solved -
						could also be between fixed geometry */
		NCTI_DCM3_D_BETWEEN_FIXED,   /* given dimension between fixed geometry -
					has not solved */
		DCM3_D_CONSTRAINS_RIGID,   /* given dimension constrains internal freedom
								  of a rigid geometry*/
		NCTI_DCM3_D_NOT_SOLVED,	/* given dimension has not solved */
		NCTI_DCM3_D_SOLVED		/* dimension value is satisfied by solution */
	} ncti_DCM3_d_node_status;

	typedef enum ncti_DCM3_transform_status {
		NCTI_DCM3_NON_IDENTITY_TRANSFORM_MATRIX = 1,
		NCTI_DCM3_NON_ZERO_RADIUS_OFFSET = 2,
		NCTI_DCM3_NON_ZERO_MINOR_RADIUS_OFFSET = 4,
		NCTI_DCM3_NON_ZERO_HALF_ANGLE_OFFSET = 8,
		NCTI_DCM3_NON_ZERO_PATTERN_VALUE_OFFSET = 16,
		NCTI_DCM3_NON_ZERO_EQUAL_DISTANCE_VALUE_OFFSET = 32
	} ncti_DCM3_transform_status;

	typedef enum ncti_DCM3_consbal_status {
		NCTI_DCM3_CONSBAL_COMPLETED,	/* constraint balance has been completed */
		NCTI_DCM3_CONSBAL_INCOMPLETE,/* the number of constraints implied by  */
		/* the dimensions has not been evaluated */
		NCTI_DCM3_CONSBAL_NOT_EVALUATED /* constraint balance not available */
					/* because model not in an evaluated state */
	} ncti_DCM3_consbal_status;

	typedef enum ncti_DCM3_dof_result_status {
		NCTI_DCM3_DOF_NOT_EVALUATED,
		NCTI_DCM3_DOF_UNKNOWN,
		NCTI_DCM3_DOF_SUCCEED
	} ncti_DCM3_dof_result_status;

	typedef	enum ncti_DCM3_dof_status {
		NCTI_DCM3_DOF_NOT_USED,
		NCTI_DCM3_DOF_STATIC,
		NCTI_DCM3_DOF_FREE,
		NCTI_DCM3_DOF_INSTANTANEOUS,
		NCTI_DCM3_DOF_STATIC_NORMAL,
		NCTI_DCM3_DOF_FREE_NORMAL,
		NCTI_DCM3_DOF_INSTANTANEOUS_NORMAL
	} ncti_DCM3_dof_status;

	typedef enum ncti_DCM3_underdefined_g_status {
		NCTI_DCM3_RADIUS_UNDERDEFINED = 1,
		NCTI_DCM3_MAJOR_RADIUS_UNDERDEFINED = 2,
		NCTI_DCM3_MINOR_RADIUS_UNDERDEFINED = 4,
		NCTI_DCM3_ANGLE_UNDERDEFINED = 8,
		NCTI_DCM3_POSITION_UNDERDEFINED = 16,
		NCTI_DCM3_HALF_ANGLE_UNDERDEFINED = 32,
		NCTI_DCM3_AXIS_ANGLE_UNDERDEFINED = 64, /* returned on ellipses */
		NCTI_DCM3_AXIS_POSITION_UNDERDEFINED = 0x80, /* returned on axial geometries */
		NCTI_DCM3_PLANE_UNDERDEFINED = 0x100, /* returned on plane, circle, torus, cone,
										  * ellipse, planar_parametric curve */
		NCTI_DCM3_DIRECTION_UNDERDEFINED = 0x200, /* returned on directed geometries */
		NCTI_DCM3_PATTERN_VALUE_UNDERDEFINED = 0x400
	} ncti_DCM3_underdefined_g_status;

	typedef enum ncti_DCM3_overdefined_d_status {
		NCTI_DCM3_OTHER_OVERDEFINED = 1,
		NCTI_DCM3_PARALLEL_OVERDEFINED = 2,
		NCTI_DCM3_PERPENDICULAR_OVERDEFINED = 4
	} ncti_DCM3_overdefined_d_status;

	typedef enum ncti_DCM3_outcome {
		NCTI_DCM3_OUTCOME_SUCCEEDED,
		NCTI_DCM3_OUTCOME_INVALID_PARAMETERS,
		NCTI_DCM3_OUTCOME_FAILED
	} ncti_DCM3_outcome;

	typedef enum ncti_DCM3_m_and_e_outcome {
		NCTI_DCM3_M_AND_E_SOLVED_EXACTLY,
		NCTI_DCM3_M_AND_E_SOLVED,
		NCTI_DCM3_M_AND_E_FAILED
	} ncti_DCM3_m_and_e_outcome;

	typedef enum ncti_DCM3_equation_status {
		NCTI_DCM3_EQUATION_OK,
		NCTI_DCM3_EQUATION_FAIL
	} ncti_DCM3_equation_status;

	typedef enum ncti_DCM3_chirality_status {
		NCTI_DCM3_CHIRALITY_NOT_EVALUATED,
		NCTI_DCM3_CHIRALITY_NOT_CHANGEABLE,
		NCTI_DCM3_CHIRALITY_CHANGEABLE
	} ncti_DCM3_chirality_status;

	typedef enum ncti_DCM3_rigidity_info {
		NCTI_DCM3_RIGIDITY_NOT_EVALUATED,
		NCTI_DCM3_RIGIDITY_NOT_RIGID,
		NCTI_DCM3_RIGIDITY_RIGID_TO_FIXED,
		NCTI_DCM3_RIGIDITY_UNKNOWN
	} ncti_DCM3_rigidity_info;

	typedef enum ncti_DCM3_measured_status {
		NCTI_DCM3_MEASURED_STATUS_UNSUPPORTED_TYPE,
		NCTI_DCM3_MEASURED_STATUS_CANNOT_MEASURE,
		NCTI_DCM3_MEASURED_STATUS_MEASURED
	} ncti_DCM3_measured_status;

	typedef enum ncti_DCM3_satisfied_status {
		NCTI_DCM3_SS_INVALID_RESOLUTION,
		NCTI_DCM3_SS_NOT_SATISFIED,
		NCTI_DCM3_SS_UNSUPPORTED_TYPE,
		NCTI_DCM3_SS_SATISFIED,
		NCTI_DCM3_SS_NOT_CHECKED
	} ncti_DCM3_satisfied_status;

	/*3. Solving and other options */

	typedef enum ncti_DCM3_option {
		NCTI_DCM3_OP_STATUS_240,		/* Instruct the DCM to return status */
		/* codes as appropriate to version 240 */
		NCTI_DCM3_OP_STATUS_250,		/* Instruct the DCM to return status */
		/* codes as appropriate to version 250 */
		NCTI_DCM3_OP_STATUS_260,		/* Instruct the DCM to return status */
		/* codes as appropriate to version 260 */
		NCTI_DCM3_OP_STATUS_CURRENT,		/* Instruct the DCM to return status */
		/* codes as appropriate to the current version */
		NCTI_DCM3_OP_RIGID_TO_FIXED_ON,	/* switch on the computation */
		/* of effectively fixed nodes */
		NCTI_DCM3_OP_RIGID_TO_FIXED_OFF,	/* switch off the computation and output */
		/* of effectively fixed nodes */
		NCTI_DCM3_OP_ANALYSE_OVERDEFINED_ON,	/* Improved overdefined diagnostics */
		NCTI_DCM3_OP_ANALYSE_OVERDEFINED_OFF,	/* at the cost of reduced performance */
		NCTI_DCM3_OP_OVER_DEFINED_SET_STATUS_ADJUSTMENT_ON,	/* Give sets an over-defined status if any members are over-defined */
		NCTI_DCM3_OP_OVER_DEFINED_SET_STATUS_ADJUSTMENT_OFF,	/* No attempt to adjust sets statuses to over-defined */
		NCTI_DCM3_OP_EVAL_RESOLVE_NOT_CONSISTENT_OFF, /* Resolve not consistent in evaluation */
		NCTI_DCM3_OP_EVAL_RESOLVE_NOT_CONSISTENT_ON, /* Default: ON */
		NCTI_DCM3_OP_DRAG_RESOLVE_NOT_CONSISTENT_OFF, /* Resolve not consistent in dragging */
		NCTI_DCM3_OP_DRAG_RESOLVE_NOT_CONSISTENT_ON, /* Default: ON */
		NCTI_DCM3_OP_WITHIN_BOUNDS_WITHIN_ON,	/* Determine what status codes are set for geometry whose position	*/
		NCTI_DCM3_OP_WITHIN_BOUNDS_WELL_DEFINED, /* would be well defined if constrained by normal dimensions		*/
		NCTI_DCM3_OP_WITHIN_BOUNDS_UNDER_DEFINED, /* rather than bounded dimensions. Default: _UNDER_DEFINED			*/
		NCTI_DCM3_OP_RE_EVAL_STATUSES_FROM_RESET_OFF, /* If re-evaluate is performing a full evaluate optionally calculate statuses */
		NCTI_DCM3_OP_RE_EVAL_STATUSES_FROM_RESET_ON, /* Default: OFF */
		NCTI_DCM3_OP_USE_OPENMP_OFF, /* Switch OpenMP on and off. OBSOLETE: now does nothing */
		NCTI_DCM3_OP_USE_OPENMP_ON,  /* Default: OFF OBSOLETE: now does nothing*/
		NCTI_DCM3_OP_STRICT_PCURVE_ORDER_POINTS, /* Strict point order on curve control */
		NCTI_DCM3_OP_STRICT_PCURVE_ORDER_NONE, /* Default: OFF */
		NCTI_DCM3_OP_HELP_POINTS_V46_OFF,   /* Stricter use of help point positions during constraint checking (default) */
		NCTI_DCM3_OP_HELP_POINTS_V46_ON,     /* Maintain compatibility with version 46 and older */
		NCTI_DCM3_OP_BOUNDED_DIMENSIONS_V48, /* Maintain compatibility with version 48 and older */
		NCTI_DCM3_OP_BOUNDED_DIMENSIONS_DEFAULT, /* Enable latest bounded dimension functionality */
		NCTI_DCM3_OP_MINIMUM_MOVE_MODE_STRICT, /* Transform minimum number of geometries, possibly with large transforms */
		NCTI_DCM3_OP_MINIMUM_MOVE_MODE_LOCAL  /* Allow more geometries to move to avoid large transforms (default) */
	} ncti_DCM3_option;

	typedef enum ncti_DCM3_set_option_return {
		NCTI_DCM3_SET_OPT_OK_CHANGE,
		NCTI_DCM3_SET_OPT_OK_NO_CHANGE,
		NCTI_DCM3_SET_OPT_INVALID_KEY,
		NCTI_DCM3_SET_OPT_INVALID_VALUE,
		NCTI_DCM3_SET_OPT_ERROR
	} ncti_DCM3_set_option_return;

	typedef enum ncti_DCM3_dof {
		NCTI_DCM3_DOF_GEOMETRIES_ONLY = 0,
		NCTI_DCM3_DOF_ALL = 6
	} ncti_DCM3_dof;

	typedef enum ncti_DCM3_evaluate_mode {
		NCTI_DCM3_EVALUATE_STANDARD,
		NCTI_DCM3_EVALUATE_RELAXATION,
		NCTI_DCM3_EVALUATE_NO_PROPAGATION
	} ncti_DCM3_evaluate_mode;

	typedef enum ncti_DCM3_drag_mode {
		NCTI_DCM3_DRAG_MINIMUM_MOVE,		/* move smallest number of geometries */
		NCTI_DCM3_DRAG_MAXIMUM_MOVE,		/* move geometries rigidly if possible */
		NCTI_DCM3_DRAG_NO_PROPAGATION,	/* move geometries with minimal transform propagation */
		NCTI_DCM3_DRAG_RELAXATION		/* solve geometries using relaxation */
	} ncti_DCM3_drag_mode;

	typedef enum ncti_DCM3_move_eval_mode {
		NCTI_DCM3_MOVE_EVAL_STANDARD,
		NCTI_DCM3_MOVE_EVAL_RELAXATION,
		NCTI_DCM3_MOVE_EVAL_MINIMUM_MOVE
	} ncti_DCM3_move_eval_mode;

	typedef enum ncti_DCM3_undo_mode {
		NCTI_DCM3_UNDO_TO_INITIAL,	/* undo to position before full evaluate */
		NCTI_DCM3_UNDO_TO_PREVIOUS	/* undo to position before re_evaluate */
	} ncti_DCM3_undo_mode;

	typedef enum ncti_DCM3_abort_response {
		NCTI_DCM3_ABORT_NOW,		/* abort the DCM operation now */
		NCTI_DCM3_ABORT_LATER	/* abort the DCM operation later */
	} ncti_DCM3_abort_response;

	typedef enum ncti_DCM3_abort_code {
		NCTI_DCM3_STARTING_NUMERICAL_SOLVING, /* Not used */
		NCTI_DCM3_ABORT_NUMERICAL_SIZE, /* Solving numerically and time intensively */
		NCTI_DCM3_ABORT_OVERDEFINED_ANY, /* Overdefined node has been identified */
		NCTI_DCM3_ABORT_OVERDEFINED_REGIONS, /* Overdefined and regions diagnostics complete */
		NCTI_DCM3_ABORT,	/* Solving normally - only abort on user intervention */
		NCTI_DCM3_ABORT_SOLVE_SIZE, /* Solving estimated to be time intensive */
		NCTI_DCM3_ABORT_STATUS_CALC_SIZE /* Status code calculation estimated to be time intensive */
	} ncti_DCM3_abort_code;

	typedef enum ncti_DCM3_data_checking_mode
	{
		/* Application data checking modes  (may be bit-wise combined) */
		NCTI_DCM3_DATA_CHECKING_OFF = 0,	/* No data checking */
		NCTI_DCM3_DATA_CHECKING_DEFAULT = 1,	/* Simple checks only */
		NCTI_DCM3_DATA_CHECKING_EXTRA = 2,	/* Check derivatives etc. */
		NCTI_DCM3_DATA_CHECKING_ALL = 3	/* Maximum checking */
	} ncti_DCM3_data_checking_mode;

	typedef enum ncti_DCM3_ellipse_parameter {
		/* help parameter/point on ellipses */
		NCTI_DCM3_ELLIPSE_PARAMETER_PARAMETER, /* Use help parameter */
		NCTI_DCM3_ELLIPSE_PARAMETER_VECTOR     /* Use help vector */
	} ncti_DCM3_ellipse_parameter;

	/*4. Dragging */

	typedef enum ncti_DCM3_drag_result {
		NCTI_DCM3_DRAG_SUCCEEDED,		/* drag succeeded */
		NCTI_DCM3_DRAG_FAILED		/* drag failed    */
	} ncti_DCM3_drag_result;

	typedef enum ncti_DCM3_drag_transformation {
		NCTI_DCM3_DT_TRANSLATION = 0,	/* translation only transformations */
		NCTI_DCM3_DT_AXIAL_ROTATION = 1, /* rotation about axis transformations */
		NCTI_DCM3_DT_GENERAL = 2,		/* translation or rotation transformations */
		NCTI_DCM3_DT_RADIUS = 3,         /* circle, sphere, cylinder, torus major radius */
		NCTI_DCM3_DT_MINOR_RADIUS = 4,	/* torus minor radius */
		NCTI_DCM3_DT_HALF_ANGLE = 5,		/* cone half angle */
		NCTI_DCM3_DT_ALONG_CURVE = 6,	/* drag along curve */
		NCTI_DCM3_DT_DO_NOT_MOVE = 7		/* pinning */
	} ncti_DCM3_drag_transformation;

	typedef enum ncti_DCM3_drag_option {
		NCTI_DCM3_DRAG_POSSIBLE,	/* drag is possible */
		NCTI_DCM3_DRAG_SPECIFIC	/* only drag if this transform can be applied */
	} ncti_DCM3_drag_option;

	typedef enum ncti_DCM3_solve_type {
		NCTI_DCM3_FULL,		/* full evaluation was required */
		NCTI_DCM3_INCREMENTAL	/* incremental evaluation was performed */
	} ncti_DCM3_solve_type;

	/*5. Specifying the solution required*/

	typedef enum ncti_DCM3_alignment {
		NCTI_DCM3_ALIGNMENT_NOT_SPECIFIED,
		NCTI_DCM3_ALIGNMENT_ALIGN,
		NCTI_DCM3_ALIGNMENT_ANTI_ALIGN
	} ncti_DCM3_alignment;

	typedef enum ncti_DCM3_half_space {
		NCTI_DCM3_HALF_SPACE_NOT_SPECIFIED,
		NCTI_DCM3_HALF_SPACE_POSITIVE,
		NCTI_DCM3_HALF_SPACE_NEGATIVE
	} ncti_DCM3_half_space;

	typedef enum ncti_DCM3_dimension_to {
		NCTI_DCM3_DIMENSION_TO_NOT_SPECIFIED = 0, /* behave as in earlier versions */
		NCTI_DCM3_DIMENSION_TO_EXTERIOR = 1,
		NCTI_DCM3_DIMENSION_TO_CENTRE_POINT = 2,
		NCTI_DCM3_DIMENSION_TO_AXIS = 3,
		NCTI_DCM3_DIMENSION_TO_PLANE = 4,
		NCTI_DCM3_DIMENSION_TO_SPINE = 5,
		NCTI_DCM3_DIMENSION_TO_APEX = 6,
		NCTI_DCM3_DIMENSION_TO_MAJOR_AXIS = 7
	} ncti_DCM3_dimension_to;

	typedef enum ncti_DCM3_help_points {
		NCTI_DCM3_DIM_TO_HELP_POINT,
		NCTI_DCM3_DIM_TO_BOUNDARY,
		NCTI_DCM3_DIM_TO_CENTRE,
		NCTI_DCM3_DIM_TO_INTERNAL_HELP_POINT
	} ncti_DCM3_help_points;

	typedef enum ncti_DCM3_surface_orientation {
		NCTI_DCM3_SURFACE_ORIENTATION_NOT_SPECIFIED,
		NCTI_DCM3_SURFACE_ORIENTATION_ALIGN,
		NCTI_DCM3_SURFACE_ORIENTATION_ANTI_ALIGN
	} ncti_DCM3_surface_orientation;

	typedef enum ncti_DCM3_tan_alignment {
		NCTI_DCM3_TAN_ALIGNMENT_EQUAL,
		NCTI_DCM3_TAN_ALIGNMENT_OPPOSITE,
		NCTI_DCM3_TAN_ALIGNMENT_CURRENT,
		NCTI_DCM3_TAN_ALIGNMENT_FREE
	} ncti_DCM3_tan_alignment;

	typedef enum ncti_DCM3_alignment_type {
		NCTI_DCM3_ALIGNMENT,
		NCTI_DCM3_ORIENTATION,
		NCTI_DCM3_TAN_ALIGNMENT,
		NCTI_DCM3_ALIGNMENT_UNKNOWN
	} ncti_DCM3_alignment_type;
	/*6. Pre-evaluate checking */

	typedef enum ncti_DCM3_check_result {
		NCTI_DCM3_CHECK_POSSIBLE,		/* dimension can be added	   */
		NCTI_DCM3_CHECK_UNKNOWN,		/* unable to check dimension	   */
		NCTI_DCM3_CHECK_NOT_POSSIBLE,	/* insufficient degrees of freedom */
		/* to add dimension		   */
		NCTI_DCM3_CHECK_NOT_EVALUATED	/* model not in an evaluated state */
	} ncti_DCM3_check_result;

	/*7. erase-callback types */

	typedef enum ncti_DCM3_node_type {
		NCTI_DCM3_G_NODE,
		NCTI_DCM3_D_NODE,
		NCTI_DCM3_R_NODE,
		NCTI_DCM3_E_NODE,
		NCTI_DCM3_V_NODE,
		NCTI_DCM3_P_NODE
	} ncti_DCM3_node_type;

	typedef enum ncti_DCM3_bs_status {
		NCTI_DCM3_BS_STATUS_OK,
		NCTI_DCM3_BS_STATUS_NOT_A_SPLINE,
		NCTI_DCM3_BS_STATUS_BAD_DATA,
		NCTI_DCM3_BS_STATUS_OVER_DEFINED,
		NCTI_DCM3_BS_STATUS_NOT_SOLVED
	} ncti_DCM3_bs_status;

	typedef enum ncti_DCM3_bs_rigidity {
		NCTI_DCM3_BS_RIGIDITY_RIGID,
		NCTI_DCM3_BS_RIGIDITY_SCALABLE,
		NCTI_DCM3_BS_RIGIDITY_FLEXIBLE
	} ncti_DCM3_bs_rigidity;

	typedef enum ncti_DCM3_bs_periodicity {
		NCTI_DCM3_BS_PERIODICITY_NON_PER,
		NCTI_DCM3_BS_PERIODICITY_PER
	} ncti_DCM3_bs_periodicity;

	typedef enum ncti_DCM3_bs_rationality {
		NCTI_DCM3_BS_RATIONALITY_NON_RAT,
		NCTI_DCM3_BS_RATIONALITY_RAT
	} ncti_DCM3_bs_rationality;

	typedef enum ncti_DCM3_bs_planarity {
		NCTI_DCM3_BS_PLANARITY_NON_PLA,
		NCTI_DCM3_BS_PLANARITY_PLA
	} ncti_DCM3_bs_planarity;

	typedef enum ncti_DCM3_bs_dependence {
		NCTI_DCM3_BS_DEPENDENCE_CP,
		NCTI_DCM3_BS_DEPENDENCE_INTERP
	} ncti_DCM3_bs_dependence;

	typedef enum ncti_DCM3_bs_solving_mode {
		NCTI_DCM3_BS_SOLVING_MODE_STANDARD,
		NCTI_DCM3_BS_SOLVING_MODE_LOCAL
	} ncti_DCM3_bs_solving_mode;

	typedef enum ncti_DCM3_bs_parameterisation {
		NCTI_DCM3_BS_PARAMETERISATION_FIXED,          /* user-defined fixed */
		NCTI_DCM3_BS_PARAMETERISATION_VARIABLE,       /* user-defined variable */
		NCTI_DCM3_BS_PARAMETERISATION_CHORD_LENGTH,   /* DCM internal variable using chord length parameterisation */
		NCTI_DCM3_BS_PARAMETERISATION_CENTRIPETAL,    /* DCM internal variable using centripetal parameterisation */
		NCTI_DCM3_BS_PARAMETERISATION_CHORD_LENGTH_52 /* DCM internal variable using chord length with v52 and earlier limitations */
	} ncti_DCM3_bs_parameterisation;

	typedef enum ncti_DCM3_bs_knot_generation {
		NCTI_DCM3_BS_KNOT_GENERATION_MODE1,
		NCTI_DCM3_BS_KNOT_GENERATION_MODE2
	} ncti_DCM3_bs_knot_generation;

	typedef enum ncti_DCM3_bs_interp_magnitude {
		NCTI_DCM3_BS_INTERP_MAGNITUDE_FIXED,
		NCTI_DCM3_BS_INTERP_MAGNITUDE_VARIABLE
	} ncti_DCM3_bs_interp_magnitude;

	typedef enum ncti_DCM3_bs_cp_freedom {
		NCTI_DCM3_BS_CP_FREEDOM_FREE,
		NCTI_DCM3_BS_CP_FREEDOM_FIXED
	} ncti_DCM3_bs_cp_freedom;

	typedef enum ncti_DCM3_bs_itype {
		NCTI_DCM3_BS_ITYPE_COI,
		NCTI_DCM3_BS_ITYPE_G_COI,
		NCTI_DCM3_BS_ITYPE_DERIV1,
		NCTI_DCM3_BS_ITYPE_DERIV2,
		NCTI_DCM3_BS_ITYPE_CURVATURE,
		NCTI_DCM3_BS_ITYPE_DERIV1_DIR,
		NCTI_DCM3_BS_ITYPE_DERIV1_LEN
	} ncti_DCM3_bs_itype;

	typedef enum ncti_DCM3_bs_iduration {
		NCTI_DCM3_BS_IDURATION_REFRESH_ONLY,
		NCTI_DCM3_BS_IDURATION_ALWAYS,
		NCTI_DCM3_BS_IDURATION_CREATION_ONLY
	} ncti_DCM3_bs_iduration;

	typedef enum ncti_DCM3_bs_istatus {
		NCTI_DCM3_BS_ISTATUS_SOLVED,
		NCTI_DCM3_BS_ISTATUS_REMOVED,
		NCTI_DCM3_BS_ISTATUS_OVER_DEFINED,
		NCTI_DCM3_BS_ISTATUS_NOT_SOLVED
	} ncti_DCM3_bs_istatus;

	typedef enum ncti_DCM3_bs_data_mask {
		NCTI_DCM3_BS_RIGIDITY = 0x00000001,
		NCTI_DCM3_BS_PERIODICITY = 0x00000002,
		NCTI_DCM3_BS_RATIONALITY = 0x00000004,
		NCTI_DCM3_BS_PLANARITY = 0x00000008,
		NCTI_DCM3_BS_DEPENDENCE = 0x00000010,
		NCTI_DCM3_BS_SOLVING_MODE = 0x00000020,
		NCTI_DCM3_BS_PARAMETERISATION = 0x00000040,
		NCTI_DCM3_BS_KNOT_GENERATION = 0x00000080,
		NCTI_DCM3_BS_DEGREE = 0x00000100,
		NCTI_DCM3_BS_KNOT_VECTOR = 0x00000200,
		NCTI_DCM3_BS_CP_N = 0x00000400,
		NCTI_DCM3_BS_CP_G_NODES = 0x00000800,
		NCTI_DCM3_BS_CP_VECTORS = 0x00001000,
		NCTI_DCM3_BS_CP_WEIGHTS = 0x00002000,
		NCTI_DCM3_BS_CP_FREEDOMS = 0x00004000,
		NCTI_DCM3_BS_INTERP_N = 0x00008000,
		NCTI_DCM3_BS_INTERP_G_NODES = 0x00010000,
		NCTI_DCM3_BS_INTERP_VECTORS = 0x00020000,
		NCTI_DCM3_BS_INTERP_PARAMETERS = 0x00040000,
		NCTI_DCM3_BS_INTERP_TYPES = 0x00080000,
		NCTI_DCM3_BS_INTERP_WEIGHTS = 0x00100000,
		NCTI_DCM3_BS_INTERP_DURATIONS = 0x00200000,
		NCTI_DCM3_BS_INTERP_STATUSES = 0x00400000,
		NCTI_DCM3_BS_INTERP_CON_BAL = 0x00800000,
		NCTI_DCM3_BS_INTERP_D_STATUSES = 0x01000000,
		NCTI_DCM3_BS_INTERP_MAGNITUDE = 0x02000000
	} ncti_DCM3_bs_data_mask;


	typedef enum ncti_DCM3_bs_surface_data_mask {
		NCTI_DCM3_BS_SURFACE_RIGIDITY = 0x00000001,
		NCTI_DCM3_BS_SURFACE_U_PERIODICITY = 0x00000002,
		NCTI_DCM3_BS_SURFACE_V_PERIODICITY = 0x00000004,
		NCTI_DCM3_BS_SURFACE_RATIONALITY = 0x00000008,
		NCTI_DCM3_BS_SURFACE_U_DEGREE = 0x00000010,
		NCTI_DCM3_BS_SURFACE_V_DEGREE = 0x00000020,
		NCTI_DCM3_BS_SURFACE_U_KNOT_VECTOR = 0x00000040,
		NCTI_DCM3_BS_SURFACE_V_KNOT_VECTOR = 0x00000080,
		NCTI_DCM3_BS_SURFACE_U_CP_N = 0x00000100,
		NCTI_DCM3_BS_SURFACE_V_CP_N = 0x00000200,
		NCTI_DCM3_BS_SURFACE_CP_VECTORS = 0x00000400,
		NCTI_DCM3_BS_SURFACE_CP_WEIGHTS = 0x00000800
	} ncti_DCM3_bs_surface_data_mask;

	typedef enum ncti_DCM3_directed_type {
		NCTI_DCM3_NOT_DIRECTED,				/* Not a directed distance */
		NCTI_DCM3_FIXED_DIRECTION,			/* Distance measured in a fixed direction */
		NCTI_DCM3_PARALLEL_TO_GEOM			/* Distance measured parallel to a given geometry */
	} ncti_DCM3_directed_type;

	/*10 generated surfaces types*/
	typedef enum ncti_DCM3_generated_surface_status
	{
		NCTI_DCM3_GS_STATUS_UNDEFINED_ERROR = 0x00000001,
		NCTI_DCM3_GS_STATUS_INVALID_GENERATOR = 0x00000002,
		NCTI_DCM3_GS_STATUS_SWEEP_GENERATOR_NOT_G1_CONTINUOUS = 0x00000004,
		NCTI_DCM3_GS_STATUS_SWEEP_DIRECTION_INCORRECT = 0x00000008,
		NCTI_DCM3_GS_STATUS_SPIN_GENERATOR_NOT_C1_CONTINUOUS = 0x00000010,
		NCTI_DCM3_GS_STATUS_SPIN_GENERATOR_NOT_PLANAR = 0x00000020,
		NCTI_DCM3_GS_STATUS_SPIN_DIRECTION_INCORRECT = 0x00000040,
		NCTI_DCM3_GS_STATUS_SPIN_BASEPOINT_INCORRECT = 0x00000080,
		NCTI_DCM3_GS_STATUS_SPIN_AXIS_NOT_IN_GENERATOR_PLANE = 0x00000100
	} ncti_DCM3_generated_surface_status;

	typedef enum ncti_DCM3_generated_surface_data_mask {
		NCTI_DCM3_GS_TYPE = 0x00000001,
		NCTI_DCM3_GS_GENERATOR_BS = 0x00000002,
		NCTI_DCM3_GS_GENERATOR_GNODE = 0x00000004,
		NCTI_DCM3_GS_DIRECTION = 0x00000008,
		NCTI_DCM3_GS_BASEPOINT = 0x00000010
	} ncti_DCM3_generated_surface_data_mask;

/*12. Overdefined diagnostics */
	typedef enum ncti_DCM3_overdefined_regions_return {
		NCTI_DCM3_ORR_NOT_EVALUATED,
		NCTI_DCM3_ORR_NOT_OVER_DEFINED,
		NCTI_DCM3_ORR_OVER_DEFINED
	} ncti_DCM3_overdefined_regions_return;

	typedef enum ncti_DCM3_overdefined_region_type {
		NCTI_DCM3_ORT_CLASS_CONTRADICTION_PARALLEL,
		NCTI_DCM3_ORT_CLASS_CONTRADICTION_POSITION,
		NCTI_DCM3_ORT_GENERAL,
		NCTI_DCM3_ORT_ORPHANED
	} ncti_DCM3_overdefined_region_type;

	typedef enum ncti_DCM3_piece_type {

		/* Directly applied application nodes
			NCTI_DCM3_piece_data:
				dim always set, according to piece type.
				geometry data set only where indicated.
			Sub-pieces: None.
		  */
		NCTI_DCM3_PT_D_NODE,			/* dim is app pointer to d_node (geom1, 2 and 3 set) */
		NCTI_DCM3_PT_R_NODE,			/* dim is app pointer to r_node (geom1 only set) */
		NCTI_DCM3_PT_E_NODE,			/* dim is app pointer an e_node */
		NCTI_DCM3_PT_P_NODE_FIXED,	/* dim is app pointer a fixed p_node (geom1 set to the parametric g_node) */
		NCTI_DCM3_PT_G_NODE_RIGID,	/* dim is app pointer to a set or rigid spline g_node */
		NCTI_DCM3_PT_G_NODE_FIXED,	/* dim is app pointer to a fixed g_node */
		NCTI_DCM3_PT_G_NODE,			/* dim is app pointer to an orphaned g_node */

		/* Constraints that are sub-components of direct application constraints.
			These are output in preference to the full node if they are sufficient
			to make the model over-defined.
			E.g. A distance between two planes creates an implied parallel.
			NCTI_DCM3_piece_data:
				dim is set to the app ptr to d_node in all cases.
				geom1 and geom2 define implied constraint.
			Sub-pieces: none
			*/
		NCTI_DCM3_PT_D_IMPLIED_PARALLEL = 20,
		NCTI_DCM3_PT_D_IMPLIED_PERPENDICULAR,
		NCTI_DCM3_PT_D_IMPLIED_COINCIDENT,
		NCTI_DCM3_PT_D_IMPLIED_EQUAL_RADIUS,
		NCTI_DCM3_PT_D_IMPLIED_EQUAL_MINOR_RADIUS,
		NCTI_DCM3_PT_D_IMPLIED_EQUAL_HALF_ANGLE,

		/*	Constraints implied by a combination of 2 or more other constraints.
			Only for parallel and position contradictions.
			NCTI_DCM3_piece_data:
				dim is not set
				geom1 and geom2 describe the implied constraint
			Sub-pieces: 2 or more sub-pieces
			*/
		NCTI_DCM3_PT_IMPLIED_PARALLEL = 40,
		NCTI_DCM3_PT_IMPLIED_PERPENDICULAR,
		NCTI_DCM3_PT_IMPLIED_COINCIDENT,

		/*  Constraints implied by rigidity of a set or spline.
			NCTI_DCM3_piece_data:
				dim is not set
				geom1 and geom2 are the geometries linked by the implicit constraint
			Sub-pieces: 2 or more sub-pieces
			*/
		NCTI_DCM3_PT_RIGID_PARALLEL = 60,
		NCTI_DCM3_PT_RIGID_PERPENDICULAR,
		NCTI_DCM3_PT_RIGID_ANGLE,
		NCTI_DCM3_PT_RIGID_COINCIDENT,
		NCTI_DCM3_PT_RIGID_DISTANCE,

		/*  Groups of equivalent constraints where multiple over-defining paths may exist.
			Only for parallel and position contradictions.
			NCTI_DCM3_piece_data:
				dim is not set
				geom1 and geom2 set to representative geometries within the class.
			Sub-pieces: 2 or more sub-pieces comprising all class members
			*/
		NCTI_DCM3_PT_CLASS_PARALLEL = 80,
		NCTI_DCM3_PT_CLASS_CONCENTRIC,
		NCTI_DCM3_PT_CLASS_PLANAR

	} ncti_DCM3_piece_type;

	/*13. Move and evaluate change target*/
	typedef enum ncti_DCM3_move_eval_change {
		NCTI_DCM3_MOVE_EVAL_TRANSFORM,
		NCTI_DCM3_MOVE_EVAL_RADIUS,
		NCTI_DCM3_MOVE_EVAL_MAJOR_RADIUS,
		NCTI_DCM3_MOVE_EVAL_MINOR_RADIUS,
		NCTI_DCM3_MOVE_EVAL_HALF_ANGLE,
		NCTI_DCM3_MOVE_EVAL_PATTERN_VALUE
	} ncti_DCM3_move_eval_change;

	/*14. Misc */

	/* General frustum return value */

	typedef enum ncti_DCM3_f_outcome
	{
		NCTI_DCM3_F_OUTCOME_OK,
		NCTI_DCM3_F_OUTCOME_ERROR,
		NCTI_DCM3_F_OUTCOME_NOT_IMPLEMENTED,
		NCTI_DCM3_F_OUTCOME_NOT_REGISTERED
	} ncti_DCM3_f_outcome;

	typedef enum ncti_DCM3_tos_return {
		NCTI_DCM3_TOSR_NOT_RETURNED,
		NCTI_DCM3_TOSR_RETURNED
	} ncti_DCM3_tos_return;

	typedef enum ncti_DCM3_task_outcome
	{
		NCTI_DCM3_TASK_OUTCOME_OK,
		NCTI_DCM3_TASK_OUTCOME_INVALID,
		NCTI_DCM3_TASK_OUTCOME_ABORTED
	} ncti_DCM3_task_outcome;



	/* Transform bias support */
	typedef enum ncti_DCM3_bias
	{
		NCTI_DCM3_BIAS_TRANSFORM_STRONG = 1,
		NCTI_DCM3_BIAS_TRANSFORM_WEAK = 2
	} ncti_DCM3_bias;


	typedef enum ncti_DCM3_bias_component
	{
		NCTI_DCM3_BIAS_COMPONENT_WHOLE,
		NCTI_DCM3_BIAS_COMPONENT_CENTRE_POINT,
		NCTI_DCM3_BIAS_COMPONENT_AXIS,
		NCTI_DCM3_BIAS_COMPONENT_DIRECTION,
		NCTI_DCM3_BIAS_COMPONENT_INTERNAL_FREEDOM1,
		NCTI_DCM3_BIAS_COMPONENT_INTERNAL_FREEDOM2
	} ncti_DCM3_bias_component;

	typedef enum ncti_DCM3_rigid_accuracy_warning
	{
		NCTI_DCM3_RAW_NEAR_PARALLEL,
		NCTI_DCM3_RAW_NEAR_PERPENDICULAR,
		NCTI_DCM3_RAW_NEAR_COINCIDENCE,
		NCTI_DCM3_RAW_INACCURATE_DIRECTION_BETWEEN
	}  NCTI_DCM3_rigid_accuracy_warning;

	typedef enum ncti_DCM3_accuracy_warning_return
	{
		NCTI_DCM3_AWR_FAILED,
		NCTI_DCM3_AWR_ABORTED,
		NCTI_DCM3_AWR_OPTION_NOT_SET,
		NCTI_DCM3_AWR_NOT_EVALUATED,
		NCTI_DCM3_AWR_SUCCEEDED
	} ncti_DCM3_accuracy_warning_return;

	typedef enum ncti_DCM3_geometry_component
	{
		NCTI_DCM3_GEOMETRY_UNKNOWN,
		NCTI_DCM3_POINT_X,
		NCTI_DCM3_POINT_Y,
		NCTI_DCM3_CIRCLE_RADIUS,
		NCTI_DCM3_CIRCLE_CENTER_X,
		NCTI_DCM3_CIRCLE_CENTER_Y,
		NCTI_DCM3_CYLINDER_RADIUS,
		NCTI_DCM3_SPHERE_RADIUS,
		NCTI_DCM3_SPHERE_CENTER_X,
		NCTI_DCM3_SPHERE_CENTER_Y,
		NCTI_DCM3_ELLIPSE_MINOR_RADIUS,
		NCTI_DCM3_ELLIPSE_MAJOR_RADIUS,
		NCTI_DCM3_ELLIPSE_CENTER_X,
		NCTI_DCM3_ELLIPSE_CENTER_Y,
		NCTI_DCM3_TORUS_MINOR_RADIUS,
		NCTI_DCM3_TORUS_MAJOR_RADIUS,
		NCTI_DCM3_TORUS_CENTER_X,
		NCTI_DCM3_TORUS_CENTER_Y,
		NCTI_DCM3_CONE_HALF_ANGLE
	} ncti_DCM3_geometry_component;

	typedef struct ncti_DCM3_bs_data {
		Ncti_UInteger			data_mask;
		Ncti_UInteger			bad_data_mask;
		ncti_DCM3_bs_rigidity			rigidity;
		ncti_DCM3_bs_periodicity		periodicity;
		ncti_DCM3_bs_rationality		rationality;
		ncti_DCM3_bs_planarity	 planarity;
		ncti_DCM3_bs_dependence		dependence;
		ncti_DCM3_bs_solving_mode		solving_mode;
		ncti_DCM3_bs_parameterisation	parameterisation;
		ncti_DCM3_bs_knot_generation  knot_generation;
		Ncti_Integer						degree;
		std::vector<Ncti_Double>  knot_vector;
		Ncti_Integer						cp_n;
		std::vector<NCTI_G_NODE> cp_g_nodes;
		std::vector<Ncti_Double> cp_vectors;
		std::vector<Ncti_Double> cp_weights;
		std::vector<ncti_DCM3_bs_cp_freedom> cp_freedoms;
		Ncti_Integer						interp_n;
		std::vector<NCTI_G_NODE> interp_g_nodes;
		std::vector<Ncti_Double> interp_vectors;
		std::vector<Ncti_Double> interp_parameters;
		std::vector<ncti_DCM3_bs_itype> interp_types;
		std::vector<Ncti_Double> interp_weights;
		std::vector<ncti_DCM3_bs_iduration> interp_durations;
		std::vector<ncti_DCM3_bs_istatus> interp_statuses;
		Ncti_Integer						interp_con_bal;
		std::vector<ncti_DCM3_d_node_status> interp_d_statuses;
		ncti_DCM3_bs_interp_magnitude interp_magnitude;
	} ncti_DCM3_bs_data;

	typedef struct ncti_DCM3_generated_surface_data {
		unsigned int data_mask;
		unsigned int bad_data_mask;
		ncti_DCM3_g_type type;
		ncti_DCM3_bs_data* generator_bs;
		double direction[3];
		double basepoint[3];
	}ncti_DCM3_generated_surface_data;

	typedef struct ncti_DCM3_piece_data {

		NctiDisplayObject* dim = nullptr;							/* Application pointer to over-defining node. May be NULL */

		NctiDisplayDCM3Geometry* geom1 = nullptr;						/* First geometry in piece. May be NULL */
		ncti_DCM3_dimension_to geom1_dim_to;		/* Component of geom1 */

		NctiDisplayDCM3Geometry* geom2 = nullptr;
		ncti_DCM3_dimension_to geom2_dim_to;

		NctiDisplayDCM3Geometry* geom3 = nullptr;
		ncti_DCM3_dimension_to geom3_dim_to;

		ncti_DCM3_piece_type type;				/* Type of constraint that is over-defining the region.
											   The type defines which other member data is set */

		void* id = nullptr;							/* Identifier for sub-pieces */

	} ncti_DCM3_piece_data;

	typedef struct ncti_DCM3_bs_surface_data {
		Ncti_UInteger			data_mask;
		ncti_DCM3_bs_rigidity		rigidity;
		ncti_DCM3_bs_periodicity		u_periodicity;
		ncti_DCM3_bs_periodicity		v_periodicity;
		ncti_DCM3_bs_rationality		rationality;
		Ncti_Integer				u_degree = 0;
		Ncti_Integer				v_degree = 0;
		std::vector<Ncti_Double> u_knot_vector;
		std::vector<Ncti_Double> v_knot_vector;
		Ncti_Integer				u_cp_n = 0;
		Ncti_Integer				v_cp_n = 0;
		std::vector<Ncti_Double> cp_vectors;
		std::vector<Ncti_Double> cp_weights;
	} ncti_DCM3_bs_surface_data;

	typedef struct ncti_DCM3_constraint_data {
		NctiDisplayDCM3Dimension* dim = nullptr;
		NctiDisplayDCM3Geometry* geom1 = nullptr;					
		NctiDisplayDCM3Geometry* geom2 = nullptr;
		NctiDisplayDCM3Geometry* geom3 = nullptr;
	} ncti_DCM3_constraint_data;

	const std::map<ncti_DCM3_d_type, const char*> nctiConsTypeMap
	{
		{NCTI_DCM3_DISTANCE, "DCM3_DISTANCE"},
		{NCTI_DCM3_ANGLE, "DCM3_ANGLE"},
		{NCTI_DCM3_CONCENTRIC, "DCM3_CONCENTRIC"},
		{NCTI_DCM3_RADIUS, "DCM3_RADIUS"},
		{NCTI_DCM3_COINCIDENT, "DCM3_COINCIDENT"},
		{NCTI_DCM3_PARALLEL, "DCM3_PARALLEL"},
		{NCTI_DCM3_PERPENDICULAR, "DCM3_PERPENDICULAR"},
		{NCTI_DCM3_TANGENT, "DCM3_TANGENT"},
		{NCTI_DCM3_MAJOR_RADIUS, "DCM3_MAJOR_RADIUS"},
		{NCTI_DCM3_MINOR_RADIUS, "DCM3_MINOR_RADIUS"},
		{NCTI_DCM3_EQUAL_RADIUS, "DCM3_EQUAL_RADIUS"},
		{NCTI_DCM3_MIDPOINT, "DCM3_MIDPOINT"},
		{NCTI_DCM3_DEPENDENCE, "DCM3_DEPENDENCE"},
		{NCTI_DCM3_EQUAL_PARAMETER, "DCM3_EQUAL_PARAMETER"},
		{NCTI_DCM3_EQUAL_DIRECTION, "DCM3_EQUAL_DIRECTION"},
		{NCTI_DCM3_EQUAL_CURVATURE, "DCM3_EQUAL_CURVATURE"},
		{NCTI_DCM3_EQUAL_FIRST_DERIVATIVE, "DCM3_EQUAL_FIRST_DERIVATIVE"},
		{NCTI_DCM3_EQUAL_SECOND_DERIVATIVE, "DCM3_EQUAL_SECOND_DERIVATIVE"},
		{NCTI_DCM3_CURVE_LENGTH, "DCM3_CURVE_LENGTH"},
		{NCTI_DCM3_SYMMETRIC, "DCM3_SYMMETRIC"},
		{NCTI_DCM3_HALF_ANGLE, "DCM3_HALF_ANGLE"},
		{NCTI_DCM3_COINCIDENT_AROUND_SPINE, "DCM3_COINCIDENT_AROUND_SPINE"},
		{NCTI_DCM3_COINCIDENT_WITH_SPINE, "DCM3_COINCIDENT_WITH_SPINE"},
		{NCTI_DCM3_EQUAL_HALF_ANGLE, "DCM3_EQUAL_HALF_ANGLE"},
		{NCTI_DCM3_EQUAL_CURVATURE_VECTOR, "DCM3_EQUAL_CURVATURE_VECTOR"},
		{NCTI_DCM3_ANGLE_PLANAR, "DCM3_ANGLE_PLANAR"},
		{NCTI_DCM3_SURFACE_NORMAL, "DCM3_SURFACE_NORMAL"},
		{NCTI_DCM3_PATTERNED, "DCM3_PATTERNED"},
		{NCTI_DCM3_PATTERN_VALUE, "DCM3_PATTERN_VALUE"},
		{NCTI_DCM3_EQUAL_DISTANCED, "DCM3_EQUAL_DISTANCED"},
		{NCTI_DCM3_EQUAL_DISTANCE_VALUE, "DCM3_EQUAL_DISTANCE_VALUE"}
	};

	const std::map<ncti_DCM3_d_node_status, const char*> nctiDNodeStatusMap
	{
		{NCTI_DCM3_D_UNKNOWN, "DCM3_D_UNKNOWN"},
		{NCTI_DCM3_D_OVER_DEFINED, "DCM3_D_OVER_DEFINED"},
		{NCTI_DCM3_D_NOT_CONSISTENT, "DCM3_D_NOT_CONSISTENT"},
		{NCTI_DCM3_D_NOT_CONSISTENT_DIMENSIONS, "DCM3_D_NOT_CONSISTENT_DIMENSIONS"},
		{NCTI_DCM3_D_NOT_CONSISTENT_OTHER, "DCM3_D_NOT_CONSISTENT_OTHER"},
		{NCTI_DCM3_D_NOT_CONSISTENT_UNKNOWN, "DCM3_D_NOT_CONSISTENT_UNKNOWN"},
		{NCTI_DCM3_D_NOT_CHANGED, "DCM3_D_NOT_CHANGED"},
		{NCTI_DCM3_D_BETWEEN_SET_MEMBERS, "DCM3_D_BETWEEN_SET_MEMBERS"},
		{NCTI_DCM3_D_BETWEEN_FIXED, "DCM3_D_BETWEEN_FIXED"},
		{DCM3_D_CONSTRAINS_RIGID, "DCM3_D_BETWEEN_FIXED"},
		{NCTI_DCM3_D_NOT_SOLVED, "DCM3_D_NOT_SOLVED"},
		{NCTI_DCM3_D_SOLVED, "DCM3_D_SOLVED"}
	};


	const std::map< ncti_DCM3_g_node_status, const char*> nctiGNodeStatusMap
	{
		{NCTI_DCM3_G_UNKNOWN, "DCM3_G_UNKNOWN"},
		{NCTI_DCM3_G_FIXED, "DCM3_G_FIXED"},
		{NCTI_DCM3_G_OVER_DEFINED, "DCM3_G_OVER_DEFINED"},
		{NCTI_DCM3_G_NOT_CONSISTENT, "DCM3_G_NOT_CONSISTENT"},
		{NCTI_DCM3_G_NOT_CONSISTENT_DIMENSIONS, "DCM3_G_NOT_CONSISTENT_DIMENSIONS"},
		{NCTI_DCM3_G_NOT_CONSISTENT_OTHER, "DCM3_G_NOT_CONSISTENT_OTHER"},
		{NCTI_DCM3_G_NOT_CONSISTENT_UNKNOWN, "DCM3_G_NOT_CONSISTENT_UNKNOWN"},
		{NCTI_DCM3_G_NOT_CHANGED, "DCM3_G_NOT_CHANGED"},
		{NCTI_DCM3_G_WELL_DEFINED, "DCM3_G_WELL_DEFINED"},
		{NCTI_DCM3_G_UNDER_DEFINED, "DCM3_G_UNDER_DEFINED"},
		{NCTI_DCM3_G_WITHIN_BOUNDS, "DCM3_G_WITHIN_BOUNDS"}
	};

	const std::map<ncti_DCM3_help_points, const char*> nctiHelpPointsMap
	{
		{NCTI_DCM3_DIM_TO_HELP_POINT, "DCM3_DIM_TO_HELP_POINT"},
		{NCTI_DCM3_DIM_TO_BOUNDARY, "DCM3_DIM_TO_BOUNDARY"},
		{NCTI_DCM3_DIM_TO_CENTRE, "DCM3_DIM_TO_CENTRE"},
		{NCTI_DCM3_DIM_TO_INTERNAL_HELP_POINT, "DCM3_DIM_TO_INTERNAL_HELP_POINT"}
	};

	const std::map<ncti_DCM3_dimension_to, const char*> nctiDimensionToMap
	{
		{NCTI_DCM3_DIMENSION_TO_NOT_SPECIFIED, "DCM3_DIMENSION_TO_NOT_SPECIFIED"},
		{NCTI_DCM3_DIMENSION_TO_EXTERIOR, "DCM3_DIMENSION_TO_EXTERIOR"},
		{NCTI_DCM3_DIMENSION_TO_CENTRE_POINT, "DCM3_DIMENSION_TO_CENTRE_POINT"},
		{NCTI_DCM3_DIMENSION_TO_AXIS, "DCM3_DIMENSION_TO_AXIS"},
		{NCTI_DCM3_DIMENSION_TO_PLANE, "DCM3_DIMENSION_TO_PLANE"},
		{NCTI_DCM3_DIMENSION_TO_SPINE, "DCM3_DIMENSION_TO_SPINE"},
		{NCTI_DCM3_DIMENSION_TO_APEX, "DCM3_DIMENSION_TO_APEX"},
		{NCTI_DCM3_DIMENSION_TO_MAJOR_AXIS, "DCM3_DIMENSION_TO_MAJOR_AXIS"}
	};


	const std::map<ncti_DCM3_parametric_type, const char*> nctiParametricTypeMap
	{
		{NCTI_DCM3_PARAMETRIC_PERIODIC, "DCM3_PARAMETRIC_PERIODIC"},
		{NCTI_DCM3_PARAMETRIC_BOUNDED, "DCM3_PARAMETRIC_BOUNDE"}
	};


	const std::map<ncti_DCM3_discontinuity_side, const char*> nctiDiscontinuitySideMap
	{
		{NCTI_DCM3_DS_LOWER, "DCM3_DS_LOWER"},
		{NCTI_DCM3_DS_UPPER, "DCM3_DS_UPPER"},
		{NCTI_DCM3_DS_NO_DISCONTINUITY, "DCM3_DS_NO_DISCONTINUITY"}
	};

	const std::map<ncti_DCM3_bias, const char*> nctiBiasMap
	{
		{NCTI_DCM3_BIAS_TRANSFORM_STRONG, "DCM3_BIAS_TRANSFORM_STRONG"},
		{NCTI_DCM3_BIAS_TRANSFORM_WEAK, "DCM3_BIAS_TRANSFORM_WEAK"}
	};

	const std::map<ncti_DCM3_bias_component, const char*> nctiBiasComponentMap
	{
		{NCTI_DCM3_BIAS_COMPONENT_WHOLE, "DCM3_BIAS_COMPONENT_WHOLE"},
		{NCTI_DCM3_BIAS_COMPONENT_CENTRE_POINT, "DCM3_BIAS_COMPONENT_CENTRE_POINT"},
		{NCTI_DCM3_BIAS_COMPONENT_AXIS, "DCM3_BIAS_COMPONENT_AXIS"},
		{NCTI_DCM3_BIAS_COMPONENT_DIRECTION, "DCM3_BIAS_COMPONENT_DIRECTION"},
		{NCTI_DCM3_BIAS_COMPONENT_INTERNAL_FREEDOM1, "DCM3_BIAS_COMPONENT_INTERNAL_FREEDOM1"},
		{NCTI_DCM3_BIAS_COMPONENT_INTERNAL_FREEDOM2, "DCM3_BIAS_COMPONENT_INTERNAL_FREEDOM2"}
	};

	const std::map<ncti_DCM3_bs_data_mask, const char*> nctiBSDataMask
	{
		{NCTI_DCM3_BS_RIGIDITY, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_PERIODICITY, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_RATIONALITY, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_PLANARITY, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_DEPENDENCE, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_SOLVING_MODE, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_PARAMETERISATION, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_KNOT_GENERATION, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_DEGREE, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_KNOT_VECTOR, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_CP_N, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_CP_G_NODES, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_CP_VECTORS, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_CP_WEIGHTS, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_CP_FREEDOMS, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_N, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_G_NODES, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_VECTORS, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_PARAMETERS, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_TYPES, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_WEIGHTS, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_DURATIONS, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_STATUSES, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_CON_BAL, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_D_STATUSES, "DCM3_BS_RIGIDITY" },
		{NCTI_DCM3_BS_INTERP_MAGNITUDE, "DCM3_BS_RIGIDITY" }
	};

	const std::map<ncti_DCM3_bs_periodicity, const char*> nctiBSPeriodicityMap
	{
		{NCTI_DCM3_BS_PERIODICITY_NON_PER, "DCM3_BS_PERIODICITY_NON_PER" },
		{NCTI_DCM3_BS_PERIODICITY_PER, "DCM3_BS_PERIODICITY_PER" }
	} ;

	const std::map<ncti_DCM3_bs_rigidity, const char*> nctiBSRigidityMap
	{
		{NCTI_DCM3_BS_RIGIDITY_RIGID, "DCM3_BS_RIGIDITY_RIGID" },
		{NCTI_DCM3_BS_RIGIDITY_SCALABLE, "DCM3_BS_RIGIDITY_SCALABLE" },
		{NCTI_DCM3_BS_RIGIDITY_FLEXIBLE, "DCM3_BS_RIGIDITY_FLEXIBLE" }
	};

	const std::map<ncti_DCM3_bs_rationality, const char*> nctiBSRationalityMap
	{
		{NCTI_DCM3_BS_RATIONALITY_NON_RAT, "DCM3_BS_RATIONALITY_NON_RAT" },
		{NCTI_DCM3_BS_RATIONALITY_RAT, "DCM3_BS_RATIONALITY_RAT" }
	};

	const std::map<ncti_DCM3_alignment, const char*> nctiAlignmentMap
	{
		{NCTI_DCM3_ALIGNMENT_NOT_SPECIFIED, "DCM3_ALIGNMENT_NOT_SPECIFIED" },
		{NCTI_DCM3_ALIGNMENT_ALIGN, "DCM3_ALIGNMENT_ALIGN" },
		{NCTI_DCM3_ALIGNMENT_ANTI_ALIGN, "DCM3_ALIGNMENT_ANTI_ALIGN" }
	};

	const std::map<ncti_DCM3_surface_orientation, const char*> nctiOrientationMap
	{
		{NCTI_DCM3_SURFACE_ORIENTATION_NOT_SPECIFIED, "DCM3_SURFACE_ORIENTATION_NOT_SPECIFIED" },
		{NCTI_DCM3_SURFACE_ORIENTATION_ALIGN, "DCM3_SURFACE_ORIENTATION_ALIGN" },
		{NCTI_DCM3_SURFACE_ORIENTATION_ANTI_ALIGN, "DCM3_SURFACE_ORIENTATION_ANTI_ALIGN" }
	};

	const std::map<ncti_DCM3_g_type, const char*> nctiGeoTypeMap
	{
		{NCTI_DCM3_POINT, "DCM3_POINT"},
		{NCTI_DCM3_LINE, "DCM3_LINE"},
		{NCTI_DCM3_CIRCLE, "DCM3_CIRCLE"},
		{NCTI_DCM3_PLANE, "DCM3_PLANE"},
		{NCTI_DCM3_CYLINDER, "DCM3_CYLINDER"},
		{NCTI_DCM3_SPHERE, "DCM3_SPHERE"},
		{NCTI_DCM3_SWEEP_SURFACE, "DCM3_SWEEP_SURFACE"},
		{NCTI_DCM3_PARAMETRIC_SURFACE, "DCM3_PARAMETRIC_SURFACE"},
		{NCTI_DCM3_PARAMETRIC_CURVE, "DCM3_PARAMETRIC_CURVE"},
		{NCTI_DCM3_SPLINE_CURVE, "DCM3_SPLINE_CURVE"},
		{NCTI_DCM3_SET, "DCM3_SET"},
		{NCTI_DCM3_TORUS, "DCM3_TORUS"},
		{NCTI_DCM3_CONE, "DCM3_CONE"},
		{NCTI_DCM3_ELLIPSE, "DCM3_ELLIPSE"},
		{NCTI_DCM3_SPLINE_SURFACE, "DCM3_SPLINE_SURFACE"},
		{NCTI_DCM3_SPIN_SURFACE, "DCM3_SPIN_SURFACE"},
		{NCTI_DCM3_LINEAR_PATTERN, "DCM3_LINEAR_PATTERN"},
		{NCTI_DCM3_PATTERN_ARRAY, "DCM3_PATTERN_ARRAY"},
		{NCTI_DCM3_CIRCULAR_PATTERN, "DCM3_CIRCULAR_PATTERN"},
		{NCTI_DCM3_SWEEP_SPLINE_SURFACE, "DCM3_SWEEP_SPLINE_SURFACE"},
		{NCTI_DCM3_EQUAL_DISTANCE, "DCM3_EQUAL_DISTANCE"},
		{NCTI_DCM3_SPIN_SPLINE_SURFACE, "DCM3_SPIN_SPLINE_SURFACE"},
		{NCTI_DCM3_UNKNOWN, "DCM3_UNKNOWN"}
	};

	const std::map<ncti_DCM3_e_type, const char*> nctiEquationTypeMap
	{
		{NCTI_DCM3_LINEAR_EQUATION, "DCM3_LINEAR_EQUATION" },
		{NCTI_DCM3_NON_LINEAR_EQUATION, "DCM3_NON_LINEAR_EQUATION" },
		{NCTI_DCM3_LINEAR_INEQUALITY, "DCM3_LINEAR_INEQUALITY" },
		{NCTI_DCM3_UNKNOWN_EQUATION, "DCM3_UNKNOWN_EQUATION" }
	};
}
#endif
