#ifndef NctiDCMSet_H
#define NctiDCMSet_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCMSet : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMSet)
	public:
		virtual ~NctiDCMSet();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			std::vector<NctiDisplayDCMGeometry*> m_fmembers;
	
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_SET; }
		virtual NctiDCMEXGType type() const override { return EX_SET; }
		virtual void transform(double i_mat[3][3]) override;
	public:
		int add_to_set(NctiDisplayDCMGeometry* i_gn);
		int remove_from_set(NctiDisplayDCMGeometry* i_gn);
		int num() const { return m_fmembers.size(); }
		NctiDisplayDCMGeometry* member(size_t i_index) { return m_fmembers[i_index]; }
	};
}
#endif