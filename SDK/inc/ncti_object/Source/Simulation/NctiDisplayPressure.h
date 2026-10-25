#ifndef NctiDisplayPressure_H
#define NctiDisplayPressure_H
#include "NctiDisplayLoadObject.h"
#include <NctiMeshManager.h>
namespace NCTI
{
	
	/**
	* @brief The pressure object
	*/
	class DECL_NCTI_OBJECT NctiDisplayPressure : public NctiDisplayLoadObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayPressure)
	public:
		virtual ~NctiDisplayPressure();
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
		NCTI_VERSION(1, Ncti_Integer, m_type, sd_read_double);//0:Vertex 1:geometry face;
		NCTI_VERSION(1, Ncti_Double, m_Magnitude, sd_read_double);
	public:
		
		/**
		* @brief Set magnitude
		* @param[in] i_size
		*/
		void SetMagnitude(Ncti_Double i_size);
		
		/**
		* @brief Get magnitude
		* @return th value
		*/
		Ncti_Double GetMagnitude() const { return m_Magnitude; }
	};
}
#endif
