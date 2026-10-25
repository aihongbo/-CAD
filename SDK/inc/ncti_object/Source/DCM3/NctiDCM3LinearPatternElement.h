#ifndef NctiDCM3LinearPatternElement_H
#define NctiDCM3LinearPatternElement_H
#include "dcl_ncti_object.h"
#include "NctiDCM3PatternElement.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	/**
	* @brief linear pattern element
	* @details create a linear pattern
	* @see NctiDCM3PatternElement
	*/
	class DECL_NCTI_OBJECT NctiDCM3LinearPatternElement : public NctiDCM3PatternElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3LinearPatternElement)
	public:
		virtual ~NctiDCM3LinearPatternElement();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_LINEAR_PATTERN; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
	};
}
#endif