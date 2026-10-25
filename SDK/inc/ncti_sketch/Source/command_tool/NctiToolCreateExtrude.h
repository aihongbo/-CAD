#ifndef NctiToolCreateExtrude_H
#define NctiToolCreateExtrude_H
#include "NctiWinToolSelectDo.h"
#include "dcl_ncti_sketch.h"
namespace NCTI
{
	class NctiDisplayGSketch;
	class NctiDisplayGExtrude;
	class NctiRubberbandExtrude;
	class DECL_NCTI_SKETCH NctiToolCreateExtrude : public NctiWinToolSelectDo
	{
	public:

		/**
		 * Constructs a NctiToolCreateExtrude.
		 */
		NctiToolCreateExtrude(NctiDisplayGExtrude* i_pDoExtrude);

		/**
		 * @nodoc
		 */
		virtual ~NctiToolCreateExtrude();

		/**
		 * Returns EnumNctiResult.
		 */
		void RedrawRubberband(double i_dHeight, bool i_bReverse, bool i_bBothSide, bool i_bUseAngle, double i_dAngle);

		/**
		 * Retruns EnumNctiResult.
		 */
		 //	EnumNctiResult ProcessPickDo();

// 	private:
// 		/**
// 		 * @nodoc
// 		 */
// 		EnumNctiResult process_marker(NctiRenderGeometryItem* i_key);
// 
// 		/**
// 		 * @nodoc
// 		 */
// 		virtual void on_l_button_up();
// 
// 		/**
// 		 * @nodoc
// 		 */
// 		virtual bool process_left_click_selection();
	private:
		NctiRubberbandExtrude* m_pRubberbandExtrude;
		NctiDisplayGSketch* m_pTargetSketch;
	};
}


#endif
