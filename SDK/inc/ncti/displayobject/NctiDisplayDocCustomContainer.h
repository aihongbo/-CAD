#ifndef NctiDisplayDocCustomContainer_H
#define NctiDisplayDocCustomContainer_H
#include "NctiDisplayDocFileContainer.h"
#include "ncti_include.h"
namespace NCTI
{
	class NctiDisplayModelBody;
	/**
	* @brief Doc Custom Container class
	* @details Base Class of Core or Mesh Container.Such as OCC Container
	* @see NctiDisplayDocFileContainer,NctiDisplayDocElement
	*/
	class DECL_NCTI NctiDisplayDocCustomContainer : public NctiDisplayDocFileContainer
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocCustomContainer)
	public:
		~NctiDisplayDocCustomContainer();
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
	public:
		/**
	   * @brief Initialization when reading the document obj class
	   * @details Define Core or Mesh Container, need to implement, override
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult ActivateData();
	public:
		/**
	   * @brief Get bodies of all NctiDisplayModelBody in a kernel Container
	   * @details Only kernel container is useful
	   * @param[out] o_ModelBodyVec the vector of NCTI_MODEL_TAG
	   * @return EnumNctiResult
	   */
		void GetAllBody(std::vector<NCTI_MODEL_TAG>& o_ModelBodyVec);
		/**
	   * @brief Get NctiDisplayModelBody by body in a kernel Container
	   * @details Only kernel container is useful
	   * @param[in] i_ModelBody NCTI_MODEL_TAG obj
	   * @return EnumNctiResult
	   */
		NctiDisplayModelBody* GetDisplayObjByBody(NCTI_MODEL_TAG i_ModelBody);
	public:
		/**
	   * @brief Get dcm type in a Container.
	   * @return const char*
	   */
		const char* GetDcmDocType();
		/**
	   * @brief Set dcm type in a Container\
	   * @param[in] i_dcm_doc_type the dcm enum
	   * @return const char*
	   */
		void SetDcmDocType(EnumGCSDoc i_dcm_doc_type);
		/**
	   * @brief Get Mesh type in a Container
	   * @return const char*
	   */
		const char* GetMeshDocType();
		/**
	   * @brief Set Mesh type in a Container
	   * @param[in] i_mesh_doc_type the mesh enum
	   * @return const char*
	   */
		void SetMeshDocType(EnumMeshDoc i_mesh_doc_type);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		Ncti_Char* m_dcm_doc_type;
		Ncti_Char* m_mesh_doc_type;
	public:
		/**
	   * @brief Is Wire Body.
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody NCTI_MODEL_TAG body
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsWireBody(NCTI_MODEL_TAG i_pBody) { return false; }
		/**
	   * @brief Is Sheet Body.
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody NCTI_MODEL_TAG obj
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsSheetBody(NCTI_MODEL_TAG i_pBody) { return false; }
		/**
	   * @brief Is Solid Body.
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody NCTI_MODEL_TAG obj
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsSolidBody(NCTI_MODEL_TAG i_pBody) { return false; }
		/**
	   * @brief Is Edge cell.
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody NCTI_MODEL_TAG obj
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsEdge(NCTI_MODEL_TAG i_pCell) { return false; }
		/**
	   * @brief Is Face cell.
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody NCTI_MODEL_TAG obj
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsFace(NCTI_MODEL_TAG i_pCell) { return false; }
		/**
	   * @brief Get persistent tag of body or cell
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_FatherObj need to get body of NctiDisplayModelBody
	   * @param[in] i_ModelBody NCTI_MODEL_TAG obj
	   * @param[out] o_id get the tag by i_ModelBody
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean get_persistent_tag(
			NctiDisplayModelBody* i_FatherObj,
			NCTI_MODEL_TAG i_ModelBody,
			Ncti_Long& o_id) { return false; }
		/**
	   * @brief Get body void of tag
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_FatherObj need to get body of NctiDisplayModelBody
	   * @param[out] o_ModelBody get NCTI_MODEL_TAG void by tag
	   * @param[in] i_id input the tag 
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean get_void_from_tag(
			NctiDisplayModelBody* i_FatherObj,
			NCTI_MODEL_TAG& o_ModelBody,
			Ncti_Long i_id) { return false; }
		virtual Ncti_Boolean get_void_from_tag(
			NCTI_MODEL_TAG i_Body,
			NCTI_MODEL_TAG& o_ModelBody,
			Ncti_Long i_id) {
			return false;
		}
		/**
	   * @brief tessellation body
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody input body
	   * @param[out] o_NctiMeshDataVec the triangular mesh
	   * @param[out] o_FaceShapeVec one to one
	   * @param[out] o_FloatVec the polyline
	   * @param[out] o_EdgeShapeVec one to one
	   * @param[out] o_PtVec the vertex
	   * @param[out] o_VertexShapeVec one to one
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean tessellation_body(
			NCTI_MODEL_TAG i_pBody, 
			std::vector<NctiMeshData>& o_NctiMeshDataVec, 
			std::vector<NCTI_MODEL_TAG>& o_FaceShapeVec, 
			std::vector<std::vector<Ncti_Float>>& o_FloatVec, 
			std::vector<NCTI_MODEL_TAG>& o_EdgeShapeVec,
			std::vector<NctiPosition>& o_PtVec,
			std::vector<NCTI_MODEL_TAG>& o_VertexShapeVec){ return false; }
		/**
	   * @brief clone body.
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody input the cloned body
	   * @param[out] o_Body the result
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean clone_body(
			NCTI_MODEL_TAG i_pBody,
			NCTI_MODEL_TAG& o_Body){ return false; }
		/**
	   * @brief delete body.
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody the delete body
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean delete_body(
			NCTI_MODEL_TAG i_pBody){ return false; }
		/**
	   * @brief get body label
	   * @details Define kernel container, need to implement, override
	   * @param[in] i_pBody
	   * @return Ncti_Boolean
	   */
		virtual const char* get_label(NCTI_MODEL_TAG i_pBody) { return nullptr; }
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean inti_geobject(NCTI_MODEL_TAG i_pBody) { return false; }
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean get_gecell(NCTI_MODEL_TAG i_pBody, NCTI_MODEL_TAG i_pCell, NCTI_MODEL_TAG& o_pGECell) { return false; }
	};
}

#endif

