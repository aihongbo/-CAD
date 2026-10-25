#ifndef ncti_dcl_PluginManager_H
#define ncti_dcl_PluginManager_H


#ifndef DECL_NCTI_PLUGINMANAGER  
#ifdef NCTI_DLL
# ifdef EXPORT_NCTI_PLUGINMANAGER 
#ifdef _MSC_VER
#define DECL_NCTI_PLUGINMANAGER __declspec(dllexport)
#else
#define DECL_NCTI_PLUGINMANAGER __attribute__((visibility("default")))
#endif 
# else  
#ifdef _MSC_VER
#define DECL_NCTI_PLUGINMANAGER __declspec(dllimport)
#else
#define DECL_NCTI_PLUGINMANAGER __attribute__((visibility("default")))
#endif 

# endif
#else
# define DECL_NCTI_PLUGINMANAGER
#endif
#endif

#endif // !ncti_dcl_PluginManager_H


