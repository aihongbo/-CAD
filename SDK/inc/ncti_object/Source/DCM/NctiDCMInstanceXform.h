#ifndef NctiDCMInstanceXform_H
#define NctiDCMInstanceXform_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDCMInstanceXform : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMInstanceXform)
	public:
		virtual ~NctiDCMInstanceXform();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify()	const override { return NCTI_DCM_POINT; }
		virtual NctiDCMEXGType type() const override { return EX_INSTANCE; }
		virtual void transform(Ncti_Double i_mat[3][3]) override;
	public:
		void get_transform(Ncti_Double o_mat[3][3]);
		void Set_transform(const Ncti_Double i_mat[3][3]);
		void Set_transform(const NctiDCMEXVec2d& i_vec);
	};
}
#endif