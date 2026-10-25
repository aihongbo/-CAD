#ifndef NctiDisplayConcentratedForces_H
#define NctiDisplayConcentratedForces_H
#include "NctiDisplayLoadObject.h"
namespace NCTI
{
	//集中力	
	/**
	* @brief the concentration
	*/
	class DECL_NCTI_OBJECT NctiDisplayConcentratedForces : public NctiDisplayLoadObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayConcentratedForces)
	public:
		virtual ~NctiDisplayConcentratedForces();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		virtual EnumNctiResult ActivateData(
			NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		//physical parameter
		NCTI_VERSION(1, NctiVector, m_Direction, sd_read_vector);//the load direction in the cid frame
		NCTI_VERSION(1, Ncti_Double, m_Magnitude, sd_read_double);//the load's magnitude
	public:
		
		/**
		* @brief set the direction of the force
		* @param[in] i_dir, the direction
		*/
		void SetDirection(const NctiVector& i_dir);
		
		/**
		* @brief set the magnitude
		* @param[in] i_size, the direction
		*/
		void SetMagnitude(Ncti_Double magnitude);
	public:
		/**
		* @brief get the direction of the force
		* @return the direction
		*/
		const NctiVector& GetDirection() const { return m_Direction; }
		
		/**
		* @brief set the magnitude
		* @return the direction
		*/
		Ncti_Double GetMagnitude() const { return m_Magnitude; }
	};
}
#endif
