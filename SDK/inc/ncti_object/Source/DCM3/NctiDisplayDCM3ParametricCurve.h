#ifndef NctiDisplayDCM3ParametricCurve_H
#define NctiDisplayDCM3ParametricCurve_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
#include <functional>
namespace NCTI
{
	class NctiDCM3Variable;
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3ParametricCurve : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3ParametricCurve)
	public:
		virtual ~NctiDisplayDCM3ParametricCurve();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1);
		Ncti_Boolean m_hasSumMat;
		Ncti_Double m_sumMat[4][4] = { 0 };
		Ncti_Double m_low, m_up;
		Ncti_Boolean m_periodic;
		Ncti_Long m_fitPtCount;
		Ncti_Double m_tol;
		std::vector<Ncti_Double> m_fdiscon_vals;
		std::function<void(const NctiDisplayDCM3Geometry* geo, double pt[3], double p1[3], double p2[3], int dcon_indx, double t, ncti_DCM3_discontinuity_side side)> m_evaluator_imp;
		std::function<void(const NctiDisplayDCM3Geometry* geo, double pt[3], int dcon_indx, double t, ncti_DCM3_discontinuity_side side)> m_func_imp;

		std::string m_exprX;
		std::string m_exprY;
		std::string m_exprZ;
		std::vector<NctiDCM3Variable*> m_vars;
	private:
		void transform_sum_mat(Ncti_Double i_mat[4][4]);
		void after_sum_mat(Ncti_Double* o_xyz, Ncti_Boolean i_isPoint) const;
		void firstDerivative(Ncti_Double o_der[3], int i_dcon_indx, double i_t, ncti_DCM3_discontinuity_side i_sid) const;
		void secondDerivative(Ncti_Double o_der[3], int i_dcon_indx, double i_t, ncti_DCM3_discontinuity_side i_sid) const;

	public:
		ncti_DCM3_g_type identify()	const { return NCTI_DCM3_PARAMETRIC_CURVE; }
		void SetEvaluatorImp(std::function<void(const NctiDisplayDCM3Geometry* geo, double pt[3], double p1[3], double p2[3], int dcon_indx, double t, ncti_DCM3_discontinuity_side side)> imp);
		void SetFuncImp(std::function<void(const NctiDisplayDCM3Geometry* geo, double pt[3], int dcon_indx, double t, ncti_DCM3_discontinuity_side side)> imp);
		void SetLimit(Ncti_Double i_low, Ncti_Double i_up, Ncti_Boolean i_isPeriodic);
		void SetDisconVals(const std::vector<Ncti_Double> & i_vals);
		void SetFitPtCount(Ncti_Long i_count);
	public:
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;

	public:
		std::function<void(const NctiDisplayDCM3Geometry* geo, double pt[3], double p1[3], double p2[3], int dcon_indx, double t, ncti_DCM3_discontinuity_side side)> evaluatorImp() const { return m_evaluator_imp; }
		std::function<void(const NctiDisplayDCM3Geometry* geo, double pt[3], int dcon_indx, double t, ncti_DCM3_discontinuity_side side)> funcImp() const { return m_func_imp; }
		Ncti_Double low() const { return m_low; }
		Ncti_Double up() const { return m_up; }
		Ncti_Boolean isPeriodic() const { return m_periodic; }
		const std::vector<Ncti_Double>& discon_vals() const { return m_fdiscon_vals; }
		Ncti_Long fitPtCount() const { return m_fitPtCount; };
		std::vector<NctiPosition> fitPt() const;
		NctiPosition pt(Ncti_Double i_param) const;

		ncti_DCM3_parametric_type limits(double* o_t_low, double* o_t_up)const;
		void evaluator(double o_pos[3], double o_firstDer[3], double o_secondDer[3], double i_t) const;

		int n_discons() const;
		void discon_values(double* o_tvals) const;
		void discon_data(double o_pos[3], double o_firstDer[3], double o_secondDer[3], int i_dcon_indx, double i_t, ncti_DCM3_discontinuity_side i_side) const;
		void setExpressionX(const char* i_expr);
		const char* getExpressionX() const { return m_exprX.c_str(); }
		const char* getExpressionY() const { return m_exprY.c_str(); }
		void setExpressionY(const char* i_expr);
		const char* getExpressionZ() const { return m_exprZ.c_str(); }
		void setExpressionZ(const char* i_expr);

		void addVariable(NctiDCM3Variable* i_pVar);
		const std::vector<NctiDCM3Variable*>& getVariables() const;
	};
}
#endif