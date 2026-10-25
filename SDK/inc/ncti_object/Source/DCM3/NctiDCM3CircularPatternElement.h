#ifndef NctiDCM3CircularPatternElement_H
#define NctiDCM3CircularPatternElement_H
#include "dcl_ncti_object.h"
#include "NctiDCM3PatternElement.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	/**
	* @brief circular pattern element
	* @details set circular pattern base data
	* @see NctiDCM3PatternElement
	*/
	class DECL_NCTI_OBJECT NctiDCM3CircularPatternElement : public NctiDCM3PatternElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3CircularPatternElement)
	public:
		virtual ~NctiDCM3CircularPatternElement();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDCMEXVec3d m_base_point;
	public:
		/**
		* @brief initialize circular pattern base point
		* @param[in] i_basePoint, the base point of circular pattern 
		*/
		void InitBasePoint(const NctiDCMEXVec3d& i_basePoint);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_CIRCULAR_PATTERN; } 
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
	public:
		/**
		* @brief get the circular pattern base point
		* @return NctiDCMEXVec3d
		*/
		NctiDCMEXVec3d base_point() const { return m_base_point; }
	};
}
#endif