#ifndef NctiDisplayBuckleStep_H
#define NctiDisplayBuckleStep_H
#include "NctiDisplayFBStep.h"
#include "NctiPhyParaDef.h"
#include <NctiMeshManager.h>
namespace NCTI
{
	class NctiDisplayLoadObject;
	//屈曲分析步	
	/**
	* @brief The buckle step object
	*/
	class DECL_NCTI_OBJECT NctiDisplayBuckleStep : public NctiDisplayFBStep
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayBuckleStep)
	public:
		virtual ~NctiDisplayBuckleStep();
	public:
		virtual void Init();
		SimulationStateType GetState() const override;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_VERSION_OBJECT(1, std::vector<NctiDisplayLoadObject*>, m_LoadsVec, sd_read_size);

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
		const std::vector<NctiDisplayLoadObject*>& GetLoads() const { return m_LoadsVec; }

		/**
		* @brief Check whether the load exists in the step
		* @param[in] i_Load, The load object
		* @return true or false
		*/
		bool ContainsLoad(const NctiDisplayBasePhysicalObj* i_Load) const;
	};
}
#endif
