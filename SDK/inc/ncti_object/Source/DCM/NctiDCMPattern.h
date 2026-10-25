#ifndef NctiDCMPattern_H
#define NctiDCMPattern_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMPattern : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMPattern)
	public:
		virtual ~NctiDCMPattern();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_value;
		bool m_default;
		NctiDisplayDCMGeometry* m_pRefGeom;
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_PATTERN; }
	public:
		void SetValue(const double i_value);
		double Value() const;
		bool IsDefault() const { return m_default; }
		bool IsLinearPattern() const;
		NctiVector GetPatDirection() const;
		NctiPosition GetPatAxis() const;
		void SetRefGeom(NctiDisplayDCMGeometry* geom) { m_pRefGeom = geom; }
	};
}
#endif