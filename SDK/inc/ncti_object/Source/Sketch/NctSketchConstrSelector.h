#ifndef NctSketchConstrSelector_H
#define NctSketchConstrSelector_H
#include "dcl_ncti_object.h"
#include "NctiDCMDef.h"

namespace NCTI {
    class NctiDisplaySketchObject;
    class NctiDisplayDocSketch;
    class DECL_NCTI_OBJECT NctSketchConstrSelector : public NCTI_BASE_CLASS
    {
    public:
        NctSketchConstrSelector(NctiDisplayDocSketch* pDocSketch, ncti_DCM_d_type constrType);
        ~NctSketchConstrSelector();

        bool selectGeometry1();
        bool selectGeometry2();
        bool selectGeometry3();
        NctiDisplaySketchObject* getSelectedGeometry1() const { return m_selObj1; }
        NctiDisplaySketchObject* getSelectedGeometry2() const { return m_selObj2; }
        NctiDisplaySketchObject* getSelectedGeometry3() const { return m_selObj3; }

    private:
        NctiDisplaySketchObject* selectGeometry(std::vector<const char*> i_typeIds);
        void getSelectedSketchObjects(std::vector<const char*> i_typeIds, std::vector< NctiDisplaySketchObject*>& o_selObjs);
        void getConstrSupportedTypes(const char* i_selectedTypeId, std::vector<const char*>& o_typeIds);
        void getParallelSupportedTypes(std::vector<const char*>& o_typeIds);
        void getPerpendicularSupportedTypes(std::vector<const char*>& o_typeIds);
        void getTangentSupportedTypes(const char* i_selectedTypeId, std::vector<const char*>& o_typeIds);
    private:
        ncti_DCM_d_type m_constrType;
        NctiDisplayDocSketch* m_pDocSketch;
        NctiDisplaySketchObject* m_selObj1;
        NctiDisplaySketchObject* m_selObj2;
        NctiDisplaySketchObject* m_selObj3;
    };
}

#endif // !NctSketchConstrSelector_H