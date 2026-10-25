#ifndef NctiDisplayDCM3Line_H
#define NctiDisplayDCM3Line_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Line : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Line)
	public:
		virtual ~NctiDisplayDCM3Line();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec3d	m_fbase_point;
		NctiDCMEXVec3d	m_fdirection;
	public:
		void InitBasePoint(const NctiDCMEXVec3d& i_pos);
		void InitDirection(const NctiDCMEXVec3d& i_dir);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_LINE; }
		virtual void transform(Ncti_Double i_mat[4][4]) override;
		virtual std::string describe() const override;
	public:
		const NctiDCMEXVec3d& base_point() const { return m_fbase_point; }
		const NctiDCMEXVec3d& direction() const { return m_fdirection; }
		void copy(NctiDisplayDCM3Line& i_pLine) { m_fbase_point = i_pLine.base_point(); m_fdirection = i_pLine.direction(); }
	};
}
#endif