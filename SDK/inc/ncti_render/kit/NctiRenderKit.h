#pragma once

#include "NctiRenderObject.h"

/**
* @def NCTI_RENDER_KIT_FUNCTIONS
* @brief declare the typename info for NctiRenderKit,implementation the new_kit virtual function
* @param [in] RENDER_OBJECT_CLASS_NAME the class name
* @see NCTI_RENDER_DEF
*/
#define NCTI_RENDER_KIT_FUNCTIONS(RENDER_OBJECT_CLASS_NAME) \
    NCTI_RENDER_FUNCTIONS(RENDER_OBJECT_CLASS_NAME);\
    virtual ~RENDER_OBJECT_CLASS_NAME() = default;\
    private:NctiRenderKit* clone_kit()const override{\
        auto kit = new RENDER_OBJECT_CLASS_NAME();\
        kit->CopyKit(this);\
        return kit;\
    }

namespace NCTI
{
    class NctiViewerRenderer;

    /**
    * @brief Base class for render kit.
    * @details kit added in segment item
    * @see NctiRenderSegmentItem
    */
    class DECL_NCTI_RENDER NctiRenderKit : public NctiRenderObject
    {
        NCTI_RENDER_FUNCTIONS(NctiRenderKit);
    public:
        NctiRenderKit();
        virtual ~NctiRenderKit();

        virtual NctiRenderKit* clone_kit()const = 0;

        /**
        * @brief Copy data From i_kit
        * @param[in] i_kit kit to copy
        */
        void CopyKit(const NctiRenderKit* i_kit);

        /**
        * @brief Copy this to i_kit
        * @param[in] i_kit target kit
        */
        bool AttachKit(NctiRenderKit* i_kit)const;

        /**
        * @brief HashCode
        */
        size_t HashCode()const;
        size_t HashCode(int j)const;

        /**
        * @brief init the kit attribute
        * @details used in render pipeline,internal used
        * @param[in] index the attribute index
        * @param[in] at the initialize value
        * @param[in] TYPE must implement the hash_code function for check modification
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        template <typename TYPE>
        void init_kit_attr(int index, const TYPE& at) {
            init_attr_impl<TYPE, NctiRenderKitATT>(index, at);
        }

        template <typename TYPE>
        void init_attr(int index, const TYPE& at) = delete;
    };
}
