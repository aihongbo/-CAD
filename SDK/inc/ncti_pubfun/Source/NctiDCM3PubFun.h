#ifndef NctiDCM3PubFun_H
#define NctiDCM3PubFun_H
#include "ncti_base.h"
#include "dcl_ncti_pubfun.h"
#include "NctiDCM3Def.h"
#include <string>
namespace NCTI
{
	class NctiBaseModel;
	class NctiDocument;
	class NctiDisplayDCM3DimSys;
	class NctiDisplayDCM3Dimension;
	class NctiDisplayDCM3Geometry;
	class NctiDisplayDCM3Point;
	class NctiDisplayDCM3Line;
	class NctiDisplayDCM3Plane;
	class NctiDisplayDCM3Circle;
	class NctiDisplayDCM3Cylinder;
	class NctiDCM3Set;
	class NctiDisplayModelBody;
	class NctiPosition;
	class NctiVector;
	/**
	* @brief dcm3 public functions
	* @details dcm3 public functions
	* @see NctiDCM3Def
	*/
	class DECL_NCTI_PUBFUN NctiDCM3PubFun
	{
	public:
		NctiDCM3PubFun();
		~NctiDCM3PubFun();

		static Ncti_Boolean Check(NctiBaseModel* i_pBaseModel, NctiDisplayDCM3DimSys* i_pDimSys, NctiDisplayDCM3Dimension* i_pDim, NctiDisplayDCM3Geometry* i_pGeom1, NctiDisplayDCM3Geometry* i_pGeom2, ncti_DCM3_check_result& o_res);
		/*​
		* @brief DCM3 Check
		* @param i_pDocment Document Pointer
		* @param i_dimSysName Dimension System Name
		* @param i_dnodeName D Node Name
		* @param i_gnodeName1 Geometry Node Name 1
		* @param i_gnodeName2 Geometry Node Name 2
		* @param o_checkResult Output Check Result
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean Check(NctiDocument* i_pDocment, const char* i_dimSysName, const char* i_dnodeName, const char* i_gnodeName1, const char* i_gnodeName2, ncti_DCM3_check_result& o_checkResult);
		static Ncti_Boolean StatusD(NctiBaseModel* i_pBaseModel, NctiDisplayDCM3DimSys* i_pDimSys, NCTI_D_NODE i_dn, ncti_DCM3_d_node_status& o_status);
		static Ncti_Boolean StatusR(NctiBaseModel* i_pBaseModel, NctiDisplayDCM3DimSys* i_pDimSys, NCTI_R_NODE i_rn, ncti_DCM3_d_node_status& o_status);
		static Ncti_Boolean GetOverdefinedConstraints(NctiBaseModel* i_pBaseModel, NctiDisplayDCM3DimSys* i_pDimSys, std::vector< ncti_DCM3_constraint_data>& o_OverConsVec);
		static ncti_DCM3_alignment_type GetAlignmentType(NctiDisplayDCM3Geometry* i_pGeom1, NctiDisplayDCM3Geometry* i_pGeom2, ncti_DCM3_d_type i_dt);

		/**
		* @brief Get DCM3 Resolution
		* @param i_pDocment Document Pointer
		* @param i_DimSysName Dimension System Name
		* @param o_res Output Resolution
		* @param o_size Output Size
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetResolution(NctiDocument* i_pDocment, const char* i_DimSysName, Ncti_Double& o_res, Ncti_Double& o_size);

		/**
		* @brief Get DCM3 Help Point
		* @param i_pDocment Document Pointer
		* @param i_DimSysName Dimension System Name
		* @param i_dn D Node
		* @param i_GeomName Geometry Name
		* @param o_hp Output Help Point
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetHelpPoint(NctiDocument* i_pDocment, const char* i_DimSysName, NCTI_D_NODE i_dn, const char* i_GeomName, NctiPosition& o_hp);

		/**
		* @brief Get DCM3 Help Parameter
		* @param i_pDocment Document Pointer
		* @param i_DimSysName Dimension System Name
		* @param i_dn D Node
		* @param i_GeomName Geometry Name
		* @param o_hp Output Help Parameter
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetHelpParameter(NctiDocument* i_pDocment, const char* i_DimSysName, NCTI_D_NODE i_dn, const char* i_GeomName, Ncti_Double& o_hp);

		/**
		* @brief Get DCM3 Spline Evaluator
		* @param i_pDocment Document Pointer
		* @param i_DimSysName Dimension System Name
		* @param i_SplineName Spline Name
		* @param i_n_der Derivative Order
		* @param i_hp Help Parameter
		* @param i_side Discontinuity Side
		* @param o_arr Output Array
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetSplineEvaluator(NctiDocument* i_pDocment, const char* i_DimSysName, const char* i_SplineName, Ncti_Integer i_n_der, Ncti_Double i_hp, ncti_DCM3_discontinuity_side i_side, Ncti_Double* o_arr);

		/**
		* @brief Verify DCM3 Transform
		* @param i_pGeom Geometry Pointer
		* @param i_mat Transformation Matrix
		* @param i_offset1 First Offset
		* @param i_offset2 Second Offset
		* @param i_status Status
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean VerifyTransform(NctiDisplayDCM3Geometry* i_pGeom, const Ncti_Double i_mat[4][4], Ncti_Double i_offset1, Ncti_Double i_offset2, Ncti_Integer i_status);

		/**
		* @brief Get DCM3 geometry pointer by g_node pointer
		* @param[in] i_pBaseModel, Base model pointer
		* @param[in] i_pDimSys, DCM3 dimension system object pointer
		* @param[in] i_gn, DCM3 geometry node pointer
		* @param[out] o_pGeom, DCM3 geometry object pointer
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetGeometryByNode(NctiBaseModel* i_pBaseModel, NctiDisplayDCM3DimSys* i_pDimSys, NCTI_G_NODE i_gn, NctiDisplayDCM3Geometry*& o_pGeom);

		/*​
		* @brief Get DCM3 Constraints Of Geometry
		* @param i_pDocment Document Pointer
		* @param pDimSys 3D Dimension System Pointer
		* @param pDCMGeom 3D DCM Geometry Pointer
		* @param o_ConsGeomVec Output Constraint Geometry Vector
		* @return std::vector<std::string>
		*/
		static std::vector<std::string> GetConsOfGeometry(NctiDocument* i_pDocment, NctiDisplayDCM3DimSys* pDimSys, NctiDisplayDCM3Geometry* pDCMGeom, std::vector< NctiDisplayDCM3Geometry*>& o_ConsGeomVec);

		/*​
		* @brief Get DCM3 D Node Constraints
		* @param i_pDocment Document Pointer
		* @param pDimSys 3D Dimension System Pointer
		* @param dn D Node
		* @return std::string
		*/
		static std::string GetDNConstraints(NctiDocument* i_pDocment, NctiDisplayDCM3DimSys* pDimSys, NCTI_D_NODE dn);

		/*​
		* @brief Get DCM3 R Node Constraints
		* @param i_pDocment Document Pointer
		* @param pDimSys 3D Dimension System Pointer
		* @param rn R Node
		* @return std::string
		*/
		static std::string GetRNConstraints(NctiDocument* i_pDocment, NctiDisplayDCM3DimSys* pDimSys, NCTI_R_NODE rn);

		static std::string GetConsChName(ncti_DCM3_d_type i_dt);
	};
}
#endif // !NctiDCM3PubFun_H
