#ifndef NctiDisplayDCMLine_H
#define NctiDisplayDCMLine_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDisplayDCMLine : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMLine)
	public:
		virtual ~NctiDisplayDCMLine();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec2d	m_fbase_point;
		NctiDCMEXVec2d	m_fdirection;
		
	public:
		void InitBasePoint(const NctiDCMEXVec2d& i_pos);
		void InitDirection(const NctiDCMEXVec2d& i_dir);
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_LINE; }
		virtual NctiDCMEXGType type() const override { return EX_LINE; }
		virtual void transform(Ncti_Double i_mat[3][3]) override;
	public:
		const NctiDCMEXVec2d& base_point() const { return m_fbase_point; }
		const NctiDCMEXVec2d& direction() const { return m_fdirection; }
	};
}
#endif