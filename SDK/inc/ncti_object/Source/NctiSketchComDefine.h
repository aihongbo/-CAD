#ifndef _NCTI_SKETCH_DEF_H_
#define _NCTI_SKETCH_DEF_H_

#pragma region sketch command
#define _NctiCommandWorkPlane_ID_						"cmd_workplane"
#define _NctiCommandSwitchSketchContainer_ID_			"cmd_switch_sketch_container"
#define _NctiCommandSketchGroup_ID_						"cmd_sketch_group"
#define _NctiCommandSketch_ID_							"cmd_sketch"
#define _NctiCommandRevolve_ID_							"cmd_skt_revolve"
#define _NctiCommandResetSketchCamera_ID_				"cmd_reset_sketch_camera"
#define _NctiCommandRenderingModeSketch_ID_				"cmd_render_sketch"
#define _NctiCommandRebuildSketch_ID_					"cmd_rebuild_sketch"
#define _NctiCommandProjection_ID_						"cmd_projection"
#define _NctiCommandMoveSketchObjUp_ID_					"cmd_move_sketch_obj_up"
#define _NctiCommandMoveSketchObjTop_ID_				"cmd_move_sketch_obj_top"
#define _NctiCommandMoveSketchObjEnd_ID_				"cmd_move_sketch_obj_end"
#define _NctiCommandMoveSketchObjDown_ID_				"cmd_move_sketch_obj_down"
#define _NctiCommandMoveSketchObj_ID_					"cmd_move_sketch_obj"	
#define _NctiCommandFixSketchModel_ID_					"cmd_fix_sketch_model"	
#define _NctiCommandExtrude_ID_							"cmd_skt_extrude"	
#define _NctiCommandEditSketchTan2Circles_ID_			"cmd_edit_sketch_tan_2_circles"	
#define _NctiCommandEditSketchSpline_ID_				"cmd_edit_sketch_spline"
#define _NctiCommandEditSketchRect_ID_					"cmd_edit_sketch_rect"
#define _NctiCommandEditSketchPolyline_ID_				"cmd_edit_sketch_polyline"
#define _NctiCommandEditSketchPolygon_ID_				"cmd_edit_sketch_polygon"
#define _NctiCommandEditSketchObject_ID_				"cmd_edit_sketch_obj"
#define _NctiCommandEditSketchLine_ID_					"cmd_edit_sketch_line"
#define _NctiCommandEditSketchGrid_ID_					"cmd_edit_sketch_grid"
#define _NctiCommandEditSketchEllipse_ID_				"cmd_edit_sketch_ellipse"
#define _NctiCommandEditSketchDot_ID_					"cmd_edit_sketch_dot"		
#define _NctiCommandEditSketchCircle_ID_				"cmd_edit_sketch_circle"
#define _NctiCommandEditSketchCenterLine_ID_			"cmd_edit_sketch_cnter_line"
#define _NctiCommandEditSketchArc_ID_					"cmd_edit_sketch_arc"
#define _NctiCommandDeleteSketchObj_ID_					"cmd_dlt_sketch_obj"
#define _NctiCommandDeleteFeature_ID_					"cmd_dlt_feature"
#define _NctiCommandDeleteDocSketch_ID_					"cmd_dlt_doc_sketch"
#define _NctiCommandCreateSketchTan2Circles_ID_			"cmd_create_sketch_tan_2_circles"
#define _NctiCommandCreateSketchSpline_ID_				"cmd_create_sketch_spline"
#define _NctiCommandCreateSketchRect_ID_				"cmd_create_sketch_rect"
#define _NctiCommandCreateSketchPolyline_ID_			"cmd_create_sketch_polyline"
#define _NctiCommandCreateSketchPolygon_ID_				"cmd_create_sketch_polygon"
#define _NctiCommandCreateSketchObject_ID_				"cmd_create_sketch_obj"
#define _NctiCommandCreateSketchLine_ID_				"cmd_create_sketch_line"
#define _NctiCommandCreateSketchEllipse_ID_				"cmd_create_sketch_ellipse"
#define _NctiCommandCreateSketchDot_ID_					"cmd_create_sketch_dot"	
#define _NctiCommandCreateSketchCircle_ID_				"cmd_create_sketch_circle"
#define _NctiCommandCreateSketchCenterLine_ID_			"cmd_create_sketch_center_line"
#define _NctiCommandCreateSketchArc_ID_					"cmd_create_sketch_arc"	
#define _NctiCommandCreateDocSketch_ID_					"cmd_doc_sketch"
#define _NctiCommandChangeSketchObjBoolMode_ID_			"cmd_change_sketch_obj_bool"
#define _NctiCommandChangeFeatureBoolMode_ID_			"cmd_change_feat_bool"

#pragma endregion sketch command				


enum EnumNctiSketchBooleanMode
{
	NCTI_SKETCH_BOOLEAN_UNITE,
	NCTI_SKETCH_BOOLEAN_SUBTRACT
};

enum EnumNctiFeatureBooleanMode
{
	NCTI_FEATURE_BOOLEAN_UNITE,
	NCTI_FEATURE_BOOLEAN_SUBTRACT
};

enum EnumNctiEuler
{
	NCTI_EURER_XYZ = 0,
	NCTI_EURER_ZYZ
};

#define NCTI_IDENTITY_MATRIX {1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f}

#ifdef _WIN32
#define NCTI_CALL_CONVENTION _stdcall
#define NCTI_EXPORT _declspec(dllexport)
#else
#define NCTI_CALL_CONVENTION
#define NCTI_EXPORT
#endif

#define NCTI_DEF_CALLBACK( FUNCTION_NAME_TO_SET_CALLBACK, CPP_RETURN_TYPE, CPP_FUNCTION_NAME, ... ) \
typedef CPP_RETURN_TYPE (NCTI_CALL_CONVENTION * proto_##CPP_FUNCTION_NAME)(__VA_ARGS__);\
static proto_##CPP_FUNCTION_NAME cb_##CPP_FUNCTION_NAME = NULL;\
extern "C" NCTI_EXPORT void NCTI_CALL_CONVENTION FUNCTION_NAME_TO_SET_CALLBACK( proto_##CPP_FUNCTION_NAME funcp )\
{\
cb_##CPP_FUNCTION_NAME = funcp;\
}

enum EnumNctiColor
{
	NCTI_BLACK,
	NCTI_RED,
	NCTI_GREEN,
	NCTI_BLUE,
	NCTI_CYAN,
	NCTI_YELLOW,
	NCTI_MAGENTA,
	NCTI_WHITE,
	NCTI_RGB,
	NCTI_DEF_COLOR
};

enum EnumNctiDimArrowDirection
{
	NCTI_DIM_ARW_DIR_NORMAL = 1,
	NCTI_DIM_ARW_DIR_REVERSE
};

enum EnumNctiDimTextPosition
{
	NCTI_DIM_TEXT_CENTER = 1,
	NCTI_DIM_TEXT_START,
	NCTI_DIM_TEXT_END
};

#define RADFSTR_FILE_NEW									"New"
#define RADFSTR_FILE_OPEN								"Open"
#define RADFSTR_FILE_CLOSE								"Close"
#define RADFSTR_FILE_SAVE								"Save"
#define RADFSTR_FILE_SAVE_AS								"Save As"
#define RADFSTR_EDIT_UNDO								"Undo"
#define RADFSTR_EDIT_REDO								"Redo"
#define RADFSTR_MODEL_IMPORT_SAT							"Import SAT"
#define RADFSTR_MODEL_IMPORT_IGES						"Import IGES"
#define RADFSTR_MODEL_IMPORT_CATPART						"Import CATPart"
#define RADFSTR_MODEL_EXPORT_SAT							"Export SAT"
#define RADFSTR_MODEL_WORKPLANE_NEW						"New Work Plane"
#define RADFSTR_MODEL_WORKPLANE_EDIT						"Edit Work Plane"
#define RADFSTR_MODEL_SKETCH_DEFINE						"Define Sketch"
#define RADFSTR_MODEL_SKETCH_DOT							"Dot"
#define RADFSTR_MODEL_SKETCH_CENTERLINE					"Center Line"
#define RADFSTR_MODEL_SKETCH_CIRCLE						"Circle"
#define RADFSTR_MODEL_SKETCH_RECT						"Rect"
#define RADFSTR_MODEL_SKETCH_CLOSEDPOLYLINE				"Closed Polyline"
#define RADFSTR_MODEL_SKETCH_ELLIPSE						"Ellipse"
#define RADFSTR_MODEL_SKETCH_GROUP						"Group"
#define RADFSTR_MODEL_SKETCH_GROUP_DISMISS				"Group Dissmiss"
#define RADFSTR_MODEL_SKETCH_LINE						"Line"
#define RADFSTR_MODEL_SKETCH_ARC							"Arc"
#define RADFSTR_MODEL_SKETCH_POLYLINE					"Polyline"
#define RADFSTR_MODEL_SKETCH_SPLINE						"Spline"
#define RADFSTR_MODEL_SKETCH_EXTRUDE						"Extrude"
#define RADFSTR_MODEL_SKETCH_REVOLVE						"Revolve"
#define RADFSTR_MODEL_SKETCH_FIXMODEL					"Fix Sketch Model"
#define RADFSTR_MODEL_SKETCH_REBUILD						"Rebuild Sketch Model"
#define RADFSTR_MODEL_EDIT_SKETCH						"Edit Sketch"
#define RADFSTR_MODEL_MODELING_BOOLEAN_UNITE				"Unite"
#define RADFSTR_MODEL_MODELING_BOOLEAN_SUBTRACT			"Subtract"
#define RADFSTR_MODEL_MODELING_BLENDING					"Blending"
#define RADFSTR_MODEL_MODELING_CHAMFER					"Chamfer"
#define RADFSTR_MODEL_MODELING_PROJECTION				"Projection"
#define RADFSTR_MODEL_MODELING_OFFSET					"Offset"
#define RADFSTR_MODEL_MODELING_EXTRUDE					"Extrude"
#define RADFSTR_MODEL_DISPLAY							"Display"
#define RADFSTR_MODEL_ERASE								"Erase"
#define RADFSTR_MESH_PROPERTY							"Property"
#define RADFSTR_MESH_GENERATEMESH						"Generate Mesh"
#define RADFSTR_MESH_DELETEMESH							"Delete Mesh"
#define RADFSTR_MESH_IMPORT_NEUTRAL_FILE					"Import Neutral"
#define RADFSTR_MESH_EXPORT_NEUTRAL_FILE					"Export Neutral"
#define RADFSTR_MESH_CUTTINGPLANE						"Cutting Plane"
#define RADFSTR_MESH_LOCAL_MESH_SIZE						"Local Mesh Size"
#define RADFSTR_MESH_CONDITION_CONSTRAINT_NEW			"New Constraint"
#define RADFSTR_MESH_CONDITION_CONSTRAINT_EDIT			"Edit Constraint"
#define RADFSTR_MESH_CONDITION_CONSTRAINT_DELETE			"Delete Constraint"
#define RADFSTR_MESH_CONDITION_DISPLACEMENT_NEW			"New Displacement"
#define RADFSTR_MESH_CONDITION_DISPLACEMENT_EDIT			"Edit Displacement"
#define RADFSTR_MESH_CONDITION_DISPLACEMENT_DELETE		"Delete Displacement"
#define RADFSTR_MESH_CONDITION_WEIGHT_NEW				"New Weight"
#define RADFSTR_MESH_CONDITION_WEIGHT_EDIT				"Edit Weight"
#define RADFSTR_MESH_CONDITION_WEIGHT_DELETE				"Delete Weight"
#define RADFSTR_MESH_CONDITION_SURFACEPRESSURE_NEW		"New Surface Pressure"
#define RADFSTR_MESH_CONDITION_SURFACEPRESSURE_EDIT		"Edit Surface Pressure"
#define RADFSTR_MESH_CONDITION_SURFACEPRESSURE_DELETE	"Delete Surface Pressure"
#define RADFSTR_MESH_CONDITION_GROUP_NEW					"New Group"
#define RADFSTR_MESH_CONDITION_GROUP_EDIT				"Edit Group"
#define RADFSTR_MESH_CONDITION_GROUP_DELETE				"Delete Group"
#define RADFSTR_MESH_CONDITION_GRAVITY_NEW				"New Gravity"
#define RADFSTR_MESH_CONDITION_GRAVITY_EDIT				"Edit Gravity"
#define RADFSTR_MESH_CONDITION_GRAVITY_DELETE			"Delete Gravity"
#define RADFSTR_MESH_CONDITION_CENTRIFUGAL_NEW			"New Centrifugal"
#define RADFSTR_MESH_CONDITION_CENTRIFUGAL_EDIT			"Edit Centrifugal"
#define RADFSTR_MESH_CONDITION_CENTRIFUGAL_DELETE		"Delete Centrifugal"
#define RADFSTR_MESH_CONDITION_ELECTROMAGNETIC_NEW		"New Electromagnetic"
#define RADFSTR_MESH_CONDITION_ELECTROMAGNETIC_EDIT		"Edit Electromagnetic"
#define RADFSTR_MESH_CONDITION_ELECTROMAGNETIC_DELETE	"Delete Electromagnetic"
#define RADFSTR_MESH_MATERIAL_LINEARELASTIC_NEW			"New Linearelastic"
#define RADFSTR_MESH_MATERIAL_LINEARELASTIC_EDIT			"Edit Linearelastic"
#define RADFSTR_MESH_MATERIAL_LINEARELASTIC_DELETE		"Delete Linearelastic"
#define RADFSTR_MESH_MATERIAL_EXPANSIONCOEFFICIENT_NEW	"New Expansion Coefficient"
#define RADFSTR_MESH_MATERIAL_EXPANSIONCOEFFICIENT_EDIT		"Edit Expansion Coefficient"
#define RADFSTR_MESH_MATERIAL_EXPANSIONCOEFFICIENT_DELETE	"Delete Expansion Coefficient"
#define RADFSTR_VIEW_VIEWMODE_MODELVIEW					"Model View"
#define RADFSTR_VIEW_VIEWMODE_VOIDVIEW					"Void View"
#define RADFSTR_VIEW_VIEWMODE_MESHVIEW					"Mesh View"
#define RADFSTR_VIEW_VIEWMODE_CONTOURVIEW				"Contour View"
#define RADFSTR_VIEW_VIEWMODE_VECTORVIEW					"Vector View"
#define RADFSTR_VIEW_CAMERA_XY							"XY"
#define RADFSTR_VIEW_CAMERA_YZ							"YZ"
#define RADFSTR_VIEW_CAMERA_ZX							"ZX"
#define RADFSTR_VIEW_CAMERA_ISO							"ISO"
#define RADFSTR_VIEW_CAMERA_DEFAULT						"Default"
#define RADFSTR_VIEW_CAMERA_ZOOMALL						"Zoom All"
#define RADFSTR_VIEW_CAMERA_ZOOM_WINDOW					"Zoom Window"
#define RADFSTR_VIEW_CAMERA_MOUSE						"Mouse Camera"
#define RADFSTR_HELP										"Help"
#define RADFSTR_GRID_DISPLAY_ON							"Grid On"
#define RADFSTR_GRID_DISPLAY_OFF							"Grid Off"
#define RADFSTR_GRID_SNAP_ON								"Snap On"
#define RADFSTR_GRID_SNAP_OFF							"Snap Off"
#define RADFSTR_RENDER_SOLID								"Render Solid"
#define RADFSTR_RENDER_WIRE								"Render Wire"
#define RADFSTR_RENDER_TRANSPARENT						"Render Transparent"

#define RADFSTR_EXIT_SKETCH								"End Sketch"
#define RADFSTR_DELETE									"Delete"
#define RADFSTR_FINISH									"Finish"
#define RADFSTR_EDIT										"Edit"
#define RADFSTR_DONE										"Done"
#define	RADFSTR_MOVE										"Move"
#define RADFSTR_ROTATE									"Rotate"
#define RADFSTR_INPUT_COORDINATE							"Input Coordinate"
#define RADFSTR_INPUT_RADIUS								"Input Radius"
#define RADFSTR_INPUT_DIAMETER							"Input Diameter"
#define RADFSTR_BOOLMODE_TO_SUBTRACT						"Mode > Subtract"
#define RADFSTR_BOOLMODE_TO_UNITE						"Mode > Unite"
#define RADFSTR_MOVE_TO_TOP								"Move to Top"
#define RADFSTR_MOVE_TO_END								"Move to End"
#define RADFSTR_MOVE_UP									"Move Up"
#define RADFSTR_MOVE_DOWN								"Move Down"
#define RADFSTR_VALUE									"Value"
#define RADFSTR_SCALE									"Scale"
#define RADFSTR_INFORMATION								"Information"
#define RADFSTR_CHANGE_NAME								"Change Name"
#define RADFSTR_CONVERT_HOOPS_TO_BREP					"Convert HOOPS -> B-Rep"
#define RADFSTR_ACTIVATE									"Activate"
#define RADFSTR_DEACTIVATE								"Deactivate"

#define RADFSTR_CIRCLE_MODE_TO_RADIUS					"Mode > Radius"
#define RADFSTR_CIRCLE_MODE_TO_DIAMETER					"Mode > Diameter"

#define RADFSTR_ARC_MODE_FIX_END_POINTS					"Mode > Fix End Points"
#define RADFSTR_ARC_MODE_FIX_CENTER						"Mode > Fix Center"

#define RADFSTR_MESHER_INITIALIZE						"Mesher initialized"
#define RADFSTR_MESHER_MESHING							"Generating Mesh Data"
#define RADFSTR_MESHER_MESHING_COMPLETED					"Mesh generation completed"
#define RADFSTR_MESHER_MESH_NOT_GENERATED				"Mesh was not generated"
#define RADFSTR_MESHER_NUMBER_OF_MESH					"Number of Mesh"
#define RADFSTR_MESHER_READ_AMGUM_FILE					"Read AGMum file"
#define RADFSTR_MESHER_SET_TO_PROPERTY					"Set to Mesher property"

#define RADFSTR_MESH_LINEAR_STATIC						"Static Linear"
#define RADFSTR_MESH_NON_LINEAR_STATIC					"Static Non Linear"
#define RADFSTR_MESH_EIGENVALUE							"Eigenvalue"
#define RADFSTR_MESH_WARN_DELETE_MESH					"Deleting Mesh Data also deletes all attributes aggregated. \nWould you like to continue?"
#define RADFSTR_MESH_DEGREE								"Degree"
#define RADFSTR_MESH_NUM_CELL							"Cell Count"
#define RADFSTR_MESH_GENERATE_LOD						"Generate LOD"

#define RADFSTR_CONTOUR_GRADATION						"Gradation"
#define RADFSTR_CONTOUR_SOLID							"Solid"

#define RADFSTR_ANALYSIS_VECTOR_SCALE					"Vector Scale"
#define RADFSTR_ANALYSIS_RUN_SOLVER						"Run Solver"
#define RADFSTR_ANALYSIS_SOLVER_FINISHED					"Solver finished"
#define RADFSTR_ANALYSIS_GENERATE_ANIMATION				"Generate animation"

#define RADFSTR_SELECTION_SHAPE_RECT						"Rectangle"
#define RADFSTR_SELECTION_SHAPE_CIRCLE					"Circle"
#define RADFSTR_SELECTION_SHAPE_FREEHAND					"Freehand"

#define RADFSTR_SELECT_FACE_EDGE							"Please select a edge or face of model"

#define RADFSTR_ROBOTICS_MOVE_TCP						"Move Tool Position"
#define RADFSTR_ROBOTICS_MOVE_TCP_PATH					"Move Tool Path"
#define RADFSTR_ROBOTICS_NEW_TEACHING_POINT				"New Teaching Point"
#define RADFSTR_ROBOTICS_SAVE_ANIMATION					"Save Animation"
#define RADFSTR_ROBOTICS_ROBOT_POSITION_MANIPULATION	"Robot Manipulation"
#define RADFSTR_ROBOTICS_POSITIONING_ROBOT				"Positioning Robot"
#define RADFSTR_ROBOTICS_MSG_SELECT_ROBOT				"Please select Robot(s) in advance"
#define RADFSTR_ROBOTICS_SAVE_ROBOT						"Save Robot"

#define RADFSTR_ERROR_INVALID_PROFILE					"Profile has problem. Failed to make a solid."
#define RADFSTR_ERROR_INTERNAL_ASK_DEBUG					"Internal Error. Write debug information?"
#define RADFSTR_ERROR_MESHING_FAILED						"Meshing failed. Process is halted."
#define RADFSTR_ERROR_READ_FILE							"Critical error in loading process."
#define RADFSTR_ERROR_READ_FILE_INVALID_CHECK			"Reading file has failed. Please check the file."
#define RADFSTR_ERROR_NO_DATA							"There is no data."
#define RADFSTR_ERROR_INVALID_BLENDING_RADIUS			"Blending Radius is invalid."
#define RADFSTR_ERROR_INVALID_CHAMFER_DISTANCE			"Chamfer Distance is invalid"
#define RADFSTR_ERROR_FILE_TYPE_NOT_SUPPORTED			"Given file is not supported"
#define RADFSTR_ERROR_FILE_INTEROP_CATIAV5_DEBUG			"Can't run InterOp CATIA V5 under Debug mode"
#define RADFSTR_ERROR_MESHER_PROFILE_SELECT_BODY			"Mesher property doesn't have body. Set body for the property."
#define RADFSTR_ERROR_OPTION_TYPE_MISSMATCH				"Option type missmatch. (Line = "
#define RADFSTR_ERROR_OPTION_INVALID_NAME				"The option name is not valid. (Line = "
#define RADFSTR_ERROR_INVALID_SCALE						"Scale value was changed to 1.0."
#define RADFSTR_ERROR_NO_SHARED_MODEL					"No shared model"
#define RADFSTR_ERROR_INVALID_BODY_CONTAINER			"Can't copy. Please click Body first, then click Container same type."
#define RADFSTR_ERROR_NO_OBJECT_SELECTED				"Please select one or more objects."
#define RADFSTR_ERROR_ACTIVE_PARENT_DOCUMENT			"Invalid Active Document. Activate the parent document."
#define RADFSTR_ERROR_NO_VALID_BODY_SELECTED			"No valid body has been selected."
#define RADFSTR_ERROR_MULTIBYTE_NAME					"Multibyte file name is not supported."
#define RADFSTR_ERROR_INVALID_INPUT_VALUE				"Input value is not valid."
#define RADFSTR_ERROR_FILE_NOT_FOUND					"File Not Found."
#define RADFSTR_ERROR_EDGES_NOT_CONNECTED               "Edges are not connected."
#define RADFSTR_ERROR_OPERATION_UNSUCCESSFUL			"Operation Unsuccessful"

#define RADFSTR_CONFIRM_EXIT_ACTIVE_COMMAND				"Is it OK to exit the current command?"
#define RADFSTR_CONFIRM_EXIT_INTERRUPT					"Is it OK to exit interrupt command?"
#define RADFSTR_CONFIRM_REMOVE_COLOR					"Remove existing color?"
#define RADFSTR_MSG_SELECT_BODY							"<Please select a Body>"
#define RADFSTR_MSG_SELECT_FACE							"<Please select a Face>"
#define RADFSTR_MSG_SELECT_SKETCH						"<Please select a Sketch>"

#define RADFSTR_CONFIRM_NO_UNDO							"You can't undo this operation. Continue?"

#define RADFSTR_AEC_NEW_WINDOW							"New Window"

#define RADFSTR_GGCM_CONST_HORIZON                       "Horizontal Constraint"
#define RADFSTR_GGCM_CONST_VERTICAL                      "Vartical Constraint"
#define RADFSTR_GGCM_CONST_LENGTH						"Length Constraint"
#define RADFSTR_GGCM_CONST_TANGENT						"Tangent Constraint"
#define RADFSTR_GGCM_DISP_COLLISION_ON					"Display"
#define RADFSTR_GGCM_DISP_COLLISION_OFF					"Erase"

#define RADFSTR_RESET_SKETCH_CAMERA						"Reset Camera"

#define RADFSTR_SET_VARIABLE_RANGE						"Set Variable Range"

#define RADFSTR_ANIME_PLAY_ANIMATION						"Play Animation"
#define RADFSTR_ANIME_SAVE_HSF							"Save HSF"

#define RADFSTR_MEASURE_DISTANCE						"Measure Distance"
#define RADFSTR_UNSHARE_MODEL							"Unshare Model"
#define RADFSTR_COPY_MODEL_BODY							"Copy Body"
#define RADFSTR_CHANGE_COLOR							"Change Color"
#define RADFSTR_DYNAMIC_FACETING						"Dynamic Faceting"
#define RADFSTR_EDIT_COORDINATE							"Edit Coordinate"
#define RADFSTR_UP_SIDE_DOWN							"UpSideDown"

#define RADFSTR_VIEW_1									"View 1"
#define RADFSTR_VIEW_2									"View 2"
#define RADFSTR_VIEW_3									"View 3"
#define RADFSTR_VIEW_4									"View 4"
#define RADFSTR_VIEW_5									"View 5"
#define RADFSTR_VIEW_6									"View 6"

#define RADFSTR_ROBOT_DO_YOU_WANT_REVERSE_DIRECTION		"Would you like to reverse the direction?"
#define RADFSTR_ROBOT_REVERSE							"Reverse"
#define RADFSTR_ROBOT_NO_REVERSE						"No Reverse"

#endif