#ifndef NctiDisplayGModelObject_H
#define NctiDisplayGModelObject_H
#include "NctiDisplayObject.h"
#include "NctiPosition.h"
#include "NctiVector.h"
namespace NCTI
{
	class NctiObjectAssist;
	class NctiDisplayDocCustomContainer;
	class NctiDisplayDocImageContainer;
	/**
	* @brief G Model Object class
	* @details Base Class of NctiDisplayModelBody
	* @see NctiDisplayModelBody,NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayGModelObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGModelObject)
	public:
		virtual ~NctiDisplayGModelObject();
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
		/**
	   * @brief Update the display
	   * @details need to implement, override
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult UpdateDisplay();

		/**
	   * @brief call back to do something
	   * @details need to implement, override
	   * @return EnumNctiDoCallbackStatus
	   */
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
	protected:
		/**
	   * @brief internal used
	   */
		virtual void update_link();
	public:
		/**
	   * @brief get the model key
	   * @details all the geometry is in the model key 
	   * @return NctiRenderSegmentItem
	   */
        NCTI::NctiRenderSegmentItem* GetModelKey()const;

        /**
       * @brief new the model key
       */
        NCTI::NctiRenderSegmentItem* NewModelKey(Ncti_Boolean i_openfile = false);

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	protected:
		//no save
		NctiData_NctiHoopsKey*	m_pDataKeyModel;
	};
}
#endif


