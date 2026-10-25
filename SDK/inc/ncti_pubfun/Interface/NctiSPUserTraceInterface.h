#ifndef NctiSPUserTraceInterface_H
#define NctiSPUserTraceInterface_H
#include "dcl_ncti_pubfun.h"
#include "NctiTrace.h"
#include <map>
namespace NCTI
{
	class NctiBaseView;
	class NctiRenderOperator;
	class NctiWindowPlatform;

	class NctiPCDeformationCage;
	class NctiPCDeformationCageMouse;

	class DECL_NCTI_PUBFUN NctiSPUserTraceInterface: public NctiTrace
	{
	public:
		NctiSPUserTraceInterface(NctiWindowPlatform* i_pViewPlatform);
		~NctiSPUserTraceInterface();
	public:
		virtual void HistoryIsStart();
		virtual void HistoryIsEndBySucceeded();
		virtual void HistoryIsEndByFailed();
	public:
		//virtual void SetOperatorCallBack(NctiBaseView* i_pBaseView);
		virtual void NotifySelectionDataChanged();
		virtual void ExecuteCameraCallback(NctiBaseView* i_pBaseView);
		virtual void NotifyRenderItemSelectionDataChanged(NctiBaseView* i_pBaseView);
	private:
		std::vector<NctiRenderOperator*> m_RenderOperatorVec;
		std::map<NctiBaseView*, NctiPCDeformationCage*> m_MapCDeformationCage;
		std::map<NctiBaseView*, NctiPCDeformationCageMouse*> m_MapPCDeformationCageMouse;
	};
}
#endif
