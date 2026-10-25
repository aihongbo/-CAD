#ifndef NctiDisplayGRevolve_H
#define NctiDisplayGRevolve_H
#include "NctiDisplayGFeature.h"
#include "ncti.h"
#include "dcl_ncti_object.h"
#include "NctiSketchComDefine.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayGRevolve : public NctiDisplayGFeature
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGRevolve)
	public:
		void Init();
		virtual ~NctiDisplayGRevolve();
		virtual bool	    MoveActualToWork();

		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoVariable);
		virtual EnumNctiResult CreateModelBody(NCTI_MODEL_TAG& i_pDoBodyCreated, NctiDisplayDocCustomContainer* i_pDocCustomContaine) override;
		bool	GetReverse();
		void	SetReverse(bool i_bReverse);
		bool	GetUseAngle();
		void	SetUseAngle(bool i_bUseAngle);
		void	GetAngle(double& o_dStartAngle, double& o_dEndAngle);
		void	SetAngle(double i_dStartAngle, double i_dEndAngle);
		void    SetAxisVisibility(bool i_bOnOff);
		void	SetEditMode(bool i_bEdit) { m_bEdit = i_bEdit; };
		bool	IsEditMode() { return m_bEdit; };

	private:
		bool	m_bReverse;
		bool	m_bUseAngle;
		double	m_dStartAngle;
		double	m_dEndAngle;

		NctiPosition		m_cOrigin;
		NctiVector	m_cAxis;

		bool	m_bEdit;
	};
}
#endif
