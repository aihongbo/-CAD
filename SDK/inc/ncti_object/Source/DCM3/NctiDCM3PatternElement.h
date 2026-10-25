#ifndef NctiDCM3PatternElement_H
#define NctiDCM3PatternElement_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	/**
	* @brief the base class of pattern elements
	* @details create a pattern
	* @see NctiDisplayDCM3Geometry
	*/
	class DECL_NCTI_OBJECT NctiDCM3PatternElement : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3PatternElement)
	public:
		virtual ~NctiDCM3PatternElement();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	protected:
		double m_value;
		double m_value_offset;
		NctiDCMEXVec3d m_direction;
	public:
		/**
		* @brief initialize pattern value
		* @param[in] i_val, distance value if linear pattern or radiance value if circular pattern
		*/
		void InitValue(double i_val);
		/**
		* @brief initialize pattern direction
		* @param[in] i_dir, pattern direction
		*/
		void InitDirection(const NctiDCMEXVec3d& i_dir);
	public:
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
	public:
		/**
		* @brief get pattern value
		* @return double
		*/
		double value() const { return m_value; }
		/**
		* @brief set pattern value
		* @param[in] i_val, distance value if linear pattern or radiance value if circular pattern
		*/
		void set_value(double i_val);
		/**
		* @brief get pattern offset value
		* @return double
		*/
		double value_offset() const { return m_value_offset; }
		/**
		* @brief get pattern direction
		* @return NctiDCMEXVec3d
		*/
		NctiDCMEXVec3d direction() const { return m_direction; }
		/**
		* @brief set pattern direction
		* @param[in] i_dir, pattern direction
		*/
		void set_direction(const NctiDCMEXVec3d& i_dir); 
	};
}
#endif