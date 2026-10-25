#ifndef NctiRenderTextItem_H
#define NctiRenderTextItem_H
#include "NctiRenderGeometryItem.h"
#include "ncti_render.h"
#include "string.h"
namespace NCTI
{
    class NctiRenderFonts;

    /**
     * @brief Text Geometry Render Object
     */
    class DECL_NCTI_RENDER NctiRenderTextItem : public NctiRenderGeometryItem
    {
        NCTI_RENDER_FUNCTIONS(NctiRenderTextItem);
    public:

        NctiRenderTextItem();
        virtual ~NctiRenderTextItem();

        /**
         * @brief clone self.completion virtual function
         */
        NctiRenderGeometryItem* clone()const override;

        /**
         * @brief set word position
         * @param[in] i_pt position
         */
        void SetPosition(const NctiPosition& i_pt);

        /**
         * @brief set text values
         * @param[in] t texts
         */
        void SetTextValue(const std::vector<std::wstring>& t);

        /**
         * @brief set word hight
         * @param[in] h word hight,in pixel
         */
        void SetHeight(float h);

        /**
         * @brief SetAlign
         * @param[in] ax align in x
         * @param[in] ay align in y
         */
        void SetAlign(RenderAlgnX ax, RenderAlgnY ay);

        /**
         * @brief completion virtual function
         * @return text size
         */
        Ncti_Size GetVertexCount()const override;

        /**
         * @brief completion virtual function
         * @return text position
         */
        NctiPosition GetPosition(int)const override;
        /**
         * @brief GetPositions
         */
        const VertexDataType& GetPositions()const override;
        /**
         * @brief Get bounding box.completion virtual function
         */
        bool GetBox(NctiViewerRenderer* i_pViewerRenderer, NctiPosition& o_Max, NctiPosition& o_Min)override;

        /**
         * @brief get render data
         * @details internal usage in self render
         */
        bool GetDispAttr(std::vector<Ncti_UInteger>&, NctiRenderFonts*)const;

        /**
         * @brief modify the text position without rebuild the scene tree
         * @param[in] i_pViewerRenderer render to direct update the text position
         * @param[in] i_pt the new text position
         */
        void SetVertexBuffer(NctiViewerRenderer* i_pViewerRenderer, const NctiPosition& i_pt);

        /**
         * @brief set word interval
         * @param[in] w word interval,in pixel
         */
        void SetTextInterval(float w);

        /**
         * @brief get word interval
         * @return word interval,in pixel
         */
        float GetTextInterval()const;

        /**
         * @brief set line interval
         * @param[in] w line interval,in pixel
         */
        void SetLineInterval(float w);

        /**
         * @brief get line interval
         * @return line interval,in pixel
         */
        float GetLineInterval()const;

        /**
         * @brief get word hight
         * @return word hight,in pixel
         */
        float GetHeight()const;


        /**
         * @brief clear text values
         */
        void ClearTextValue();


        /**
         * @brief add text values to a new line
         * @param[in] t text
         */
        void AddTextValue(const char*t);

        /**
         * @brief set text values
         * @param[in] t text
         */
        void SetTextValue(const char* t);

        /**
         * @brief get text values
         */
        const std::vector<std::wstring>& GetTextValue()const;

        /**
         * @brief set font name
         * @details the font must be added before in NctiRenderManager
         * @see NctiRenderManager::AllFonts
         */
        void SetFontName(const std::string& i_fontName);

        /**
         * @brief get font name
         */
        std::string GetFontName()const;

        /**
         * @brief get font file path
         */
        std::string GetFontFile()const;

    private:
        std::vector<std::wstring> m_lastText;
    };
}
#endif
