#ifndef NctiDisplayLoadMoment_H
#define NctiDisplayLoadMoment_H
#include "NctiDisplayLoadObject.h"
#include <NctiMeshManager.h>
namespace NCTI
{
	//力矩
	
	/**
	* @brief The moment object
	*/
	class DECL_NCTI_OBJECT NctiDisplayLoadMoment : public NctiDisplayLoadObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayLoadMoment)
	public:
		virtual ~NctiDisplayLoadMoment();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		virtual EnumNctiResult ActivateData(
			NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		NCTI_VERSION(1, NctiVector, m_Direction, sd_read_vector);
		NCTI_VERSION(1, Ncti_Integer, m_type, sd_read_double);//0:Vertex 1:geometry face;
		NCTI_VERSION(1, Ncti_Double, m_Magnitude, sd_read_double);
	public:
		
		/**
		* @brief Set the direction
		* @param[in] i_dir, the Vector
		*/
		void SetDirection(const NctiVector& i_dir);
		
		/**
		* @brief Set the magnitude
		* @param[in] i_size, the value
		*/
		void SetMagnitude(Ncti_Double i_size);
	public:
		
		/**
		* @brief Get the direction
		* @return the Vector
		*/
		const NctiVector& GetDirection() const { return m_Direction; }
		
		/**
		* @brief Get the magnitude
		* @return the magnitude
		*/
		Ncti_Double GetMagnitude() const { return m_Magnitude; }
	};
}
#endif
