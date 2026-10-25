#ifndef NctiRenderObject_H
#define NctiRenderObject_H
#include "ncti_render.h"
#include "ncti_base.h"
#include "functional"
#include <vector>
#include "NctiRenderMemoryPool.h"

#ifdef __GNUC__
#include <cstring>
#endif
#include <map>
#include <type_traits>

/**
* @def NCTI_RENDER_FUNCTIONS
* @brief declare the typename info for polymorphisms
* @param [in] RENDER_OBJECT_CLASS_NAME the class name
* @see NCTI_RENDER_DEF
*/

#define NCTI_RENDER_FUNCTIONS(RENDER_OBJECT_CLASS_NAME) \
public:\
    static const char* ID;\
    static const char* OBJECT_NAME;\
    const char* TypeName()const override;\
    bool IsTypeName(const char* i_cTypeName)const override

/**
* @def NCTI_RENDER_DEF
* @brief implementation for the typename info polymorphisms,used in CPP file
* @see NCTI_RENDER_FUNCTIONS
*/
#define NCTI_RENDER_DEF( RENDER_OBJECT_CLASS_NAME, RENDER_OBJECT_DERIVED_FROM, IDENTITY_STRING, OBJ_NAME_STRING ) \
	const char* RENDER_OBJECT_CLASS_NAME::ID = IDENTITY_STRING;\
	const char* RENDER_OBJECT_CLASS_NAME::OBJECT_NAME = OBJ_NAME_STRING;\
	const char* RENDER_OBJECT_CLASS_NAME::TypeName()const{ return RENDER_OBJECT_CLASS_NAME::ID; }\
	bool RENDER_OBJECT_CLASS_NAME::IsTypeName( const char *sTypeName )const\
	{\
		if ( (RENDER_OBJECT_CLASS_NAME::ID)[2] != sTypeName[2] )\
		{\
			return false;\
		}\
		if ( strcmp( RENDER_OBJECT_CLASS_NAME::ID, sTypeName ) == 0 )\
		{\
			return true;\
		}\
		return RENDER_OBJECT_DERIVED_FROM::IsTypeName( sTypeName );\
	}

/**
* @mainpage NctiRender Render Base Library
*
* ## module navigation
* - @ref NctiRenderGeometryItem GeometryItem
* - @ref NctiRenderSegmentItem SegmentItem
* - @ref NctiRenderKit AttributeItem
* - @ref NctiViewerRenderer Renderer base class
*
*/

namespace NCTI
{
    class NctiRenderGeometryItem;
    class NctiRenderSegmentItem;
    class NctiViewerRenderer;

    /**
    * @brief Attribute base class. internal usage
    * @sa NctiRenderATT
    */
    class NctiAttrBase:public NctiMemoryBase
    {
    public:
        NctiAttrBase();
        virtual ~NctiAttrBase();
        virtual size_t hash_code()const;

        bool copy_attr(const NctiAttrBase* o);

        template<typename OBJECT_TYPE>
        OBJECT_TYPE* raw_data()const {
#ifdef VALIDATION_ATTR
            if (typeid(OBJECT_TYPE).hash_code() != m_type)
                throw("error type!");
#endif
            return (OBJECT_TYPE*)m_pAtt;
        }

        template<typename OBJECT_TYPE>
        bool get_attr(OBJECT_TYPE& out) const {
            if (m_valid)
                out = *raw_data<OBJECT_TYPE>();
            return m_valid;
        }

        template<typename OBJECT_TYPE>
        bool set_attr(const OBJECT_TYPE &att) {
            OBJECT_TYPE* ptr = raw_data<OBJECT_TYPE>();
            if (*ptr != att)
            {
                *ptr = att;
                m_valid = true;
                return true;
            }
            if (!m_valid)
            {
                m_valid = true;
                return true;
            }
            return false;
        }

        void clear_mod();
        bool copy_mod(NctiAttrBase* o);
        bool get_mod(NctiViewerRenderer* v)const;
        bool set_mod(bool m, NctiViewerRenderer* v);

        bool valid()const;
        void unset(const std::vector<NctiViewerRenderer*>& renders);

    protected:
        std::function<bool(const NctiAttrBase*)> m_fn{nullptr};
        void* m_pAtt{nullptr};
        bool m_valid{ false };
#ifdef VALIDATION_ATTR
        std::size_t m_type{0};
#endif
    private:
        std::map<NctiViewerRenderer*, bool> m_mod;
    };
    
    /**
    * @brief Attribute used in RenderKit implement CPP.Internel usage
    * @see NctiRenderKit
    */
    template<typename OBJECT_TYPE>
    class NctiRenderATT: public NctiAttrBase
    {
    public:
        OBJECT_TYPE m_att;
        NctiRenderATT(const OBJECT_TYPE &t) :m_att(t)
        {
#ifdef VALIDATION_ATTR
            m_type = typeid(OBJECT_TYPE).hash_code();
#endif
            m_pAtt = &m_att;
            m_fn = [this](const NctiAttrBase* o) {
                auto &tar = ((NctiRenderATT*)o)->m_att;
                if (m_att != tar) {
                    m_att = tar;
                    return true;
                }
                return false;
                };
        }
    };
    
    template<typename OBJECT_TYPE>
    class NctiRenderKitATT : public NctiRenderATT<OBJECT_TYPE>
    {
    public:
        using NctiRenderATT<OBJECT_TYPE>::m_att;
        NctiRenderKitATT(const OBJECT_TYPE &t) :NctiRenderATT<OBJECT_TYPE>(t){}
        size_t hash_code()const override{
                return std::hash<OBJECT_TYPE>{}(m_att);
        }
    };


    /**
    * @brief Base class for render object.
    * @see NctiRenderKit,NctiRenderGeometryItem
    */
    class DECL_NCTI_RENDER NctiRenderObject:public NctiMemoryBase
    {
    public:
        NctiRenderObject();
        virtual~NctiRenderObject();

        /**
        * @brief move this to the NctiRenderSegmentItem
        * @see NctiRenderGeometryItem,NctiRenderSegmentItem
        */
        void MoveTo(NctiRenderSegmentItem* i_pRenderSegmentItem);

        /**
        * @brief Instance ID for render object.used in pick
        * @return the Instance ID 
        */
        Ncti_Size GetInstanceID()const;

        /**
        * @brief class identify
        * @param[in] i_sTypeName class identity,get it by TypeName() in class
        * @return true if this class type of i_sTypeName or the child class of i_sTypeName 
        * @see NCTI_RENDER_FUNCTIONS,TypeName
        */
        virtual bool IsTypeName(const char* i_sTypeName)const;

        /**
        * @brief get class identify
        * @return the class identify string
        * @see NCTI_RENDER_FUNCTIONS,IsTypeName
        */
        virtual const char* TypeName()const = 0;

        /**
        * @brief set the object own this
        * @see GetDoOwner
        */
        void SetDoOwner(NctiRenderObject* i_pRenderObject);

        /**
        * @brief get the object own this
        * @return the object own this
        * @see SetDoOwner
        */
        NctiRenderObject* GetDoOwner();

        /**
        * @brief get the NctiRenderSegmentItem object own this
        * @return the NctiRenderSegmentItem object own this or nullptr
        * @see GetDoOwner,NctiRenderSegmentItem
        */
        NctiRenderSegmentItem* GetSegmentOwner();

        /**
        * @brief add the associate render to the object
        * @details used in render pipeline,internal used
        * @return true if not added,else force
        * @see GetViewerRenderer,RemoveViewerRendere
        */
        Ncti_Boolean AddViewerRenderer(NctiViewerRenderer* i_pViewerRenderer);

        /**
        * @brief RemoveViewerRendere
        */
        Ncti_Boolean RemoveViewerRendere(NctiViewerRenderer* i_pViewerRenderer);

        /**
        * @brief get the associate renders in the object
        * @details in multiview display,the object associate with multiple renders
        * @return all renders current display the object
        * @see AddViewerRenderer,RemoveViewerRendere
        */
        const std::vector<NctiViewerRenderer*>& GetViewerRenderer()const;

        /**
        * @brief the attribute valid information
        * @details used in render pipeline,internal used
        * @param[in] index the attribute index
        * @see NctiRenderKit,NctiRenderGeometryItem
        */
        bool IsValid(int index)const;

        /**
        * @brief unset the attribute
        * @details used in render pipeline,internal used
        * @param[in] index the attribute index
        * @see NctiRenderKit,NctiRenderGeometryItem
        */
        void UnSetAttr(int index);

        /**
        * @brief unset all attribute
        * @details used in render pipeline,internal used
        * @param[in] index the attribute index
        * @see NctiRenderKit,NctiRenderGeometryItem
        */
        void UnsetEverything();

        /**
        * @brief the the display object for the render object
        * @param[in] i_pDObj the object in user interface
        * @see NctiDisplayObject
        */
        void SetDisplayObject(void* i_pDObj);

        /**
        * @brief get the display object for the render object
        * @return the display object
        * @see NctiDisplayObject
        */
        void* GetDisplayObject();

        /**
        * @brief whether the assign attribute is modify in the render
        * @details used in render pipeline,internal used
        * @param[in] i_render the render display the attribute
        * @param[in] i_index the attribute index;-1 for all arrt
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        bool IsModify(NctiViewerRenderer* i_render, int i_index = -1)const;

        /**
        * @brief reset all attribute modification info
        * @details used in render pipeline,internal used
        * @param[in] i_pViewerRenderer the render display the attribute
        * @param[in] i_index the attribute index;-1 for all arrt
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        void ResetModify(NctiViewerRenderer* i_pViewerRenderer, int i_index = -1);

        /**
        * @brief reset the attribute modification info
        * @details used in render pipeline,internal used
        * @param[in] index the index of attribute
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        void ResetModify(int index);

        /**
        * @brief Guard for disable tree modify
        * @see NctiRenderObject
        */
        class DECL_NCTI_RENDER DisableModifyGuard {
        public:
            DisableModifyGuard();
            ~DisableModifyGuard();
        };

    protected:
        /**
        * @brief notify the render to rebuild the scene
        * @details used in render pipeline,internal used
        * @see NctiViewerRenderer
        */
        void SetViewerRendererTreeModify();

        /**
        * @brief notify the render to destroy the render resource associate with the item
        * @details used in render pipeline,internal used
        * @see NctiViewerRenderer
        */
        void SetDeleteCallback();

        /**
        * @brief init the assign attribute
        * @details used in render pipeline,internal used
        * @param[in] index the attribute index
        * @param[in] at the initialize value
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        template <typename TYPE, template<typename> class AttrClass>
        void init_attr_impl(int index, const TYPE& at) {
            checkExsist(index);
            m_attr[index] = new AttrClass<TYPE>(at);
        }
        template <typename TYPE>
        void init_attr(int index, const TYPE& at) {
            init_attr_impl<TYPE, NctiRenderATT>(index, at);
        }

        /**
        * @brief set the assign attribute
        *  used in render pipeline,internal used
        * @param[in] index the attribute index
        * @param[in] at the value to be set
        * @param[in] fmod where modify the render
        *            0:auto mod,1:force mod,2:no mod,3:force mode without rebuild
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        template <typename TYPE>
        bool set_attr(int index, const TYPE& at,int fmod=0) {
            if (index >= m_attr.size() || !m_attr[index])
                throw("error index");
            bool mod = m_attr[index]->set_attr(at);
            checkMod(index,mod,fmod);
            return mod;
        }

        /**
        * @brief get the assign attribute
        * @details used in render pipeline,internal used
        * @param[in] index the attribute index
        * @param[out] out the value to be get
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        template <typename TYPE>
        bool get_attr(int index, TYPE& out)const{
            if (index >= m_attr.size() || !m_attr[index])
                throw("error index");
            return m_attr[index]->get_attr(out);
        }

        /**
        * @brief get the assign attribute
        * @details used in render pipeline,internal used
        * @param[in] index the attribute index
        * @return the value to be get
        * @see NctiRenderKit,NctiRenderGeometryItem,NctiViewerRenderer
        */
        template <typename TYPE>
        TYPE& get_attr(int index)const{
            if (index >= m_attr.size() || !m_attr[index])
                throw("error index");
            return *(m_attr[index]->raw_data<TYPE>());
        }

    private:
        void checkExsist(int index);
        void checkMod(int index,bool mod,int fmod);

        friend class NctiRenderKit;
        std::vector<NctiAttrBase*>m_attr;
        Ncti_Size m_HandleId{0};
        void* m_DisplayObject{ nullptr };
        NctiRenderObject* m_OwnerObject{nullptr};
        std::vector<NctiViewerRenderer*> m_ViewerRendererVec;
    };
}
#endif // !NctiRenderObject_H
