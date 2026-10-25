#ifndef NctiDisplayFBStep_H
#define NctiDisplayFBStep_H
#include "NctiDisplayStep.h"
#include "NctiPhyParaDef.h"
#include <NctiMeshManager.h>
namespace NCTI
{
	
	/**
	* @brief The step object
	*/
	class DECL_NCTI_OBJECT NctiDisplayFBStep : public NctiDisplayStep
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayFBStep)
	public:
		virtual ~NctiDisplayFBStep();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_VERSION(1, Ncti_UInteger, m_order, sd_read_size);
		NCTI_VERSION(1, Ncti_Double, m_range_min, sd_read_double);
		NCTI_VERSION(1, Ncti_Double, m_range_max, sd_read_double);
		NCTI_VERSION(1, Ncti_FrequencyMode, m_fmode, sd_read_long);
		NCTI_VERSION(1, std::string, m_eigensolver, sd_read_string);
		NCTI_VERSION(1, std::string, m_acoustic_coupling, sd_read_string);
		NCTI_VERSION(1, std::string, m_normalization, sd_read_string);
	public:
		
		/**
		* @brief set the order of the mode
		* @param[in] order, the order of the mode
		*/
		void SetOrder(const Ncti_UInteger order);
		
		/**
		* @brief set the frequency range
		* @param[in] min, the lower limit of frequency
		* @param[in] max, the frequency upper limit
		*/
		void SetRange(const Ncti_Double min, const Ncti_Double max);
		
		/**
		* @brief set the eigensolver
		* @param[in] eigensolver, the eigensolver
		*/
		void SetEigensolver(const std::string& eigensolver);
		
		/**
		* @brief set the acoustic coupling
		* @param[in] coupling, the acoustic coupling
		*/
		void SetAcousticCoupling(const std::string& coupling);
		
		/**
		* @brief set the normalization
		* @param[in] normalization, the normalization
		*/
		void SetNormalization(const std::string& normalization);
	public:
		
		/**
		* @brief get the frequency mode
		* @return the frequency mode
		*/
		Ncti_FrequencyMode GetFrequencyMode() const { return m_fmode; }
		
		/**
		* @brief get the order of the mode
		* @return the order of the mode
		*/
		Ncti_UInteger GetOrder() const { return m_order; }
		
		/**
		* @brief get the frequency range
		* @param[out] min, the lower limit of frequency
		* @param[out] max, the frequency upper limit
		*/
		void GetRange(Ncti_Double& o_min, Ncti_Double& o_max) const { o_min = m_range_min; o_max = m_range_max; }
		
		/**
		* @brief get the eigensolver
		* @return the eigensolver
		*/
		const std::string& GetEigensolver() const { return m_eigensolver; }
		
		/**
		* @brief get the acoustic coupling
		* @return the acoustic coupling
		*/
		const std::string& GetAcousticCoupling() const { return m_acoustic_coupling; }
		
		/**
		* @brief get the normalization
		* @return the normalization
		*/
		const std::string& GetNormalization() const { return m_normalization; }
	};
}
#endif
