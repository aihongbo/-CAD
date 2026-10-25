#ifndef NctiDisplaySinglePointConstraint_H
#define NctiDisplaySinglePointConstraint_H
#include "NctiDisplayBasePhysicalObj.h"
namespace NCTI
{	
	/**
	* @brief Constraint object
	*/
	class DECL_NCTI_OBJECT NctiDisplaySinglePointConstraint : public NctiDisplayBasePhysicalObj
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySinglePointConstraint)
	public:
		virtual ~NctiDisplaySinglePointConstraint();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		virtual EnumNctiResult ActivateData(
			NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		NCTI_VERSION(1, std::vector<Ncti_UInteger>, m_ComponentsVec, sd_read_size);
		NCTI_VERSION(1, std::vector<Ncti_Double>, m_SizeRangeVec, sd_read_size);
	public:
		
		/**
		* @brief Set degree of freedom
		* @param[in] iComponentsVec, The six degree of freedom (1,2,3,4,5,6; 1,4;...)
		*/
		void SetComponentsVec(const std::vector<Ncti_UInteger>& iComponentsVec);
		
		/**
		* @brief The DOF is prescribed to value
		* @param[in] dSizeRangeVec, The six degree of freedom value
		*/
		void SetSizeRangeVec(const std::vector<Ncti_Double>& dSizeRangeVec);
	public:
		
		/**
		* @brief Get the degree of freedom
		* @return The array of degree of freedom
		*/
		const std::vector<Ncti_UInteger>& GetComponentsVec() { return m_ComponentsVec; }
		
		/**
		* @brief Get the DOF is prescribed to value
		* @return The array of values
		*/
		const std::vector<Ncti_Double>& GetSizeRangeVecVec() { return m_SizeRangeVec; }
	};
}
#endif
