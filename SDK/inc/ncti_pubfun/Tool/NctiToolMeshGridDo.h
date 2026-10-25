#pragma once
#include "NctiTool.h"
#include "dcl_ncti_pubfun.h"
#include "ncti_event.h"
#include <vector>
#include <set>
#include <map>

namespace NCTI
{
    class NctiRubberbandScreenRect;
    class NctiRenderUnstructureItem;
    class NctiDisplayGridMesh;
    class NctiMeshBody;
    class NctiRenderTextItem;

    class DECL_NCTI_PUBFUN NctiToolMeshGridDo : public NctiTool
    {
        NCTI_TOOL_FUNCTIONS(NctiToolMeshGridDo)
    public:
        NctiToolMeshGridDo();
        void Inactivate()override;
        void ClearPreview();

        static void SetFilterType(NctiSelectType tp);
        static void SetFilterAngle(Ncti_Float tp);
        static void InitFilterType(NctiSelectType tp);

        bool on_cruise(NctiPosition st);
        bool on_drag(NctiPosition st, NctiPosition ed);
        bool on_pick(NctiPosition st, NctiPosition ed, ModifierKeys status);

    protected:
        void init_operator()override;
        EnumNctiResult ProcessContextMenu(EnumNctiMenuProcMode i_eProcMode) override;

    private:
        std::vector<NctiDisplayGridMesh*> currentGrid(std::vector<NctiRenderSegmentItem*>*ins=nullptr)const;
        void FilterInput(std::set<NctiGridPickSet>&);
        void FilterOutput(std::set<NctiGridPickSet>&);
        void UpdatePreviewText(NctiPosition pt, const std::set<NctiGridPickSet>&);

        NctiRenderSegmentItem* m_prevIns{ nullptr };
        NctiRenderUnstructureItem* m_prevLast{nullptr};
        NctiRenderTextItem* m_cellText{nullptr};
        std::set<std::pair<NctiRenderUnstructureItem*,NctiRenderSegmentItem*>> m_last;

        std::set<NctiGridPickSet> m_prevCell;
        static NctiSelectType s_filterType;
        static Ncti_Float s_filterAngle;
        static std::map<NctiGridPickSet, std::set<NctiGridPickSet>> s_AngleMap;
        static std::map<NctiGridPickSet, std::set<NctiGridPickSet>> s_TypeMap;
    };
}

