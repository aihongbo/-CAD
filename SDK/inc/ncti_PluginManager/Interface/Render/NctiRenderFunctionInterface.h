#ifndef NctiRenderFunctionInterface_H
#define NctiRenderFunctionInterface_H
#include "NctiFunctionInterface.h"
#include "NctiModelFunctionResult.h"
namespace NCTI
{
	class NctiViewerRenderer;
	/**
	* @brief define render function interface
	* @see NctiFunctionInterface
	*/
	class DECL_NCTI_PLUGINMANAGER NctiRenderFunctionInterface : public NctiFunctionInterface
	{
		NCTI_PLUGIN_FUNCTIONS(NctiRenderFunctionInterface)
	public:
		NctiRenderFunctionInterface();
		virtual~NctiRenderFunctionInterface();
		/**
	   * @brief define create viewer interface
	   * @details need to implement, override
	   * @param[in] i_RenderModelType, the render type
	   * @param[out] o_pViewerRenderer, return the render viewer
	   * @return NctiModelFunctionResult
	   */
		virtual NctiModelFunctionResult CreateViewer(
			Ncti_Integer i_RenderModelType, 
			NctiViewerRenderer*& o_pViewerRenderer);

        /**
       * @brief define DeleteViewer
       * @return NctiModelFunctionResult
       */
        virtual NctiModelFunctionResult DeleteViewer(
            NctiViewerRenderer* o_pViewerRenderer);

		/**
	   * @brief define import the mesh interface
	   * @details need to implement, override
	   * @param[in] i_filename
	   * @param[out] o_nodeCoords
	   * @param[out] o_Normals
	   * @param[out] o_elemType
	   * @param[out] o_elemData
	   * @return NctiModelFunctionResult
	   */
        virtual NctiModelFunctionResult import_file(
            const Ncti_Char* i_filename,
            std::vector<Ncti_Float>& o_nodeCoords,
            std::vector<Ncti_Float>& o_Normals,
            std::vector<NctiElementType>& o_elemType,
            std::vector<std::vector<Ncti_UInteger>>& o_elemData);

	};
}
#endif
