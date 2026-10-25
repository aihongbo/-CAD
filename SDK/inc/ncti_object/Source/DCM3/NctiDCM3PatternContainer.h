#ifndef NctiDCM3PatternContainer_H
#define NctiDCM3PatternContainer_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3PatternElement.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDCM3PatternContainer : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3PatternContainer)
	public:
		virtual ~NctiDCM3PatternContainer();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		std::vector <NctiDCM3PatternElement*> m_members;
	public:
		virtual ncti_DCM3_g_type identify() const override { return NCTI_DCM3_PATTERN_ARRAY; }
		virtual std::string describe() const override;
	public:
		void addMember(NctiDCM3PatternElement* i_pElement);
		NctiDCM3PatternElement* getMember(int i_index) const { return m_members[i_index]; }
		int count() const { return m_members.size(); }
	};
}
#endif