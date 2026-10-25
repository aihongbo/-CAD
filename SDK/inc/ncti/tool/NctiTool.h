#ifndef NctiTool_H
#define NctiTool_H
#include "ncti.h"
#include "NctiPosition.h"
#include "NctiGridPickSet.h"

#define NCTI_TOOL_FUNCTIONS( TOOL_NAME )	\
public:\
	static const char* ID;\
	virtual const char* TypeName(){ return TOOL_NAME::ID; };\
	virtual Ncti_Boolean		IsTypeName( const char *sTypeName );


#define NCTI_TOOL_DEF( TOOL_NAME, TOOL_NAME_DERIVED_FROM, IDENTITY_STRING ) \
	const char* TOOL_NAME::ID = IDENTITY_STRING;\
	Ncti_Boolean TOOL_NAME::IsTypeName( const char *sTypeName )\
{\
	if ( strcmp( TOOL_NAME::ID, sTypeName ) == 0 )\
{\
	return true;\
}\
	return TOOL_NAME_DERIVED_FROM::IsTypeName( sTypeName );\
}

namespace NCTI
{
    class NctiBaseView;
    class NctiRenderOperator;
    class NctiDisplayObject;
    class NctiRenderGeometryItem;
    class NctiRenderSegmentItem;
    class NctiRenderGeometryItem;
	/**
	* @brief The Base Tool Class
	* @details work together with NctiRenderOperator,you can create your own tools
	* @see NctiRenderOperator
	*/
    class DECL_NCTI NctiTool : public NCTI_BASE_CLASS
    {
    public:
        NctiTool();
        virtual	~NctiTool();
		/**
	   * @brief get the type name
	   * @details need to implement, override
	   * @return const char*
	   */
		virtual const char* TypeName() = 0;
		/**
	   * @brief check if the tool type is correct
	   * @param[in] i_sTypeName, the type of tool object
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsTypeName(const char* i_psName) = 0;
		/**
	   * @brief get the base view in tool
	   * @return NctiBaseView
	   */
        NctiBaseView* GetBaseView();
		/**
	   * @brief update all the base view
	   */
        void UpdateAllView();
		/**
	   * @brief context menu
	   * @details need to implement, override
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult ProcessContextMenu(EnumNctiMenuProcMode i_eProcMode);
		/**
	   * @brief ProcessESC
	   * @details need to implement, override
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult ProcessESC();
		/**
	   * @brief ProcessUndo
	   * @details need to implement, override
	   * @return EnumNctiResult
	   */
		virtual void ProcessUndo() {}
		/**
	   * @brief ProcessRedo
	   * @details need to implement, override
	   * @return EnumNctiResult
	   */
		virtual void ProcessRedo() {}
		/**
	   * @brief ProcessPreUndo
	   * @details need to implement, override
	   * @return EnumNctiResult
	   */
		virtual void ProcessPreUndo() {}
		/**
	   * @brief ProcessPreRedo
	   * @details need to implement, override
	   * @return EnumNctiResult
	   */
		virtual void ProcessPreRedo() {}
		/**
	   * @brief active tool in a base view, internal used
	   */
        void Activate(NctiBaseView* i_pBaseView);
		/**
	   * @brief set move pos
	   */
        void SetMovePos(NctiPosition pos);
		/**
	   * @brief pick point on base view, internal used
	   */
        void PickPointOnWindow();
		/**
	   * @brief preview point on base view, internal used
	   */
        NctiRenderGeometryItem* PreviewOnWindow(NctiRenderSegmentItem** ins=nullptr, std::set<NctiGridPickSet>* cells=nullptr);

		/**
	   * @brief internal used
	   */
        void ResetView();
		/**
	   * @brief internal used
	   */
        virtual void Inactivate();
		/**
	   * @brief internal used
	   */
        virtual void NotifyViewDeletion(NctiBaseView* i_pBaseView);
    protected:
		/**
	   * @brief internal used
	   */
        virtual void init_operator();
		/**
	   * @brief internal used
	   */
        void delete_operator();
	protected:
        NctiBaseView* m_pBaseView{ nullptr };
        NctiRenderOperator* m_pHBaseOperator{ nullptr };
        NCTI::NctiRenderGeometryItem* m_lKeySelected{ nullptr };
        NctiDisplayObject* m_pDoSelected{ nullptr };
        NctiPosition m_movePos{ 0,0,0 };
        NctiPosition m_prevMove;
    };
}
#endif
