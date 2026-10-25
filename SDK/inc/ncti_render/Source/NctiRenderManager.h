#ifndef NctiRenderManager_H
#define NctiRenderManager_H
#include "ncti_base.h"
#include "ncti_dcl_render.h"
#include <string>
#include <vector>
#include "NctiDebug.h"

namespace NCTI
{
	class NctiRenderFonts;
	class NctiDebug;
    class NctiRenderSegmentItem;
    class NctiRenderObject;
    /**
     * @brief render config manager
     */
	class DECL_NCTI_RENDER NctiRenderManager
	{
	public:
		virtual ~NctiRenderManager();
		static NctiRenderManager* instance();

        /**
         * @brief SetApplicationPath
         * @param[in] i_path work directory
         */
		void SetApplicationPath(const char* i_path);

        /**
         * @brief GetApplicationPath
         * @return work directory
         */
        const char* GetApplicationPath();

        /**
         * @brief ClearFont
         * @param[in] i_FontsName font name;empty for all font
         */
        void ClearFont(std::string i_FontsName = "");

        /**
         * @brief AddFonts
         * @param[in] i_FontsName font name
         * @param[in] i_FontsFileName font file
         */
		NctiRenderFonts* AddFonts(std::string i_FontsName, const char* i_FontsFileName);

        /**
         * @brief GetFonts
         * @param[in] i_FontsName font name
         * @return NctiRenderFonts
         */
		NctiRenderFonts* GetFonts(std::string i_FontsName);

        /**
         * @brief get all font added
         */
        std::vector<std::string> AllFonts()const;

        /**
         * @brief get the first font
         */
        std::string DeFaultFont();

	private:
        NctiRenderManager();
        void *m_FT_Library = nullptr;
		char* m_ApplicationPath;

		std::vector<NctiRenderFonts*> m_RenderFontsVec;
        NctiRenderFonts* m_DefualtFonts{nullptr};
	};
}
#endif // !NctiRenderManager_H
