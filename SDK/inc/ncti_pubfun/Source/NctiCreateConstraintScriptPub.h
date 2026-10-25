#ifndef NctiCreateConstraintScriptPub_H
#define NctiCreateConstraintScriptPub_H
#include "ncti_base.h"
#include "dcl_ncti_pubfun.h"
#include "NctiDCM3Def.h"
#include <vector>
#include <sstream>
namespace NCTI
{
	class NctiDisplayDocCustomContainer;
	class NctiBaseModel;
	class NctiDisplayModelBody;
	class NctiPosition;
	class NctiVector;
	/**
	* @brief create the script for constraint
	* @details create the script for constraint
	* @see NctiDCM3Def
	*/
	class DECL_NCTI_PUBFUN NctiCreateConstraintScriptPub
	{
	public:
		NctiCreateConstraintScriptPub();
		~NctiCreateConstraintScriptPub();
		/**
		* @brief get new name for dcm3 geometry type
		* @details get new name for dcm3 constraint
		* @param[in] pBaseModel, the base model
		* @param[in] g_type, the dcm3 geometry type
		* @return the new name
		*/
		static std::string GetNewName(NctiBaseModel* pBaseModel, ncti_DCM3_g_type g_type);
		/**
		* @brief get new name for dcm3 dimension type
		* @details get new name for dcm3 constraint
		* @param[in] pBaseModel, the base model
		* @param[in] d_type, the dcm3 dimension type
		* @return the new name
		*/
		static std::string GetNewName(NctiBaseModel* pBaseModel, ncti_DCM3_d_type d_type);
		/**
		* @brief get new name for type name with preffix
		* @details get new name for type name with preffix
		* @param[in] pBaseModel, the base model
		* @param[in] typeName, the type name
		* @param[in] preffix, the preffix of name
		* @return the new name
		*/
		static std::string GetNewName(NctiBaseModel* pBaseModel, const char* typeName, const char* preffix);

		//创建
		/**
		* @brief create the dcm3 dimension system script
		* @details create the dcm3 dimension system script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @return the script
		*/
		static std::string CreateDCM3DimSysScript(NctiBaseModel* pBaseModel, const char* dcmSysName);
		/**
		* @brief create the dcm3 point script
		* @details create the dcm3 dimension system script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3PointScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 point script
		* @details create the dcm3 point script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmPointName, the dcm3 point name
		* @return the script
		*/
		static std::string CreateDCM3PointScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const char* dcmSysName, const char* modelName, const char* dcmPointName);
		/**
		* @brief create the dcm3 line script
		* @details create the dcm3 line script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dir, the direction
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3LineScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const NctiVector& dir, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 line script
		* @details create the dcm3 line script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dir, the direction
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmLineName, the dcm3 line name
		* @return the script
		*/
		static std::string CreateDCM3LineScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const NctiVector& dir, const char* dcmSysName, const char* modelName, const char* dcmLineName);
		/**
		* @brief create the dcm3 circle script
		* @details create the dcm3 circle script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] radius, the radius of circle
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3CircleScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, Ncti_Double radius, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 circle script
		* @details create the dcm3 circle script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] radius, the radius of circle
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmCircleName, the dcm3 circle name
		* @return the script
		*/
		static std::string CreateDCM3CircleScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, Ncti_Double radius, const char* dcmSysName, const char* modelName, const char* dcmCircleName);
		/**
		* @brief create the dcm3 ellipse script
		* @details create the dcm3 ellipse script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] dir, the direction vector
		* @param[in] major, the major radius of ellipse
		* @param[in] minor, the minor radius of ellipse
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3EllipseScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, const NctiVector& dir, Ncti_Double major, Ncti_Double minor, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 ellipse script
		* @details create the dcm3 ellipse script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] dir, the direction vector
		* @param[in] major, the major radius of ellipse
		* @param[in] minor, the minor radius of ellipse
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmEllipseName, the dcm3 ellipse name
		* @return the script
		*/
		static std::string CreateDCM3EllipseScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, const NctiVector& dir, Ncti_Double major, Ncti_Double minor, const char* dcmSysName, const char* modelName, const char* dcmEllipseName);
		/**
		* @brief create the dcm3 plane script
		* @details create the dcm3 plane script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dir, the direction
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3PlaneScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const NctiVector& dir, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 plane script
		* @details create the dcm3 plane script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dir, the direction
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmPlaneName, the dcm3 plane name
		* @return the script
		*/
		static std::string CreateDCM3PlaneScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const NctiVector& dir, const char* dcmSysName, const char* modelName, const char* dcmPlaneName);
		/**
		* @brief create the dcm3 cylinder script
		* @details create the dcm3 cylinder script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dir, the direction
		* @param[in] radius, the radius of cylinder
		* @param[in] height, the height of cylinder
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3CylinderScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const NctiVector& dir, Ncti_Double radius, Ncti_Double height, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 cylinder script
		* @details create the dcm3 cylinder script
		* @param[in] pBaseModel, the base model
		* @param[in] pos, the position
		* @param[in] dir, the direction
		* @param[in] radius, the radius of cylinder
		* @param[in] height, the height of cylinder
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmCylinderName, the dcm3 cylinder name
		* @return the script
		*/
		static std::string CreateDCM3CylinderScript(NctiBaseModel* pBaseModel, const NctiPosition& pos, const NctiVector& dir, Ncti_Double radius, Ncti_Double height, const char* dcmSysName, const char* modelName, const char* dcmCylinderName);
		/**
		* @brief create the dcm3 sphere script
		* @details create the dcm3 sphere script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] radius, the radius of sphere
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3ShpereScript(NctiBaseModel* pBaseModel, const NctiPosition& centre,  Ncti_Double radius, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 sphere script
		* @details create the dcm3 sphere script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] radius, the radius of sphere
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmShperemName, the dcm3 sphere name
		* @return the script
		*/
		static std::string CreateDCM3ShpereScript(NctiBaseModel* pBaseModel, const NctiPosition& centre,  Ncti_Double radius, const char* dcmSysName, const char* modelName, const char* dcmShperemName);
		/**
		* @brief create the dcm3 cone script
		* @details create the dcm3 cone script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] radius, the radius of cone
		* @param[in] halfAngle, the half angle of cone
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3ConeScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, Ncti_Double radius, Ncti_Double halfAngle, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 cone script
		* @details create the dcm3 cone script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] radius, the radius of cone
		* @param[in] halfAngle, the half angle of cone
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmConeName, the dcm3 cone name
		* @return the script
		*/
		static std::string CreateDCM3ConeScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, Ncti_Double radius,  Ncti_Double halfAngle, const char* dcmSysName, const char* modelName, const char* dcmConeName);
		/**
		* @brief create the dcm3 cone script
		* @details create the dcm3 cone script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] radius, the radius of torus
		* @param[in] sectionRadius, the section radius of torus
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[out] o_dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3TorusScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, Ncti_Double radius, Ncti_Double sectionRadius, const char* dcmSysName, const char* modelName, std::string& o_dcmGeomName);
		/**
		* @brief create the dcm3 cone script
		* @details create the dcm3 cone script
		* @param[in] pBaseModel, the base model
		* @param[in] centre, the centre position
		* @param[in] normal, the normal vector
		* @param[in] radius, the radius of torus
		* @param[in] sectionRadius, the section radius of torus
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] modelName, the model name
		* @param[in] dcmTorusName, the dcm3 torus name
		* @return the script
		*/
		static std::string CreateDCM3TorusScript(NctiBaseModel* pBaseModel, const NctiPosition& centre, const NctiVector& normal, Ncti_Double radius, Ncti_Double sectionRadius, const char* dcmSysName, const char* modelName, const char* dcmTorusName);
		/**
		* @brief create the dcm3 set script
		* @details create the dcm3 set script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmGeomNameVec, the dcm3 geometry name vector
		* @param[out] o_dcmSetName, the dcm3 set name
		* @return the script
		*/
		static std::string CreateDCM3SetScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const std::vector<std::string>& dcmGeomNameVec, std::string& o_dcmSetName);
		/**
		* @brief create the dcm3 set script
		* @details create the dcm3 set script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmGeomNameVec, the dcm3 geometry name vector
		* @param[in] dcmSetName, the dcm3 set name
		* @return the script
		*/
		static std::string CreateDCM3SetScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const std::vector<std::string>& dcmGeomNameVec, const char* dcmSetName);
		/**
		* @brief create the dcm3 set script
		* @details create the dcm3 set script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmGeomNameVec, the dcm3 geometry name vector
		* @param[in] modelName, the model name
		* @param[out] o_dcmSetName, the dcm3 set name
		* @return the script
		*/
		static std::string CreateDCM3SetScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const std::vector<std::string>& dcmGeomNameVec, const char* modelName, std::string& o_dcmSetName);
		/**
		* @brief create the dcm3 set script
		* @details create the dcm3 set script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmGeomNameVec, the dcm3 geometry name vector
		* @param[in] modelName, the model name
		* @param[in] dcmSetName, the dcm3 set name
		* @return the script
		*/
		static std::string CreateDCM3SetScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const std::vector<std::string>& dcmGeomNameVec, const char* modelName, const char* dcmSetName, const std::vector<long>& i_cellIDVec = {});
		/**
		* @brief create the dcm3 spun script
		* @details create the dcm3 spun script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] outlineName, the outline name
		* @param[in] modelName, the model name
		* @param[in] pos, the position
		* @param[in] normal, the normal vector
		* @param[in] su, the start u parameter
		* @param[in] eu, the end u parameter
		* @param[in] period, the period flag
		* @param[out] o_dcmSpunName, the dcm3 spun name
		* @return the script
		*/
		static std::string CreateDCM3SpunScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* outlineName, const char* modelName, const NctiPosition& pos, const NctiVector& normal, const char* su, const char* eu, Ncti_Boolean period, const char* dcmSpunName);
		/**
		* @brief create the dcm3 swept script
		* @details create the dcm3 swept script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] sectionName, the section name
		* @param[in] modelName, the model name
		* @param[in] dir, the direction vector
		* @param[in] su, the start u parameter
		* @param[in] eu, the end u parameter
		* @param[in] period, the period flag
		* @param[in] dcmSweptName, the dcm3 swept name
		* @return the script
		*/
		static std::string CreateDCM3SweptScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* sectionName, const char* modelName, const NctiVector& dir, const char* su, const char* eu, Ncti_Boolean period, const char* dcmSweptName);
		/**
		* @brief create the dcm3 equal distance dimension script
		* @details create the dcm3 equal distance dimension script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] distance, the distance value
		* @param[in] dcmEqualDistName, the dcm3 equal distance dimension name
		* @return the script
		*/
		static std::string CreateDCM3EqualDistanceScript(NctiBaseModel* pBaseModel, const char* dcmSysName, Ncti_Double distance, const char* dcmEqualDistName);
		/**
		* @brief create the dcm3 dimension script
		* @details create the dcm3 dimension script
		* @param[in] pBaseModel, the base model
		* @param[in] d_type, the dcm3 dimension type
		* @param[out] o_DimensionName, the dcm3 dimension name
		* @return the script
		*/
		static std::string CreateDCM3DimensionScript(NctiBaseModel* pBaseModel, ncti_DCM3_d_type d_type, std::string& o_DimensionName);
		/**
		* @brief create the dcm3 dimension script
		* @details create the dcm3 dimension script
		* @param[in] pBaseModel, the base model
		* @param[in] d_type, the dcm3 dimension type
		* @param[in] dimName, the dcm3 dimension name
		* @return the script
		*/
		static std::string CreateDCM3DimensionScript(NctiBaseModel* pBaseModel, ncti_DCM3_d_type d_type, const char* dimName);
		/**
		* @brief create the dcm3 dimension script
		* @details create the dcm3 dimension script
		* @param[in] pBaseModel, the base model
		* @param[in] d_type, the dcm3 dimension type
		* @param[in] value, the dimension value
		* @param[out] o_DimensionName, the dcm3 dimension name
		* @return the script
		*/
		static std::string CreateDCM3DimensionScript(NctiBaseModel* pBaseModel, ncti_DCM3_d_type d_type, Ncti_Double value, std::string& o_DimensionName);
		/**
		* @brief create the dcm3 dimension script
		* @details create the dcm3 dimension script
		* @param[in] pBaseModel, the base model
		* @param[in] d_type, the dcm3 dimension type
		* @param[in] value, the dimension value
		* @param[in] dimName, the dcm3 dimension name
		* @return the script
		*/
		static std::string CreateDCM3DimensionScript(NctiBaseModel* pBaseModel, ncti_DCM3_d_type d_type, Ncti_Double value, const char* dimName);
		/**
		* @brief create the dcm3 linear pattern element script
		* @details create the dcm3 linear pattern element script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dir, the direction vector
		* @param[in] val, the value
		* @param[out] o_name, the dcm3 linear pattern element name
		* @return the script
		*/
		static std::string CreateDCM3LinearPatternElement(NctiBaseModel* pBaseModel, const char* dcmSysName, const NctiVector& dir, Ncti_Double val, std::string& o_name);
		/**
		* @brief create the dcm3  pattern element script
		* @details create the dcm3  pattern element script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[out] o_name, the dcm3 pattern element name
		*/
		static std::string CreateDCM3PatternContainer(NctiBaseModel* pBaseModel, const char* dcmSysName, std::string& o_name);
		/**
		* @brief create the dcm3 parametric curve script
		* @details create the dcm3 parametric curve script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmPcurveName, the dcm3 parametric curve name
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] func, the function string
		* @param[in] su, the start u parameter
		* @param[in] eu, the end u parameter
		* @param[in] period, the period flag
		* @param[in] modelName, the model name
		* @return the script
		*/
		static std::string CreateDCM3ParametricCurveScript(NctiBaseModel* pBaseModel, const char* dcmPcurveName, const char* dcmSysName, const char* func, const char* su, const char* eu, Ncti_Boolean period, const char* modelName);


		//操作
		/**
		* @brief create the dcm3 fix script
		* @details create the dcm3 fix script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmGeomName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3FixScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmGeomName);
		/**
		* @brief create the dcm3 fix parameter script
		* @details create the dcm3 fix parameter script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmParamName, the dcm3 parameter name
		* @return the script
		*/
		static std::string CreateDCM3FixParameterScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmParamName);
		/**
		* @brief create the dcm3 add dimensioned constraint script
		* @details create the dcm3 add dimensioned constraint script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmDimName, the dcm3 dimension name
		* @param[in] dcmObjName1, the first dcm3 geometry name
		* @param[in] dcmObjName2, the second dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3AdddScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmDimName, const char* dcmObjName1, const char* dcmObjName2);
		/**
		* @brief create the dcm3 add dimensioned constraint script
		* @details create the dcm3 add dimensioned constraint script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmDimName, the dcm3 dimension name
		* @param[in] dcmObjName1, the first dcm3 geometry name
		* @param[in] dcmObjName2, the second dcm3 geometry name
		* @param[in] dcmObjName3, the third dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3AdddScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmDimName, const char* dcmObjName1, const char* dcmObjName2, const char* dcmObjName3);
		/**
		* @brief create the dcm3 add dimensioned constraint script
		* @details create the dcm3 add dimensioned constraint script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmDimName, the dcm3 dimension name
		* @param[in] dcmObjName1, the first dcm3 geometry name
		* @param[in] dcmObjName2, the second dcm3 geometry name
		* @param[in] dcmObjName3, the third dcm3 geometry name
		* @param[in] dcmObjName4, the fourth dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3AdddScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmDimName, const char* dcmObjName1, const char* dcmObjName2, const char* dcmObjName3, const char* dcmObjName4);
		/**
		* @brief create the dcm3 add dimensioned constraint script
		* @details create the dcm3 add dimensioned constraint script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmDimName, the dcm3 dimension name
		* @param[in] dcmObjName, the dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3AddrScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmDimName, const char* dcmObjName);
		/**
		* @brief create the dcm3 move to set script
		* @details create the dcm3 move to set script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmSetName, the dcm3 set name
		* @param[in] dcmGeomNameVec, the vector of dcm geometry name
		* @return the script
		*/
		static std::string CreateDCM3MoveToSetScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmSetName, const std::vector<const char*>& dcmGeomNameVec);
		/**
		* @brief create the dcm3 add bias script
		* @details create the dcm3 add bias script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmNodeName, the dcm3 node name
		* @param[in] value, the bias value
		* @param[in] nodeType, the node type
		* @param[in] bias, the bias type
		* @param[in] component, the bias component type
		* @return the script
		*/
		static std::string CreateDCM3AddBiasScript(const char* dcmSysName, const char* dcmNodeName, Ncti_Double value, Ncti_Integer nodeType, ncti_DCM3_bias bias, ncti_DCM3_bias_component component = NCTI_DCM3_BIAS_COMPONENT_WHOLE);
		/**
		* @brief create the dcm3 add pattern array script
		* @details create the dcm3 add pattern array script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] containerName, the dcm3 pattern container name
		* @param[in] elementNames, the vector of dcm3 pattern element name
		* @return the script
		*/
		static std::string CreateDCM3AddPatternArrayScript(const char* dcmSysName, const char *containerName, const std::vector<std::string> &elementNames);

		//更新、编辑
		/**
		* @brief create the dcm3 set ends script
		* @details create the dcm3 set ends script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] dcmGeomName1, the first dcm3 geometry name
		* @param[in] dcmGeomName2, the second dcm3 geometry name
		* @return the script
		*/
		static std::string CreateDCM3SetEndsScript(NctiBaseModel* pBaseModel, const char* dimensionName, const char* dcmGeomName1, const char* dcmGeomName2);
		/**
		* @brief create the dcm3 set help point script
		* @details create the dcm3 set help point script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] dcmGeomName, the dcm3 geometry name
		* @param[in] hp, the help point type
		* @param[in] pos, the help point position
		* @return the script
		*/
		static std::string CreateDCM3SetHelpPointScript(NctiBaseModel* pBaseModel, const char* dimensionName, const char* dcmGeomName, ncti_DCM3_help_points hp, const NctiPosition& pos);
		/**
		* @brief create the dcm3 set help parameter script
		* @details create the dcm3 set help parameter script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] dcmGeomName, the dcm3 geometry name
		* @param[in] hpar, the help parameter value
		* @return the script
		*/
		static std::string CreateDCM3SetHelpParameterScript(NctiBaseModel* pBaseModel, const char* dimensionName, const char* dcmGeomName, Ncti_Double hpar);
		/**
		* @brief create the dcm3 set alignment script
		* @details create the dcm3 set alignment script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] alignmet, the alignment type
		* @return the script
		*/
		static std::string CreateDCM3SetAlignmentScript(NctiBaseModel* pBaseModel, const char* dimensionName, const char* alignmet);
		/**
		* @brief create the dcm3 set orientation script
		* @details create the dcm3 set orientation script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] orientation, the orientation type
		* @return the script
		*/
		static std::string CreateDCM3SetOrientationScript(NctiBaseModel* pBaseModel, const char* dimensionName, const char* orientation);
		/**
		* @brief create the dcm3 set radius type script
		* @details create the dcm3 set radius type script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] dcmGeomName, the dcm3 geometry name
		* @param[in] radType, the radius type
		* @return the script
		*/
		static std::string CreateDCM3SetRadiusTypeScript(NctiBaseModel* pBaseModel, const char* dimensionName,const char* dcmGeomName, const char* radType);
		/**
		* @brief create the dcm3 set dimension to script
		* @details create the dcm3 set dimension to script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] dcmGeomName, the dcm3 geometry name
		* @param[in] dimToType, the dimension to type
		* @return the script
		*/
		static std::string CreateDCM3SetDimToScript(NctiBaseModel* pBaseModel, const char* dimensionName,const char* dcmGeomName, const char* dimToType);
		/**
		* @brief create the dcm3 set resolution script
		* @details create the dcm3 set resolution script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] res, the resolution value
		* @param[in] size, the size value
		* @return the script
		*/
		static std::string CreateDCM3SetResolutionScript(const char* dcmSysName, Ncti_Double res, Ncti_Double size);
		/**
		* @brief create the dcm3 set pattern constrain script
		* @details create the dcm3 set pattern constrain script
		* @param[in] pBaseModel, the base model
		* @param[in] dimensionName, the dcm3 dimension name
		* @param[in] multi, the pattern constrain value vector
		* @return the script
		*/
		static std::string CreateDCM3SetPatternConstrainScript(NctiBaseModel* pBaseModel, const char* dimensionName, const std::vector<Ncti_Double> &multi);

		//求解
		/**
		* @brief create the dcm3 evaluate script
		* @details create the dcm3 evaluate script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @return the script
		*/
		static std::string CreateDCM3EvaluateScript(NctiBaseModel* pBaseModel, const char* dcmSysName);
		/**
		* @brief create the dcm3 re-evaluate script
		* @details create the dcm3 re-evaluate script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @return the script
		*/
		static std::string CreateDCM3ReEvaluateScript(NctiBaseModel* pBaseModel, const char* dcmSysName);
		/**
		* @brief create the dcm3 dynamic evaluate script
		* @details create the dcm3 dynamic evaluate script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmGeomNameVec, the vector of dcm3 geometry name
		* @param[in] trans, the vector of dcm3 transformation
		* @param[in] axis, the vector of dcm3 rotation axis
		* @param[in] angle, the rotation angle
		* @return the script
		*/
		static std::string CreateDCM3DynamicEvaluateScript(NctiBaseModel* pBaseModel, const char* dcmSysName, std::vector<const char*> dcmGeomNameVec, const NctiVector& trans, const NctiVector& axis, Ncti_Double angle);
		/**
		* @brief create the dcm3 undo evaluate script
		* @details create the dcm3 undo evaluate script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] mode, the undo mode
		* @return the script
		*/
		static std::string CreateDCM3UndoEvaluateScript(NctiBaseModel* pBaseModel, const char* dcmSysName, ncti_DCM3_undo_mode mode);

		//查询
		/**
		* @brief create the dcm3 parameter node script
		* @details create the dcm3 parameter node script
		* @param[in] pBaseModel, the base model
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmDimName, the dcm3 dimension name
		* @param[in] dcmGeomName, the dcm3 geometry name
		* @param[out] o_pnodeName, the dcm3 parameter node name
		* @return the script
		*/
		static std::string CreateDCM3ParameterNodeScript(NctiBaseModel* pBaseModel, const char* dcmSysName, const char* dcmDimName, const char* dcmGeomName, std::string& o_pnodeName);
		/**
		* @brief create the dcm Describe script
		* @details create the dcm Describe script
		* @param[in] dcmElemName, the dcm element name
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCMDescribeScript(const char* dcmElemName, std::string& o_resultName);
		/**
		* @brief create the dcm Evaluate Records script
		* @details create the dcm Evaluate Records script
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCMEvaluateRecordsScript(std::string& o_resultName);
		/**
		* @brief create the dcm3 help point script
		* @details create the dcm3 help point script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmElemName, the dcm3 element name
		* @param[in] dcmDimName, the dcm3 dimension name
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3HelpPointScript(const char* dcmSysName, const char* dcmElemName, const char* dcmDimName, std::string& o_resultName);
		/**
		* @brief create the dcm3 help parameter script
		* @details create the dcm3 help parameter script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmElemName, the dcm3 element name
		* @param[in] dcmDimName, the dcm3 dimension name
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3HelpParameterScript(const char* dcmSysName, const char* dcmElemName, const char* dcmDimName, std::string& o_resultName);
		/**
		* @brief create the dcm3 spline parameter limits script
		* @details create the dcm3 spline parameter limits script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmSplineName, the dcm3 spline name
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3SplineParameterLimitsScript(const char* dcmSysName, const char* dcmSplineName, std::string& o_resultName);
		/**
		* @brief create the dcm3 value script
		* @details create the dcm3 value script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmVarName, the dcm3 variable name
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3ValueScript(const char* dcmSysName, const char* dcmVarName, std::string& o_resultName);
		/**
		* @brief create the dcm3 status script
		* @details create the dcm3 status script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmNodeName, the dcm3 node name
		* @param[in] nodeType, the dcm3 node type
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3StatusScript(const char* dcmSysName, const char* dcmNodeName, Ncti_Integer nodeType, std::string& o_resultName);
		/**
		* @brief create the dcm3 constraints script
		* @details create the dcm3 constraints script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmNodeName, the dcm3 node name
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3ConstraintsScript(const char* dcmSysName, const char* dcmNodeName, std::string& o_resultName);
		/**
		* @brief create the dcm3 spline evaluator script
		* @details create the dcm3 spline evaluator script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[in] dcmSplineName, the dcm3 spline name
		* @param[in] t, the parameter t
		* @param[in] n_der, the number of der
		* @param[in] side, the discontinuity side
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3SplineEvaluatorScript(const char* dcmSysName, const char* dcmSplineName, Ncti_Double t, Ncti_Integer n_der, ncti_DCM3_discontinuity_side side, std::string& o_resultName);
		/**
		* @brief create the dcm3 constraint balance script
		* @details create the dcm3 constraint balance script
		* @param[in] dcmSysName, the dcm3 system name
		* @param[out] o_resultName, the result name
		* @return the script
		*/
		static std::string CreateDCM3ConstraintBalanceScript(const char* dcmSysName, std::string& o_resultName);
		//检查是否欠约束
		/**
		* @brief create the dcm3 check constraint status script
		* @details create the dcm3 check constraint status script
		* @param[in] ConBalResVarName, the constraint balance result variable name
		* @return the script
		*/
		static std::string CreateDCM3CheckConstraintStatusScript(const char* ConBalResVarName);
		/**
		* @brief create the dcm3 overdefined regions script
		* @details create the dcm3 overdefined regions script
		* @param[in] dcmSysName, the dcm3 system name
		* @return the script
		*/
		static std::string CreateDCM3OverdefinedRegionsScript(const char* dcmSysName);


		//获取数据
		/**
		* @brief get the point data
		* @details get the point data
		* @param[in] pBaseModel, the base model
		* @param[in] pModelBody, the model body
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @return true if success, false otherwise
		*/
		static bool GetPointData(NctiBaseModel* pBaseModel, NctiDisplayModelBody* pModelBody, Ncti_Long cellID, NctiPosition& o_pos);

		/**
		* @brief get the point data
		* @details get the point data
		* @param[in] pBaseModel, the base model
		* @param[in] objName, the object name
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @return true if success, false otherwise
		*/
		static bool GetPointData(NctiBaseModel* pBaseModel, const char* objName, Ncti_Long cellID, NctiPosition& o_pos);

		/**
		* @brief get the line data
		* @details get the line data
		* @param[in] pBaseModel, the base model
		* @param[in] pModelBody, the model body
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @param[out] o_dir, the output direction vector
		* @return true if success, false otherwise
		*/
		static bool GetLineData(NctiBaseModel* pBaseModel, NctiDisplayModelBody* pModelBody, Ncti_Long cellID, NctiPosition& o_pos, NctiVector& o_dir);

		/**
		* @brief get the line data
		* @details get the line data
		* @param[in] pBaseModel, the base model
		* @param[in] objName, the object name
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @param[out] o_dir, the output direction vector
		* @return true if success, false otherwise
		*/
		static bool GetLineData(NctiBaseModel* pBaseModel, const char* objName, Ncti_Long cellID, NctiPosition& o_pos, NctiVector& o_dir);

		/**
		* @brief get the circle data
		* @details get the circle data
		* @param[in] pBaseModel, the base model
		* @param[in] pModelBody, the model body
		* @param[in] cellID, the cell ID
		* @param[out] o_centre, the output centre position
		* @param[out] o_normal, the output normal vector
		* @param[out] o_radius, the output radius
		* @return true if success, false otherwise
		*/
		static bool GetCircleData(NctiBaseModel* pBaseModel, NctiDisplayModelBody* pModelBody, Ncti_Long cellID, NctiPosition& o_centre, NctiVector& o_normal, Ncti_Double& o_radius);
		
		/**
		* @brief get the circle data
		* @details get the circle data
		* @param[in] pBaseModel, the base model
		* @param[in] objName, the object name
		* @param[in] cellID, the cell ID
		* @param[out] o_centre, the output centre position
		* @param[out] o_normal, the output normal vector
		* @param[out] o_radius, the output radius
		* @return true if success, false otherwise
		*/
		static bool GetCircleData(NctiBaseModel* pBaseModel, const char* objName, Ncti_Long cellID, NctiPosition& o_centre, NctiVector& o_normal, Ncti_Double& o_radius);

		/**
		* @brief get the plane data
		* @details get the plane data
		* @param[in] pBaseModel, the base model
		* @param[in] pModelBody, the model body
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @param[out] o_dir, the output direction vector
		* @return true if success, false otherwise
		*/
		static bool GetPlaneData(NctiBaseModel* pBaseModel, NctiDisplayModelBody* pModelBody, Ncti_Long cellID, NctiPosition& o_pos, NctiVector& o_dir);

		/**
		* @brief get the plane data
		* @details get the plane data
		* @param[in] pBaseModel, the base model
		* @param[in] objName, the object name
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @param[out] o_dir, the output direction vector
		* @return true if success, false otherwise
		*/
		static bool GetPlaneData(NctiBaseModel* pBaseModel, const char* objName, Ncti_Long cellID, NctiPosition& o_pos, NctiVector& o_dir);

		/**
		* @brief get the cylinder data
		* @details get the cylinder data
		* @param[in] pBaseModel, the base model
		* @param[in] pModelBody, the model body
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @param[out] o_dir, the output direction vector
		* @param[out] o_radius, the output radius
		* @param[out] o_height, the output height
		* @return true if success, false otherwise
		*/
		static bool GetCylinderData(NctiBaseModel* pBaseModel, NctiDisplayModelBody* pModelBody, Ncti_Long cellID, NctiPosition& o_pos, NctiVector& o_dir, Ncti_Double& o_radius, Ncti_Double& o_height);
	
		/**
		* @brief get the cylinder data
		* @details get the cylinder data
		* @param[in] pBaseModel, the base model
		* @param[in] objName, the object name
		* @param[in] cellID, the cell ID
		* @param[out] o_pos, the output position
		* @param[out] o_dir, the output direction vector
		* @param[out] o_radius, the output radius
		* @param[out] o_height, the output height
		* @return true if success, false otherwise
		*/
		static bool GetCylinderData(NctiBaseModel* pBaseModel, const char* objName, Ncti_Long cellID, NctiPosition& o_pos, NctiVector& o_dir, Ncti_Double& o_radius, Ncti_Double& o_height);

		// 转换为字符串
		/**
		* @brief convert position to string
		* @details convert position to string
		* @param[in] pos, the position
		* @return the string
		*/
		static std::string ToPrositionString(const NctiPosition &pos);
		/**
		* @brief convert vector to string
		* @details convert vector to string
		* @param[in] vector, the vector
		* @return the string
		*/
		static std::string ToVectorString(const NctiVector &vector);
		/**
		* @brief convert name list to string
		* @details convert name list to string
		* @param[in] names, the name list
		* @return the string
		*/
		static std::string ToNameListString(const std::vector<std::string>& names);
		/**
		* @brief convert name to string
		* @details convert name to string
		* @param[in] name, the name
		* @return the string
		*/
		static std::string ToNameString(const std::string& name);
		template <typename T>
		/**
		* @brief convert number list to string
		* @details convert number list to string
		* @param[in] vals, the number list
		* @return the string
		*/
		static std::string ToNumberListString(const std::vector<T>& vals)
		{
			std::ostringstream oss;
			oss << "[";
			Ncti_Boolean first = true;
			for (auto&& val : vals) {
				if (first) {
					first = false;
				}
				else {
					oss << ", ";
				}
				oss << val;
			}
			oss << "]";
			return oss.str();
		}

		static std::vector<std::string> GetAssemblyScripts(NctiDisplayDocCustomContainer* i_pDocContainer, NctiBaseModel* i_pBaseModel);
	};
}
#endif // !NctiCreateConstraintScriptPub_H
