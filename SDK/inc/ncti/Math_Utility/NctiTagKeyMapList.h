#ifndef NctiTagKeyMapList_H
#define NctiTagKeyMapList_H
#include "ncti.h"
#include "NctiData.h"
#include "NctiTagKeyMap.h"
namespace NCTI
{
	class NctiFileInterface;
    class NctiRenderGeometryItem;
	/**
	* @brief  tag void and render item map list
	* @details to manager NctiTagKeyMap
	* @see NctiTagKeyMap
	*/
	class DECL_NCTI NctiTagKeyMapList : public NCTI_BASE_CLASS
	{
	public:
		NctiTagKeyMapList();
		NctiTagKeyMapList(Ncti_Integer  i_iSize);
		NctiTagKeyMapList(NctiTagKeyMapList&  i_listTagKeyMap);
		virtual ~NctiTagKeyMapList();
		/**
	   * @brief get the size of list
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetSize() { return m_iSize; }
		/**
	   * @brief get the TagKeyMap of list by index
	   * @return NctiTagKeyMap
	   */
		NctiTagKeyMap GetTagKeyMap(Ncti_Integer  i_iIndex);
		/**
	   * @brief get the tag of list by index
	   * @return Ncti_Long
	   */
		Ncti_Long GetTag(Ncti_Integer  i_iIndex);
		/**
	   * @brief get the tag void of list by index
	   * @return void
	   */
		void* GetTagVoid(Ncti_Integer  i_iIndex);
		/**
	   * @brief get the render item of list by index
	   * @return NctiRenderGeometryItem
	   */
        NCTI::NctiRenderGeometryItem* GetKey(Ncti_Integer i_iIndex);
		/**
	   * @brief set index, tag id, render item to list
	   * @param[in] i_iIndex, the index
	   * @param[in] i_tag, the tag id, such body tag id
	   * @param[in] i_key, the render item
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean SetTagKey(Ncti_Integer  i_iIndex, Ncti_Long i_tag, NCTI::NctiRenderGeometryItem* i_key);
		/**
	   * @brief set index, tag id, render item to list
	   * @param[in] i_iIndex, the index
	   * @param[in] i_tag, the tag void, such body void
	   * @param[in] i_key, the render item
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean SetTagKey(Ncti_Integer  i_iIndex, void* i_tag, NCTI::NctiRenderGeometryItem* i_key);
		/**
	   * @brief set tag id by index
	   * @param[in] i_iIndex, the index
	   * @param[in] i_tag, the tag id, such body tag id
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean SetTag(Ncti_Integer i_iIndex, Ncti_Long i_tag);
		/**
	   * @brief set tag void by index
	   * @param[in] i_iIndex, the index
	   * @param[in] i_tag, the tag void, such body void
	   * @return Ncti_Boolean
	   */
        Ncti_Boolean SetKey(Ncti_Integer  i_iIndex, NCTI::NctiRenderGeometryItem* i_key);
		/**
	   * @brief internal used
	   */
		EnumNctiResult SaveData(NctiFileInterface*  i_pFI);
		/**
	   * @brief internal used
	   */
		EnumNctiResult RestoreData(NctiFileInterface*  i_pFI);
		/**
	   * @brief internal used
	   */
		EnumNctiResult FixPointer(NctiFileInterface*  i_pFI);
		/**
	   * @brief expand the list's size
	   */
		Ncti_Boolean Expand(Ncti_UInteger i_iSizeExpand);
		/**
	   * @brief reset the list's size
	   */
		Ncti_Boolean Finalize();
	protected:
		Ncti_Integer m_iSize;
		NctiStructTagKeyMap* m_paTagKeyMap;
	};
}
NCTI_DATA_DEF(NctiTagKeyMapList)
#endif
