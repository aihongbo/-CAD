#ifndef NctiFuntionInterfaceManager_H
#define NctiFuntionInterfaceManager_H
#include "ncti_dcl_PluginManager.h"
#include "ncti_base.h"
#include <vector>
namespace NCTI
{
	class NctiRenderFunctionInterface;
	class NctiFunctionInterface;
	class NctiDocument;
	/**
	* @brief manager all function interface
	* @see NctiPCFunctionInterface, NctiRenderFunctionInterface, NctiFunctionInterface
	*/
	class DECL_NCTI_PLUGINMANAGER NctiFuntionInterfaceManager
	{
	public:
		NctiFuntionInterfaceManager();
		~NctiFuntionInterfaceManager();
		/**
	   * @brief Initialization during load all the plugins
	   */
		void InitPlugin();
		/**
	   * @brief Release during unload all the plugin
	   */
		void ReleasePlugin();
		/**
	   * @brief Initialization Document during create Document
	   */
		void InitDocument(NctiDocument* i_pDocument);
		/**
	   * @brief Release Document during Remove Document
	   */
		void ReleaseDocument(NctiDocument* i_pDocument);

		/**
	   * @brief get all other function interface
	   * @return const std::vector<NctiFunctionInterface*>&
	   */
		const std::vector<NctiFunctionInterface*>& GetOtherFunctionInterface();
	private:
        friend class NctiFunctionInterface;
        void AddOtherFunctionInterface(NctiFunctionInterface* i_pFunctionInterface);
		std::vector<NctiFunctionInterface*> m_OhterFunctionInterfaceVec;
	};
}
#endif
