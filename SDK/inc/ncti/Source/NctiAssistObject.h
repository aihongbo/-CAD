#ifndef NctiAssistObject_H
#define NctiAssistObject_H
#include "ncti_dcl.h"
#include "ncti_base.h"

#define NCTI_ASSIST_FUNCTIONS(ASSIST_OBJECT_CLASS_NAME) \
public:\
    static const char* ID;\
    static const char* OBJECT_NAME;\
    virtual const char* TypeName();\
    virtual Ncti_Boolean IsTypeName(const char* i_cTypeName);
#define NCTI_ASSIST_DEF( ASSIST_OBJECT_CLASS_NAME, ASSIST_OBJECT_DERIVED_FROM, IDENTITY_STRING, OBJ_NAME_STRING ) \
	const char* ASSIST_OBJECT_CLASS_NAME::ID = IDENTITY_STRING;\
	const char* ASSIST_OBJECT_CLASS_NAME::OBJECT_NAME = OBJ_NAME_STRING;\
	const char* ASSIST_OBJECT_CLASS_NAME::TypeName(){ return ASSIST_OBJECT_CLASS_NAME::ID; }\
	Ncti_Boolean ASSIST_OBJECT_CLASS_NAME::IsTypeName( const char *sTypeName )\
	{\
		if ( (ASSIST_OBJECT_CLASS_NAME::ID)[2] != sTypeName[2] )\
		{\
			return false;\
		}\
		if ( strcmp( ASSIST_OBJECT_CLASS_NAME::ID, sTypeName ) == 0 )\
		{\
			return true;\
		}\
		return ASSIST_OBJECT_DERIVED_FROM::IsTypeName( sTypeName );\
	}

namespace NCTI
{
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiAssistObject : public NCTI_BASE_CLASS
	{
	public:
		NctiAssistObject();
		virtual ~NctiAssistObject();
	public:
		virtual Ncti_Boolean IsTypeName(const char* i_sTypeName);
		virtual const char* TypeName() = 0;
	};
}
#endif
