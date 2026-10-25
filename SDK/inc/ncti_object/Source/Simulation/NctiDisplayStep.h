#ifndef NctiDisplayStep_H
#define NctiDisplayStep_H
#include "NctiDisplaySimulationObject.h"
#include "NctiPhyParaDef.h"
#include <NctiMeshManager.h>
#include "NctiDisplaySinglePointConstraint.h"
#include "NctiDisplayOutput.h"
namespace NCTI
{
	class NctiDisplayBasePhysicalObj;
	
	/**
	* @brief Step object
	*/
	class DECL_NCTI_OBJECT NctiDisplayStep : public NctiDisplaySimulationObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayStep)
	public:
		virtual ~NctiDisplayStep();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		SimulationStateType GetState() const override;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	protected:
		NCTI_VERSION_OBJECT(1, std::vector<NctiDisplaySinglePointConstraint*>, m_SPCVec, sd_read_size);
		NCTI_VERSION_OBJECT(1, std::vector<NctiDisplayOutput*>, m_OutputVec, sd_read_size);

		std::vector<Ncti_Long> m_SPCVecIndex;//no save
		std::vector<Ncti_Long> m_OutputVecIndex;//no save
	public:
		
		/**
		* @brief Add constraint object
		* @param[in] i_pSPC, constraint object
		*/
		void AddSPC(NctiDisplaySinglePointConstraint* i_pSPC);

		/**
		* @brief Add output object
		* @param[in] i_Output, output object
		*/
		void AddOutputs(NctiDisplayOutput* i_Output);
		
		/**
		* @brief Set constraint objects
		* @param[in] i_pSPCVec, The array constraint objects
		*/
		void SetSPC(const std::vector<NctiDisplaySinglePointConstraint*>& i_pSPCVec);

		/**
		* @brief Set output objects
		* @param[in] i_OutputVec, The array output objects
		*/
		void SetOutputs(const std::vector<NctiDisplayOutput*>& i_OutputVec);

		/**
		* @brief Get constraint objects
		* @return The array constraint objects
		*/
		const std::vector<NctiDisplaySinglePointConstraint*>& GetSPCs() const { return m_SPCVec; }

		/**
		* @brief Get output objects
		* @return The array output objects
		*/
		const std::vector<NctiDisplayOutput*>& GetOutputs() const { return m_OutputVec; }
		
		/**
		* @brief Check whether the constraint exists in the step
		* @param[in] i_pSPC, The constraint object
		* @return true or false
		*/
		bool ContainsSPC(const NctiDisplaySinglePointConstraint* i_pSPC) const;

		/**
		* @brief Check whether the output exists in the step
		* @param[in] i_Output, The output object
		* @return true or false
		*/
		bool ContainsOutput(const NctiDisplayOutput* i_Output) const;
	public:
		
	};
}
#endif
