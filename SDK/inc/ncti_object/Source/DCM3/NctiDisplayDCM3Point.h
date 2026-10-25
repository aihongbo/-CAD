#ifndef NctiDisplayDCM3Point_H
#define NctiDisplayDCM3Point_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCM3Variable;
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Point : public NctiDisplayDCM3Geometry
	{
		friend class NctiDCM3Variable;
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Point)
	public:
		virtual ~NctiDisplayDCM3Point();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec3d m_fvalue;
	public:
		void InitPoint(const NctiDCMEXVec3d& i_pos);
		void InitPoint(double i_xx, double i_yy, double i_zz);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_POINT; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
	public:
		const NctiDCMEXVec3d& value() const { return m_fvalue; }
		void copy(const NctiDisplayDCM3Point& i_pPoint) { m_fvalue = i_pPoint.value(); }
	};
}
#endif