#ifndef NctiDCMPattern2D_H
#define NctiDCMPattern2D_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMPattern2D : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMPattern2D)
	public:
		virtual ~NctiDCMPattern2D();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_values[2];
		bool m_default;
		NctiDisplayDCMGeometry* m_pDirGeom1;
		NctiDisplayDCMGeometry* m_pDirGeom2;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_PATTERN2D; }
	public:
		void SetDirections(NctiDisplayDCMGeometry* i_pDir1, NctiDisplayDCMGeometry* i_pDir2);
		void GetDirections(NctiDisplayDCMGeometry* o_pDir1, NctiDisplayDCMGeometry* o_pDir2) const;
		void GetDirections(NctiVector& o_pDir1, NctiVector& o_pDir2) const;
		void SetValues(const double i_value1, const double i_value2);
		const double* Values();
		bool IsDefault() const { return m_default; }
	};
}
#endif