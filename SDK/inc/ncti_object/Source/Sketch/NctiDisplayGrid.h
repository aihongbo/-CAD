#ifndef NctiDisplayGrid_H
#define NctiDisplayGrid_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiSketchComDefine.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDisplayGrid : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayGrid)
			NCTI_DISPLAYOBJECT_REQUIRE_CAMERA
	public:
		virtual ~NctiDisplayGrid();
		void Init(double	    i_dIntervalX,		//solid line interval
			double		i_dIntervalY,
			int			i_iNumDashLineX,	//how many dash lines 
			int			i_iNumDashLineY,
			EnumNctiGridDisplayDepth i_eGridDisplayDepth = NCTI_GRID_DEPTH_AUTO,
			EnumNctiGridDisplayMode i_eGridDisplayMode = NCTI_GRID_DISP_AUTO,
			bool        i_bSnapActive = true,
			double      i_dSnapIntervalX = 1,
			double      i_dSnapIntervalY = 1,
			double		i_dSnapIntervalZ = 1);
		virtual EnumNctiResult UpdateDisplay();
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiDoCallbackStatus Callback(
			NctiBaseView* i_pBaseView,
			EnumNctiDoCallbackType i_eType,
			NctiDisplayObject* i_pDoVariable);
		void SetDisplayDepth(EnumNctiGridDisplayDepth i_eGridDisplayDepth) { m_eGridDisplayDepth = i_eGridDisplayDepth; };
		EnumNctiGridDisplayDepth GetDisplayDepth() { return m_eGridDisplayDepth; };
		void SetDisplayMode(EnumNctiGridDisplayMode i_eGridDisplayMode);
		EnumNctiGridDisplayMode GetDisplayMode() { return m_eGridDisplayMode; };
		double GetIntervalX() { return m_dIntervalX; };
		void SetIntervalX(double i_dIntervalX);
		double GetIntervalY() { return m_dIntervalY; };
		void SetIntervalY(double i_dIntervalY);
		int GetNumDashLineX() { return m_iNumDashLineX; };
		void SetNumDashLineX(int i_iNumDashLineX) { m_iNumDashLineX = i_iNumDashLineX; };
		int GetNumDashLineY() { return m_iNumDashLineY; };
		void SetNumDashLineY(int i_iNumDashLineY) { m_iNumDashLineY = i_iNumDashLineY; };
		void SetSnapInterval(double i_dx, double i_dy, double i_dz);
		void GetSnapInterval(double& o_dx, double& o_dy, double& o_dz) { o_dx = m_dSnapIntervalX; o_dy = m_dSnapIntervalY; o_dz = m_dSnapIntervalZ; };
		void ActiveSnap(bool i_bOnOff);
		bool IsSnapActive() { return m_bSnapActive; };
		NctiPosition Snap(const NctiPosition& i_input);
		void SetUseUserDefine(bool i_bOnOff);
		bool GetUseUserDefine();
		void SetInternalDisplayMode(bool i_bOnOff);
		bool GetInternalDisplayMode();
		void SetUserDefineSnapInterval(double& i_dX, double& i_dY, double& i_dZ);
		void GetUserDefineSnapInterval(double& o_dX, double& o_dY, double& o_dZ);
	protected:
		void auto_set_grid_dense(NctiBaseView* i_pBaseView);
	private:
		double		m_dIntervalX;
		double		m_dIntervalY;
		int			m_iNumDashLineX;
		int			m_iNumDashLineY;
		EnumNctiGridDisplayDepth m_eGridDisplayDepth;
		EnumNctiGridDisplayMode m_eGridDisplayMode;
		double		m_dSnapIntervalX;
		double		m_dSnapIntervalY;
		double		m_dSnapIntervalZ;
		bool		m_bSnapActive;
		bool		m_bUseUserDefine;
		bool		m_bInternalDisplayMode;
		double		m_dUserDefineSnapIntervalX;
		double		m_dUserDefineSnapIntervalY;
		double		m_dUserDefineSnapIntervalZ;
	private:
		void Draw();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif