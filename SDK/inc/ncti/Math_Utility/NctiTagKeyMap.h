#ifndef NctiTagKeyMap_H
#define NctiTagKeyMap_H
#include "ncti.h"
namespace NCTI
{
    class NctiRenderGeometryItem;
    struct DECL_NCTI NctiStructTagKeyMap
    {
        void* tagVoid;
        Ncti_Long tag;
        NCTI::NctiRenderGeometryItem* key;
    };
	/**
	* @brief manage tag void , render item and tag id
	* @see NctiTagKeyMapList, NctiStructTagKeyMap
	*/
	class DECL_NCTI NctiTagKeyMap : public NCTI_BASE_CLASS
	{
		NctiTagKeyMap() {}; // disabled
	public:
        NctiTagKeyMap(Ncti_Long i_tag, NCTI::NctiRenderGeometryItem* i_key, void* tagVoid = nullptr);
		NctiTagKeyMap(const NctiTagKeyMap&  i_pTagKeyMap);
		/**
	   * @brief get tag id
	   * @return Ncti_Long
	   */
		Ncti_Long GetTag();
		/**
	   * @brief get render item
	   * @return NctiRenderGeometryItem
	   */
        NCTI::NctiRenderGeometryItem* GetKey();
		/**
	   * @brief get tag void
	   * @return void
	   */
		void* GetTagVoid();
		/**
	   * @brief set tag id
	   */
		void SetTag(Ncti_Long  i_tag);
		/**
	   * @brief set render item
	   */
        void SetKey(NCTI::NctiRenderGeometryItem* i_key);
	protected:
		NctiStructTagKeyMap m_tagTagKeyMap;
	};
}
#endif
