#ifndef NctiDisplayDCMParabola_H
#define NctiDisplayDCMParabola_H
#include "dcl_ncti_object.h"
#include "NctiDCMParametric.h"
#include "NctiDisplayDCMPoint.h"
#include "NctiDCMDef.h"
#include <ostream>
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDisplayDCMParabola : public NctiDCMParametric
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMParabola)
	public:
		virtual ~NctiDisplayDCMParabola();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

		NctiDisplayDCMPoint* m_ffocus_pt;
		NctiDCMEXVec2d m_ffocus_pos;
		NctiDisplayDCMPoint* m_fbase_pt;
		NctiDCMEXVec2d m_fbase_pos;
	public:
		void InitParabola(double i_lower, double i_upper, NctiDisplayDCMPoint* i_focus, NctiDisplayDCMPoint* i_base);
	public:
		virtual std::string describe() const override;
		virtual NctiDCMEXVec2d position(double i_param) override;
		virtual NctiDCMEXVec2d first_der(double i_param) override;
		virtual NctiDCMEXVec2d second_der(double i_param) override;
		virtual void transform(double i_mat[3][3]) override;
		virtual NctiDCMEXGType type() const override { return EX_PARAMETRIC; }

	public:
		NctiDCMEXVec2d direction()		const { return (m_ffocus_pos - m_fbase_pos).normal(); }
		NctiDCMEXVec2d base()			const { return m_fbase_pos; }
		NctiDCMEXVec2d focus()			const { return m_ffocus_pos; }
		NctiDisplayDCMPoint* base_pt()	const { return m_fbase_pt; }
		NctiDisplayDCMPoint* focus_pt()	const { return m_ffocus_pt; }
		// Regenerate curve in case supports (dependent geometry) have moved
		void regenerate(double i_matb[3][3], double i_matf[3][3]);
		// Restore the supports to their original position
		void restore_supports();
	};
}
#endif