#ifndef NctiDisplayModelBody_H
#define NctiDisplayModelBody_H
#include "NctiDisplayGModelObject.h"
#include "ncti_include.h"
namespace NCTI
{
	class NctiData_NctiTagKeyMapList;
	class NctiTagKeyMapList;
	class NctiDisplayDocCustomContainer;
	class NctiRenderGeometryItem;
	/**
	* @brief Model body class
	* @details the kernel body of display model object
	* @see NctiDisplayGModelObject
	*/
	class DECL_NCTI NctiDisplayModelBody : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayModelBody)
	public:
		virtual ~NctiDisplayModelBody();
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();

        /**
        * @brief Callback
        */
        EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable)override;
        
		/**
	   * @brief Update the display
	   * @details get render data from kernel, create the model key and geometry for render
	   * @param[in] i_pCustomContainer, the owner of this
	   * @param[in] i_Body, the kernel body
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult UpdateDisplay(NctiDisplayObject* i_pCustomContainer, NCTI_MODEL_TAG i_Body);
		/**
	   * @brief Initialization when reading the document obj class, internal used
	   * @details deal the render data and kernel body, organize its relationships
	   * @param[in] i_pCustomContainer, the owner of this
	   * @param[in] i_ModelBodyVec, the kernel body
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	protected:
		NCTI_VERSION(1, std::vector<NctiMeshData>, m_NctiMeshDataVec, sd_read_packed)
		NCTI_VERSION(1, std::vector<std::vector<std::vector<Ncti_Float>>>, m_UVMoreVecVec, sd_read_packed)
			std::vector < std::vector<Ncti_Float>> m_FloatVecVec;
		std::vector<NctiPosition> m_MarkerVec;
	private:
		NCTI_MODEL_TAG m_NctiBody;
		long m_NctiBodyIndex;
		std::vector<Ncti_Long> m_TempIdVec;
		std::vector<NctiMeshPacked> m_MeshPackedUVVec;
		std::vector<NctiMeshPacked> m_MeshPackedPosVec;
		std::vector<NctiMeshPacked> m_MeshPackedNorVec;
		std::vector<NctiMeshPacked> m_MeshPackedTriVec;
		std::vector<NctiMeshPacked> m_MeshPackedEdgeVec;
		Ncti_Boolean m_PackedIsSameUV;
		Ncti_Boolean m_PackedIsSamePos;
		Ncti_Boolean m_PackedIsSameNor;
		Ncti_Boolean m_PackedIsSameTri;
		Ncti_Boolean m_PackedIsSameEdge;
	public:
		/**
	   * @brief get the geometry mesh render data
	   * @details from the tessellation data of kernel body 
	   * @return const std::vector<NctiMeshData>&
	   */
		const std::vector<NctiMeshData>& GetMeshDataVec() const { return m_NctiMeshDataVec; }
		/**
	   * @brief get the geometry polyline render data
	   * @details from the tessellation data of kernel body
	   * @return const std::vector<NctiMeshData>&
	   */
		const std::vector < std::vector<Ncti_Float>>& GetPolyLineVec() { return m_FloatVecVec; }
	protected:
		NctiData_NctiTagKeyMapList* m_pDataTagKeyMapList;
	public:
		/**
	   * @brief get the kernel body of this display object
	   * @return NCTI_MODEL_TAG void*
	   */
		NCTI_MODEL_TAG GetNctiBody() { return m_NctiBody; }
		/**
	   * @brief set the kernel body of this display object
	   * @param[in] i_Body, the kernel body 
	   * @return NCTI_MODEL_TAG void*
	   */
		void SetNctiBody(NCTI_MODEL_TAG i_Body);
	public:
		/**
	   * @brief find the kernel cell by render item
	   * @param[in] i_lKey, the render item
	   * @param[out] o_ulModelTag, the kernel cell
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean FindModelTagByKey(NCTI::NctiRenderGeometryItem* i_lKey, NCTI_MODEL_TAG& o_ulModelTag);
		/**
	   * @brief find render item by the kernel cell
	   * @param[in] i_ulModelTag, the kernel cell 
	   * @param[out] o_lKey, the render item
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean FindKeyByModelTag(NCTI_MODEL_TAG i_ulModelTag, NCTI::NctiRenderGeometryItem*& o_lKey);

        /**
       * @brief get the sub geomtry bis by id
       * @param[in] i_id, sub id
       * @return Ncti_Boolean
       */
        Ncti_Boolean GetVisBySubId(Ncti_UInteger i_id);

        /**
       * @brief SetVisBySubIds
       * @param[in] i_ids, sub ids
       * @param[in] vis, visibility state
       * @return Ncti_Boolean
       */
        void SetVisBySubIds(std::vector<Ncti_UInteger> i_ids, Ncti_Boolean vis);

		/**
	   * @brief get all the kernel cell 
	   * @param[out] o_ulModelTagVec, the kernel cell list
	   */
		void GetAllModelTag(std::vector<NCTI_MODEL_TAG>& o_ulModelTagVec);
		/**
	   * @brief set the render item display state.
	   * @param[in] i_boo, true or false
	   * @return Ncti_Boolean
	   */
		void ShowOrHideAllCell(Ncti_Boolean i_boo);



	public:
		/**
	   * @brief internal used
	   */
		void Compress(Ncti_Integer)override;
		/**
	   * @brief internal used
	   */
		void UnCompress(Ncti_Integer)override;
		/**
	   * @brief internal used
	   */
		void SetUV(const std::vector<std::vector<Ncti_Float>>& i_UVVec);
		/**
	   * @brief internal used
	   */
		std::string GetMeshName() const;
		/**
	   * @brief internal used
	   */
		void SetNctiBodyIndex(Ncti_Long i_index) { m_NctiBodyIndex = i_index; }
	public:
		/**
	   * @brief internal used
	   */
		void CompressUV();
		void CompressPosition();
		void CompressNormal();
		void CompressTriangle();
		void CompressEdge();
		void UnCompressUV();
		void UnCompressPosition();
		void UnCompressNormal();
		void UnCompressTriangle();
		void UnCompressEdge();
	protected:
		/**
	   * @brief internal used
	   */
		Ncti_Boolean SetTagKeyMapList(NctiTagKeyMapList* i_pTagKeyMapList, Ncti_Boolean i_openfile = false);
	};
}
#endif // !NctiDisplayModelBody_H
