#ifndef NctiDCMInequality_H
#define NctiDCMInequality_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
#include "NctiDCMEquation.h"

namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMInequality : public NctiDCMEquation
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMInequality)
	public:
		virtual ~NctiDCMInequality();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double* m_fmax;
		double* m_fmin;
	public:
		void InitInequality(NCTI_DCM_logical e_min, NCTI_DCM_logical e_max, double d1 = 0.0, double d2 = 0.0);
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_e_type identify()	const override { return NCTI_DCM_INEQUALITY; }
		virtual bool check(double i_tol);
	public:
		double max()			const { return *m_fmax; }
		double min()			const { return *m_fmin; }
		int exist_max()			const { return m_fmax != NULL; }
		int exist_min()			const { return m_fmin != NULL; }
	};
}
#endif
