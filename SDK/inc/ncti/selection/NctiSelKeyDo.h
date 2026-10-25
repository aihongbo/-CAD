#ifndef NctiSelKeyDo_H
#define NctiSelKeyDo_H
#include "NctiSelectionData.h"
namespace NCTI
{
	class NctiDisplayObject;
	class NctiRenderGeometryItem;
	/**
	* @brief manager render item, original, instance and selection id
	* @details the base class is NctiSelectionData,
	* @see NctiSelectionData
	*/
	class DECL_NCTI NctiSelKeyDo : public NctiSelectionData
	{
		NCTI_SELDATA_FUNCTIONS(NctiSelKeyDo)
	protected:
		NctiSelKeyDo();
	public:
        NctiSelKeyDo(NCTI::NctiRenderGeometryItem* i_lKey, NctiDisplayObject* i_pDoOriginal, NctiDisplayObject* i_pDoInstance);
		virtual ~NctiSelKeyDo();
		/**
	   * @brief set the selection data, render item, original, instance
	   * @param[in] i_lKey, the render item, geometry or nullptr
	   * @param[in] i_pDoOriginal, the original object
	   * @param[in] i_pDoInstance, the instance object
	   */
        void Set(NCTI::NctiRenderGeometryItem* i_lKey, NctiDisplayObject* i_pDoOriginal, NctiDisplayObject* i_pDoInstance);
		/**
	   * @brief get the selection data, render item, original, instance
	   * @param[out] o_lKey, the render item, geometry or nullptr
	   * @param[out] o_pDoOriginal, the original object
	   * @param[out] o_pDoInstance, the instance object
	   */
        void Get(NCTI::NctiRenderGeometryItem*& o_lKey, NctiDisplayObject*& o_pDoOriginal, NctiDisplayObject*& o_pDoInstance);
		/**
	   * @brief get the selection data, instance
	   * @return NctiDisplayObject, the instance object
	   */
        NctiDisplayObject* GetDoInstance();
		/**
	   * @brief get the selection data, original
	   * @return NctiDisplayObject, the original object
	   */
        NctiDisplayObject* GetDoOriginal();
		/**
	   * @brief get the selection data, render item, geometry or nullptr
	   * @return NctiRenderGeometryItem, render item
	   */
        NCTI::NctiRenderGeometryItem* GetKey();
		/**
	   * @brief internal used
	   */
		Ncti_Integer GetSelectID();
		/**
	   * @brief internal used
	   */
         NctiSelectionData* MakeCopy()override;
		 /**
	   * @brief internal used
	   */
        void GetBox(NctiPosition& o_ptMin, NctiPosition& o_ptMax)override;
		/**
	   * @brief internal used
	   */
		Ncti_Integer GetHashIndex()override;
		/**
	   * @brief internal used
	   */
		void highlight(Ncti_Boolean high)override;
		NctiSelectionData& operator =(NctiSelectionData& i_cSource)override;
		Ncti_Boolean operator ==(NctiSelectionData& i_cSource)override;
	protected:
        NCTI::NctiRenderGeometryItem* m_lKey;
		NctiDisplayObject* m_pDoOriginal;
		NctiDisplayObject* m_pDoInstance;
		Ncti_Integer m_iSelectID;//order select id
	};
}
#endif
