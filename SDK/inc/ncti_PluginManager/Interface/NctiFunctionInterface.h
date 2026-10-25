#ifndef NctiFunctionInterface_H
#define NctiFunctionInterface_H
#include "ncti_dcl_PluginManager.h"
#include "ncti_base.h"
#include <vector>

#define NCTI_PLUGIN_FUNCTIONS(OBJECT_CLASS_NAME) \
public:\
    static const char* ID;\
    static const char* OBJECT_NAME;\
    virtual const char* TypeName();\
    virtual Ncti_Boolean IsTypeName(const char* i_cTypeName);
#define NCTI_PLUGIN_DEF(OBJECT_CLASS_NAME, OBJECT_DERIVED_FROM, IDENTITY_STRING, OBJ_NAME_STRING ) \
	const char* OBJECT_CLASS_NAME::ID = IDENTITY_STRING;\
	const char* OBJECT_CLASS_NAME::OBJECT_NAME = OBJ_NAME_STRING;\
	const char* OBJECT_CLASS_NAME::TypeName(){ return OBJECT_CLASS_NAME::ID; }\
	Ncti_Boolean OBJECT_CLASS_NAME::IsTypeName( const char *sTypeName )\
	{\
		if ( (OBJECT_CLASS_NAME::ID)[2] != sTypeName[2] )\
		{\
			return false;\
		}\
		if ( strcmp( OBJECT_CLASS_NAME::ID, sTypeName ) == 0 )\
		{\
			return true;\
		}\
		return OBJECT_DERIVED_FROM::IsTypeName( sTypeName );\
	}
namespace NCTI
{
	class NctiDocument;
	/**
	* @brief the base class of all function interface
	* @details to define new function interface class and fun
	*/
	class DECL_NCTI_PLUGINMANAGER NctiFunctionInterface : public NCTI_BASE_CLASS
	{
	public:
		NctiFunctionInterface();
		virtual ~NctiFunctionInterface();
	public:
		/**
	   * @brief check if the interface type is correct
	   * @param[in] i_sTypeName, the type of display object
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsTypeName(const char* i_sTypeName);
		/**
	   * @brief get the type name
	   * @details need to implement, override
	   * @return const char*
	   */
		virtual const char* TypeName() = 0;
	public:
		/**
	   * @brief Initialization during load plugin
	   */
		virtual void Init(){}
		/**
	   * @brief Release during unload plugin
	   */
		virtual void Release(){}
		/**
	   * @brief Initialization Document during load plugin
	   */
		virtual void InitDocument(NctiDocument* i_pDocument) {}
		/**
	   * @brief Release Document during unload plugin
	   */
		virtual void ReleaseDocument(NctiDocument* i_pDocument) {}
	};
}
#endif
