#ifndef ncti_dcl_geom_engine_H
#define ncti_dcl_geom_engine_H


#ifndef DECL_NCTI_GEOM_ENGINE
#ifdef NCTI_DLL

#ifdef EXPORT_NCTI_GEOM_ENGINE
#ifdef _MSC_VER
#define DECL_NCTI_GEOM_ENGINE __declspec(dllexport)
#else
#define DECL_NCTI_GEOM_ENGINE __attribute__((visibility("default")))
#endif 
# else 
#ifdef _MSC_VER
#define DECL_NCTI_GEOM_ENGINE __declspec(dllimport)
#else
#define DECL_NCTI_GEOM_ENGINE __attribute__((visibility("default")))
#endif 
# endif

#else
# define DECL_NCTI_GEOM_ENGINE
#endif
#endif
#endif // !ncti_dcl_base_H