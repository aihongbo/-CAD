#ifndef NctiDisplayDCMSpline_H
#define NctiDisplayDCMSpline_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
#include "NctiDisplayDCMPoint.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDisplayDCMSpline : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMSpline)
	public:
		virtual ~NctiDisplayDCMSpline();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		//Two ways of conditions for interpolation/control spline
		std::vector<NctiDisplayDCMPoint*> m_points;
		std::vector<Ncti_Double> m_fpositions;
		ncti_DCM_bs_periodicity m_fperiodicity;
		ncti_DCM_bs_data m_curBSData;
		// We may have a second definition of the spline for use in move_and_evaluate
		ncti_DCM_bs_data* m_fafter_data;
	public:
		void SetPoints(const std::vector<NctiDisplayDCMPoint*>& i_points);
		void SetPostions(const std::vector<Ncti_Double>& i_fpositions);
		void UpdatePositions(const std::vector<Ncti_Double>& i_fpositions);
		void SetPer(ncti_DCM_bs_periodicity i_fperiodicity);
		void SetSplineData(ncti_DCM_bs_data& i_bsdata);
		const ncti_DCM_bs_data& GetSplineData() const;
	public:
		virtual std::string describe() const override;
		virtual void transform(Ncti_Double i_mat[3][3]) override; // Only called for rigid splines
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_SPLINE; }
		virtual NctiDCMEXGType type() const override { return EX_SPLINE; }
	public:
		ncti_DCM_bs_periodicity periodicity() const { return m_fperiodicity; }
		const std::vector<Ncti_Double>& positions() const { return m_fpositions; }
		const std::vector<NctiDisplayDCMPoint*>& points() const { return m_points; }

		// Functions to allow 2 definitions of the spline to be held in application memory at once,
		// for use when using move_and_evaluate to change the definition - so the "before" and "after"
		// definitions may have different number of control points, etc.
		ncti_DCM_bs_data* after_spline_data() const { return m_fafter_data; }
		void set_after_spline_data(ncti_DCM_bs_data* i_asd) { m_fafter_data = i_asd; }
	};
}
#endif