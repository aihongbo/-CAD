#ifndef NctiDisplayDCMPoint_H
#define NctiDisplayDCMPoint_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDisplayDCMPoint : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMPoint)
	public:
		virtual ~NctiDisplayDCMPoint();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec2d m_fvalue;
	public:
		void InitPoint(const NctiDCMEXVec2d& i_pos);
	public:
		virtual std::string describe() const override;
		virtual void transform(double i_mat[3][3]) override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_POINT; }
		virtual NctiDCMEXGType type() const override { return EX_POINT; }
	public:
		const NctiDCMEXVec2d& value() { return m_fvalue; }
	};
}
#endif