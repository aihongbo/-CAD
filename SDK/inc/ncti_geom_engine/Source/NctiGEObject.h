#ifndef NctiGEObject_H
#define NctiGEObject_H
#include "ge_def.h"
#include "NctiPosition.h"
#include "NctiUnitVector.h"
#include <vector>
#define NCTI_GEOM_FUNCTIONS(OBJECT_CLASS_NAME) \
public:\
    static const Ncti_PChar ID;\
    static const Ncti_PChar OBJECT_NAME;\
    virtual const Ncti_PChar TypeName();\
    virtual bool IsTypeName(const Ncti_PChar i_cTypeName);
#define NCTI_GEOM_DEF( OBJECT_CLASS_NAME, OBJECT_DERIVED_FROM, IDENTITY_STRING, OBJ_NAME_STRING ) \
	const Ncti_PChar OBJECT_CLASS_NAME::ID = const_cast<Ncti_PChar>(IDENTITY_STRING);\
	const Ncti_PChar OBJECT_CLASS_NAME::OBJECT_NAME = const_cast<Ncti_PChar>(OBJ_NAME_STRING);\
	const Ncti_PChar OBJECT_CLASS_NAME::TypeName(){ return OBJECT_CLASS_NAME::ID; }\
	Ncti_Boolean OBJECT_CLASS_NAME::IsTypeName( const Ncti_PChar sTypeName )\
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

#define NCTI_GE_ATT_DEF(ATTTYPE, ATT)\
public:\
void Set_##ATT(ATTTYPE i_##ATT) { ATT = i_##ATT; }\
ATTTYPE Get_##ATT() { return ATT; }\
protected:\
	ATTTYPE ATT;

namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiGEObject : public NCTI_BASE_CLASS
	{
	public:
		NctiGEObject();
		virtual ~NctiGEObject();
	public:
		virtual Ncti_Boolean IsTypeName(const Ncti_PChar i_sTypeName);
		virtual const Ncti_PChar TypeName() = 0;
	
	
	};
}
#endif
