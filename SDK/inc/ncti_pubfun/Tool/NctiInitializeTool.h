#pragma once

#include "dcl_ncti_pubfun.h"
#include "NctiRGBAColor.h"
#include "ncti_base.h"
#include "string"

#define DeParamsColor(rgb) (RGBAColor(((((rgb)&0x0ff0000)>>16)),((((rgb)&0x0ff00)>>8)),((rgb)&0x0ff)))


namespace NCTI
{
    class NctiBaseView;
    struct PythonVersion;

    class DECL_NCTI_PUBFUN NctiInitializeTool
    {
    public:

        /**
         * @brief InitLicense InitRenderFont,InitEnvironmentPath,InitScriptSolver
         * @param[in] i_exeDir directory
         * @param[in] i_config config file path
         * @param[in] i_licDir license dir which cntains the file "gmde.lic"
         */
        NCTI::NctiErrorType InitNcti(const char* i_exeDir, const char* i_config, const char* i_licDir = nullptr);
        
        /**
         * @brief init plugins
         * @note after read config file or load dll,
         *      then call this function to init plugins
         * @see NctiScriptSolveManager
         */
        Ncti_Boolean InitPlugins();

        /**
        * @brief Initialize Display attributes from System Parameters
        * @param i_pBaseView Base View Pointer
        */
        void InitDisplay(NctiBaseView* pBaseView);

        /**
        * @brief save config to config file
        * @param[in] i_config config file path
         * @return boolean
        */
        Ncti_Boolean saveToFile(const char* i_config);

        /**
        * @brief load config from config file
        * @param[in] i_config config file path
         * @return boolean
        */
        Ncti_Boolean loadFromFile(const char* i_config);

        /**
         * @brief load Pyton model
         * @return boole
         */
        Ncti_Boolean LoadPythonModel();

        /**
         * @brief getErrorMessage
         * @param[in] i_err
         */
        std::string getErrorMessage(NCTI::NctiErrorType i_err);

        /**
         * @brief Release Plugin And License
         */
        Ncti_Boolean ReleaseNcti();

        /**
         * @brief Refresh Trace
         * @param[in] i_view Base View Pointer
         */
        void RefreshTrace(NctiBaseView* i_view);
    };
}

