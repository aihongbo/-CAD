#ifndef NctiDCMDef_H
#define NctiDCMDef_H
#ifndef NCTI_DCM_logical
#define NCTI_DCM_logical int
#define NCTI_DCM_TRUE 1
#define NCTI_DCM_FALSE 0
#endif
#include "ncti_base.h"
#include <vector>
#include <map>
namespace NCTI
{
	typedef enum ncti_g_node_status {
		NCTI_G_UNKNOWN,						/* unknown status (newly added to system) */
		NCTI_G_FIXED,       			      	/* geometry has been declared fixed	*/
		NCTI_G_FROZEN,						/* geometry has been declared frozen */
		NCTI_G_OVER_DEFINED,					/* geometry is over defined by dimensions */
		NCTI_G_NON_ALGEBRAIC,				/* geometry can only be solved non-algebraically */
		NCTI_G_NOT_CONSISTENT,				/* geometry inconsistently defined	*/
		NCTI_G_NOT_CONSISTENT_DIMENSIONS,	/* geometry inconsistently defined by */
		/* dimensions */
		NCTI_G_NOT_CONSISTENT_OTHER,			/* geometry inconsistently defined due to */
		/* other causes */
		NCTI_G_NOT_CONSISTENT_UNKNOWN,		/* geometry inconsistently defined and there */
		/* is insufficient information available to */
		/* determine the cause */
		NCTI_G_NOT_CHANGED,					/* geometry was not changed	*/
		NCTI_G_WELL_DEFINED,					/* geometry is well defined by dimensions */
		NCTI_G_UNDER_DEFINED					/* geometry is underdefined by dimensions */
	} ncti_g_node_status;

	typedef enum ncti_DCM_g_type {
		NCTI_DCM_POINT,
		NCTI_DCM_LINE,
		NCTI_DCM_CIRCLE,
		NCTI_DCM_ELLIPSE,
		NCTI_DCM_PARAMETRIC,
		NCTI_DCM_SPLINE,
		NCTI_DCM_CONIC,
		NCTI_DCM_SCALABLE_SET,
		NCTI_DCM_UNI_SCALABLE_SET,
		NCTI_DCM_BI_SCALABLE_SET,
		NCTI_DCM_SET,
		NCTI_DCM_PATTERN,
		NCTI_DCM_PATTERN2D,
		NCTI_DCM_UNKNOWN
	} ncti_DCM_g_type;

	typedef enum NctiDCMEXGType {
		EX_POINT,
		EX_LINE,
		EX_CIRCLE,
		EX_ELLIPSE,
		EX_PARAMETRIC,
		EX_SPLINE,
		EX_SCALABLE_SPLINE,
		EX_UNI_SCALABLE_SPLINE,
		EX_CONIC,
		EX_SCALABLE_SET,
		EX_UNI_SCALABLE_SET,
		EX_BI_SCALABLE_SET,
		EX_SET,
		EX_PERIMETER,
		EX_OFFSETCURVE,
		EX_COPYCURVE,
		EX_INSTANCE,
		EX_UNKNOWN
	} NctiDCMEXGType;

	typedef enum ncti_DCM_d_type {
		NCTI_DCM_DISTANCE = 0,
		NCTI_DCM_ANGLE = 1,
		NCTI_DCM_CONCENTRIC = 2,
		NCTI_DCM_RADIUS = 3,
		NCTI_DCM_PARALLEL = 4,
		NCTI_DCM_PERPENDICULAR = 5,
		NCTI_DCM_COINCIDENT = 6,
		NCTI_DCM_TANGENT = 7,
		NCTI_DCM_IDENTICAL = 8,
		NCTI_DCM_SYMMETRIC = 9,
		NCTI_DCM_MAJOR_RADIUS = 10,
		NCTI_DCM_MINOR_RADIUS = 11,
		NCTI_DCM_EQUAL_RADIUS = 12,
		NCTI_DCM_EQUAL_DISTANCE = 13,
		NCTI_DCM_MIDPOINT = 14,
		NCTI_DCM_DEPENDENCE = 15,
		NCTI_DCM_PATTERNED = 16,
		NCTI_DCM_EQUAL_PARAMETER = 17,
		NCTI_DCM_NORMAL = 18,
		NCTI_DCM_EQUAL_DIRECTION = 19,
		NCTI_DCM_EQUAL_CURVATURE = 20,
		NCTI_DCM_EQUAL_FIRST_DERIVATIVE = 21,
		NCTI_DCM_EQUAL_SECOND_DERIVATIVE = 22,
		NCTI_DCM_OFFSET = 23,
		NCTI_DCM_SIMPLE_DEPENDENCE = 24,
		NCTI_DCM_CURVE_LENGTH = 25,
		NCTI_DCM_PATTERNED_2D = 26,
		NCTI_DCM_PATTERN_VALUE = 27,
		NCTI_DCM_PATTERN_2D_VALUE_1 = 28,
		NCTI_DCM_PATTERN_2D_VALUE_2 = 29,
		NCTI_DCM_EQUAL_RELATIVE_TRANSFORM = 30,
		NCTI_DCM_ARC_LENGTH = 31,
		NCTI_DCM_LOCK_WHOLE = 32,
		NCTI_DCM_LOCK_CENTRE = 33,
		NCTI_DCM_LOCK_DIRECTION = 34,
		NCTI_DCM_CONIC_RHO = 35,
		NCTI_DCM_EQUAL_CURVATURE_DERIVATIVE = 36,
		NCTI_DCM_D_UNKNOWN = 9999,
	} ncti_DCM_d_type;

	typedef enum ncti_DCM_ellipse_parameter {
		NCTI_DCM_ELLIPSE_PARAMETER_PARAMETER,
		NCTI_DCM_ELLIPSE_PARAMETER_VECTOR
	} ncti_DCM_ellipse_parameter;

	typedef enum ncti_DCM_directed_type {
		NCTI_DCM_NOT_DIRECTED,
		NCTI_DCM_FIXED_DIRECTION,
		NCTI_DCM_PERPENDICULAR_TO_LINE,
		NCTI_DCM_PARALLEL_TO_LINE
	} ncti_DCM_directed_type;

	typedef enum ncti_DCM_half_space {
		NCTI_DCM_HALF_SPACE_NOT_SPECIFIED,	/* to be solved in DCM default direction */
		NCTI_DCM_HALF_SPACE_LEFT,			/* to be solved in left half-space */
		NCTI_DCM_HALF_SPACE_RIGHT			/* to be solved in right half-space */
	} ncti_DCM_half_space;

	typedef enum ncti_DCM_ed_alignment {
		NCTI_DCM_ED_ALIGNMENT_EQUAL,
		NCTI_DCM_ED_ALIGNMENT_OPPOSITE,
		NCTI_DCM_ED_ALIGNMENT_CURRENT
	} ncti_DCM_ed_alignment;

	typedef enum ncti_DCM_tan_alignment {
		NCTI_DCM_TAN_ALIGNMENT_EQUAL,
		NCTI_DCM_TAN_ALIGNMENT_OPPOSITE,
		NCTI_DCM_TAN_ALIGNMENT_CURRENT,
		NCTI_DCM_TAN_ALIGNMENT_FREE
	} ncti_DCM_tan_alignment;

	typedef enum ncti_DCM_norm_alignment {
		NCTI_DCM_NORM_ALIGNMENT_CLOCKWISE,
		NCTI_DCM_NORM_ALIGNMENT_ANTICLOCKWISE,
		NCTI_DCM_NORM_ALIGNMENT_CURRENT,
		NCTI_DCM_NORM_ALIGNMENT_FREE
	} ncti_DCM_norm_alignment;

	typedef enum ncti_DCM_alignment {
		NCTI_DCM_ALIGNMENT_NOT_SPECIFIED,
		NCTI_DCM_ALIGNMENT_CURRENT,
		NCTI_DCM_ALIGNMENT_ALIGN,
		NCTI_DCM_ALIGNMENT_ANTI_ALIGN,
		NCTI_DCM_ALIGNMENT_CLOCKWISE,
		NCTI_DCM_ALIGNMENT_ANTICLOCKWISE
	} ncti_DCM_alignment;

	typedef enum ncti_DCM_sym_alignment {
		NCTI_DCM_SYM_ALIGNMENT_NOT_SPECIFIED,
		NCTI_DCM_SYM_ALIGNMENT_CURRENT,
		NCTI_DCM_SYM_ALIGNMENT_ALIGN,
		NCTI_DCM_SYM_ALIGNMENT_ANTI_ALIGN
	} ncti_DCM_sym_alignment;

	typedef enum ncti_DCM_d_rigidity {
		NCTI_DCM_DIMENSION_NON_RIGID,
		NCTI_DCM_DIMENSION_RIGID
	} ncti_DCM_d_rigidity;
	typedef enum ncti_DCM_bs_periodicity {
		NCTI_DCM_BS_PERIODICITY_NON_PER,
		NCTI_DCM_BS_PERIODICITY_PER
	} ncti_DCM_bs_periodicity;

	typedef enum ncti_DCM_bs_status {
		NCTI_DCM_BS_STATUS_OK,
		NCTI_DCM_BS_STATUS_NOT_A_SPLINE,
		NCTI_DCM_BS_STATUS_BAD_DATA,
		NCTI_DCM_BS_STATUS_OVER_DEFINED,
		NCTI_DCM_BS_STATUS_NOT_SOLVED
	} ncti_DCM_bs_status;

	typedef enum ncti_DCM_bs_rigidity {
		NCTI_DCM_BS_RIGIDITY_RIGID,
		NCTI_DCM_BS_RIGIDITY_SCALABLE,
		NCTI_DCM_BS_RIGIDITY_UNI_SCALABLE,
		NCTI_DCM_BS_RIGIDITY_FLEXIBLE,
		NCTI_DCM_BS_RIGIDITY_BI_SCALABLE
	} ncti_DCM_bs_rigidity;

	typedef enum ncti_DCM_bs_rationality {
		NCTI_DCM_BS_RATIONALITY_NON_RAT,
		NCTI_DCM_BS_RATIONALITY_RAT
	} ncti_DCM_bs_rationality;

	typedef enum ncti_DCM_bs_dependence {
		NCTI_DCM_BS_DEPENDENCE_CP,
		NCTI_DCM_BS_DEPENDENCE_INTERP
	} ncti_DCM_bs_dependence;

	typedef enum ncti_DCM_bs_solving_mode {
		NCTI_DCM_BS_SOLVING_MODE_STANDARD,
		NCTI_DCM_BS_SOLVING_MODE_LOCAL
	} ncti_DCM_bs_solving_mode;

	typedef enum ncti_DCM_bs_parameterisation {
		NCTI_DCM_BS_PARAMETERISATION_FIXED,              /* User-defined fixed */
		NCTI_DCM_BS_PARAMETERISATION_VARIABLE,           /* User-defined variable */
		NCTI_DCM_BS_PARAMETERISATION_CHORD_LENGTH,       /* Automatic chord-length parameterisation */
		NCTI_DCM_BS_PARAMETERISATION_CENTRIPETAL,        /* Automatic centripetal parameterisation */
		NCTI_DCM_BS_PARAMETERISATION_CHORD_LENGTH_69     /* Legacy behaviour for chord-length parameterisation */
	} ncti_DCM_bs_parameterisation;

	typedef enum ncti_DCM_bs_cp_freedom {
		NCTI_DCM_BS_CP_FREEDOM_FREE,
		NCTI_DCM_BS_CP_FREEDOM_FIXED
	} ncti_DCM_bs_cp_freedom;

	typedef enum ncti_DCM_bs_itype {
		NCTI_DCM_BS_ITYPE_COI,
		NCTI_DCM_BS_ITYPE_G_COI,
		NCTI_DCM_BS_ITYPE_DERIV1,
		NCTI_DCM_BS_ITYPE_DERIV2,
		NCTI_DCM_BS_ITYPE_CURVATURE,						/* Not currently supported */
		NCTI_DCM_BS_ITYPE_DERIV1_DIR,
		NCTI_DCM_BS_ITYPE_DERIV1_LEN
	} ncti_DCM_bs_itype;

	typedef enum ncti_DCM_bs_iduration {
		NCTI_DCM_BS_IDURATION_REFRESH_ONLY,
		NCTI_DCM_BS_IDURATION_ALWAYS,
		NCTI_DCM_BS_IDURATION_CREATION_ONLY
	} ncti_DCM_bs_iduration;

	typedef enum ncti_DCM_bs_istatus {
		NCTI_DCM_BS_ISTATUS_SOLVED,
		NCTI_DCM_BS_ISTATUS_REMOVED,
		NCTI_DCM_BS_ISTATUS_OVER_DEFINED,
		NCTI_DCM_BS_ISTATUS_NOT_SOLVED
	} ncti_DCM_bs_istatus;

	typedef enum ncti_DCM_bs_data_mask {
		NCTI_DCM_BS_RIGIDITY = 0x00000001,
		NCTI_DCM_BS_PERIODICITY = 0x00000002,
		NCTI_DCM_BS_RATIONALITY = 0x00000004,
		NCTI_DCM_BS_DEPENDENCE = 0x00000008,
		NCTI_DCM_BS_SOLVING_MODE = 0x00000010,
		NCTI_DCM_BS_PARAMETERISATION = 0x00000020,
		NCTI_DCM_BS_DEGREE = 0x00000040,
		NCTI_DCM_BS_KNOT_VECTOR = 0x00000080,
		NCTI_DCM_BS_CP_N = 0x00000100,
		NCTI_DCM_BS_CP_G_NODES = 0x00000200,
		NCTI_DCM_BS_CP_VECTORS = 0x00000400,
		NCTI_DCM_BS_CP_WEIGHTS = 0x00000800,
		NCTI_DCM_BS_CP_FREEDOMS = 0x00001000,
		NCTI_DCM_BS_INTERP_N = 0x00002000,
		NCTI_DCM_BS_INTERP_G_NODES = 0x00004000,
		NCTI_DCM_BS_INTERP_V_NODES = 0x00008000,
		NCTI_DCM_BS_INTERP_VECTORS = 0x00010000,
		NCTI_DCM_BS_INTERP_PARAMETERS = 0x00020000,
		NCTI_DCM_BS_INTERP_TYPES = 0x00040000,
		NCTI_DCM_BS_INTERP_WEIGHTS = 0x00080000,
		NCTI_DCM_BS_INTERP_DURATIONS = 0x00100000,
		NCTI_DCM_BS_INTERP_STATUSES = 0x00200000,
		NCTI_DCM_BS_INTERP_CON_BAL = 0x00400000,
		NCTI_DCM_BS_INTERP_D_STATUSES = 0x00800000,
		NCTI_DCM_BS_SCALE_DIRECTION = 0x01000000
	} ncti_DCM_bs_data_mask;

	typedef enum ncti_d_node_status {
		NCTI_D_UNKNOWN,						/* unknown status (newly added to system) */
		NCTI_D_BETWEEN_FIXED,				/* dimension not solved as it is between */
		/* fixed or frozen geometries */
		NCTI_D_BETWEEN_SET_MEMBERS,			/* dimension not solved as it is between */
		/* members of the same set */
		NCTI_D_OVER_DEFINED,					/* dimension specification is over-defined */
		NCTI_D_NON_ALGEBRAIC,			 	/* dimension can only be solved non-algebraically */
		NCTI_D_NOT_CONSISTENT,				/* given dimension value is inconsistent */
		NCTI_D_NOT_CONSISTENT_DIMENSIONS,	/* given dimension value is inconsistent due */
		/* to a bad dimensioning scheme	*/
		NCTI_D_NOT_CONSISTENT_OTHER,			/* given dimension value is inconsistent due to */
		/* other causes */
		NCTI_D_NOT_CONSISTENT_UNKNOWN,		/* dimension value inconsistent and there */
		/* is insufficient information available to */
		/* determine the cause */
		NCTI_D_NOT_SOLVED,					/* dimension not solved as it is either not */
		/* satisfied or connected to geometries with a */
		/* NOT_CHANGED status or a NOT_CONSISTENT status */
		NCTI_D_NOT_CHANGED,					/* given dimension not changed */
		NCTI_D_SOLVED     				  	/* dimension value is satisfied by solution */
	} ncti_d_node_status;

	typedef enum ncti_DCM_transform_status {
		NCTI_DCM_NON_IDENTITY_TRANSFORM_MATRIX = 0x00000001,
		NCTI_DCM_NON_ZERO_INTERNAL_FREEDOM_OFFSET1 = 0x00000002,
		NCTI_DCM_NON_ZERO_INTERNAL_FREEDOM_OFFSET2 = 0x00000004,
		NCTI_DCM_NON_UNIT_SCALE = 0x00000008,
		NCTI_DCM_NON_UNIT_SCALE2 = 0x00000010,
		NCTI_DCM_CIRCLE_INVERTED = 0x00000020,
		NCTI_DCM_INVALID_TRANSFORM = 0x00000040,
		NCTI_DCM_INVALID_NODE = 0x00000080,
		NCTI_DCM_CIRCLE_JUST_INVERTED = 0x00000100
	} ncti_DCM_transform_status;

	typedef struct ncti_DCM_bs_data {
		Ncti_UInteger			data_mask;
		Ncti_UInteger			bad_data_mask;
		ncti_DCM_bs_rigidity			rigidity;
		ncti_DCM_bs_periodicity		periodicity;
		ncti_DCM_bs_rationality		rationality;
		ncti_DCM_bs_dependence		dependence;
		ncti_DCM_bs_solving_mode		solving_mode;
		ncti_DCM_bs_parameterisation	parameterisation;
		Ncti_Integer						degree;
		std::vector<Ncti_Double>  knot_vector;
		Ncti_Integer						cp_n;
		std::vector<NCTI_G_NODE> cp_g_nodes;
		std::vector<Ncti_Double> cp_vectors;
		std::vector<Ncti_Double> cp_weights;
		std::vector<ncti_DCM_bs_cp_freedom> cp_freedoms;
		Ncti_Integer						interp_n;
		std::vector<NCTI_G_NODE> interp_g_nodes;
		std::vector<NCTI_G_NODE> interp_v_nodes;
		std::vector<Ncti_Double> interp_vectors;
		std::vector<Ncti_Double> interp_parameters;
		std::vector<ncti_DCM_bs_itype> interp_types;
		std::vector<Ncti_Double> interp_weights;
		std::vector<ncti_DCM_bs_iduration> interp_durations;
		std::vector<ncti_DCM_bs_istatus> interp_statuses;
		Ncti_Integer						interp_con_bal;
		std::vector<ncti_d_node_status> interp_d_statuses;
		std::vector<Ncti_Double> scale_direction;
	} ncti_DCM_bs_data;

	typedef enum ncti_DCM_dragging_result {
		NCTI_DCM_DRAG_SUCCEEDED,		/* drag succeeded */
		NCTI_DCM_DRAG_FAILED			/* drag failed */
	} ncti_DCM_dragging_result;

	typedef enum ncti_DCM_conic_status {
		NCTI_DCM_CONIC_STATUS_OK,
		NCTI_DCM_CONIC_STATUS_NOT_A_CONIC,
		NCTI_DCM_CONIC_STATUS_WRONG_CONIC_TYPE,
		NCTI_DCM_CONIC_STATUS_BAD_DATA,
		NCTI_DCM_CONIC_STATUS_INCOMPATIBLE_DATA,
		NCTI_DCM_CONIC_STATUS_MISSING_DATA,
		NCTI_DCM_CONIC_STATUS_NOT_SOLVED
	} ncti_DCM_conic_status;

	typedef enum ncti_DCM_conic_data_mask {
		NCTI_DCM_CONIC_TYPE = 0x00000001,
		NCTI_DCM_CONIC_SHAPE = 0x00000002,
		NCTI_DCM_CONIC_RIGIDITY = 0x00000004,
		NCTI_DCM_CONIC_BEZIER_RHO = 0x00000008,
		NCTI_DCM_CONIC_CP_N = 0x00000010,
		NCTI_DCM_CONIC_CP_G_NODES = 0x00000020,
		NCTI_DCM_CONIC_CP_VECTORS = 0x00000040,
		NCTI_DCM_CONIC_AXIS_DIRECTION = 0x00000080,
		NCTI_DCM_CONIC_ECCENTRICITY = 0x00000100,
		NCTI_DCM_CONIC_NEAR_VERTEX = 0x00000200,
		NCTI_DCM_CONIC_NEAR_FOCUS = 0x00000400
	} ncti_DCM_conic_data_mask;

	typedef enum ncti_DCM_conic_type {
		NCTI_DCM_CONIC_TYPE_BEZIER,
		NCTI_DCM_CONIC_TYPE_FIXED_SHAPE_BEZIER,
		NCTI_DCM_CONIC_TYPE_FIXED_RHO_BEZIER
	} ncti_DCM_conic_type;

	typedef enum ncti_DCM_conic_shape {
		NCTI_DCM_CONIC_SHAPE_ELLIPSE,
		NCTI_DCM_CONIC_SHAPE_PARABOLA,
		NCTI_DCM_CONIC_SHAPE_HYPERBOLA
	} ncti_DCM_conic_shape;

	typedef enum ncti_DCM_conic_rigidity {
		NCTI_DCM_CONIC_RIGIDITY_RIGID,
		NCTI_DCM_CONIC_RIGIDITY_SCALABLE,
		NCTI_DCM_CONIC_RIGIDITY_FLEXIBLE
	} ncti_DCM_conic_rigidity;

	typedef struct ncti_DCM_conic_data {
		Ncti_UInteger data_mask;
		Ncti_UInteger bad_data_mask;

		ncti_DCM_conic_type type;
		ncti_DCM_conic_shape shape;
		ncti_DCM_conic_rigidity rigidity;

		Ncti_Double bezier_rho;

		std::vector<NCTI_G_NODE> cp_g_nodes;
		std::vector<Ncti_Double> cp_vectors;

		Ncti_Double axis_direction[2];

		Ncti_Double eccentricity;
		Ncti_Double near_vertex[2];
		Ncti_Double near_focus[2];
	} ncti_DCM_conic_data;

	typedef enum ncti_DCM_autocon_version {
		NCTI_DCM_AUTOCON_VERSION_1,
		NCTI_DCM_AUTOCON_VERSION_2
	} ncti_DCM_autocon_version;

	typedef enum ncti_DCM_autocon_check_movement {
		NCTI_DCM_AUTOCON_CHECK_MOVEMENT_OFF = 0,
		NCTI_DCM_AUTOCON_CHECK_MOVEMENT_LEVEL_1 = 1
	} ncti_DCM_autocon_check_movement;

	
	typedef enum ncti_DCM_changed_longevity {
		NCTI_CHANGED_UNTIL_RE_EVALUATE,	/* only changed until next re_evaluate */
		NCTI_CHANGED_UNTIL_EVALUATE		/* recompute on every re_evaluate */
	} ncti_DCM_changed_longevity;

	typedef enum ncti_DCM_solving_mode {
		NCTI_DCM_MINIMUM_MOVE_SOLVE,			/* move the smallest number of geometries */
		NCTI_DCM_STANDARD_SOLVE,				/* solve using standard method */
		NCTI_DCM_RELAXATION_SOLVE,			/* use relaxation for underconstrained bits */
		NCTI_DCM_WEIGHTED_STANDARD_SOLVE,	/* use standard method, but with weighting of */
		/* specified geometries. */
		NCTI_DCM_LOCALISED_SOLVE 			/* localise the solve around changing inputs */
	} ncti_DCM_solving_mode;

	typedef struct ncti_DCM_autocon_options {
		ncti_DCM_autocon_version version;
		double tol_lin;
		double tol_ang;
		unsigned int constraint_mask;
		unsigned int directed_geometry_mask;
		std::vector<NCTI_G_NODE> g_from;
		std::vector<NCTI_G_NODE> g_region;
		std::vector<NCTI_G_NODE> g_preferred;
		std::vector<NCTI_G_NODE> g_sym_axes;
		std::vector<NCTI_G_NODE> g_ed_from;
		std::vector<NCTI_G_NODE> g_ed_to;
		ncti_DCM_solving_mode solving_mode;
		ncti_DCM_autocon_check_movement check_movement_level;
		double check_movement_tol_lin;
		double check_movement_tol_ang;
	} ncti_DCM_autocon_options;


	typedef enum ncti_DCM_e_type {
		NCTI_DCM_LINEAR_EQUATION,
		NCTI_DCM_NON_LINEAR_EQUATION,
		NCTI_DCM_INEQUALITY,
		NCTI_DCM_RIGID_LINEAR_EQUATION,
		NCTI_DCM_RIGID_LINEAR_INEQUALITY,			/* EXPERIMENTAL - disabled */
		NCTI_DCM_UNKNOWN_EQUATION
	} ncti_DCM_e_type;

	typedef enum ncti_DCM_dragging_option {
		NCTI_DCM_DRAG_POSSIBLE,		/* drag if possible	*/
		NCTI_DCM_DRAG_SPECIFIC     	/* drag if this transform can be applied */
	} ncti_DCM_dragging_option;

	typedef enum ncti_DCM_dragging_transformation {
		NCTI_DCM_DT_GENERAL,                 /* rotation+translation	*/
		NCTI_DCM_DT_TRANSLATION,             /* translation only	*/
		NCTI_DCM_DT_RADIUS,                  /* circle radius only */
		NCTI_DCM_DT_MAJOR_RADIUS,            /* ellipse major radius only */
		NCTI_DCM_DT_MINOR_RADIUS,            /* ellipse minor radius only */
		NCTI_DCM_DT_OFFSET_DISTANCE,			/* offset distance only	*/
		NCTI_DCM_DT_SCALE_FACTOR				/* set scaling only	*/
	} ncti_DCM_dragging_transformation;

	typedef enum ncti_DCM_autodim_version {
		NCTI_DCM_AUTODIM_VERSION_1
	} ncti_DCM_autodim_version;

	typedef enum ncti_DCM_autodim_block_singular {
		NCTI_DCM_AUTODIM_BLOCK_SINGULAR_OFF = 0,
		NCTI_DCM_AUTODIM_BLOCK_SINGULAR_LEVEL_1 = 1
	} ncti_DCM_autodim_block_singular;

	typedef struct ncti_DCM_autodim_options {
		ncti_DCM_autodim_version version;
		ncti_DCM_autodim_block_singular block_singular;
	} ncti_DCM_autodim_options;

	typedef enum ncti_DCM_autodim_status {
		NCTI_DCM_AUTODIM_NOT_EVALUATED,
		NCTI_DCM_AUTODIM_ABORTED,
		NCTI_DCM_AUTODIM_COMPLETED
	} ncti_DCM_autodim_status;

	typedef enum ncti_DCM_autodim_g_type {
		NCTI_DCM_ADG_POINT,
		NCTI_DCM_ADG_LINE,
		NCTI_DCM_ADG_CIRCLE,
		NCTI_DCM_ADG_ELLIPSE,
		NCTI_DCM_ADG_PARAMETRIC,
		NCTI_DCM_ADG_SPLINE,
		NCTI_DCM_ADG_CONIC,
		NCTI_DCM_ADG_ALL
	} ncti_DCM_autodim_g_type;

	typedef enum ncti_DCM_autodim_d_type {
		NCTI_DCM_ADD_DISTANCE,
		NCTI_DCM_ADD_ANGLE,
		NCTI_DCM_ADD_RADIUS,
		NCTI_DCM_ADD_MAJOR_RADIUS,
		NCTI_DCM_ADD_MINOR_RADIUS,
		NCTI_DCM_ADD_RADII,
		NCTI_DCM_ADD_DIRECTED_PARALLEL,
		NCTI_DCM_ADD_DIRECTED_PERPENDICULAR,
		NCTI_DCM_ADD_ALL
	} ncti_DCM_autodim_d_type;

	typedef enum ncti_DCM_autodim_mask_option {
		NCTI_DCM_ADM_ALL,
		NCTI_DCM_ADM_SYMMETRIC_PAIRS,
		NCTI_DCM_ADM_FROM_G,
		NCTI_DCM_ADM_INTER_G,
		NCTI_DCM_ADM_FROM_SYMMETRY_AXES,
		NCTI_DCM_ADM_BETWEEN_PAIRS
	} ncti_DCM_autodim_mask_option;

	typedef enum ncti_DCM_constraint_end {
		NCTI_DCM_CONSTRAINT_END_ONE,
		NCTI_DCM_CONSTRAINT_END_TWO
	} ncti_DCM_constraint_end;

	typedef enum ncti_DCM_para_ext_type {
		NCTI_DCM_PARA_EXT_TYPE_CUSTOM,
		NCTI_DCM_PARA_EXT_TYPE_LINEAR,
		NCTI_DCM_PARA_EXT_TYPE_BS_POLYNOMIAL
	} ncti_DCM_para_ext_type;

	typedef enum ncti_DCM_para_ext_start_type {
		NCTI_DCM_PARA_EXT_START_TYPE_END,
		NCTI_DCM_PARA_EXT_START_TYPE_FIXED,
		NCTI_DCM_PARA_EXT_START_TYPE_VARIABLE
	} ncti_DCM_para_ext_start_type;

	typedef enum ncti_DCM_para_ext_end_type {
		NCTI_DCM_PARA_EXT_END_TYPE_FIXED,
		NCTI_DCM_PARA_EXT_END_TYPE_VARIABLE
	} ncti_DCM_para_ext_end_type;

	typedef enum ncti_DCM_para_ext_end {
		NCTI_DCM_PARA_EXT_END_MIN,
		NCTI_DCM_PARA_EXT_END_MAX
	} ncti_DCM_para_ext_end;

	typedef enum ncti_DCM_offset_side {
		NCTI_DCM_OFFSET_LEFT,	/* offset is to left (offset parametrics) */
		NCTI_DCM_OFFSET_RIGHT,	/* offset is to right (offset parametrics) */
		NCTI_DCM_OFFSET_INSIDE,	/* offset is inside (offset ellipses) */
		NCTI_DCM_OFFSET_OUTSIDE	/* offset is outside (offset ellipses) */
	} ncti_DCM_offset_side;


	typedef enum ncti_DCM_undo_mode {
		NCTI_DCM_UNDO_TO_INITIAL,
		NCTI_DCM_UNDO_TO_PREVIOUS
	} ncti_DCM_undo_mode;

	typedef enum ncti_DCM_m_and_e_outcome {
		NCTI_DCM_M_AND_E_SOLVED,			/* Solved, but one or more of the */
		/*  geometries didn't receive the */
		/*  specified transform	*/
		NCTI_DCM_M_AND_E_SOLVED_EXACTLY,	/* Solved, and all geometries	*/
		/*  received the specified transform */
		NCTI_DCM_M_AND_E_FAILED,			/* Failed to solve */
		NCTI_DCM_M_AND_E_ABORTED			/* Aborted by application */
	} ncti_DCM_m_and_e_outcome;

	typedef enum ncti_DCM_evaluation_type {
		NCTI_DCM_FULL_EVAL,					/* Full evaluation performed for */
		/*  the whole model. */
		NCTI_DCM_PARTIALLY_INCREMENTAL_EVAL,	/* Some of model was evaluated	*/
		/*   incrementally.	*/
		NCTI_DCM_FULLY_INCREMENTAL_EVAL,		/* All of the model was evaluated */
		/*   incrementally.	*/
		NCTI_DCM_EVAL_ABORTED,				/* Aborted by application	*/
		NCTI_DCM_NOT_EVAL					/* Not evaluated */
	} ncti_DCM_evaluation_type;

	typedef enum ncti_DCM_evaluated_outcome {
		NCTI_DCM_EVALUATED_FULLY,		/* Whole model in an evaluated state */
		NCTI_DCM_EVALUATED_PARTIALLY,	/* Some of the model in an evaluated state */
		NCTI_DCM_EVALUATED_NONE			/* None of the model in an evaluated state */
	} ncti_DCM_evaluated_outcome;


	typedef enum ncti_DCM_autocon_mask {
		NCTI_DCM_ACM_IDENTICAL = 0x00000001,
		NCTI_DCM_ACM_SYMMETRIC = 0x00000002,
		NCTI_DCM_ACM_COINCIDENT = 0x00000004,
		NCTI_DCM_ACM_CONCENTRIC = 0x00000008,
		NCTI_DCM_ACM_PARALLEL = 0x00000010,
		NCTI_DCM_ACM_PERPENDICULAR = 0x00000020,
		NCTI_DCM_ACM_TANGENT = 0x00000040,
		NCTI_DCM_ACM_EQUAL_RADIUS = 0x00000080,
		NCTI_DCM_ACM_NORMAL = 0x00000100,
		NCTI_DCM_ACM_EQUAL_DISTANCE = 0x00000200,
		NCTI_DCM_ACM_ALL = 0x000003FF
	} ncti_DCM_autocon_mask;

	typedef enum ncti_DCM_satisfied_status {
		NCTI_DCM_SS_INVALID_RESOLUTION,
		NCTI_DCM_SS_NOT_SATISFIED,
		NCTI_DCM_SS_UNSUPPORTED_TYPE,
		NCTI_DCM_SS_SATISFIED,
		NCTI_DCM_SS_HELP_POINTS_NOT_SATISFIED,
		NCTI_DCM_SS_NOT_CHECKED
	} ncti_DCM_satisfied_status;

	typedef enum ncti_DCM_dos_status {
		NCTI_DCM_DOS_SUCCEEDED,
		NCTI_DCM_DOS_MODEL_NOT_SATISFIED,
		NCTI_DCM_DOS_ABORTED,
		NCTI_DCM_DOS_FAILED,
		NCTI_DCM_DOS_UNKNOWN
	} ncti_DCM_dos_status;

	typedef enum ncti_DCM_dof_result_status {
		NCTI_DCM_DOF_NOT_EVALUATED,
		NCTI_DCM_DOF_UNKNOWN,
		NCTI_DCM_DOF_SUCCESS
	} ncti_DCM_dof_result_status;

	typedef enum ncti_DCM_dof_info_type {
		NCTI_DCM_DOF_NO_INFO,
		NCTI_DCM_DOF_ROT_CENTRE,
		NCTI_DCM_DOF_TRANS_DIRECTION,
		NCTI_DCM_DOF_TRANS_INST_DIRECTION,
		NCTI_DCM_DOF_TRANS_AROUND,
		NCTI_DCM_DOF_TRANS_FREE_DIRECTION,
		NCTI_DCM_DOF_ROT_FREE_CENTRE,
		NCTI_DCM_DOF_FREE_POSITION
	} ncti_DCM_dof_info_type;

	typedef enum ncti_DCM_underdefined_g_status {
		NCTI_DCM_RADIUS_UNDERDEFINED = 0x00000001,
		NCTI_DCM_MAJOR_RADIUS_UNDERDEFINED = 0x00000002,
		NCTI_DCM_MINOR_RADIUS_UNDERDEFINED = 0x00000004,
		NCTI_DCM_ANGLE_UNDERDEFINED = 0x00000008,
		NCTI_DCM_POSITION_UNDERDEFINED = 0x00000010,
		NCTI_DCM_ANGLE2_UNDERDEFINED = 0x00000020,
		NCTI_DCM_SCALE_UNDERDEFINED = 0x00000040,
		NCTI_DCM_SINGULAR_UNDERDEFINED = 0x00000080,
		NCTI_DCM_SINGULAR_UNDERDEFINED_INDIRECT = 0x00000100,
		NCTI_DCM_PATTERN_VALUE_UNDERDEFINED = 0x00000200,
		NCTI_DCM_PATTERN_VALUE2_UNDERDEFINED = 0x00000400,
		NCTI_DCM_OFFSET_DISTANCE_UNDERDEFINED = 0x00000800,
		NCTI_DCM_RHO_UNDERDEFINED = 0x00001000,
		NCTI_DCM_G_SUPPORTS_UNDERDEFINED = 0x00002000,
		NCTI_DCM_V_SUPPORTS_UNDERDEFINED = 0x00004000,
		NCTI_DCM_G_SUPPORTS_RIGID_ANGLE_UNDERDEFINED = 0x00008000,
		NCTI_DCM_G_SUPPORTS_RIGID_POSITION_UNDERDEFINED = 0x00010000,
		NCTI_DCM_G_SUPPORTS_SCALABLE_SCALE_UNDERDEFINED = 0x00020000,
		NCTI_DCM_G_SUPPORTS_SCALABLE_ANGLE_UNDERDEFINED = 0x00040000,
		NCTI_DCM_G_SUPPORTS_SCALABLE_POSITION_UNDERDEFINED = 0x00080000,
		NCTI_DCM_SCALE2_UNDERDEFINED = 0x00100000,
		NCTI_DCM_G_SUPPORTS_SCALABLE_SCALE2_UNDERDEFINED = 0x00200000,
		NCTI_DCM_VALUE_UNDERDEFINED = 0x00400000
	} ncti_DCM_underdefined_g_status;

	typedef enum ncti_DCM_evaluate_mode {
		NCTI_DCM_EVALUATE,
		NCTI_DCM_EVALUATE_PARTITIONS,
		NCTI_DCM_RE_EVALUATE,
		NCTI_DCM_MOVE_AND_EVALUATE,
		NCTI_DCM_DYNAMIC_EVALUATE,
		NCTI_DCM_DYNAMIC_EVALUATE_PARTITIONS
	} ncti_DCM_evaluate_mode;

	const std::map<ncti_DCM_d_type, const char*> nctiDCMConsTypeMap
	{
		{NCTI_DCM_DISTANCE, "DCM_DISTANCE"},
		{NCTI_DCM_ANGLE, "DCM_ANGLE"},
		{NCTI_DCM_CONCENTRIC, "DCM_CONCENTRIC"},
		{NCTI_DCM_RADIUS, "DCM_RADIUS"},
		{NCTI_DCM_PARALLEL, "DCM_PARALLEL"},
		{NCTI_DCM_PERPENDICULAR, "DCM_PERPENDICULAR"},
		{NCTI_DCM_COINCIDENT, "DCM_COINCIDENT"},
		{NCTI_DCM_TANGENT, "DCM_TANGENT"},
		{NCTI_DCM_IDENTICAL, "DCM_IDENTICAL"},
		{NCTI_DCM_SYMMETRIC, "DCM_SYMMETRIC"},
		{NCTI_DCM_MAJOR_RADIUS, "DCM_MAJOR_RADIUS"},
		{NCTI_DCM_MINOR_RADIUS, "DCM_MINOR_RADIUS"},
		{NCTI_DCM_EQUAL_RADIUS, "DCM_EQUAL_RADIUS"},
		{NCTI_DCM_EQUAL_DISTANCE, "DCM_EQUAL_DISTANCE"},
		{NCTI_DCM_MIDPOINT, "DCM_MIDPOINT"},
		{NCTI_DCM_DEPENDENCE, "DCM_DEPENDENCE"},
		{NCTI_DCM_PATTERNED, "DCM_PATTERNED"},
		{NCTI_DCM_EQUAL_PARAMETER, "DCM_EQUAL_PARAMETER"},
		{NCTI_DCM_NORMAL, "DCM_NORMAL"},
		{NCTI_DCM_EQUAL_DIRECTION, "DCM_EQUAL_DIRECTION"},
		{NCTI_DCM_EQUAL_CURVATURE, "DCM_EQUAL_CURVATURE"},
		{NCTI_DCM_EQUAL_FIRST_DERIVATIVE, "DCM_EQUAL_FIRST_DERIVATIVE"},
		{NCTI_DCM_EQUAL_SECOND_DERIVATIVE, "DCM_EQUAL_SECOND_DERIVATIVE"},
		{NCTI_DCM_OFFSET, "DCM_OFFSET"},
		{NCTI_DCM_SIMPLE_DEPENDENCE, "DCM_SIMPLE_DEPENDENCE"},
		{NCTI_DCM_CURVE_LENGTH, "DCM_CURVE_LENGTH"},
		{NCTI_DCM_PATTERNED_2D, "DCM_PATTERNED_2D"},
		{NCTI_DCM_PATTERN_VALUE, "DCM_PATTERN_VALUE"},
		{NCTI_DCM_PATTERN_2D_VALUE_1, "DCM_PATTERN_2D_VALUE_1"},
		{NCTI_DCM_PATTERN_2D_VALUE_2, "DCM_PATTERN_2D_VALUE_2"},
		{NCTI_DCM_EQUAL_RELATIVE_TRANSFORM, "DCM_EQUAL_RELATIVE_TRANSFORM"},
		{NCTI_DCM_ARC_LENGTH, "DCM_ARC_LENGTH"},
		{NCTI_DCM_LOCK_WHOLE, "DCM_LOCK_WHOLE"},
		{NCTI_DCM_LOCK_CENTRE, "DCM_LOCK_CENTRE"},
		{NCTI_DCM_LOCK_DIRECTION, "DCM_LOCK_DIRECTION"},
		{NCTI_DCM_CONIC_RHO, "DCM_CONIC_RHO"},
		{NCTI_DCM_EQUAL_CURVATURE_DERIVATIVE, "DCM_EQUAL_CURVATURE_DERIVATIVE"}
	};

	const std::map<ncti_d_node_status, const char*> nctiDCMDNodeStatusMap
	{
		{NCTI_D_UNKNOWN, "D_UNKNOWN"},
		{NCTI_D_BETWEEN_FIXED, "D_BETWEEN_FIXED"},
		{NCTI_D_BETWEEN_SET_MEMBERS, "D_BETWEEN_SET_MEMBERS"},
		{NCTI_D_OVER_DEFINED, "D_OVER_DEFINED"},
		{NCTI_D_NON_ALGEBRAIC, "D_NON_ALGEBRAIC"},
		{NCTI_D_NOT_CONSISTENT, "D_NOT_CONSISTENT"},
		{NCTI_D_NOT_CONSISTENT_DIMENSIONS, "D_NOT_CONSISTENT_DIMENSIONS"},
		{NCTI_D_NOT_CONSISTENT_OTHER, "D_NOT_CONSISTENT_OTHER"},
		{NCTI_D_NOT_CONSISTENT_UNKNOWN, "D_NOT_CONSISTENT_UNKNOWN"},
		{NCTI_D_NOT_SOLVED, "D_NOT_SOLVED"},
		{NCTI_D_NOT_CHANGED, "D_NOT_CHANGED"},
		{NCTI_D_SOLVED, "D_SOLVED"}
	};

	const std::map< ncti_g_node_status, const char*> nctiDCMGNodeStatusMap
	{
		{NCTI_G_UNKNOWN, "G_UNKNOWN"},
		{NCTI_G_FIXED, "G_FIXED"},
		{NCTI_G_FROZEN, "G_FROZEN"},
		{NCTI_G_OVER_DEFINED, "G_OVER_DEFINED"},
		{NCTI_G_NON_ALGEBRAIC, "G_NON_ALGEBRAIC"},
		{NCTI_G_NOT_CONSISTENT, "G_NOT_CONSISTENT"},
		{NCTI_G_NOT_CONSISTENT_DIMENSIONS, "G_NOT_CONSISTENT_DIMENSIONS"},
		{NCTI_G_NOT_CONSISTENT_OTHER, "G_NOT_CONSISTENT_OTHER"},
		{NCTI_G_NOT_CONSISTENT_UNKNOWN, "G_NOT_CONSISTENT_UNKNOWN"},
		{NCTI_G_NOT_CHANGED, "G_NOT_CHANGED"},
		{NCTI_G_WELL_DEFINED, "G_WELL_DEFINED"},
		{NCTI_G_UNDER_DEFINED, "G_UNDER_DEFINED"}
	};
}
#endif
