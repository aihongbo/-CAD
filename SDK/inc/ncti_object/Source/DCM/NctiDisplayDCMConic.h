#ifndef NctiDisplayDCMConic_H
#define NctiDisplayDCMConic_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCMGeometry.h"
#include "NctiDisplayDCMPoint.h"
#include "NctiDCMDef.h"
namespace NCTI
{
	class NctiDCMEXVec2d;
	class DECL_NCTI_OBJECT NctiDisplayDCMConic : public NctiDisplayDCMGeometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMConic)
	public:
		virtual ~NctiDisplayDCMConic();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_f_rho;
		NctiDisplayDCMPoint* m_pStartPoint;
		NctiDisplayDCMPoint* m_pMidPoint;
		NctiDisplayDCMPoint* m_pEndPoint;
		NctiDCMEXVec2d m_st;
		NctiDCMEXVec2d m_ctrl;
		NctiDCMEXVec2d m_en;
	public:
		void Set_g_st(NctiDisplayDCMPoint* i_st);
		void Set_g_ctrl(NctiDisplayDCMPoint* i_ctrl);
		void Set_g_en(NctiDisplayDCMPoint* i_en);
		void Set_st(const NctiDCMEXVec2d& i_st);
		void Set_ctrl(const NctiDCMEXVec2d& i_ctrl);
		void Set_en(const NctiDCMEXVec2d& i_en);
		void SetRHO(const double& i_rho);
	public:
		virtual std::string describe() const override;
		virtual ncti_DCM_g_type identify() const override { return NCTI_DCM_CONIC; }
		virtual NctiDCMEXGType type() const override { return EX_CONIC; }
		virtual void transform(Ncti_Double i_mat[3][3]) override;
	public:
		void set_rho(const double& i_rho) { m_f_rho = i_rho; }
		double rho() const { return m_f_rho; }

		bool vector_defined() const { return m_pStartPoint == NULL; }
		void update_vectors(NctiDCMEXVec2d& i_st, NctiDCMEXVec2d& i_ctrl, NctiDCMEXVec2d& i_en);

		NCTI_G_NODE start_cp() const { return m_pStartPoint->get_g_node(); }
		NCTI_G_NODE mid_cp() const { return m_pMidPoint->get_g_node(); }
		NCTI_G_NODE end_cp() const { return m_pEndPoint->get_g_node(); }

		NctiDCMEXVec2d start_point() const { return vector_defined() ? m_st : m_pStartPoint->value(); }
		NctiDCMEXVec2d mid_point() const { return vector_defined() ? m_ctrl : m_pMidPoint->value(); }
		NctiDCMEXVec2d end_point() const { return vector_defined() ? m_en : m_pEndPoint->value(); }
	};
}
#endif