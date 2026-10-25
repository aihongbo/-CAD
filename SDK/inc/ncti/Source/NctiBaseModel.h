#ifndef NctiBaseModel_H
#define NctiBaseModel_H
#include "ncti.h"
#include "string"
namespace NCTI
{
	class NctiBaseDB;
	class NctiManager;
	class NctiBaseView;
	class NctiDocument;
	class NctiBodyLifeCycleManager;
	class NctiDisplayObject;
	class NctiBody;
	class NctiRenderSegmentItem;
	/**
	* @brief one document has one base model
	* @details it can help you to get all the object or data
	* @see NctiManager,NctiBaseView,NctiDocument
	*/
	class DECL_NCTI NctiBaseModel : public NCTI_BASE_CLASS
	{
	public:
		NctiBaseModel();
		virtual ~NctiBaseModel();
		/**
	   * @brief get manager by manager type
	   * @details support all the manager,such as command manager, history manager...
	   * @param[in] i_iManagerType, the manager of type
	   * @return NctiManager
	   */
		NctiManager* GetManager(Ncti_Integer i_iManagerType);
		/**
	   * @brief get the root render key 
	   * @details it use to save model key ,the model key has many geometry
	   * @return NctiRenderSegmentItem
	   */
        NCTI::NctiRenderSegmentItem* GetRootKey();
		/**
	   * @brief get first base view
	   * @details get all base view by NctiBaseView's Next()
	   * @return NctiBaseView
	   */
		NctiBaseView* GetFirstBaseView();
		/**
	   * @brief add base view to base model
	   * @details get all base view by NctiBaseView's Next()
	   * @return NctiBaseView
	   */
        NctiBaseView* AddBaseView(const std::string& name = "");
		/**
	   * @brief get last base view
	   * @return NctiBaseView
	   */
		NctiBaseView* get_last_view();
		/**
	   * @brief refresh all the base views
	   */
		void RefreshViews();

        /**
        * @brief SetPreviewMode
        */
        void SetPreviewMode(Ncti_Boolean i_en);

		/**
	   * @brief set active base view
	   * @param[in] i_pActiveView
	   */
		void SetActiveBaseView(NctiBaseView* i_pActiveView);
		/**
	   * @brief get active base view
	   * @return NctiBaseView
	   */
        NctiBaseView* GetActiveBaseView()const;
		/**
	   * @brief remove the base view
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean RemoveBaseView(NctiBaseView *i_pTarget);
		/**
	   * @brief remove the document
	   */
		void SetDocument(NctiDocument* i_pDocument);
		/**
	   * @brief get the document
	   * @return NctiDocument
	   */
		NctiDocument* GetDocument() { return m_Document; }
		/**
	   * @brief remove the base view by name
	   * @param[in] i_name, the base view
	   * @return NctiDocument
	   */
		NctiBaseView* GetBaseViewByName(const char* i_name);
		/**
	   * @brief get the body life cycle manager
	   * @return NctiBodyLifeCycleManager
	   */
		NctiBodyLifeCycleManager* GetBodyLifeCycleManager() { return m_BodyLifeCycleManager; }
		/**
	   * @brief Deallocate i_pDoTarget
	   * @param[in] i_pDoTarget, remove the display object
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean Deallocate(NctiDisplayObject*& i_pDoTarget);
		/**
	   * @brief Deallocate i_pDoTarget
	   * @param[in] i_pDoTarget, remove the body object
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean Deallocate(NctiBody*& i_pDoTarget);

	public:
		/**
	   * @brief internal used
	   */
		void NotifySelectionDataChanged();
		/**
	   * @brief internal used
	   */
		void NotifyDocDeletion();

	private:
		Ncti_Integer m_iNumManager;
		NctiManager** m_paManager;
        NCTI::NctiRenderSegmentItem* m_keyRoot;
		NctiBaseView* m_pFirstView;
		NctiBaseView* m_pActiveView;
		Ncti_Boolean m_bTerminationNotified;
		NctiDocument* m_Document;
		NctiBodyLifeCycleManager* m_BodyLifeCycleManager;
		
	};
}

#endif // !NctiBaseModel_H
