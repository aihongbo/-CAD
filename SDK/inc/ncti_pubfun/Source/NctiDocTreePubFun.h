#pragma once

#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include "string"
#include "vector"

namespace NCTI
{
    class NctiDocument;
    class NctiDisplayObject;
    class NctiRenderSegmentItem;
    class NctiRenderGeometryItem;
    class NctiSketchConstrManager;

	struct NctiTreeData
	{
		uint32_t id;
		std::string name;
		std::string type;
		void* pObject;
		std::vector<NctiTreeData> vChild;
		NctiTreeData() :id(0), pObject(nullptr) {}
	};

	/**
	* @brief The Doc Tree Public Function Class 
	*/
	class DECL_NCTI_PUBFUN NctiDocTreePubFun
	{
	public:
		/**
		* @brief Get Only Object Tree
		* @param pObject Object Pointer
		* @param headItem Output Head Item
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetOnlyObjectTree(NctiDisplayObject * pObject, NctiTreeData & headItem);

		/**
		* @brief Display Only Object Tree
		* @param Item Tree Item
		* @return NctiTreeData
		*/
		static NctiTreeData DisOnlyObjectTree(NctiTreeData & Item);

        /**
        * @brief Get Sketch Constraint Tree
        * @param i_pConstrMan Sketch Constraint Manager Object Pointer
        * @param io_headItem Output Head Item
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetSketchConstrTree(NctiSketchConstrManager* i_pConstrMan, NctiTreeData& io_headItem);

        /**
        * @brief Get Assemble Tree
        * @param pRootObject Root Object Pointer
        * @param treeData Output Tree Data
        * @param bOnlyAssemble Only Assemble Flag
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetAssembleTree(NctiDisplayObject* pRootObject, NctiTreeData& treeData, bool bOnlyAssemble);
        /**
        * @brief Get Assemble Tree
        * @param pObject Object Pointer
        * @return NctiTreeData
        */
        static NctiTreeData GetAssembleTree(NctiDisplayObject* pObject);

        /**
        * @brief Get Object Tree
        * @param i_pDocment Document Pointer
        * @param treeData Output Tree Data
        * @param bOnlyAssemble Only Assemble Flag
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetObjectTree(NctiDocument* i_pDocment, NctiTreeData& treeData, bool bOnlyAssemble);
        /**
        * @brief Get Object Tree
        * @param pObject Object Pointer
        * @param headItem Output Head Item
        * @param bOnlyPart Only Part Flag
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetObjectTree(NctiDisplayObject* pObject, NctiTreeData& headItem, bool bOnlyPart);

		/**
		* @brief Get Object Tree
		* @param pObject Object Pointer
		* @return NctiTreeData
		*/
		static NctiTreeData GetObjectTree(NctiDisplayObject * pObject);

        //场景树
        /**
        * @brief Get Scene Tree
        * @param i_pDocment Document Pointer
        * @param treeData Output Tree Data
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetSceneTree(NctiDocument* i_pDocment, NctiTreeData& treeData);

        /**
        * @brief Get Scene Tree
        * @param pSceneItem Scene Item Pointer
        * @param bInc Include Flag
        * @return NctiTreeData
        */
        static NctiTreeData GetSceneTree(NctiRenderSegmentItem* pSceneItem, bool bInc = false);


		/**
		* @brief Get Object Type
		* @param pRootObject Root Object Pointer
		* @return std::string
		*/
		static std::string GetObjectType(NctiDisplayObject * pRootObject);

        /**
        * @brief Get Render Segment Property Data
        * @param pRenderSegmentItem Render Segment Item Pointer
        * @param jsonData Output JSON Data
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetRenderSegmentPropData(NctiRenderSegmentItem* pRenderSegmentItem, std::string& jsonData);

        /**
        * @brief Get Render Geometry Property Data
        * @param pRenderSegmentItem Render Segment Item Pointer
        * @param jsonData Output JSON Data
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetRenderGeometryPropData(NctiRenderGeometryItem* pRenderSegmentItem, std::string& jsonData);

        /**
        * @brief Get Display Object Property Data
        * @param pObject Object Pointer
        * @param jsonData Output JSON Data
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetDisplayObjectPropData(NctiDisplayObject* pObject, std::string& jsonData);

        /**
        * @brief Get Render Property Data
        * @param pObject Object Pointer
        * @param jsonData Output JSON Data
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetRenderPropData(void* pObject, std::string& jsonData);

        /**
        * @brief Get Object Property Data
        * @param pObject Object Pointer
        * @param jsonData Output JSON Data
        * @return Ncti_Boolean
        */
        static Ncti_Boolean GetObjectPropData(void* pObject, std::string& jsonData);
};
}
