#ifndef NctiManager_H
#define NctiManager_H
#include "ncti.h"
#include <string>
#include "NctiMutex.h"
namespace NCTI
{
	class NctiManagerGenerator;
}

#define NCTI_MANAGER_TYPEDEF(MANAGER_NAME) extern Ncti_Integer MANAGER_NAME##_TYPE;
#define NCTI_MANAGER_FUNCTIONS(MANAGER_NAME) \
public:\
    static const char* ID;\
    MANAGER_NAME();\
    virtual const char* TypeName(){return "";};\
    virtual Ncti_Boolean IsTypeName(const char* i_cpTypeName);\
public:
#define NCTI_MANAGER_DEF(MANAGER_NAME, MANAGER_NAME_DERIVED_FROM, IDENTITY_STRING)\
    const char* NCTI::MANAGER_NAME::ID = IDENTITY_STRING; \
    Ncti_Boolean NCTI::MANAGER_NAME::IsTypeName(const char* i_cpTypeName)\
    {\
        if (strcmp(NCTI::MANAGER_NAME::ID, i_cpTypeName) == 0)\
        {\
            return true; \
        }\
        return NCTI::MANAGER_NAME_DERIVED_FROM::IsTypeName(i_cpTypeName); \
    }
#define NCTI_MANAGER_REGISTRATION(MANAGER_NAME)\
    Ncti_Integer MANAGER_NAME##_TYPE;\
    NCTI::NctiManager* Generate_##MANAGER_NAME()\
    {\
       NCTI::NctiManager* pManager = NCTI_NEW MANAGER_NAME(); \
       return pManager; \
	}\
    static NctiManagerGenerator Register_##MANAGER_NAME(\
                                MANAGER_NAME##_TYPE,\
                                (const char*)MANAGER_NAME::ID,\
                                (NCTI::NctiManager* (*)(...))Generate_##MANAGER_NAME);
    
namespace NCTI
{
	class NctiBaseModel;
	class NctiDisplayObject;
	class NctiBody;
	 /**
	* @brief Base Class of manager, such as doc view, history manager
	* @see NctiDummyBaseClass
	*/
	class DECL_NCTI NctiManager : public NCTI_BASE_CLASS
	{
	public:
		NctiManager();
		virtual ~NctiManager();
	public:
		/**
	   * @brief check if the display type is correct
	   * @param[in] i_sTypeName, the type of display object
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsTypeName(const char* i_cpTypeName);
		/**
	   * @brief get the type name
	   * @details need to implement, override
	   * @return const char*
	   */
		const char* TypeName();
	public:
		/**
	   * @brief set the manage tag
	   * @param[in] i_iTag
	   */
		void SetTag(Ncti_Integer i_iTag);
		/**
	   * @brief set the base model
	   * @param[in] i_pBaseModel
	   */
		void SetBaseModel(NctiBaseModel* i_pBaseModel);
		/**
	   * @brief get the base model
	   * @param[in] i_pBaseModel
	   */
		NctiBaseModel* GetBaseModel() { return m_pBaseModel; }
		/**
	   * @brief  Deallocate display object in a memory pool
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean Deallocate(NctiDisplayObject*& i_pObj) { return false; }
		/**
	   * @brief  Deallocate body object in a memory pool
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean Deallocate(NctiBody*& i_pObj) { return false; }
		/**
	   * @brief  Allocate display object in a memory pool
	   * @return NctiDisplayObject*
	   */
		virtual NctiDisplayObject* Allocate(const char* i_cTypeName) { return nullptr; }
	public:
		/**
	   * @brief internal used
	   * @details need to implement, override
	   */
		virtual void notify_selection_data_changed();
		/**
	   * @brief internal used
	   * @details need to implement, override
	   */
		virtual void NotifyTermination();
		/**
	   * @brief internal used
	   */
		void Lose(NctiDisplayObject* i_pDo);
	protected:
		NctiBaseModel* m_pBaseModel;
		Ncti_Boolean m_bIsClosing;
        NctiMutex m_mutex;
	private:
		Ncti_Integer m_iTag;
		
	};
}
#endif // !NctiManager_H
