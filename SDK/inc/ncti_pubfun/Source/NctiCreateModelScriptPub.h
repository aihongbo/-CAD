#ifndef NctiCreateModelScriptPub_H
#define NctiCreateModelScriptPub_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include "NctiDesignMultiBoolean.h"
namespace NCTI
{
	class NctiBaseModel;
	class NctiTopoFace;
	class NctiTopoCell;
	class NctiDisplayModelBody;
	class NctiGeomLine;
	class NctiGeomCircle;
	class NctiGeomBezierCurve;
	class NctiGeomBSplineCurve;
	class NctiGeomEllipse;
	class NctiGeomCurve;
	class NctiGeomSurface;
	class NctiAxis;

	/**
	* @brief create the script for model
	* @details create the script for model
	*/
	class DECL_NCTI_PUBFUN NctiCreateModelScriptPub
	{
	public:
		NctiCreateModelScriptPub();
		~NctiCreateModelScriptPub();

		/**
		* @brief get the model script from select model
		* @details get the model script from select model
		* @return the script
		*/
		static std::string GetModelScripFromSelectData(NctiBaseModel* i_pBaseModel);

		/**
		* @brief get new name for type name
		* @details get new name for type name
		* @param[in] i_pBaseModel, the base model
		* @return the new name
		*/
		static std::string GetNewName(NctiBaseModel* i_pBaseModel);
		/**
		* @brief get selected object name and edge id
		* @details get selected object name and edge id
		* @param[in] i_pBaseModel, the base model
		* @param[out] i_objNameVec, the object name vector
		* @param[out] i_edgeIDVec, the edge id vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetSelectData(NctiBaseModel* i_pBaseModel,
			std::vector<std::string>& i_objNameVec, std::vector<Ncti_Long>& i_edgeIDVec);
		/**
		* @brief get geometry from trimmed curve
		* @details get geometry from trimmed curve
		* @param geomCurve, the geometry curve
		* @return true if success, false otherwise
		*/
		static void GetGeomFromTrimmedCurve(NctiGeomCurve*& geomCurve);
		/**
		* @brief get geometry from trimmed surface
		* @details get geometry from trimmed surface
		* @param pSurface, the geometry surface
		* @return true if success, false otherwise
		*/
		static void GetGeomFromTrimmedSurface(NctiGeomSurface*& pSurface);
		/**
		* @brief get selected object name
		* @details get selected object name
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_objNameVec, the object name vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetSelectData(NctiBaseModel* i_pBaseModel, std::vector<std::string>& o_objNameVec);

		//点
		/**
		* @brief create the python command script by point
		* @details create the point script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the point name
		* @param[in] i_pt, the point position
		* @return the script
		*/
		static std::string CreateVertexPyCommand(NctiBaseModel* i_pBaseModel, const char* i_name, const NctiPosition& i_pt);
		//线
		/**
		* @brief create the python command script by line
		* @details create the line script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the line name
		* @param[in] i_pt, the point position
		* @param[in] i_dir, the line direction
		* @return the script
		*/
		static std::string CreateLinePyCommand(NctiBaseModel* i_pBaseModel, const char* i_name, const NctiPosition& i_pt, const NctiVector& i_dir);
		//圆
		/**
		* @brief create the python command script by circle
		* @details create the circle script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the circle name
		* @param[in] i_pt, the center position
		* @param[in] i_normal, the normal vector
		* @param[in] i_r, the radius
		* @return the script
		*/
		static std::string CreateCirclePyCommand(NctiBaseModel* i_pBaseModel, const char* i_name, const NctiPosition& i_pt, const NctiVector& i_normal, Ncti_Double i_r);
		//椭圆
		/**
		* @brief create the python command script by ellipse
		* @details create the ellipse script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the ellipse name
		* @param[in] i_pt, the center position
		* @param[in] i_normal, the normal vector
		* @param[in] i_dir, the direction vector
		* @param[in] i_major, the major radius
		* @param[in] i_minor, the minor radius
		* @return the script
		*/
		static std::string CreateEllipsePyCommand(NctiBaseModel* i_pBaseModel, const char* i_name, const NctiPosition& i_pt, const NctiVector& i_normal, const NctiVector& i_dir, Ncti_Double i_major, Ncti_Double i_minor);
		//面
		/**
		* @brief create the python command script by plane
		* @details create the plane script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the plane name
		* @param[in] i_pt, the point position
		* @param[in] i_normal, the plane normal
		* @return the script
		*/
		static std::string CreatePlanePyCommand(NctiBaseModel* i_pBaseModel, const char* i_name, const NctiPosition& i_pt, const NctiVector& i_normal);

		//box
		/**
		* @brief create the box script
		* @details create the box script
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwis
		*/
		static Ncti_Boolean CreateBoxScript(NctiBaseModel* i_pBaseModel, std::string& o_strCmd);
		/**
		* @brief create the box script
		* @details create the box script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_edgeIDVec, the edge id vector
		* @param[out] o_ptCenter, the box center position
		* @param[out] o_ZAxis, the box Z axis
		* @param[out] o_XAxis, the box X axis
		* @param[out] o_Length, the box length
		* @param[out] o_Width, the box width
		* @param[out] o_Heigth, the box height
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateBoxScript(NctiBaseModel* i_pBaseModel,
			const std::vector<std::string>& i_objNameVec, const std::vector<Ncti_Long>& i_edgeIDVec,
			NctiPosition& o_ptCenter, NctiVector& o_ZAxis, NctiVector& o_XAxis, double& o_Length, double& o_Width, double& o_Heigth);
		/**
		* @brief create the box script
		* @details create the box script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_pt, the box center position
		* @param[in] i_ZAxis, the box Z axis
		* @param[in] i_XAxis, the box X axis
		* @param[in] i_Length, the box length
		* @param[in] i_Width, the box width
		* @param[in] i_Heigth, the box height
		* @return the script
		*/
		static std::string CreateBoxPyCommand(NctiBaseModel* i_pBaseModel, const NctiPosition& i_pt, const NctiVector& i_ZAxis, const NctiVector& i_XAxis, double i_Length, double i_Width, double i_Heigth);

		//圆柱
		/**
		* @brief create the cylinder script
		* @details create the cylinder script
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateCylinderScript(NctiBaseModel* i_pBaseModel, std::string& o_strCmd);
		/**
		* @brief create the cylinder script
		* @details create the cylinder script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_cellIdVec, the cell id vector
		* @param[out] o_strCmd, the output script
		* @param[out] o_strName, the output cylinder name
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateCylinderScript(NctiBaseModel* i_pBaseModel,
			const std::vector<std::string>& i_objNameVec, const std::vector<Ncti_Long>& i_cellIdVec, std::string& o_strCmd, std::string& o_strName);
		/**
		* @brief create the cylinder script
		* @details create the cylinder script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objName, the object name
		* @param[in] i_cellId, the cell id
		* @param[out] o_Axis, the cylinder axis
		* @param[out] o_Radius, the cylinder radius
		* @param[out] o_Height, the cylinder height
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateCylinderScript(NctiBaseModel* i_pBaseModel,
			const std::string& i_objName, const Ncti_Long& i_cellId, NctiAxis& o_Axis, Ncti_Double& o_Radius, Ncti_Double& o_Height);
		/**
		* @brief create the cylinder script
		* @details create the cylinder script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_axis, the cylinder axis
		* @param[in] i_dRadius, the cylinder radius
		* @param[in] i_Height, the cylinder height
		* @param[out] o_strName, the output cylinder name
		* @return the script
		*/
		static std::string CreateCylinderPyScript(NctiBaseModel* i_pBaseModel, const NctiAxis& i_axis, const Ncti_Double& i_dRadius, const Ncti_Double& i_Height, std::string& o_strName);
		/**
		* @brief create the cylinder script
		* @details create the cylinder script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the cylinder name
		* @param[in] i_axis, the cylinder axis
		* @param[in] i_dRadius, the cylinder radius
		* @param[in] i_Height, the cylinder height
		* @return the script
		*/
		static std::string CreateCylinderPyScript(NctiBaseModel* i_pBaseModel, const char* i_name, const NctiAxis& i_axis, const Ncti_Double& i_dRadius, const Ncti_Double& i_Height);

		//圆锥
		/**
		* @brief create the cone script
		* @details create the cone script
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_strCmdVec, the output script vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateConeScript(NctiBaseModel* i_pBaseModel, std::vector<std::string>& o_strCmdVec);
		/**
		* @brief create the cone script
		* @details create the cone script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_cellIdVec, the cell id vector
		* @param[out] o_strCmdVec, the output script vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateConeScript(NctiBaseModel* i_pBaseModel,
			const std::vector<std::string>& i_objNameVec, const std::vector<Ncti_Long>& i_cellIdVec, std::vector<std::string>& o_strCmdVec);
		/**
		* @brief create the cone script
		* @details create the cone script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objName, the object name
		* @param[in] i_cellId, the cell id
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateConeScript(NctiBaseModel* i_pBaseModel,
			const std::string& i_objName, const Ncti_Long& i_cellId, std::string& o_strCmd);
		/**
		* @brief create the cone script
		* @details create the cone script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_dButtonRadius, the bottom radius
		* @param[in] i_dTopRadius, the top radius
		* @param[in] i_dHeight, the height of the cone
		* @param[in] i_pt, the center position of the bottom
		* @param[in] i_ZAxis, the cone Z axis
		* @param[in] i_XAxis, the cone X axis
		* @param[in] i_dAngle, the angle of the cone
		* @return the script
		*/
		static std::string CreateConePyCommand(NctiBaseModel* i_pBaseModel, double i_dButtonRadius, double i_dTopRadius, double i_dHeight,
			NctiPosition i_pt, NctiVector i_ZAxis, NctiVector i_XAxis, double i_dAngle);
		/**
		* @brief create the cone script
		* @details create the cone script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the cone name
		* @param[in] i_dButtonRadius, the bottom radius
		* @param[in] i_dTopRadius, the top radius
		* @param[in] i_dHeight, the height of the cone
		* @param[in] i_pt, the center position of the bottom
		* @param[in] i_normal, the cone normal vector
		* @return the script
		*/
		static std::string CreateConePyCommand(NctiBaseModel* i_pBaseModel, const char* i_name, double i_dButtonRadius, double i_dTopRadius, double i_dHeight,
			const NctiPosition& i_pt, const NctiVector& i_normal);

		//球
		/**
		* @brief create the sphere script
		* @details create the sphere script
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_strCmdVec, the output script vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateSphereScript(NctiBaseModel* i_pBaseModel, std::vector<std::string>& o_strCmdVec);
		/**
		* @brief create the sphere script
		* @details create the sphere script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_cellIdVec, the cell id vector
		* @param[out] o_strCmdVec, the output script vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateSphereScript(NctiBaseModel* i_pBaseModel,
			const std::vector<std::string>& i_objNameVec, const std::vector<Ncti_Long>& i_cellIdVec, std::vector<std::string>& o_strCmdVec);
		/**
		* @brief create the sphere script
		* @details create the sphere script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_dRadius, the sphere radius
		* @param[in] i_pt, the sphere center position
		* @param[in] i_ZAxis, the sphere Z axis
		* @return the script
		*/
		static std::string CreateSphereScript(NctiBaseModel* i_pBaseModel, double i_dRadius, NctiPosition i_pt, NctiVector i_ZAxis);
		/**
		* @brief create the sphere script
		* @details create the sphere script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the sphere name
		* @param[in] i_dRadius, the sphere radius
		* @param[in] i_pt, the sphere center position
		* @param[in] i_ZAxis, the sphere Z axis
		* @return the script
		*/
		static std::string CreateSphereScript(NctiBaseModel* i_pBaseModel,const char* i_name, double i_dRadius, NctiPosition i_pt, NctiVector i_ZAxis);

		//圆环
		/**
		* @brief create the torus script
		* @details create the torus script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the torus name
		* @param[in] i_radius, the torus major radius
		* @param[in] i_sectionRadius, the torus minor radius
		* @param[in] i_pt, the torus center position
		* @param[in] i_ZAxis, the torus Z axis
		* @return the script
		*/
		static std::string CreateTorusPyCommand(NctiBaseModel* i_pBaseModel, const char* i_name, double i_radius, double i_sectionRadius, NctiPosition i_pt, NctiVector i_ZAxis);
		//布尔
		/**
		* @brief create the boolean script of multi objects
		* @details create the boolean script of multi objects
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_BoolType, the boolean type(UNKNOWN = -1, UNIT = 0, CUT = 1, INTERSECT = 2)
		* @param[in] i_baseObjectNames, the base object names
		* @param[in] i_toolObjectNames, the tool object names
		* @return the script
		*/
		static std::string CreateMultiBooleanPyScript(NctiBaseModel* i_pBaseModel, int i_BoolType, const std::vector<std::string>& i_baseObjectNames, const std::vector<std::string>& i_toolObjectNames);
		
		//圆角 倒角
		/**
		* @brief create the chamfer script
		* @details create the chamfer script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_cellIdVec, the cell id vector
		* @param[out] o_objNameVec, the output object name vector
		* @param[out] o_ptVecVec, the output point vector vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateChamferScript(NctiBaseModel* i_pBaseModel,
			const std::vector<std::string>& i_objNameVec, const std::vector<Ncti_Long>& i_cellIdVec, std::vector<std::string>& o_objNameVec, std::vector<std::vector<NctiPosition>>& o_ptVecVec);
		/**
		* @brief create the chamfer python command
		* @details create the chamfer python command
		* @param[in] i_i_pBaseModel, the base model
		* @param[in] i_ChamferType, the chamfer type
		* @param[in] i_Radius, the chamfer radius
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_ptVecVec, the point vector vector
		* @return the script vector
		*/
		static std::vector<std::string> CreateChamferPyCommand(NctiBaseModel* i_pBaseModel, Ncti_Integer i_ChamferType, double i_Radius, const std::vector<std::string>& i_objNameVec, const std::vector<std::vector<NctiPosition>>& i_ptVecVec);

		//Array
		/**
		* @brief get length and direction from selected object 
		* @details get length and direction from selected object 
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_Length, the length
		* @param[out] o_vec, the direction vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetLengthAndDir(NctiBaseModel* i_pBaseModel, double& o_Length, NctiVector& o_vec);
		/**
		* @brief get direction from selected object
		* @details get direction from selected object
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_vec, the direction vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetVector(NctiBaseModel* i_pBaseModel, NctiVector& o_vec);
		/**
		* @brief create the rectangular array script
		* @details create the rectangular array script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_Num, the number of the array
		* @param[in] i_Length, the length of the array
		* @param[in] i_MoveVec, the move vector
		* @return the script vector
		*/
		static std::vector<std::string> CreateRectangularArrayPyScript(NctiBaseModel* i_pBaseModel, const std::vector<std::string>& i_objNameVec, int i_Num, double i_Length, const NctiVector& i_MoveVec);
		/**
		* @brief create the circular array script
		* @details create the circular array script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_Num, the number of the array
		* @param[in] i_Angle, the angle of the array
		* @param[in] i_pt, the center position of the array
		* @param[in] i_normal, the normal vector of the array
		* @return the script vector
		*/
		static std::vector<std::string> CreateRotateArrayPyScript(NctiBaseModel* i_pBaseModel, const std::vector<std::string>& i_objNameVec,
			int i_Num, double i_Angle, const NctiPosition& i_pt, const NctiVector& i_normal);
		
		//创建线条、轮廓、拉伸
		/**
		* @brief create the curve wire primitive script
		* @details create the curve wire primitive script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_bCreateFace, whether to create face
		* @param[in] i_strNameVec, the object name vector
		* @param[in] i_edgeVec, the edge id vector
		* @param[out] o_strCmdVec, the output script vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateCurveWirePrimScript(
			NctiBaseModel* i_pBaseModel, bool i_bCreateFace, const std::vector<std::string>& i_strNameVec,
			const std::vector<Ncti_Long>& i_edgeVec, std::vector<std::string>& o_strCmdVec);
		/**
		* @brief create the curve wire primitive script from face
		* @details create the curve wire primitive script from face
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pTopoFace, the topo face
		* @param[in] i_Index, the index
		* @param[in] i_headName, the head name
		* @param[in] i_bCreateFace, whether to create face
		* @param[in] i_bPrism, whether to create prism
		* @param[in] i_prismVec, the prism vector
		* @param[out] o_WireNames, the wrie names
		* @return the script vector
		*/
		static std::vector<std::string> CreateCurveWirePrimFromFaceScript(
			NctiDisplayModelBody* i_pModelBody, NctiTopoFace* i_pTopoFace, int Index, const std::string i_headName,
			bool i_bCreateFace, bool i_bPrism, NctiVector i_prismVec, std::vector<std::string>& o_WireNames);
		/**
		* @brief create surface =script from face
		* @details create the curve wire primitive script from face
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pTopoFace, the topo face
		* @param[in] i_Index, the index
		* @param[in] i_headName, the head name
		* @return the script vector
		*/
		static std::vector<std::string> CreateSurfaceScript(
			NctiDisplayModelBody* i_pModelBody, NctiTopoFace* i_pTopoFace, int i_Index, const std::string& i_headName);
		/**
		* @brief get the edge curve command
		* @details get the edge curve command
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pCell, the topo cell
		* @param[in] i_name, the edge name
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetEdgeCurveCmd(NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pCell, const std::string& i_name, std::string& o_strCmd);
		/**
		* @brief get the edge curve command
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pCell, the topo cell
		* @param[in] i_pCurve, the curve object
		* @param[in] i_name, the edge name
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetCurveCmd(NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pCell, NctiGeomCurve* i_pCurve, const std::string& i_name, std::string& o_strCmd);
		/**
		* @brief create the line script
		* @details create the line script
		* @param[in] i_pt1, the line start point
		* @param[in] i_pt2, the line end point
		* @param[in] i_name, the line name
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateLineScript(const NctiPosition& i_pt1, const NctiPosition& i_pt2, const std::string& i_name, std::string& o_strCmd);
		/**
		* @brief create the circle script
		* @details create the circle script
		* @param[in] i_center, the circle center point
		* @param[in] i_normal, the circle normal vector
		* @param[in] i_radius, the circle radius
		* @
		*/
		static Ncti_Boolean CreateLineScript(NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pCell, NctiGeomLine* i_pLine, const std::string& i_name, std::string& o_strCmd);
		/**
		* @brief create the circle script
		* @details create the circle script
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pCell, the topo cell
		* @param[in] i_pCircle, the geometry circle
		* @param[in] i_name, the circle name
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateCircleScript(NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pCell, NctiGeomCircle* i_pCircle, const std::string& i_name, std::string& o_strCmd);
		/**
		* @brief create the bezier script
		* @details create the bezier script
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pCell, the topo cell
		* @param[in] i_pBezierCurve, the geometry bezier curve
		* @param[in] i_name, the bezier name
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/ 
		static Ncti_Boolean CreateBezierScript(NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pCell, NctiGeomBezierCurve* i_pBezierCurve, const std::string& i_name, std::string& o_strCmd);
		/**
		* @brief create the bspline script
		* @details create the bspline script
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pCell, the topo cell
		* @param[in] i_pBSplineCurve, the geometry bspline curve
		* @param[in] i_name, the bspline name
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateBSplineScript(NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pCell, NctiGeomBSplineCurve* i_pBSplineCurve, const std::string& i_name, std::string& o_strCmd);
		/**
		* @brief create the ellipse script
		* @details create the ellipse script
		* @param[in] i_pModelBody, the model body
		* @param[in] i_pCell, the topo cell
		* @param[in] i_pEllipseCurve, the geometry ellipse curve
		* @param[in] i_name, the ellipse name
		* @param[out] o_strCmd, the output script
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateEllipseScript(NctiDisplayModelBody* i_pModelBody, NctiTopoCell* i_pCell, NctiGeomEllipse* i_pEllipseCurve, const std::string& i_name, std::string& o_strCmd);

		/**
		* @brief get angle from two selected cells which are curves
		* @details get angle from selected cells which are curves
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_dAngle, the angle
		*/
		static Ncti_Boolean GetAngle(NctiBaseModel* i_pBaseModel, double& o_dAngle);
		/**
		* @brief get the center of a circle or the midpoint of the centers of two circles from selectData
		* @details get the center of a circle or the midpoint of the centers of two circles from selectData
		* @param[in] i_pBaseModel, the base model
		* @param[out] i_pt, the center point
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetCenterPt(NctiBaseModel* i_pBaseModel, NctiPosition& i_pt);
		/**
		* @brief create the revolve script
		* @details create the revolve script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_strNameVec, the object name vector
		* @param[in] i_edgeVec, the edge id vector
		* @param[out] o_strCmdVec, the output script vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateRevolvePyScript(NctiBaseModel* i_pBaseModel, const std::vector<std::string>& i_strNameVec,
			const std::vector<Ncti_Long>& i_edgeVec, std::vector<std::string>& o_strCmdVec);
		/**
		* @brief create the revolve script
		* @details create the revolve script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_resName, the revolve name
		* @param[in] i_outlineName, the outline name
		* @param[in] i_pos, the revolve axis position
		* @param[in] i_normal, the revolve axis normal
		* @param[in] i_rotateAngle, the revolve angle
		* @return the script
		*/
		static std::string CreateRevolvePyScript(NctiBaseModel* i_pBaseModel,const char* i_resName, const char* i_outlineName, const NctiPosition& i_pos, const NctiVector& i_normal, Ncti_Double i_rotateAngle);
		/**
		* @brief create the cross section script
		* @details create the cross section script
		* @param[in] i_pEdgeBodyVec, the edge model body vector
		* @param[in] i_pEdgeCellVec, the edge topo cell vector
		* @param[out] o_strCmds, the output script vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean CreateCrossSectionScript(const std::vector<NctiDisplayModelBody*>& i_pEdgeBodyVec, const std::vector<NctiTopoCell*>& i_pEdgeCellVec, std::vector<std::string>& o_strCmds);
		//Transform
		/**
		* @brief create the move script
		* @details create the move script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_strNameVec, the object name vector
		* @param[in] i_Vec, the move vector
		* @return the script
		*/
		static std::string CreateMovePyCommand(const std::vector<std::string>& i_strNameVec, const NctiVector& i_Vec);
		//mirror
		/**
		* @brief get center point and direction from selected cells 
		* @details get center point and direction from selected cells (circle and circle,or point and point)
		* @param[in] i_pBaseModel, the base model
		* @param[out] o_pt, the center point
		* @param[out] o_vec, the direction vector
		* @return true if success, false otherwise
		*/
		static Ncti_Boolean GetCenterPtAndDir(NctiBaseModel* i_pBaseModel, NctiPosition& o_pt, NctiVector& o_vec);
		/**
		* @brief create the mirror script
		* @details create the mirror script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_objNameVec, the object name vector
		* @param[in] i_pt, the mirror plane point
		* @param[in] i_vec, the mirror plane normal
		* @return the script vector
		*/
		static std::vector<std::string> CreateMirrorPyScript(NctiBaseModel* i_pBaseModel, const std::vector<std::string>& i_objNameVec, const NctiPosition& i_pt, const NctiVector& i_vec);
		//swept
		/**
		* @brief create the swept script
		* @details create the swept script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_resName, the swept name
		* @param[in] i_spineName, the spine name
		* @param[in] i_sectionName, the section name
		* @param[in] i_sweptMode, the swept mode
		* @return the script
		*/
		static std::string CreateSweptPyScript(NctiBaseModel* i_pBaseModel, const char* i_resName, const char* i_spineName, const char* i_sectionName, Ncti_Integer i_sweptMode);
		//trim
		/**
		* @brief create the trim script
		* @details create the trim script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_resName, the trim name
		* @param[in] i_sourceName, the source name
		* @param[in] i_su, the start u parameter
		* @param[in] i_eu, the end u parameter
		* @return the script
		*/
		static std::string CreateTrimPyScript(NctiBaseModel* i_pBaseModel, const char* i_resName, const char* i_sourceName, Ncti_Double i_su, Ncti_Double i_eu);
		/**
		* @brief create the trim script
		* @details create the trim script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_resName, the trim name
		* @param[in] i_sourceName, the source name
		* @param[in] i_su, the start u parameter string
		* @param[in] i_eu, the end u parameter string
		* @return the script
		*/
		static std::string CreateTrimPyScript(NctiBaseModel* i_pBaseModel, const char* i_resName, const char* i_sourceName, const char* i_su, const char* i_eu);
		//delete
		/**
		* @brief create the delete script
		* @details create the delete script
		* @param[in] i_pBaseModel, the base model
		* @param[in] i_name, the object name
		* @return the script
		*/
		static std::string CreateDeletePyScript(NctiBaseModel* i_pBaseModel, const char* i_name);

	};
}
#endif // !NctiCreateModelScriptPub_H
