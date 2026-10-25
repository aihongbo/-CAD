#ifndef NctiDisplayGFeature_H
#define NctiDisplayGFeature_H
#include "NctiDisplayGroup.h"
#include "NctiDisplayGSketch.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiSketchComDefine.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayGFeature : public NctiDisplayGroup
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGFeature)
	public:
		void	Init();
		virtual ~NctiDisplayGFeature();
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual void UpdateSketch(NctiDisplayDocCustomContainer* i_pDocCustomContainer);
		virtual bool	    MoveActualToWork();
		virtual NctiTransf	GetTransform();

		NctiDisplayGSketch* GetDoSketch();
		virtual EnumNctiResult CreateModelBody(NCTI_MODEL_TAG& i_pDoBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine);
		void	GetBooleanMode(EnumNctiFeatureBooleanMode& o_eBoolMode);
		void	SetBooleanMode(EnumNctiFeatureBooleanMode i_eBoolMode);
		bool	IsValid();
		void	SetValid();
		NctiRenderSegmentItem* GetModelKey() { return m_keyModel; };
		void AddGFeatureID(Ncti_Long i_id);
		void RemoveAllFeatureID();
		const std::vector<Ncti_Long>& GetGFeatureID() { return m_GFeatureIDVec; }
	protected:
		EnumNctiResult	post_feature_creation(NCTI_MODEL_TAG i_pDoBody, NctiDisplayDocCustomContainer* i_pDocCustomContaine);
	protected:
		EnumNctiFeatureBooleanMode m_eBooleanMode;
		NctiRenderSegmentItem* m_keyModel;
	private:
		bool m_bValid;
		std::vector<Ncti_Long> m_GFeatureIDVec;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif