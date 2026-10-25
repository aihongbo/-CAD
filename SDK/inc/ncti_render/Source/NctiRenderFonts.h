#ifndef NctiRenderFonts_H
#define NctiRenderFonts_H
#include "NctiRenderObject.h"
#include "string"
#include "vector"

namespace NCTI
{
    /**
     * @brief internal usage
     */
    struct DECL_NCTI_RENDER NctiCharacter
    {
        std::vector<unsigned char> image;
        int startx{ -1 }, starty{ -1 };
        int sizex{ 0 }, sizey{ 0 };
        float bearX{ 0 }, bearY{ 0 };
        float advance{0};
    };

    class NctiViewerRenderer;
    class NctiRenderTextItem;
    class DECL_NCTI_RENDER NctiRenderFonts : public NctiDummyBaseClass
    {
    public:

        /**
         * @brief construct
         * @param[in] i_FontsName font name
         */
        NctiRenderFonts(const std::string& i_FontsName);
        virtual ~NctiRenderFonts();

        /**
         * @brief init the font
         * @param[in] i_ft the free type object
         * @param[in] i_FontsFileName the font file
         */
        Ncti_Boolean InitFont(void* i_ft, const char* i_FontsFileName);

        /**
         * @brief ResetModify
         * @details reset the associate text object modify state
         */
        void ResetModify(NctiViewerRenderer* i_pViewerRenderer);

        /**
         * @brief IsModify
         */
        bool IsModify(NctiViewerRenderer* i_pViewerRenderer);

        /**
         * @brief get font name
         */
        const std::string& GetFontsName()const;

        /**
         * @brief get font file
         */
        const std::string& GetFontFile()const;

        /**
         * @brief update the font word
         * @param[in] str text to be display
         * @return the string length
         */
        float UpdateString(std::wstring str);

        /**
         * @brief update the font word
         * @param[in] i_c char to be display
         * @return the character
         */
        NctiCharacter* TouchCharacter(Ncti_WChar i_c);

        /**
         * @brief detach the text item from the font
         * @param[in] text text to be display
         */
        void DetachTextItem(NctiRenderTextItem* text, NctiViewerRenderer*);
        void DetachAllItem();

        /**
         * @brief Attach the text item to the font
         * @param[in] text text to be display
         */
        void AttachTextItem(NctiRenderTextItem*);

        /**
         * @brief get the font image buffer
         * @details internal usage
         */
        const std::vector<unsigned char>& GetImageData()const;

    private:
        void DealCharacter();
        class PrivateData;
        PrivateData* _d;
    };
}
#endif
