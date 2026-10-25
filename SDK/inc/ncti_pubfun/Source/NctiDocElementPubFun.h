#ifndef NctiDocElementPubFun_H
#define NctiDocElementPubFun_H
#include "dcl_ncti_pubfun.h"
#include "ncti.h"
#include "ncti_base.h"
#include "NctiGPropDef.h"
#include "NctiGBoundsDef.h"
#include "NctiGeoDataDef.h"
#include <unordered_map>
#include <NctiDCMDef.h>
#include <NctiDCM3Def.h>
#include <vector>
#include <map>
#include <stdint.h>
#include "ncti_event.h"
#include "NctiGridPickSet.h"
#include "ncti_include.h"
namespace NCTI
{
	class NctiDisplayDocElement;
	class NctiDocument;
	class NctiBaseModel;
	class NctiTestSystemObject;
	class NctiDisplayObjectList;
	class NctiDisplayDocCustomContainer;
	class NctiDisplayObject;
	class NctiRenderSceneItem;
	class NctiDisplayModelBody;
	class NctiTopoCell;
	class NctiBaseView;
	class NctiAiModelSystemObject;
	class NctiDisplayDCMGeometry;
	class NctiDisplayDCMDimension;
	class NctiDisplayDCM3Geometry;
	class NctiTopoFace;
	class NctiAxis;
	class NctiRenderSegmentItem;
	class NctiRenderGeometryItem;
	class NctiTestCaseToModelManage;
	class NctiDisplayDCMDimSys;
	class NctiDisplayDCM3DimSys;
	class NctiDisplayGridMesh;
	class NctiDisplaySet;
	class NctiDisplaySection;
	class NctiDisplayMaterialAttribute;
	class NctiDisplayCoupling;
	class NctiDisplayTie;
	class NctiGeometryResult;
	class NctiPosition;
	class NctiRenderTriangleItem;
	class NctiTopoFace;
	class NctiTopoEdge;
	struct ConstraintCompare;

	/**
	* @brief The Doc Element Public Function Class 
	* @details provide some public function for document element about geometry and topology operation
	*/
	class DECL_NCTI_PUBFUN NctiDocElementPubFun
	{
	public:
		NctiDocElementPubFun();
		~NctiDocElementPubFun();
	public:
		/**
		* @brief Create New Part Document
		* @param i_ModelDoc Model Document Type
		* @param i_DCMDoc Constraint Document Type
		* @param i_mesh Mesh Document Type
		* @return New Part Document ID
		*/
		static Ncti_UInteger NewPart(EnumModelDoc i_ModelDoc, EnumGCSDoc i_DCMDoc = NCTI_GCS_DCM, EnumMeshDoc i_mesh = NCTI_MESH_GMSH);
		/**
		* @brief Create New Assemble Document
		* @param i_ModelDoc Model Document Type
		* @param i_DCMDoc Constraint Document Type
		* @param i_mesh Mesh Document Type
		* @return New Assemble Document ID
		*/
		static Ncti_UInteger NewAssemble(EnumModelDoc i_ModelDoc, EnumGCSDoc i_DCMDoc = NCTI_GCS_DCM, EnumMeshDoc i_mesh = NCTI_MESH_GMSH);
		/**
		* @brief Create Part Document
		* @param i_pOwner Owner Document Element
		* @param i_ModelDoc Model Document Type
		* @return void
		*/
		static void CreatePart(NctiDisplayDocElement * i_pOwner, EnumModelDoc i_ModelDoc);


		/**
		* @brief Export File
		* @param i_pContainer Document Custom Container Pointer
		* @param i_filename Export File Name
		* @param i_pListObj Display Object List Pointer
		* @param i_opt Export Option
		* @return void
		*/
		static void ExportFile(NctiDisplayDocCustomContainer * i_pContainer, const char* i_filename, NctiDisplayObjectList * i_pListObj, int i_opt = -1);

		/**
		* @brief Create Test System Object
		* @param i_pBaseModel Base Model Pointer
		* @return void
		*/
		static void CreateTestSystemObject(NctiBaseModel * i_pBaseModel);

		/**
		* @brief Get Test System Object
		* @param i_pBaseModel Base Model Pointer
		* @return NctiTestSystemObject Pointer
		*/
		static NctiTestSystemObject * GetTestSystemObject(NctiBaseModel * i_pBaseModel);

		/**
		* @brief Get Current Document Custom Container
		* @param i_pBaseModel Base Model Pointer
		* @return NctiDisplayDocCustomContainer Pointer
		*/
		static NctiDisplayDocCustomContainer * GetCurrenDocCustom(NctiBaseModel * i_pBaseModel);

		/**
		* @brief Get Object List By Name
		* @param i_pDocCustomContainer Document Custom Container Pointer
		* @param i_ClassID Class ID
		* @param i_ObjectNameVec Object Name Vector
		* @param o_pObjList Output Object List Pointer
		* @return void
		*/
		static void GetObjectListByName(NctiDisplayDocCustomContainer * i_pDocCustomContainer, const Ncti_Char * i_ClassID, const std::vector<const Ncti_Char*>&i_ObjectNameVec, NctiDisplayObjectList * o_pObjList);

		/**
		* @brief Get Object By Name
		* @param i_pDocCustomContainer Document Custom Container Pointer
		* @param i_ClassID Class ID
		* @param i_ObjectName Object Name
		* @param o_pObj Output Object Pointer
		* @return void
		*/
		static void GetObjectListByName(NctiDisplayDocCustomContainer * i_pDocCustomContainer, const Ncti_Char * i_ClassID, const Ncti_Char * i_ObjectName, NctiDisplayObject * &o_pObj);

		/**
		* @brief Get Object List By Name
		* @param i_pDocment Document Pointer
		* @param i_ClassID Class ID
		* @param i_ObjectNameVec Object Name Vector
		* @param o_ObjVec Output Object Vector
		* @param isAllPart Search All Parts
		* @return void
		*/
		static void GetObjectListByName(NctiDocument * i_pDocment, const Ncti_Char * i_ClassID, const std::vector<std::string>&i_ObjectNameVec, std::vector<NctiDisplayObject*>&o_ObjVec, bool isAllPart = false);

		/**
		* @brief Get Object By Name
		* @param i_pDocment Document Pointer
		* @param i_ClassID Class ID
		* @param i_ObjectName Object Name
		* @param o_pObj Output Object Pointer
		* @return void
		*/
		static void GetObjectListByName(NctiDocument * i_pDocment, const Ncti_Char * i_ClassID, const Ncti_Char * i_ObjectName, NctiDisplayObject * &o_pObj);

		/**
		* @brief Get Object By Name
		* @param i_pBaseModel Base Model Pointer
		* @param i_ClassID Class ID
		* @param i_ObjectName Object Name
		* @param o_pObj Output Object Pointer
		* @return void
		*/
		static void GetObjectListByName(NctiBaseModel * i_pBaseModel, const Ncti_Char * i_ClassID, const Ncti_Char * i_ObjectName, NctiDisplayObject * &o_pObj);

		/**
		* @brief Get Object By Name
		* @param i_pBaseModel Base Model Pointer
		* @param i_ObjectName Object Name
		* @param o_pObj Output Object Pointer
		* @return void
		*/
		static void GetObjectListByName(NctiBaseModel * i_pBaseModel, const Ncti_Char * i_ObjectName, NctiDisplayObject * &o_pObj);

		/**
		* @brief Get Object Name List
		* @param i_pBaseModel Base Model Pointer
		* @param o_objNameList Output Object Name List
		* @param i_ClassID Class ID
		* @return void
		*/
		static void GetObjectNameList(NctiBaseModel * i_pBaseModel, std::vector<std::string>&o_objNameList, const Ncti_Char * i_ClassID = nullptr);

		/**
		* @brief Get Object By Class ID
		* @param i_pDocment Document Pointer
		* @param i_ClassID Class ID
		* @param o_ObjVec Output Object Vector
		* @return void
		*/
		static void GetObjectByClassID(NctiDocument * i_pDocment, const Ncti_Char * i_ClassID, std::vector<NctiDisplayObject*>&o_ObjVec);
		/**
		* @brief Set Selection By Name And CellID
		* @param i_pDocment Document Pointer
		* @param i_ObjNameCellIDVec Object Name And CellID Map
		* @param isClear Clear Previous Selection
		* @param isAllPart Search All Parts
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SetSelectionByNameAndCellID(
			NctiDocument * i_pDocment,
			const std::unordered_map<std::string, std::vector<Ncti_Long>>&i_ObjNameCellIDVec,
			bool isClear = true, bool isAllPart = false);

		/**
		* @brief Set Selection By Name And CellID
		* @param i_pDocment Document Pointer
		* @param i_ObjectNameVec Object Name Vector
		* @param i_CellIDVec CellID Vector
		* @param isClear Clear Previous Selection
		* @param isAllPart Search All Parts
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SetSelectionByNameAndCellID(
			NctiDocument * i_pDocment,
			const std::vector<std::string>&i_ObjectNameVec,
			const std::vector<Ncti_Long>&i_CellIDVec,
			bool isClear = true, bool isAllPart = false);

		/**
		* @brief Set Selection By Name And CellID
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param isClear Clear Previous Selection
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SetSelectionByNameAndCellID(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID, bool isClear = true);

		/**
		* @brief Set Grid Selection By Name
		* @param i_pDocment Document Pointer
		* @param i_ObjectNameVec Object Name Vector
		* @param gridselect Grid Selection Set
		* @param status Selection Status
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SetGridSelectionByName(
			NctiDocument * i_pDocment,
			const std::vector<std::string>&i_ObjectNameVec,
			const std::set<NctiGridPickSet>&gridselect={},
            const ModifierKeys &status = ModifierKeys());

		/**
		* @brief Get Edge Mid Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_pt Output Position
		* @return bool
		*/
		static bool GetEdgeMidPoint(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			NctiPosition & o_pt);

		/**
		* @brief Get Edge Point From Parameter U
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param i_U Parameter U Value
		* @param o_pt Output Position
		* @return bool
		*/
		static bool GetEdgePointFromU(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			Ncti_Double i_U,
			NctiPosition & o_pt);

		/**
		* @brief Find Edge By Nearest Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_PointVec Point Vector
		* @param o_CellIDVec Output Cell ID Vector
		* @return bool
		*/
		static bool FindEdgeByNearestPoint(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			const std::vector<NctiPosition>&i_PointVec,
			std::vector<Ncti_Long>&o_CellIDVec);

		/**
		* @brief Find All Edges
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_CellVec Output Cell Vector
		* @return bool
		*/
		static bool FindAllEdges(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			std::vector<Ncti_Long>&o_CellVec);

		/**
		* @brief Find All Faces
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_CellVec Output Cell Vector
		* @return bool
		*/
		static bool FindAllFaces(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			std::vector<Ncti_Long>&o_CellVec);

		/**
		* @brief Find All Vertexs
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_CellVec Output Cell Vector
		* @return bool
		*/
		static bool FindAllVertexs(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			std::vector<Ncti_Long>&o_CellVec);

		/**
		* @brief Extract Geometry Properties
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_geomProp Output Geometry Properties
		* @return void
		*/
		static void ExtractProp(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			NctiGeomProp & o_geomProp);

		/**
		* @brief Extract Bounds
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_geomBounds Output Geometry Bounds
		* @return void
		*/
		static void ExtractBounds(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			NctiGeomBounds & o_geomBounds);

		/**
		* @brief Extract Cell Bounds
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_geomBounds Output Geometry Bounds
		* @return void
		*/
		static void ExtractCellBounds(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			NctiGeomBounds & o_geomBounds);

		/**
		* @brief Set Object Visibility
		* @param i_pDocment Document Pointer
		* @param i_name Object Name
		* @param i_boo Visibility Flag
		* @return void
		*/
		static void SetVisibility(NctiDocument * i_pDocment, const Ncti_Char * i_name, Ncti_Boolean i_boo);

		/**
		* @brief Data Exchange
		* @param i_pDocment Document Pointer
		* @param i_Input Input File
		* @param i_Output Output File
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean DataExchange(NctiDocument * i_pDocment, const Ncti_Char * i_Input, const Ncti_Char * i_Output);

		/**
		* @brief Set Object Alpha By Selection
		* @param i_pDocment Document Pointer
		* @param alpha Alpha Value
		* @return void
		*/
		static void SetAlhpaBySel(NctiDocument * i_pDocment, float alpha);

		/**
		* @brief Set Object Petra By Selection
		* @param i_pDocment Document Pointer
		* @param petra Petra Value
		* @return void
		*/
		static void SetPetraBySel(NctiDocument * i_pDocment, float petra);

		/**
		* @brief Set All Objects Visible
		* @param i_pDocment Document Pointer
		* @return void
		*/
		static void SetVisibilityAllShow(NctiDocument * i_pDocment);

		/**
		* @brief Set Objects Visibility
		* @param i_pDocment Document Pointer
		* @param visibilityMap Visibility Map
		* @param vis Visibility Flag
		* @return void
		*/
		static void SetVisibilityObjs(NctiDocument * i_pDocment, const std::map<std::string, std::vector<Ncti_UInteger>>&visibilityMap, bool vis);

		/**
		* @brief Set Objects Only Show
		* @param i_pDocment Document Pointer
		* @param visibilityMap Visibility Map
		* @return void
		*/
		static void SetVisibilityOnlyShow(NctiDocument * i_pDocment, const std::map<std::string, std::vector<Ncti_UInteger>>&visibilityMap);

		/**
		* @brief Pick Ray Get Point By Face
		* @param i_face Triangle Face Item
		* @param posRay Ray Position
		* @param uvecRay Ray Direction Vector
		* @param out Output Position
		* @return bool
		*/
		static bool PickRayGetPointByFace(NctiRenderTriangleItem * i_face, NctiPosition posRay, NctiUnitVector uvecRay, NctiPosition & out);

		/**
		* @brief Set Focus By Selection
		* @param i_pDocment Document Pointer
		* @return void
		*/
		static void SetFocusBySel(NctiDocument * i_pDocment);

		/**
		* @brief Set Visibility By Selection
		* @param i_pDocment Document Pointer
		* @param vis Visibility Flag
		* @return void
		*/
		static void SetVisibilityBySel(NctiDocument * i_pDocment, bool vis);

		/**
		* @brief merge grid node
		* @param i_pGridMeshs
		* @return void
		*/
		static void MergeGridNode(std::vector<NctiDisplayGridMesh*> i_pGridMeshs);

		/**
		* @brief Set Visibility Only Show By Selection
		* @param i_pDocment Document Pointer
		* @return void
		*/
		static void SetVisibilityOnlyShowBySel(NctiDocument * i_pDocment);

		/**
		* @brief Get Selection Mode
		* @param i_pDocment Document Pointer
		* @param selBody Body Selection Flag
		* @param selFace Face Selection Flag
		* @param selLine Line Selection Flag
		* @param selMarker Marker Selection Flag
		* @return void
		*/
		static void GetSelectMode(NctiDocument * i_pDocment, bool& selBody, bool& selFace, bool& selLine, bool& selMarker);

		/**
		* @brief Cancel Selection
		* @param i_pDocment Document Pointer
		* @return void
		*/
		static void CancelSelection(NctiDocument * i_pDocment);

		/**
		* @brief Set Body Selection Mode
		* @param i_pDocment Document Pointer
		* @param boo Selection Flag
		* @return void
		*/
		static void SetSelectBody(NctiDocument * i_pDocment, Ncti_Boolean boo);

		/**
		* @brief Set Face Selection Mode
		* @param i_pDocment Document Pointer
		* @param boo Selection Flag
		* @return void
		*/
		static void SetSelectFace(NctiDocument * i_pDocment, Ncti_Boolean boo);

		/**
		* @brief Set Line Selection Mode
		* @param i_pDocment Document Pointer
		* @param boo Selection Flag
		* @return void
		*/
		static void SetSelectLine(NctiDocument * i_pDocment, Ncti_Boolean boo);

		/**
		* @brief Set Marker Selection Mode
		* @param i_pDocment Document Pointer
		* @param boo Selection Flag
		* @return void
		*/
		static void SetSelectMarker(NctiDocument * i_pDocment, Ncti_Boolean boo);

		/**
		* @brief Set Selection Tool
		* @param i_pDocment Document Pointer
		* @param tt Selection Type
		* @return void
		*/
		static void SetSelectTool(NctiDocument * i_pDocment, NctiSelectType tt);

		/**
		* @brief Find Face By Nearest Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_PointVec Point Vector
		* @param o_CellIDVec Output Cell ID Vector
		* @return bool
		*/
		static bool FindFaceByNearestPoint(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			const std::vector<NctiPosition>&i_PointVec,
			std::vector<Ncti_Long>&o_CellIDVec);

		/**
		* @brief Get Face Mid Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_pt Output Position
		* @return bool
		*/
		static bool GetFaceMidPoint(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			NctiPosition & o_pt);

		/**
		* @brief Get Face Point From UV Parameters
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param i_U Parameter U Value
		* @param i_V Parameter V Value
		* @param o_pt Output Position
		* @return bool
		*/
		static bool GetFacePointFromUV(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			Ncti_Double i_U,
			Ncti_Double i_V,
			NctiPosition & o_pt);

		/**
		* @brief Get Face Attribute Points
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_pts Output Position Vector
		* @return bool
		*/
		static bool GetFaceAttribPoints(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			std::vector<NctiPosition>&o_pts);

		/**
		* @brief Get All Cell Vector
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_CellVec Output Cell Vector
		* @return bool
		*/
		static bool GetAllCellVec(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			std::vector<NCTI_MODEL_TAG>&o_CellVec);

		/**
		* @brief Delete All Objects
		* @param i_pDocment Document Pointer
		* @return void
		*/
		static void DeleteAllObject(NctiDocument * i_pDocment);

		/**
		* @brief Get Display Object From Selection Manager(Those objects are not repeated)
		* @param i_pDocment Document Pointer
		* @param o_ObjVec Output Object Vector
		* @return void
		*/
		static void GetDisplayObjectFromSelManager(
			NctiDocument * i_pDocment,
			std::vector<NctiDisplayObject*>&o_ObjVec);

		/**
		* @brief Get Display Object From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_ObjVec Output Object Vector
		* @param o_CellVec Output Cell Vector(If the length of o_CellVec is greater than 0, it must be equal to the length of o_ObjVec)
		* @return void
		*/
		static void GetDisplayObjectFromSelManager(
			NctiDocument* i_pDocment,
			std::vector<NctiDisplayObject*>& o_ObjVec,
			std::vector<NCTI_MODEL_TAG>& o_CellVec);

		/**
		* @brief Get Display Object From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_ObjVec Output Object Vector
		* @param o_CellVecVec Output Cell Vector Vector
		* @return void
		*/
		static void GetDisplayObjectFromSelManager(
			NctiDocument * i_pDocment,
			std::vector<NctiDisplayObject*>&o_ObjVec,
			std::vector< std::vector<NCTI_MODEL_TAG>>&o_CellVecVec);

		/**
		* @brief Get Name From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_ObjNameVec Output Object Name Vector
		* @param o_CellIDVec Output Cell ID Vector
		* @param o_GECellVec Output GE Cell Vector
		* @return void
		*/
		static void GetNameFromSelManager(
			NctiDocument * i_pDocment,
			std::vector<std::string>&o_ObjNameVec,
			std::vector<Ncti_Long>&o_CellIDVec,
			std::vector<NctiTopoCell*>&o_GECellVec);

		/**
		* @brief Get Name From Selection Manager(These names may be duplicated)
		* @param i_pDocment Document Pointer
		* @param o_ObjNameVec Output Object Name Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetNameFromSelManager(
			NctiDocument * i_pDocment,
			std::vector<std::string>&o_ObjNameVec);

		/**
		* @brief Get Visual Mode
		* @param bFace Face Display Flag
		* @param bLines Lines Display Flag
		* @param bMarkers Markers Display Flag
		* @return void
		*/
		static void GetVisualMode(bool& bFace, bool& bLines, bool& bMarkers);

		/**
		* @brief Set Visual Mode
		* @param i_pDocment Document Pointer
		* @param bFace Face Display Flag
		* @param bLines Lines Display Flag
		* @param bVertex Vertex Display Flag
		* @return void
		*/
		static void SetVisualMode(NctiDocument * i_pDocment, Ncti_Boolean bFace, Ncti_Boolean bLines, Ncti_Boolean bVertex);

		/**
		* @brief Get XYZ From Point
		* @param i_pModelBody model body
		* @param i_CellID Cell ID
		* @param o_pt Output Position
		* @return bool
		*/
		static bool GetXYZFromPoint(
			NctiDisplayModelBody* i_pModelBody,
			Ncti_Long i_CellID,
			NctiPosition & o_pt);

		/**
		* @brief Get XYZ From Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_pt Output Position
		* @return bool
		*/
		static bool GetXYZFromPoint(
			NctiDocument* i_pDocment,
			const Ncti_Char* i_ObjName,
			Ncti_Long i_CellID,
			NctiPosition& o_pt);

		/**
		* @brief Get End Points From Edge
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_ptS Output Start Position
		* @param o_ptE Output End Position
		* @param o_vecS Output Start Vector
		* @param o_vecE Output End Vector
		* @return bool
		*/
		static bool GetEndPointsFromEdge(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			NctiPosition & o_ptS,
			NctiPosition & o_ptE,
			NctiVector & o_vecS,
			NctiVector & o_vecE
		);

		/**
		* @brief Get Value From Edge By Parameter
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param i_Param Parameter Value
		* @param o_Point Output Position
		* @param o_Tangent Output Tangent Vector
		* @param o_SecDer Output Second Derivative
		* @param i_isTangentNormalize Normalize Tangent Flag
		* @return bool
		*/
		static bool GetValueFromEdgeByParam(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			Ncti_Double i_Param,
			NctiPosition & o_Point,
			NctiVector & o_Tangent,
			NctiVector & o_SecDer,
			Ncti_Boolean i_isTangentNormalize = true
		);

		/**
		* @brief Get Value From Edge By Parameter
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param i_Param Parameter Value
		* @param o_Point Output Position
		* @param o_Tangent Output Tangent Vector
		* @param i_isTangentNormalize Normalize Tangent Flag
		* @return bool
		*/
		static bool GetValueFromEdgeByParam(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID,
			Ncti_Double i_Param,
			NctiPosition & o_Point,
			NctiVector & o_Tangent,
			Ncti_Boolean i_isTangentNormalize = true
		);

		/**
		* @brief Get Topology Number
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_LocDif Local Difference Flag
		* @param o_topNb Output Topology Number Map
		* @return bool
		*/
		static bool GetTopolNb(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Boolean i_LocDif,
			std::map<int, int>&o_topNb
		);

		/**
		* @brief Save Image To Test Object
		* @param i_pBaseModel Base Model Pointer
		* @param i_Buffer Image Buffer
		* @param i_w Image Width
		* @param i_h Image Height
		* @param i_rowPitch Row Pitch
		* @return void
		*/
		static void SaveImageToTestObj(
			NctiBaseModel * i_pBaseModel,
			const std::vector<unsigned char>&i_Buffer,
			Ncti_Integer i_w,
			Ncti_Integer i_h,
			Ncti_Integer i_rowPitch);

		/**
		* @brief Set Camera
		* @param i_pBaseModel Base Model Pointer
		* @param i_pos Camera Position
		* @param i_tar Camera Target
		* @param i_up Camera Up Vector
		* @return void
		*/
		static void SetCamera(NctiBaseModel * i_pBaseModel, const NctiPosition & i_pos, const NctiPosition & i_tar, const NctiVector & i_up);

		/**
		* @brief Open File
		* @param i_filename File Name
		* @return Ncti_UInteger
		*/
		static Ncti_UInteger OpenFile(const Ncti_Char * i_filename);

		/**
		* @brief Write Python Script
		* @param i_pBaseModel Base Model Pointer
		* @param i_PythonVec Python Script Vector
		* @return void
		*/
		static void WritePython(NctiBaseModel* i_pBaseModel, const std::vector<std::string>& i_PythonVec);
		/*​
		* @brief Select Same Radius Face
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SelectSameRadiusFace(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID);

		/*​
		* @brief Check If Run Success
		* @param i_pBaseModel Base Model Pointer
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean IsRunSuccesse(NctiBaseModel * i_pBaseModel);

		/*​
		* @brief Create Geometry Object
		* @param i_pBaseModel Base Model Pointer
		* @param i_ObjName Object Name
		* @return void
		*/
		static void CreateGeObject(NctiBaseModel * i_pBaseModel, const Ncti_Char * i_ObjName);

		/*​
		* @brief Get Bounding Box
		* @param i_pDocment Document Pointer
		* @param i_ObjNames Object Names Vector
		* @param o_ptMin Output Minimum Point
		* @param o_ptMax Output Maximum Point
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetBoundingBox(
			NctiDocument * i_pDocment,
			std::vector<const Ncti_Char*> i_ObjNames,
			NctiPosition & o_ptMin,
			NctiPosition & o_ptMax);

		/*​
		* @brief Get Oriented Bounding Box
		* @param i_pDocment Document Pointer
		* @param i_ObjNames Object Names Vector
		* @param o_Axis Output Axis
		* @param o_XSize Output X Size
		* @param o_YSize Output Y Size
		* @param o_ZSize Output Z Size
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetOrientedBoundingBox(
			NctiDocument * i_pDocment,
			std::vector<std::string> i_ObjNames,
			NctiAxis & o_Axis,
			Ncti_Double & o_XSize,
			Ncti_Double & o_YSize,
			Ncti_Double & o_ZSize);

		/*​
		* @brief Get Cell Oriented Bounding Box
		* @param i_pContainer Document Custom Container Pointer
		* @param i_pModelBody Model Body Pointer
		* @param i_CellVec Cell Vector
		* @param o_Axis Output Axis
		* @param o_XSize Output X Size
		* @param o_YSize Output Y Size
		* @param o_ZSize Output Z Size
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetCellOrientedBoundingBox(
			NctiDisplayDocCustomContainer * i_pContainer,
			NctiDisplayModelBody * i_pModelBody,
			std::vector<Ncti_Long> i_CellVec,
			NctiAxis & o_Axis,
			Ncti_Double & o_XSize,
			Ncti_Double & o_YSize,
			Ncti_Double & o_ZSize);

		/*​
		* @brief Get Geometry Shape
		* @param i_pBaseModel Base Model Pointer
		* @param i_pModelObj Model Object Pointer
		* @param i_CellVec Cell Vector
		* @param o_GECellVec Output Geometry Cell Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetGEShape(
			NctiBaseModel * i_pBaseModel,
			NctiDisplayModelBody * i_pModelObj,
			const std::vector<NCTI_MODEL_TAG>&i_CellVec,
			std::vector<NctiTopoCell*>&o_GECellVec);

		/*​
		* @brief Set Selection Manager
		* @param i_DisplayObjectVec Display Object Vector
		* @param i_pBaseView Base View Pointer
		* @param i_bNotifySelectionDataChanged Notify Selection Data Changed Flag
		* @param i_IsNeedToClear Need To Clear Flag
		* @return void
		*/
		static void SetSelectionManager(
			const std::vector<NctiDisplayObject*>&i_DisplayObjectVec,
			NctiBaseView * i_pBaseView,
			bool i_bNotifySelectionDataChanged = true,
			bool i_IsNeedToClear = true);

		/*​
		* @brief Set Selection Manager
		* @param i_DisObjMap Display Object And Cell ID Map
		* @param i_pBaseView Base View Pointer
		* @param i_bNotifySelectionDataChanged Notify Selection Data Changed Flag
		* @param i_IsNeedToClear Need To Clear Flag
		* @return void
		*/
		static void SetSelectionManager(
			const std::unordered_map<NctiDisplayObject*, std::vector<Ncti_Long>>& i_DisObjMap,
			NctiBaseView* i_pBaseView,
			bool i_bNotifySelectionDataChanged = true,
			bool i_IsNeedToClear = true);

		/*​
		* @brief Set Select All Objects
		* @param i_pBaseView Base View Pointer
		* @return void
		*/
		static void SetSelectAllObjects(NctiBaseView * i_pBaseView);

		/*​
		* @brief Get Constraint Json From Object
		* @param pDimSys Dimension System Pointer
		* @return std::string
		*/
		static std::string GetConstraintJsonFromObject(NctiDisplayDCMDimSys * pDimSys);

		/*​
		* @brief Update Constraint Compare
		* @param i_pDocment Document Pointer
		* @param pDCMGeom DCM Geometry Pointer
		* @param consGeomVec Constraint Geometry Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConsCompare(NctiDocument * i_pDocment, NctiDisplayDCMGeometry * pDCMGeom, const std::vector< NctiDisplayDCMGeometry*>&consGeomVec);

		/*​
		* @brief Update Constraint Compare
		* @param i_pDocment Document Pointer
		* @param pDimSys 2D Dimension System Pointer
		* @param pDim 2D Dimension Pointer
		* @param status Dimension Status
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConsCompare(NctiDocument* i_pDocment, NctiDisplayDCMDimension* pDim, ncti_d_node_status status);

		/*​
		* @brief Get 3D Constraint Json From Object
		* @param pDimSys 3D Dimension System Pointer
		* @return std::string
		*/
		static std::string Get3DConstraintJsonFromObject(NctiDisplayDCM3DimSys * pDimSys);

		/*​
		* @brief Update Constraint Compare With Json
		* @param i_pDocment Document Pointer
		* @param strJson Json String
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConsCompare(NctiDocument * i_pDocment, const char* strJson);

		/*​
		* @brief Update Constraint Compare With Json Vector
		* @param i_pDocment Document Pointer
		* @param strJsonVec Json String Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConsCompare(NctiDocument * i_pDocment, const std::vector<const char*>&strJsonVec);

		/*​
		* @brief Update Constraint Compare For DCM3 Geometry
		* @param i_pDocment Document Pointer
		* @param pDCMGeom 3D DCM Geometry Pointer
		* @param consGeomVec Constraint Geometry Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConsCompare(NctiDocument * i_pDocment, NctiDisplayDCM3Geometry * pDCMGeom, const std::vector< NctiDisplayDCM3Geometry*>&consGeomVec);

		/*​
		* @brief Update Constraint Compare With Degree Of Freedom
		* @param i_pDocment Document Pointer
		* @param i_dimSysName 2/3D Dimension System Name
		* @param d_of_f Degree Of Freedom
		* @param d_of_c Degree Of Constraint
		* @param d_of_rigid Degree Of Rigid
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConsCompare(NctiDocument * i_pDocment, const char* i_dimSysName, Ncti_Integer d_of_f, Ncti_Integer d_of_c, Ncti_Integer d_of_rigid);

		/*​
		* @brief Update Constraint Compare With Constraint Data
		* @param i_pDocment Document Pointer
		* @param i_pDimSys 3D Dimension System Pointer
		* @param i_consDataVec Constraint Data Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConsCompare(NctiDocument * i_pDocment, NctiDisplayDCM3DimSys * i_pDimSys, const std::vector< ncti_DCM3_constraint_data>&i_consDataVec);

		/*​
		* @brief Update Constraint Json
		* @param i_pDocment Document Pointer
		* @param pDimSys 3D Dimension System Pointer
		* @param pnodeName Node Name
		* @param status Node Status
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConstraintJson(NctiDocument * i_pDocment, NctiDisplayDCM3DimSys * pDimSys, const char* pnodeName, ncti_DCM3_g_node_status status);

		/*​
		* @brief Update Constraint Json With Geometry Parameters
		* @param i_pDocment Document Pointer
		* @param pDimSys 3D Dimension System Pointer
		* @param geomName Geometry Name
		* @param param Parameter Value
		* @param derPeriod Derivation Period
		* @param side Discontinuity Side
		* @param values Values Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean UpdateConstraintJson(NctiDocument * i_pDocment, NctiDisplayDCM3DimSys * pDimSys, const char* geomName, Ncti_Double param, Ncti_Long derPeriod, ncti_DCM3_discontinuity_side side, const std::vector<Ncti_Double> &values);

		/*​
		* @brief Add Constraint Result
		* @param i_pDocment Document Pointer
		* @param preStr Previous String
		* @param afterStr After String
		* @param evaluate_type Evaluate Type
		* @param isOk Is OK Flag
		* @param errMsg Error Message
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean AddConstraintResult(NctiDocument * i_pDocment, const std::string & preStr, const std::string & afterStr, const std::string & evaluate_type, Ncti_Boolean isOk = false, const char* errMsg = "");

		/*​
		* @brief Get Constraint Result
		* @param i_pDocment Document Pointer
		* @param index Index
		* @param o_consCom Output Constraint Compare
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetConstraintResult(NctiDocument * i_pDocment, Ncti_UInteger index, ConstraintCompare & o_consCom);

		/*​
		* @brief Set Constraint Result
		* @param i_pDocment Document Pointer
		* @param index Index
		* @param i_consCom Input Constraint Compare
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SetConstraintResult(NctiDocument * i_pDocment, Ncti_UInteger index, ConstraintCompare & i_consCom);

		/*​
		* @brief Rename Object
		* @param i_pDocment Document Pointer
		* @param pObj Object Pointer
		* @param newObjName New Object Name
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean Rename(NctiDocument * i_pDocment, NctiDisplayObject * pObj, const Ncti_Char * newObjName);

		/*​
		* @brief Modify Display Name
		* @param i_pDocment Document Pointer
		* @param pObj Object Pointer
		* @param newDisplayName New Display Name
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean ModifyDisplayName(NctiDocument * i_pDocment, NctiDisplayObject * pObj, const Ncti_Char * newDisplayName);

		/*​
		* @brief Nofity Element Tree Changed
		* @param i_pBaseModel Base Model pointer
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean NofityElementTreeChanged(NctiBaseModel* i_pBaseModel);
		/*​
		* @brief Get Normal By UV Parameters
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param i_u Parameter U Value
		* @param i_v Parameter V Value
		* @param o_Normal Output Normal Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetNormalByUV(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName,
			Ncti_Long i_CellID, Ncti_Double i_u, Ncti_Double i_v, NctiVector & o_Normal);

		//通过最近点查找实体的Vertex
		/*​
		* @brief Find Vertex By Nearest Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_PointVec Point Vector
		* @param o_CellIDVec Output Cell ID Vector
		* @return bool
		*/
		static bool FindVertexByNearestPoint(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			const std::vector<NctiPosition>&i_PointVec,
			std::vector<Ncti_Long>&o_CellIDVec);

		/*​
		* @brief Get Closest Point And Tangent
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellId Cell ID
		* @param i_Point Input Point
		* @param o_ClosetPoint Output Closest Point
		* @param o_Tangent Output Tangent Vector
		* @return bool
		*/
		static bool GetClosetPointAndTangent(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			Ncti_Integer i_CellId,
			const NctiPosition & i_Point,
			NctiPosition & o_ClosetPoint,
			NctiVector & o_Tangent);

		/*​
		* @brief Calculate Distance Between Edge And Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_Point Input Point
		* @param o_Dist Output Distance
		* @return bool
		*/
		static bool CalDistanceEdgeAndPoint(
			NctiDocument * i_pDocment,
			const Ncti_Char * i_ObjName,
			const NctiPosition & i_Point,
			Ncti_Double & o_Dist);

		//获取截面不闭合的点数量
		/*​
		* @brief Get Section Alone Vertex Count
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param cellID Cell ID
		* @param o_alone Output Alone Vertex Count
		* @return bool
		*/
		static bool GetSectionAloneVertex(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Long cellID, Ncti_Integer & o_alone);

		//保存当前视图为图像
		/*​
		* @brief Save Current View To Image
		* @param i_pDocment Document Pointer
		* @param filePath File Path
		* @return bool
		*/
		static bool SaveCurViewToImage(NctiDocument * i_pDocment, const std::string & filePath);

		//Clear时清除记录的系统信息
		/*​
		* @brief Clear System Object Info
		* @param i_pDocment Document Pointer
		* @return bool
		*/
		static bool ClearSysObjectInfo(NctiDocument * i_pDocment);

		//获取NctiGeomCylindricalSurface的半径
		/*​
		* @brief Get Cylindrical Surface Radius
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_Radius Output Radius
		* @return bool
		*/
		static bool GetCylindricalSurfaceRadius(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Long i_CellID, Ncti_Double & o_Radius);

		//获取NctiGeomCylindricalSurface半径及坐标系
		/*​
		* @brief Get Cylindrical Surface Radius And Axis
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_Radius Output Radius
		* @param o_axis Output Axis
		* @return bool
		*/
		static bool GetCylindricalSurfaceRadius(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Long i_CellID, Ncti_Double & o_Radius, NctiAxis & o_axis);

		//获取两实体之间最小距离
		/*​
		* @brief Get Minimum Distance Between Two Entities
		* @param i_pDocment Document Pointer
		* @param i_FirObjName First Object Name
		* @param i_SecObjName Second Object Name
		* @param i_deflection Deflection Value
		* @param i_Parallel Parallel Flag
		* @param o_Distance Output Distance
		* @return bool
		*/
		static bool GetMiniDistance(NctiDocument * i_pDocment, const Ncti_Char * i_FirObjName, const Ncti_Char * i_SecObjName, Ncti_Double i_deflection, Ncti_Boolean i_Parallel, Ncti_Double & o_Distance);

		//获取两单元之间最小距离
		/*​
		* @brief Get Minimum Distance Between Two Cells
		* @param i_pModelBody Model Body Pointer
		* @param i_FirstCell First Cell ID
		* @param i_SecondCell Second Cell ID
		* @param i_deflection Deflection Value
		* @param i_Parallel Parallel Flag
		* @param o_Distance Output Distance
		* @return bool
		*/
		static bool GetMiniDistance(NctiDisplayModelBody * i_pModelBody, Ncti_Long i_FirstCell, Ncti_Long i_SecondCell, Ncti_Double i_deflection, Ncti_Boolean i_Parallel, Ncti_Double & o_Distance);
		//获取俩实体的单元之间最小距离
		/*​
		* @brief Get Minimum Distance Between Two Cells
		* @param i_pModelBody Model Body Pointer
		* @param i_FirstCell First Cell ID
		* @param i_SecondCell Second Cell ID
		* @param i_deflection Deflection Value
		* @param i_Parallel Parallel Flag
		* @param o_Distance Output Distance
		* @return bool
		*/
		static bool GetMiniDistance(NctiDocument* i_pDocment, const Ncti_Char* i_FirObjName, Ncti_Long i_FirstCell, const Ncti_Char* i_SecObjName,  Ncti_Long i_SecondCell, Ncti_Double i_deflection, Ncti_Boolean i_Parallel, Ncti_Double& o_Distance);

		//获取两实体之间的极值
		/*​
		* @brief Get Extrema Between Two Entities
		* @param i_pDocment Document Pointer
		* @param i_FirObjName First Object Name
		* @param i_SecObjName Second Object Name
		* @param o_Extrema Output Extrema
		* @return bool
		*/
		static bool GetExtrema(NctiDocument * i_pDocment, const Ncti_Char * i_FirObjName, const Ncti_Char * i_SecObjName, Ncti_Geo_Extrema & o_Extrema);

		//获取点在线或者面的投影点
		/*​
		* @brief Get Project Point On Line Or Surface
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_Point Input Point
		* @param o_ProjPointVec Output Project Point Vector
		* @return bool
		*/
		static bool GetProjectPoint(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, const NctiPosition & i_Point, std::vector<Ncti_Geo_Project_Point>&o_ProjPointVec);

		/*​
		* @brief Get Project Point On Cell
		* @param i_pModelBody Model Body Pointer
		* @param i_CellID Cell ID
		* @param i_Point Input Point
		* @param o_ProjPointVec Output Project Point Vector
		* @return bool
		*/
		static bool GetProjectPoint(NctiDisplayModelBody * i_pModelBody, Ncti_Long i_CellID, const NctiPosition & i_Point, std::vector<Ncti_Geo_Project_Point>&o_ProjPointVec);
		// 通过选择集中的圆线获取圆属性
		/**
		* @brief Get Circle Property From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_Props Output Circle Properties Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetCirclePropertyFromSelManager(NctiDocument * i_pDocment, std::vector<Ncti_Geo_Circle_Property>&o_Props);

		// 通过选择集中的椭圆线获取圆属性
		/**
		* @brief Get Ellipse Property From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_Props Output Ellipse Properties Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetEllipsePropertyFromSelManager(NctiDocument * i_pDocment, std::vector<Ncti_Geo_Ellipse_Property>&o_Props);

		// 通过选择集获取边属性，不区分是否直线，只取起点和终点及其两点距离
		/**
		* @brief Get Edge Property From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_Props Output Edge Properties Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetEdgePropertyFromSelManager(NctiDocument * i_pDocment, std::vector<Ncti_Geo_Edge_Property>&o_Props);

		// 通过选择集中的圆柱面获取圆柱属性
		/**
		* @brief Get Cylinder Property From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_Prop Output Cylinder Properties Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetCylinderPropertyFromSelManager(NctiDocument * i_pDocment, std::vector<Ncti_Geo_Cylinder_Property>&o_Prop);

		// 通过选择集中的面或边获取向量
		/**
		* @brief Get Vector Property From Selection Manager
		* @param i_pDocment Document Pointer
		* @param o_Prop Output Vector Property
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetVectorPropertyFromSelManager(NctiDocument * i_pDocment, NctiVector & o_Prop);

		// 通过选择集中的面或边获取角度
		/**
		* @brief Get Angle Property From Selection Manager
		* @param i_pDocment Document Pointer
		* @param d_Angle Output Angle Value
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetAnglePropertyFromSelManager(NctiDocument * i_pDocment, Ncti_Double & d_Angle);

		// 按照edge获取shell的个数
		/**
		* @brief Get Shell Count By Edge
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_Num Output Shell Count
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetShellCountByEdge(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Integer & o_Num);

		// 碰撞检测
		/**
		* @brief Topology Clash Detection
		* @param i_pDocment Document Pointer
		* @param i_TargetObjName Target Object Names Vector
		* @param i_ToolObjName Tool Object Names Vector
		* @param o_ClashType Output Clash Types Vector
		* @param o_ClashPairs Output Clash Pairs Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean TopolClash(NctiDocument * i_pDocment, const std::vector<std::string> &i_TargetObjName, const std::vector<std::string>&i_ToolObjName, std::vector<unsigned int>&o_ClashType, std::vector<std::pair<unsigned int, unsigned int>>&o_ClashPairs);

		// 寻找点附近的几何体
		/**
		* @brief Find Geometry By Nearest Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_PointVec Point Vector
		* @param o_CellIDVec Output Cell ID Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean FindGeomByNearestPoint(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, const std::vector<NctiPosition>&i_PointVec, std::vector<Ncti_Long>&o_CellIDVec);

		// 创建变换矩阵
		/**
		* @brief Create And Check Transformation Matrix
		* @param i_pDocment Document Pointer
		* @param i_HasRotation Has Rotation Flag
		* @param i_axis Rotation Axis
		* @param i_angle Rotation Angle
		* @param i_scale Scale Factor
		* @param i_HasMirror Has Mirror Flag
		* @param i_planePos Mirror Plane Position
		* @param i_PlaneNormal Mirror Plane Normal
		* @param o_matrix Output Transformation Matrix
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean CreateAndCheckTransf(NctiDocument * i_pDocment, Ncti_Boolean i_HasRotation, NctiVector i_axis, Ncti_Double i_angle, Ncti_Double i_scale, Ncti_Boolean i_HasMirror, const NctiPosition & i_planePos, const NctiVector & i_PlaneNormal, Ncti_Double o_matrix[4][4]);

		// 计算曲线对象的包围盒
		/**
		* @brief Find Curve Bounding Box
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_EdgeID Edge ID
		* @param o_box Output Bounding Box
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean FindCurveBox(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Integer i_EdgeID, Ncti_Double o_box[6]);

		// 变换矩阵应用于向量
		/**
		* @brief Transform Direction Vector
		* @param i_pDocment Document Pointer
		* @param i_vec Input Vector
		* @param i_matrix Transformation Matrix
		* @param o_vec Output Transformed Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean TransformDirection(NctiDocument * i_pDocment, const NctiVector & i_vec, Ncti_Double i_matrix[4][4], NctiVector & o_vec);

		// 判断两个变换矩阵是否相同
		/**
		* @brief Check If Two Transformation Matrices Are Equal
		* @param i_pDocment Document Pointer
		* @param i_matrix First Transformation Matrix
		* @param i_matrix2 Second Transformation Matrix
		* @param o_equal Output Equality Flag
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean TransformEqual(NctiDocument * i_pDocment, Ncti_Double i_matrix[4][4], Ncti_Double i_matrix2[4][4], Ncti_Boolean & o_equal);

		// 获取实体的子对象的属性集
		/**
		* @brief Get Entity Subobject Attributes
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param i_type Attribute Type
		* @param o_attibs Output Attributes Map
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetAttrib(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Integer i_CellID, Ncti_Attrib_Type i_type, std::map<std::string, std::vector<std::string>>&o_attibs);

		// 设置实体的子对象的属性集
		/**
		* @brief Set Entity Subobject Attributes
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param i_attribName Attribute Name
		* @param i_value Attribute Values Vector
		* @param i_type Attribute Type
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SetAttrib(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Integer i_CellID, const Ncti_WChar * i_attribName, const std::vector<std::string>&i_value, Ncti_Attrib_Type i_type);

		//
		/**
		* @brief Check Entity Validity
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_FaceIDOrObjName Face ID or Object Name Pair
		* @param o_valid Output Validity Flag
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean CheckEntity(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, const std::pair<Ncti_Integer, std::string> &i_FaceIDOrObjName, Ncti_Boolean & o_valid);

		//获取倒圆角面的ID
		/**
		* @brief Search Face Fillets
		* @param i_pDocment Document Pointer
		* @param i_pModelBody Model Body Pointer
		* @param i_minRadius Minimum Radius
		* @param i_maxRaidus Maximum Radius
		* @param i_filletType Fillet Type
		* @param o_faceCellIDs Output Face Cell IDs Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SearchFaceFillets(NctiDocument * i_pDocment, NctiDisplayModelBody * i_pModelBody, Ncti_Double i_minRadius, Ncti_Double i_maxRaidus, Ncti_Integer i_filletType, std::vector<Ncti_Long>&o_faceCellIDs);

		//获取孔洞
		/**
		* @brief Search Holes
		* @param i_pDocment Document Pointer
		* @param i_pModelBody Model Body Pointer
		* @param i_minDiameter Minimum Diameter
		* @param i_maxDiameter Maximum Diameter
		* @param o_holes Output Holes Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SearchHoles(NctiDocument * i_pDocment, NctiDisplayModelBody * i_pModelBody, Ncti_Double i_minDiameter, Ncti_Double i_maxDiameter, std::vector<std::vector<Ncti_Long>>&o_holes);

		//判断孔洞的凹凸性
		/**
		* @brief Check If Hole Is Concave
		* @param i_pModelBody Model Body Pointer
		* @param i_HoleFaceCellID Hole Face Cell ID
		* @param i_FaceCellIDs Face Cell IDs Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean IsConcave(NctiDisplayModelBody * i_pModelBody, Ncti_Long & i_HoleFaceCellID, std::vector<Ncti_Long>&i_FaceCellIDs);

		//判断面是否是小特征面
		/**
		* @brief Check If Face Is Small Feature
		* @param i_pDocment Document Pointer
		* @param i_pModelBody Model Body Pointer
		* @param i_FaceCellID Face Cell ID
		* @param i_tolerance Tolerance Value
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean IsSmallFace(NctiDocument * i_pDocment, NctiDisplayModelBody * i_pModelBody, Ncti_Long i_FaceCellID, Ncti_Double i_tolerance);

		//获取LOGO
		/**
		* @brief Search Logos
		* @param i_pDocment Document Pointer
		* @param i_pModelBody Model Body Pointer
		* @param i_MaxWidth Maximum Width
		* @param i_MaxHeight Maximum Height
		* @param i_MinFaceNum Minimum Face Number
		* @param o_Logos Output Logos Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SearchLogos(NctiDocument * i_pDocment, NctiDisplayModelBody * i_pModelBody, Ncti_Double i_MaxWidth, Ncti_Double i_MaxHeight, Ncti_Long i_MinFaceNum, std::vector<std::vector<Ncti_Long>>&o_Logos);

		//判断面构成的区域是否半封闭
		/**
		* @brief Check If Face Region Is Semi - Closed
		* @param i_pModelBody Model Body Pointer
		* @param i_EdgeLoop Edge Loop Vector
		* @param i_FaceCellVec Face Cell Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean IsSemiClosed(NctiDisplayModelBody * i_pModelBody, std::vector<Ncti_Long>&i_EdgeLoop, std::vector<Ncti_Long> i_FaceCellVec);

		//搜索BODY中异常的对象
		/**
		* @brief Search Abnormal Cells In Body
		* @param i_pModelBody Model Body Pointer
		* @param i_vtAbnormalCellType Abnormal Cell Types Vector
		* @param critical_value Critical Values
		* @param o_vtAbnormalCells Output Abnormal Cells Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean SearchAbnormalCells(NctiDisplayModelBody * i_pModelBody, const std::vector<Ncti_AbnormalCell_Type>&i_vtAbnormalCellType, const AbnormalCellCriticalValue & critical_value, std::vector<std::vector<NCTI_MODEL_TAG> >&o_vtAbnormalCells);

		//Ai
		/**
		* @brief Create AI Model System Object
		* @param i_pBaseModel Base Model Pointer
		* @return void
		*/
		static void CreateAiModelSystemObject(NctiBaseModel * i_pBaseModel);

		/**
		* @brief Get AI Model System Object
		* @param i_pBaseModel Base Model Pointer
		* @return NctiAiModelSystemObject Pointer
		*/
		static NctiAiModelSystemObject * GetAiModelSystemObject(NctiBaseModel * i_pBaseModel);

		//
		/**
		* @brief Create Test Case To Model Manage Object
		* @param i_pBaseModel Base Model Pointer
		* @return void
		*/
		static void CreateTestCaseToModelManageObject(NctiBaseModel * i_pBaseModel);

		/**
		* @brief Get Test Case To Model Manage Object
		* @param i_pBaseModel Base Model Pointer
		* @return NctiTestCaseToModelManage Pointer
		*/
		static NctiTestCaseToModelManage * GetTestCaseToModelManageObject(NctiBaseModel * i_pBaseModel);

		public:
		//RecordInfor
		/**
		* @brief Record Information
		* @param i_pBaseModel Base Model Pointer
		* @param i_str Information String
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean RecordInfor(NctiBaseModel * i_pBaseModel, const std::string & i_str);

		public:
		//Search.
		//查找面的所有关联面（当前面edge关联的所有面）
		/**
		* @brief Find All Loop From Face
		* @param i_pBaseModel Base Model Pointer
		* @param i_pTopoCell Topology Cell Pointer
		* @param bContainOwner Contain Owner Flag
		* @param o_FaceCellVec Output Face Cell Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean FindAllLoopFromFace(NctiBaseModel * i_pBaseModel, NctiTopoCell * i_pTopoCell, bool bContainOwner, std::vector<NCTI_MODEL_TAG>&o_FaceCellVec);

		//获取面直线edge长度（非圆弧）
		/**
		* @brief Get Edge Length From Face
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_CellID Cell ID
		* @param o_LengthVec Output Length Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetEdgeLengthFromFace(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Long i_CellID, std::vector<Ncti_Double>&o_LengthVec);

		/**
		* @brief Get Edge Length From Face
		* @param pDisplayObject Display Object Pointer
		* @param i_CellID Cell ID
		* @param o_LengthVec Output Length Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetEdgeLengthFromFace(NctiDisplayObject * pDisplayObject, Ncti_Long i_CellID, std::vector<Ncti_Double>&o_LengthVec);

		/**
		* @brief Get Edge Radius From Face
		* @param pDisplayObject Display Object Pointer
		* @param i_CellID Cell ID
		* @param o_RadiusVec Output Radius Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetEdgeRadiusFromFace(NctiDisplayObject * pDisplayObject, Ncti_Long i_CellID, std::vector<Ncti_Double>&o_RadiusVec);

		//获取面外环edge长度
		/**
		* @brief Get Edge Length From Face Outer Loop
		* @param pDisplayObject Display Object Pointer
		* @param i_CellID Cell ID
		* @param o_LengthVec Output Length Vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetEdgeLengthFromFaceOuterLoop(NctiDisplayObject * pDisplayObject, Ncti_Long i_CellID, std::vector<Ncti_Double>&o_LengthVec);

		//获取edge长度
		/**
		* @brief Get Edge Length
		* @param pDisplayObject Display Object Pointer
		* @param i_EdgeCellID Edge Cell ID
		* @param o_length Output Length
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetEdgeLength(NctiDisplayObject * pDisplayObject, Ncti_Long i_EdgeCellID, Ncti_Double & o_length);

		//获取子文档 bAllNext：true：所有子文档；false：一级子文档；assemble：false：非装配文档；true：装配文档；
		/**
		* @brief Get All Sub Documents
		* @param pRootObject Root Object Pointer
		* @param subDocVec Output Sub Document Vector
		* @param bAllNext All Next Flag
		* @param assemble Assemble Flag
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetAllSubDoc(NctiDisplayObject * pRootObject, std::vector<NctiDisplayDocElement*>&subDocVec, Ncti_Boolean bAllNext = true, Ncti_Boolean assemble = false);

		/**
		* @brief Get Document Element By Name
		* @param i_pDocument Document Pointer
		* @param ElementName Element Name
		* @return NctiDisplayDocElement Pointer
		*/
		static NctiDisplayDocElement * GetDocElementByName(NctiDocument * i_pDocument, const Ncti_Char * ElementName);


		/**
		* @brief Search Loop Face
		* @param i_pDocment Document Pointer
		* @param i_ObjVec Object Vector
		* @param i_CellVec Cell Vector
		* @param o_ObjNameCellIDMap Output Object Name Cell ID Map
		* @return void
		*/
		static void SearchLoopFace(NctiDocument * i_pDocment, const std::vector<NctiDisplayObject*>&i_ObjVec, const std::vector<NCTI_MODEL_TAG>&i_CellVec, std::unordered_map<std::string, std::vector<Ncti_Long>>&o_ObjNameCellIDMap);

		/**
		* @brief Search Connected Face
		* @param i_pDocment Document Pointer
		* @param i_ObjVec Object Vector
		* @param i_CellVec Cell Vector
		* @param o_ObjNameCellIDMap Output Object Name Cell ID Map
		* @return void
		*/
		static void SearchConnectFace(NctiDocument * i_pDocment, const std::vector<NctiDisplayObject*>&i_ObjVec, const std::vector<NCTI_MODEL_TAG>&i_CellVec, std::unordered_map<std::string, std::vector<Ncti_Long>>&o_ObjNameCellIDMap);

		/**
		* @brief Search Same Connected Face
		* @param i_pDocment Document Pointer
		* @return void
		*/
		static void SearchSameConnectFace(NctiDocument * i_pDocment);

		/**
		* @brief Search Non - Planar Connected Face
		* @param i_pDocment Document Pointer
		* @param i_ObjVec Object Vector
		* @param i_CellVec Cell Vector
		* @param o_ObjNameCellIDMap Output Object Name Cell ID Map
		* @return void
		*/
		static void SearchNoPlaneConnectFace(NctiDocument * i_pDocment, const std::vector<NctiDisplayObject*>&i_ObjVec, const std::vector<NCTI_MODEL_TAG>&i_CellVec, std::unordered_map<std::string, std::vector<Ncti_Long>>&o_ObjNameCellIDMap);

		//抽取要素
		/**
		* @brief Extract Subobject
		* @param i_pDocment Document Pointer
		* @return void
		*/
		static void ExtractSubobject(NctiDocument * i_pDocment);

		//是否有命令再运行
		/**
		* @brief Check If Command Is Running
		* @param i_pDocment Document Pointer
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean IsHaveRunCommand(NctiDocument * i_pDocment);

		//获取当前Container信息
		/**
		* @brief Get Current Container Message
		* @param i_pDocment Document Pointer
		* @return std::string
		*/
		static std::string GetCurContainerMessage(NctiDocument * i_pDocment);

		/**
		* @brief Get Current Container Message
		* @param pDoc Document Element Pointer
		* @return std::string
		*/
		static std::string GetCurContainerMessage(NctiDisplayDocElement * pDoc);

		/**
		* @brief Get Current Container Simple Message
		* @param pDoc Document Element Pointer
		* @param iType Information Type
		* @return std::string
		*/
		static std::string GetCurContainerSimpleMessage(NctiDisplayDocElement * pDoc, int iType);

		//根据字符串获取内核类型
		/**
		* @brief Get Model Document Type From String
		* @param TypeName Type Name String
		* @return EnumModelDoc
		*/
		static EnumModelDoc GetModelDocFromString(const Ncti_Char * TypeName);

		/**
		* @brief Get DCM Document Type From String
		* @param TypeName Type Name String
		* @return EnumGCSDoc
		*/
		static EnumGCSDoc GetDCMDocFromString(const Ncti_Char * TypeName);

		/**
		* @brief Get Mesh Document Type From String
		* @param TypeName Type Name String
		* @return EnumMeshDoc
		*/
		static EnumMeshDoc GetMeshDocFromString(const Ncti_Char * TypeName);

		//获取对象BOX
		/**
		* @brief Get Mesh Data Bounding Box
		* @param i_meshDBVec Mesh Data Vector
		* @param o_Max Output Maximum Point
		* @param o_Min Output Minimum Point
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetMeshDataBox(const std::vector<NctiMeshData>&i_meshDBVec, NctiPosition & o_Max, NctiPosition & o_Min);

		/**
		* @brief Get Polyline Bounding Box
		* @param i_fltDBVec Float Data Vector
		* @param o_Max Output Maximum Point
		* @param o_Min Output Minimum Point
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetPolyLineBox(const std::vector<std::vector<float>>& i_fltDBVec, NctiPosition& o_Max, NctiPosition& o_Min);

		public:
		/**
		* @brief Test System Add Result
		* @param pBaseModel Base Model Pointer
		* @param i_Result Geometry Result Pointer
		* @return void
		*/
		static void TestSystemAddResult(NctiBaseModel * pBaseModel, NctiGeometryResult * i_Result);



		//提取面片中的任一点
		/**
		* @brief Find Face Interior Point
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_Point Output Interior Point
		* @return bool
		*/
		static bool FindFaceInteriorPoint(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, NctiPosition & o_Point);

		//对Body中的图元进行归类
		/**
		* @brief Entity Categorize
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_method Categorization Method
		* @return bool
		*/
		static bool EntityCategorize(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Integer i_method);

		//获取当前会话中的所有partition对象的tag
		/**
		* @brief Find All Partitions
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_vtPartitions Output Partitions Vector
		* @return bool
		*/
		static bool FindAllPartitions(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, std::vector<Ncti_Integer>&o_vtPartitions);

		//获取装配体中所有instance对象的tag
		/**
		* @brief Find Assembly Instances
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_vtInstances Output Instances Vector
		* @return bool
		*/
		static bool FindAssemblyInstances(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, std::vector<Ncti_Integer>&o_vtInstances);

		//获取与指定vertex有关的所有shell对象
		/**
		* @brief Find Shells By Vertex
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_pVertexCell Vertex Cell Tag
		* @param o_vtShelles Output Shells Vector
		* @return bool
		*/
		static bool FindShellsByVertex(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, NCTI_MODEL_TAG i_pVertexCell, std::vector<Ncti_Integer>&o_vtShelles);

		//获取face中的所有loop对象
		/**
		* @brief Find Face Loops
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_vtLoops Output Loops Vector
		* @return bool
		*/
		static bool FindFaceLoops(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, std::vector<Ncti_Integer>&o_vtLoops);

		//创建一个新的partition，并返回这个新partition的次序（即session中第几个partition，因为session中的partition的顺序一般不变）
		/**
		* @brief Create Partition
		* @param i_pDocment Document Pointer
		* @param o_partitionTag Output Partition Tag
		* @return bool
		*/
		static bool PartitionCreate(NctiDocument * i_pDocment, Ncti_Integer & o_partitionTag);

		//设置i_partitionCurrent为当前的partition
		/**
		* @brief Set Current Partition
		* @param i_pDocment Document Pointer
		* @param i_partitionCurrent Partition To Set As Current
		* @return bool
		*/
		static bool PartitionSetCurrent(NctiDocument * i_pDocment, Ncti_Integer i_partitionCurrent);

		//获取当前的partition
		/**
		* @brief Get Current Partition From Session
		* @param i_pDocment Document Pointer
		* @param o_partitionCurrent Output Current Partition
		* @return bool
		*/
		static bool SessionAskCurrPartition(NctiDocument * i_pDocment, Ncti_Integer & o_partitionCurrent);

		//在partition中创建新的pmark
		/**
		* @brief Create Pmark In Partition
		* @param i_pDocment Document Pointer
		* @param i_partition Partition ID
		* @param o_pmark Output Pmark
		* @return bool
		*/
		static bool PartitionMakePmark2(NctiDocument * i_pDocment, Ncti_Integer i_partition, Ncti_Integer & o_pmark);

		// 更新partition中的pmark，并删除原来的currentpmark
		/**
		* @brief Advance Pmark In Partition
		* @param i_pDocment Document Pointer
		* @param i_partition Partition ID
		* @param o_pmark Output New Pmark
		* @return bool
		*/
		static bool PartitionAdvancePmark(NctiDocument * i_pDocment, Ncti_Integer i_partition, Ncti_Integer & o_pmark);

		// 更新partition中的pmark，并删除原来的currentpmark
		/**
		* @brief Goto Pmark
		* @param i_pDocment Document Pointer
		* @param i_pmark Pmark To Goto
		* @return bool
		*/
		static bool PmarkGoto2(NctiDocument * i_pDocment, Ncti_Integer i_pmark);

		// 将几个partition中的pmarks合并到第一个partition，并删除其他partition
		/**
		* @brief Merge Partitions
		* @param i_pDocment Document Pointer
		* @param i_partitions Partitions Vector
		* @param i_pmarks Pmarks Vector
		* @return bool
		*/
		static bool PartitionMerge(NctiDocument * i_pDocment, std::vector<Ncti_Integer> i_partitions, std::vector<Ncti_Integer> i_pmarks);

		// 删除指定的partition
		/**
		* @brief Delete Partition
		* @param i_pDocment Document Pointer
		* @param i_partition Partition To Delete
		* @return bool
		*/
		static bool PartitionDelete(NctiDocument * i_pDocment, Ncti_Integer i_partition);

		// 复制指定的partition
		/**
		* @brief Copy Partition
		* @param i_pDocment Document Pointer
		* @param i_partition Partition To Copy
		* @param o_partitioncopy Output Copied Partition
		* @return bool
		*/
		static bool PartitionCopy(NctiDocument * i_pDocment, Ncti_Integer i_partition, Ncti_Integer & o_partitioncopy);

		// 查询pmark在其partition的ID
		/**
		* @brief Get Pmark Identifier
		* @param i_pDocment Document Pointer
		* @param i_pmark Pmark
		* @param o_identifier Output Identifier
		* @return bool
		*/
		static bool PmarkAskIdentifier(NctiDocument * i_pDocment, Ncti_Integer i_pmark, Ncti_Integer & o_identifier);

		// 输出partition
		/**
		* @brief Transmit Partition
		* @param i_pDocment Document Pointer
		* @param i_partition Partition ID
		* @param i_FullFileName File Name
		* @param i_transmit_deltas Transmit Deltas Flag
		* @return bool
		*/
		static bool PartitionTransmit(NctiDocument * i_pDocment, Ncti_Integer i_partition, const Ncti_Char * i_FullFileName, Ncti_Integer i_transmit_deltas);

		// 输出partition的delta
		/**
		* @brief Transmit Partition Delta
		* @param i_pDocment Document Pointer
		* @param i_partition Partition ID
		* @return bool
		*/
		static bool PartitionTransmitDelta(NctiDocument * i_pDocment, Ncti_Integer i_partition);

		// 输入partition
		/**
		* @brief Receive Partition
		* @param i_pDocment Document Pointer
		* @param i_FullFileName File Name
		* @param i_receive_deltas Receive Deltas Flag
		* @param o_partition Output Received Partition
		* @return bool
		*/
		static bool PartitionReceive(NctiDocument * i_pDocment, const Ncti_Char * i_FullFileName, Ncti_Integer i_receive_deltas, Ncti_Integer & o_partition);

		// 输入partition的delta
		/**
		* @brief Receive Partition Deltas
		* @param i_pDocment Document Pointer
		* @param i_partition Partition ID
		* @return bool
		*/
		static bool PartitionReceiveDeltas2(NctiDocument * i_pDocment, Ncti_Integer i_partition);

		// 根据ID查找partition中的pmark
		/**
		* @brief Find Pmark By ID In Partition
		* @param i_pDocment Document Pointer
		* @param i_partition Partition ID
		* @param i_identifier Identifier
		* @param o_pmark Output Pmark
		* @return bool
		*/
		static bool PartitionFindPmarkById(NctiDocument * i_pDocment, Ncti_Integer i_partition, Ncti_Integer i_identifier, Ncti_Integer & o_pmark);

		// 创建sessionmark
		/**
		* @brief Create Mark
		* @param i_pDocment Document Pointer
		* @param o_mark Output Mark
		* @return bool
		*/
		static bool MarkCreate(NctiDocument * i_pDocment, Ncti_Integer & o_mark);

		// 查找pmarks
		/**
		* @brief Get Pmarks From Mark
		* @param i_pDocment Document Pointer
		* @param i_mark Mark
		* @param o_pmarksVec Output Pmarks Vector
		* @return bool
		*/
		static bool MarkAskPmarks(NctiDocument * i_pDocment, Ncti_Integer i_mark, std::vector<Ncti_Integer>&o_pmarksVec);

		// 查询pmark是否被某个mark
		/**
		* @brief Check If Pmark Is Used By Mark
		* @param i_pDocment Document Pointer
		* @param i_pmark Pmark
		* @param o_is_used Output Usage Flag
		* @return bool
		*/
		static bool PmarkIsUsedByMark(NctiDocument * i_pDocment, Ncti_Integer i_pmark, Ncti_Boolean & o_is_used);

		// 跳到哪个mark上
		/**
		* @brief Goto Mark
		* @param i_pDocment Document Pointer
		* @param i_mark Mark To Goto
		* @return bool
		*/
		static bool MarkGoto2(NctiDocument * i_pDocment, Ncti_Integer i_mark);

		// 输出session
		/**
		* @brief Transmit Session
		* @param i_pDocment Document Pointer
		* @param i_FullFileName File Name
		* @return bool
		*/
		static bool SessionTransmit(NctiDocument * i_pDocment, const Ncti_Char * i_FullFileName);

		// 输入session
		/**
		* @brief Receive Session
		* @param i_pDocment Document Pointer
		* @param i_FullFileName File Name
		* @return bool
		*/
		static bool SessionReceive(NctiDocument * i_pDocment, const Ncti_Char * i_FullFileName);

		// 创建Bulletin board
		/**
		* @brief Create Bulletin Board
		* @param i_pDocment Document Pointer
		* @param i_create Create Operations Vector
		* @param i_deleet Delete Operations Vector
		* @param i_copy Copy Operations Vector
		* @param i_transfer Transfer Operations Vector
		* @param i_merge Merge Operations Vector
		* @param i_split Split Operations Vector
		* @param i_transform Transform Operations Vector
		* @param i_change_attrib Change Attribute Operations Vector
		* @param i_change Change Operations Vector
		* @return bool
		*/
		static bool BBCreate(NctiDocument * i_pDocment, std::vector<Ncti_Integer> i_create, std::vector<Ncti_Integer> i_deleet, std::vector<Ncti_Integer> i_copy, std::vector<Ncti_Integer> i_transfer, std::vector<Ncti_Integer> i_merge, std::vector<Ncti_Integer> i_split, std::vector<Ncti_Integer> i_transform, std::vector<Ncti_Integer> i_change_attrib, std::vector<Ncti_Integer> i_change);

		// 设置Bulletin board状态
		/**
		* @brief Set Bulletin Board Status
		* @param i_pDocment Document Pointer
		* @param i_status Status
		* @return bool
		*/
		static bool BBSetStatus(NctiDocument * i_pDocment, Ncti_Boolean i_status);

		// 输出Bulletin board
		/**
		* @brief Output Bulletin Board Events
		* @param i_pDocment Document Pointer
		* @param i_empty Empty Flag
		* @param o_events Output Events Vector
		* @param o_entities Output Entities Vector
		* @param o_event_types Output Event Types Vector
		* @param o_classes Output Classes Vector
		* @return bool
		*/
		static bool BBOutputEvents(NctiDocument * i_pDocment, Ncti_Boolean i_empty, std::vector< Ncti_Integer>&o_events, std::vector< Ncti_Integer>&o_entities, std::vector< Ncti_Integer>&o_event_types, std::vector< Ncti_Integer>&o_classes);

		/**
		* @brief Ask Bulletin Board Parameters
		* @param i_pDocment Document Pointer
		* @param o_bbParamResult Output Bulletin Board Parameters
		* @return bool
		*/
		static bool BBAsk(NctiDocument * i_pDocment, NCTIBbParam & o_bbParamResult);

		/**
		* @brief Ask Bulletin Board Status
		* @param i_pDocment Document Pointer
		* @param o_bbStatusResult Output Bulletin Board Status
		* @return bool
		*/
		static bool BBAskStatus(NctiDocument * i_pDocment, NCTIBbStatus & o_bbStatusResult);

		// 删除所有mark
		/**
		* @brief Delete All Marks
		* @param i_pDocment Document Pointer
		* @return bool
		*/
		static bool MarkDeleteAll(NctiDocument * i_pDocment);


		//开启历史
		/**
		* @brief Start History
		* @param pBaseModel Base Model Pointer
		* @return void
		*/
		static void StartHistory(NctiBaseModel * pBaseModel);

		//结束历史
		/**
		* @brief End History
		* @param pBaseModel Base Model Pointer
		* @param i_eStatus End Status
		* @return void
		*/
		static void EndHistory(NctiBaseModel * pBaseModel, EnumNctiResult i_eStatus = NCTI_SUCCEEDED);

		//查找曲线上的点
		/**
		* @brief Find Point On Curve
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_edgeID Edge ID
		* @param i_fMeasureValue Measure Value
		* @param i_nMeasureMode Measure Mode
		* @param o_vtPoints Output Points Vector
		* @return bool
		*/
		static bool FindPointOnCurve(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Long i_edgeID, Ncti_Double i_fMeasureValue, Ncti_Long i_nMeasureMode, std::vector<NctiPosition>&o_vtPoints);

		//Body fault check
		/**
		* @brief Body Fault Check
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_vtFaults Output Faults Vector
		* @return bool
		*/
		static bool BodyFaultCheck(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, std::vector<BodyCheckFaultResult>&o_vtFaults);

		//查找曲线、曲面上的自交区域
		/**
		* @brief Find Cell Self Intersection
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_cellID Cell ID
		* @param o_vtSelfIntInfo Output Self Intersection Info Vector
		* @return bool
		*/
		static bool FindCellSelfInt(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Long i_cellID, std::vector<CellSelfIntDegensInfo>&o_vtSelfIntInfo);

		//查找曲线、曲面上的退化区域
		/**
		* @brief Find Cell Degenerations
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_cellID Cell ID
		* @param o_vtDegensInfo Output Degeneration Info Vector
		* @return bool
		*/
		static bool FindCellDegens(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, Ncti_Long i_cellID, std::vector<CellSelfIntDegensInfo>&o_vtDegensInfo);

		//body 鉴定
		/**
		* @brief Body Identify General
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param o_vtFaults Output Faults Vector
		* @return bool
		*/
		static bool BodyIdentifyGeneral(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, std::vector<NCTIBodyGeneralResult>&o_vtFaults);

		//得到实体参数
		/**
		* @brief Ask Entity Parameters
		* @param i_pDocment Document Pointer
		* @param i_ModelTagVec Model Tag Vector
		* @param i_paramVector Parameter Vector
		* @param o_paramValueStr Output Parameter Value Strings
		* @return bool
		*/
		static bool AskEntityParam(NctiDocument * i_pDocment, NCTI_MODEL_TAG i_ModelTagVec, std::vector<Ncti_Integer>&i_paramVector, std::vector<std::string>&o_paramValueStr);

		//输出Body对象的拓补和几何信息
		/**
		* @brief Output Topology Info With Geometry
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_vtCellIndex Cell Index Vector
		* @param i_pFileName File Name
		* @return bool
		*/
		static bool OutputTopolInfoWithGeom(NctiDocument * i_pDocment, const Ncti_Char * i_ObjName, const std::vector<Ncti_Long>& i_vtCellIndex, int i_nLevel, const char* const i_pFileName);

		//得到拓扑的OBB包围盒
		/**
		* @brief Get OBB Bounding Box
		* @param i_pDocment Document Pointer
		* @param ModelTagVec Model Tag Vector
		* @param paraData Parameter Data
		* @param boxData Output Box Data
		* @return bool
		*/
		static bool GetObbBoungdingBox(NctiDocument * i_pDocment, const std::vector<NCTI_MODEL_TAG>&i_ModelTagVec, const std::vector<NctiPosition>&paraData, std::vector<NctiPosition>&boxData);

		//输出Body对象的拓补和几何信息
		/**
		* @brief feature identification
		* @param i_pDocment Document Pointer
		* @param i_ObjName Object Name
		* @param i_opt input identify option
		* @param o_vtFeatureFaces output feature faces
		* @return bool
		*/
		static bool IdentifyFeature(NctiDocument* i_pDocment, const Ncti_Char* i_ObjName, const NCTIIdentifyFeatureOption& i_opt, std::vector<NCTIIdentifyFeatureResult>& o_vtFeatureFaces);

		//由网格获取有效的Section
		/**
		* @brief Get Sections From Grid Mesh
		* @param i_pGridMesh Grid Mesh Pointer
		* @return std::vector<NctiDisplaySection*>
		*/
		static std::vector<NctiDisplaySection*> GetSectionFromGridMesh(NctiDisplayGridMesh* i_pGridMesh);

		//由Section获取Set
		/**
		* @brief Get Sets From Section
		* @param i_pSectionVec Section Vector
		* @return std::vector<NctiDisplaySet*>
		*/
		static std::vector<NctiDisplaySet*> GetSetFromSection(const std::vector<NctiDisplaySection*>& i_pSectionVec);

		//由Section获取材料
		/**
		* @brief Get Materials From Section
		* @param i_pSectionVec Section Vector
		* @return std::vector<NctiDisplayMaterialAttribute*>
		*/
		static std::vector<NctiDisplayMaterialAttribute*> GetMaterialFromSection(const std::vector<NctiDisplaySection*>& i_pSectionVec);

		//由网格获取有效的耦合
		/**
		* @brief Get Couplings From Grid Mesh
		* @param i_pGridMesh Grid Mesh Pointer
		* @return std::vector<NctiDisplayCoupling*>
		*/
		static std::vector<NctiDisplayCoupling*> GetCouplingFromGridMesh(NctiDisplayGridMesh* i_pGridMesh);

		//由耦合获取Set
		/**
		* @brief Get Sets From Coupling
		* @param i_pCouplingVec Coupling Vector
		* @return std::vector<NctiDisplaySet*>
		*/
		static std::vector<NctiDisplaySet*> GetSetFromCoupling(const std::vector<NctiDisplayCoupling*>& i_pCouplingVec);

		//由网格获取有效的Tie
		/**
		* @brief Get Ties From Grid Mesh
		* @param i_pGridMesh Grid Mesh Pointer
		* @param o_pSetVec out put sets pointer
		* @return std::vector<NctiDisplayTie*>
		*/
		static std::vector<NctiDisplayTie*> GetTieFromGridMesh(const std::vector<NctiDisplayGridMesh*>& i_pGridMeshVec, std::vector<NctiDisplaySet*>& o_pSetVec);

		public:
		/**
		* @brief Base View Callback Instance
		* @param i_pBaseView Base View Pointer
		* @param i_Type Callback Type
		* @param pObj Display Object Pointer
		* @return void
		*/
		static void BaseViewCallBackInstance(NctiBaseView * i_pBaseView, EnumNctiDoCallbackType i_Type, NctiDisplayObject * pObj);
		
		/**
		* @brief Merge meshs
		* @param MeshDataVec meshs
		* @return NctiMeshData
		*/
		static void MergeMeshDataVec(const std::vector<NctiMeshData>& MeshDataVec, NctiMeshData& oMeshData);

		/*
		* @brief output Parasolid format file，X_T、X_B、or xmt_txt、xmt_bin file order 295
		* @param i_pDocment Document Pointer
		* @param i_FullFileName full file name
		* @param i_vtModelBody  model body vector
		* return bool
		*/
		static bool OutputPKXTXBFile(NctiDocument* i_pDocment, const Ncti_Char* const i_FullFileName, const std::vector<const Ncti_Char*>& i_vtModleBodyName);
		
		/**
		* @brief Get the geometric full path of the displayModelBody
		* @param[in] i_pModelBody, the displayModelBody pointer
		* @param[out] o_fullPath, the geometric all head id
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetGeometryFullPath(NctiDisplayModelBody* i_pModelBody, std::string& o_fullPath);
		
		/**
		* @brief Get the geometric id of the displayModelBody
		* @param[in] i_pModelBody, the displayModelBody pointer
		* @param[out] o_originalID, the geometric id
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetGeometryOriginalID(NctiDisplayModelBody* i_pModelBody, Ncti_Size& o_originalID);
		
		/**
		* @brief Get the feature id of the displayModelBody
		* @param[in] i_pModelBody, the displayModelBody pointer
		* @param[in] i_cellIds, the feature index vector
		* @param[out] o_ids, the feature id vector
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetFeatureOriginalID(NctiDisplayModelBody* i_pModelBody, const std::vector<Ncti_Integer>& i_cellIds, std::vector<Ncti_Size>& o_ids);

		/**
		* @brief Compare two model from same document
		* @param[in] i_pDocment Document Pointer
		* @param[in] i_selfObjName Self Object Name
		* @param[in] i_otherObjName Other Object Name
		* @param[in] i_uFacePtCount U Face Point Count
		* @param[in] i_vFacePtCount V Face Point Count
		* @param[in] i_edgePtCount Edge Point Count
		* @param[in] i_edgePtStep Edge Point Step
		* @param[in] i_tol Tolerance
		* @param[in] i_resultPath Result Path
		* @param[out] o_type Compare Type
		* @param[out] o_selfMap Cell id map, key is self cell id, value is other cell id
		* @param[out] o_otherMap Cell id map, key is other cell id, value is self cell id
		* @param[out] o_errorString Error String
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean ModelCompare(NctiDocument* i_pDocment,const Ncti_Char* i_selfObjName, const Ncti_Char* i_otherObjName, Ncti_Integer i_uFacePtCount, Ncti_Integer i_vFacePtCount, Ncti_Integer i_edgePtCount, Ncti_Double i_edgePtStep, Ncti_Double i_tol, const Ncti_Char* i_resultPath
			, std::string &o_type, std::map<Ncti_Integer, Ncti_Integer>& o_selfMap, std::map<Ncti_Integer, Ncti_Integer>& o_otherMap, std::string* o_errorString);
		
		/**
		* @brief Compare tow model from ncti file
		* @param[in] i_selfPath Self Path
		* @param[in] i_otherPath Other Path
		* @param[in] i_tol Tolerance
		* @param[in] i_resultPath Result Path
		* @param[out] o_type Compare Type
		* @param[out] o_selfMap Cell id map, key is self cell id, value is other cell id
		* @param[out] o_otherMap Cell id map, key is other cell id, value is self cell id
		* @param[out] o_errorString Error String
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean ModelCompare(const Ncti_Char* i_selfPath, const Ncti_Char* i_otherPath, Ncti_Double i_tol, const Ncti_Char* i_resultPath
			, std::string& o_type, std::map<Ncti_Integer, Ncti_Integer>& o_selfMap, std::map<Ncti_Integer, Ncti_Integer>& o_otherMap, std::string* o_errorString);
		
		/**
		* @brief Export model compare info
		* @param[in] i_pDocment Document Pointer
		* @param[in] i_path Path
		* @param[in] i_objName Object Name
		* @param[in] i_uFacePtCount U Face Point Count
		* @param[in] i_vFacePtCount V Face Point Count
		* @param[in] i_edgePtCount Edge Point Count
		* @param[in] i_edgePtStep Edge Point Step
		* @param[in] i_tol Tolerance
		* @param[out] o_errorString Error String
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean ExportModelCompareInfo(NctiDocument* i_pDocment, const Ncti_Char* i_path, const Ncti_Char* i_objName, Ncti_Integer i_uFacePtCount, Ncti_Integer i_vFacePtCount, Ncti_Integer i_edgePtCount, Ncti_Double i_edgePtStep, Ncti_Double i_tol, std::string *o_errorString);
	
		/**
		* @brief Get geometry type
		* @param[in] i_pDocment Document Pointer
		* @param[in] i_objName Object Name
		* @param[in] i_cellIds The id of specify cell in object 
		* @param[out] o_type The Type list
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetGeGeomType(NctiDocument* i_pDocment, const Ncti_Char* i_objName, const std::vector<Ncti_Integer>& i_cellIds, std::vector<std::string> &o_type);
	
		/**
		* @brief Get geometry sub type (face line)
		* @param[in] i_pDocment Document Pointer
		* @param[in] i_objName Object Name
		* @param[in] i_cellIds The id of specify cell in object 
		* @param[out] o_type The Type list
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GeometrySubType(NctiDocument* i_pDocment, const Ncti_Char* i_objName, const std::vector<Ncti_Integer>& i_cellIds, std::vector<std::string> &o_type);
	
		/**
		* @brief Get geometry face type
		* @param[in] i_topoFace NctiTopoFace
		* @return string
		*/
		static std::string GetGeFaceType(NctiTopoFace* i_topoFace);
	
		/**
		* @brief Get geometry face type
		* @param[in] i_topoEdge NctiTopoEdge
		* @return string
		*/
		static std::string GetGeEdgeType(NctiTopoEdge* i_topoEdge);

		/**
		* @brief Update View
		* @param[in] i_pDocment Document Pointer
		*/
		static void UpdateView(NctiDocument* i_pDocment);

		/**
		* @brief Update View
		* @param[in] i_pContainer DocCustomContainer Pointer
		*/
		static void UpdateView(NctiDisplayDocCustomContainer* i_pContainer);

		/**
		* @brief Update View
		* @param[in] i_pBaseModel BaseModel Pointer
		*/
		static void UpdateView(NctiBaseModel* i_pBaseModel);

		/**
		* @brief Determine if all the surfaces are planar
		* @param[in] i_pModelBody geomitry
		* @param[in] i_cellIdVec face ids,null:all the surfaces of geometry
		* @param[in] i_planarTolerance
		* @return std::vector<Ncti_Boolean>
		*/
		static std::vector<Ncti_Boolean> GetFacesPlanar(NctiDisplayModelBody* i_pModelBody, const std::vector<Ncti_Long>& i_cellIdVec, double i_planarTolerance = 1e-3f);

		/**
		* @brief Get length of a certain range of edge 
		* @param[in] i_pModelBody edge
		* @param[in] i_startParam, start parameter
		* @param[in] i_endParam, end parameter
		* @param[out] o_len, length
		* @return Ncti_Boolean
		* */
		static bool GetRangeEdgeLength(NctiDisplayModelBody* i_pEdgeBody, Ncti_Double i_startParam, Ncti_Double i_endParam, Ncti_Double& o_len);
};
}
#endif
