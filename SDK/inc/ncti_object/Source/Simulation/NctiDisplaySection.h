#ifndef NctiDisplaySection_H
#define NctiDisplaySection_H
#include "NctiDisplaySimulationObject.h"
#include "NctiPhyParaDef.h"
#include <NctiMeshManager.h>
namespace NCTI
{	
	/**
	* @brief The section object
	*/
	class NctiDisplaySet;
	class NctiDisplayMaterialAttribute;
	class DECL_NCTI_OBJECT NctiDisplaySection : public NctiDisplaySimulationObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySection)
	public:
		virtual ~NctiDisplaySection();
	public:
		virtual void Init();
		void HighlightSegment(bool i_bOnOff)override;
		SimulationStateType GetState() const override;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	protected:
		NCTI_VERSION_OBJECT(1, NctiDisplaySet*, m_pSet, sd_read_long);
		NCTI_VERSION_OBJECT(1, NctiDisplayMaterialAttribute*, m_pMaterial, sd_read_long);
		NCTI_VERSION_OBJECT(1, std::string, m_sType, sd_read_long);
		NCTI_VERSION_OBJECT(1, Ncti_Double, m_dShellThickness, sd_read_long);
		NCTI_VERSION_OBJECT(1, Ncti_Double, m_dShellSampling, sd_read_long);

	public:

		/**
		* @brief Set set
		* @param[in] pSet, the set
		*/
		void SetSet(NctiDisplaySet* pSet);

		/**
		* @brief Set materia
		* @param[in] pMaterial, the materia
		*/
		void SetMaterial(NctiDisplayMaterialAttribute* pMaterial);

		/**
		* @brief Set section type 
		* @param[in] sType, the section type  ("SHELL"; "SOLID";"BEAM"; )
		*/
		void SetSectionType(const std::string& sType);

		/**
		* @brief Set shell thickness
		* @param[in] the thickness
		*/
		void SetShellThickness(const Ncti_Double&);

		/**
		* @brief Set shell sampling
		* @param[in] the sampling
		*/
		void SetShellSampling(const Ncti_Double&);

		/**
		* @brief Get set
		* @return the set
		*/
		NctiDisplaySet* GetSet();

		/**
		* @brief Get materia
		* @return the materia
		*/
		NctiDisplayMaterialAttribute* GetMaterial();

		/**
		* @brief Get section type 
		* @return the section type  
		*/
		const std::string& GetSectionType();

		/**
		* @brief Get shell thickness
		* @return the thickness
		*/
		const Ncti_Double& GetShellThickness();

		/**
		* @brief Get shell sampling
		* @return the sampling
		*/
		const Ncti_Double& GetShellSampling();
	};
}
#endif
