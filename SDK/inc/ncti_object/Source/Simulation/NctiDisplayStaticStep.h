#ifndef NctiDisplayStaticStep_H
#define NctiDisplayStaticStep_H
#include "NctiDisplayStep.h"
#include "NctiPhyParaDef.h"
#include "NctiMeshManager.h"
#include "NctiDisplayLoadObject.h"
namespace NCTI
{
	class NctiDisplayLoadObject;
	
	/**
	* @brief Static step object
	*/
	class DECL_NCTI_OBJECT NctiDisplayStaticStep : public NctiDisplayStep
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayStaticStep)
	public:
		virtual ~NctiDisplayStaticStep();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		SimulationStateType GetState() const override;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_VERSION_OBJECT(1, std::vector<NctiDisplayLoadObject*>, m_LoadsVec, sd_read_size);
		NCTI_VERSION_OBJECT(1, std::vector<double>, m_stepValues, sd_read_size);
		NCTI_READ_AND_WRITE_VERSION_FUN(2)
		NCTI_VERSION_OBJECT(2, Ncti_Boolean, m_bNlgeom, sd_read_bool);
		
		std::vector<Ncti_Long> m_LoadsVecIndex;//no save
	public:
		
		/**
		* @brief Add load object
		* @param[in] i_Load, the load object
		*/
		void AddLoads(NctiDisplayLoadObject* i_Load);

		/**
		* @brief Set load objects
		* @param[in] i_LoadVec, the array of load objects
		*/
		void SetLoads(const std::vector<NctiDisplayLoadObject*>& i_LoadVec);
		
		/**
		* @brief Get load objects
		* @param[in] return the array of load objects
		*/
		const std::vector<NctiDisplayLoadObject*>& GetLoads() const { return m_LoadsVec; }

		/**
		* @brief Set load objects
		* @param[in] i_LoadVec, the array of load objects
		*/
		void SetStepValue(const std::vector<double>& i_values);
		
		/**
		* @brief Get load objects
		* @return the array of load objects
		*/
		const std::vector<double>& GetStepValue() const { return m_stepValues; }

		/**
		* @brief Set Nlgeom value
		* @param[in] i_value, Nlgeom value
		*/
		void SetNlgeom(const Ncti_Boolean& i_value);

		/**
		* @brief Get Nlgeom value
		* @return the Nlgeom value
		*/
		const Ncti_Boolean& GetNlgeom() const { return m_bNlgeom; }

		/**
		* @brief Check whether the load exists in the step
		* @param[in] i_Load, The load object
		* @return true or false
		*/
		bool ContainsLoad(const NctiDisplayBasePhysicalObj* i_Load) const;
	public:
		
	};
}
#endif
