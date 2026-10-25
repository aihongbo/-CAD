#ifndef dcl_ncti_sketch_H
#define dcl_ncti_sketch_H
#ifndef DECL_NCTI_SKETCH
#ifdef NCTI_DLL

#ifdef EXPORT_NCTI_SKETCH
#ifdef _MSC_VER
#define DECL_NCTI_SKETCH __declspec(dllexport)
#else
#define DECL_NCTI_SKETCH __attribute__((visibility("default")))
#endif 
# else 
#ifdef _MSC_VER
#define DECL_NCTI_SKETCH __declspec(dllimport)
#else
#define DECL_NCTI_SKETCH __attribute__((visibility("default")))
#endif 

# endif

#else
# define DECL_NCTI_SKETCH
#endif
#endif

#endif // 



