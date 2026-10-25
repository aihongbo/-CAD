#ifndef NctiRenderFunction_H
#define NctiRenderFunction_H
#include "ncti_dcl_PluginManager.h"
#include "NctiModelFunctionResult.h"
namespace NCTI
{
	class NctiViewerRenderer;
	class DECL_NCTI_PLUGINMANAGER NctiRenderFunction
	{
	public:
		/**
	   * @brief call create viewer interface
	   * @param[in] i_RenderModelType, the render type
	   * @param[out] o_pViewerRenderer, return the render viewer
	   * @return NctiModelFunctionResult
	   */
		static NctiModelFunctionResult CreateViewer(Ncti_Integer i_RenderModelType, NctiViewerRenderer*& o_pViewerRenderer);

        /**
       * @brief call DeleteViewer
       * @return NctiModelFunctionResult
       */
        static NctiModelFunctionResult DeleteViewer(NctiViewerRenderer* o_pViewerRenderer);
		/**
	   * @brief call import the mesh interface
	   * @param[in] i_filename
	   * @param[out] o_nodeCoords
	   * @param[out] o_Normals
	   * @param[out] o_elemType
	   * @param[out] o_elemData
	   * @return NctiModelFunctionResult
	   */
        static NctiModelFunctionResult import_file(
            const Ncti_Char* i_filename,
            std::vector<Ncti_Float>& o_nodeCoords,
            std::vector<Ncti_Float>& o_Normals,
            std::vector<NctiElementType>& elemType,
            std::vector<std::vector<Ncti_UInteger>>& elemData);
	};
}
#endif
