#ifndef NctiToolSelectDo_H
#define NctiToolSelectDo_H
#include "NctiTool.h"
namespace NCTI
{
	class NctiOpSelectDo;
	class NctiDisplayObject;
	class NctiDisplayObjectList;
    class NctiDisplayViewObject;
	/**
	* @brief the system default tool, internal used
	* @details work together with NctiOpSelectDo
	* @see NctiRenderOperator,NctiOpSelectDo
	*/
	class DECL_NCTI NctiToolSelectDo : public NctiTool
	{
		NCTI_TOOL_FUNCTIONS(NctiToolSelectDo)
	public:
		NctiToolSelectDo();
		virtual ~NctiToolSelectDo();
        EnumNctiResult ProcessContextMenu(EnumNctiMenuProcMode i_eProcMode) override;

		virtual void on_l_button_down();
		virtual void on_l_button_up();
		virtual void on_l_button_down_and_move();

		virtual void on_l_button_dbl_clk();
		virtual Ncti_Boolean process_region_selection();
        virtual Ncti_Boolean process_left_click_selection();

		void set_point(const NctiPosition& i_pt);
        void set_drag_point(const NctiPosition& i_hpoint);
		NctiDisplayObject* GetPickDo();
		void invalidate_selection();

	protected:
        void init_operator()override;
		NctiPosition m_DragPoint;
		NctiPosition m_point;
		Ncti_Integer	m_iSelectionMode;
		EnumNctiSelectionShape m_eSelectionShape;
		Ncti_Boolean m_bDrag;
		Ncti_Boolean m_bFocus;
	};
}
#endif // !NctiToolSelectDo_H
