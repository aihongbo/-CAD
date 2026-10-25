#ifndef NctiDCM3EqualDistance_H
#define NctiDCM3EqualDistance_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDCMEXVec3d;
	/**
	* @brief euqal distance constraint
	* @details set euqal distance constraint data
	* @see NctiDisplayDCM3Geometry
	*/
	class DECL_NCTI_OBJECT NctiDCM3EqualDistance : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3EqualDistance)
	public:
		virtual ~NctiDCM3EqualDistance();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_fdistance;
		double m_distance_offset;
	public:
		/**
		* @brief initialize eauql distance value
		* @param[in] i_distance, eauql distance value
		*/
		void InitDistance(Ncti_Double i_distance);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_EQUAL_DISTANCE; }
		virtual std::string describe() const override;
		virtual void ResetLastTransform() override;
	public:
		/**
		* @brief get equal distance value
		* @return double
		*/
		double distance() const { return m_fdistance; }
		/**
		* @brief set eauql distance value
		* @param[in] i_distance, eauql distance value
		*/
		void set_distance(double i_distance);
		/**
		* @brief get offset distance value from last change
		* @return double
		*/
		double distance_offset() const { return m_distance_offset; }
	};
}
#endif