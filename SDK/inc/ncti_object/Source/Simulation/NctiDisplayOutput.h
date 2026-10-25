#ifndef NctiDisplayOutput_H
#define NctiDisplayOutput_H
#include "NctiDisplaySimulationObject.h"
#include "NctiPhyParaDef.h"
#include <NctiMeshManager.h>
namespace NCTI
{
	//输出
	
	/**
	* @brief The output object
	*/
	class DECL_NCTI_OBJECT NctiDisplayOutput : public NctiDisplaySimulationObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayOutput)
	public:
		virtual ~NctiDisplayOutput();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		NCTI_VERSION(1, Ncti_OutputType, m_OutputType, sd_read_long);
		NCTI_VERSION(1, std::vector<std::string>, m_NodeVars, sd_read_packed);
		NCTI_VERSION(1, std::vector<std::string>, m_ElementVars, sd_read_packed);
		std::map<std::string, std::string> m_OutputOptionMap; 
		std::map<std::string, std::string> m_NodeOptionMap;
		std::map<std::string, std::string> m_ElementOptionMap;

		//no save
		Ncti_Integer m_FileVersion_m_OutputOptionMap = sd_read_packed;
		Ncti_Integer m_FileVersion_m_NodeOptionMap = sd_read_packed;
		Ncti_Integer m_FileVersion_m_ElementOptionMap = sd_read_packed;

	public:
		
		/**
		* @brief Set step output type
		* @param[in] type
		*/
		void SetStepOutputType(const Ncti_OutputType type);

		/**
		* @brief Set node variables
		* @param[in] vars, the vecter of the variables
		*/
		void SetNodeVariables(const std::vector<std::string>& vars);

		/**
		* @brief Set element variables
		* @param[in] vars, the vecter of the variables
		*/
		void SetElementVariables(const std::vector<std::string>& vars);

		/**
		* @brief Set output options
		* @param[in] options, the map of the options
		*/
		void SetOutputOptions(const std::map<std::string, std::string>& options);

		/**
		* @brief Set node options
		* @param[in] options, the map of the options
		*/
		void SetNodeOptions(const std::map<std::string, std::string>& options);

		/**
		* @brief Set element options
		* @param[in] options, the map of the options
		*/
		void SetElementOptions(const std::map<std::string, std::string>& options);
	public:
		/**
		* @brief Set step output type
		* @return the type
		*/
		Ncti_OutputType GetOutputType() const { return m_OutputType; }

		/**
		* @brief Set node variables
		* @return the vecter of the variables
		*/
		const std::vector<std::string> GetNodeVariables() const { return m_NodeVars; }

		/**
		* @brief Set element variables
		* @return the vecter of the variables
		*/
		const std::vector<std::string> GetElementVariables() const { return m_ElementVars; }

		/**
		* @brief Set output options
		* @return the map of the options
		*/
		const std::map<std::string, std::string> GetOutputOptions() const { return m_OutputOptionMap; }

		/**
		* @brief Set node options
		* @return the map of the options
		*/
		const std::map<std::string, std::string> GetNodeOptions() const { return m_NodeOptionMap; }

		/**
		* @brief Set element options
		* @return the map of the options
		*/
		const std::map<std::string, std::string> GetElementOptions() const { return m_NodeOptionMap; }

	};
}
#endif
