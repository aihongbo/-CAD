#ifndef NctiDisplayDCM3Swept_H
#define NctiDisplayDCM3Swept_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
#include <functional>

namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Swept : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Swept)
	public:
		virtual ~NctiDisplayDCM3Swept();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDisplayDCM3Geometry* m_curve;
		NctiDCMEXVec3d m_direction_swept;
		Ncti_Double m_low, m_up;
		Ncti_Boolean m_periodic;
		std::function<void(const NctiDisplayDCM3Swept* geo, double t, double *c, double *cp, double *cpp)> m_evaluator_imp;

		Ncti_Double m_directTransMat[4][4];
	public:
		void InitCurve(NctiDisplayDCM3Geometry* i_curve);
		void InitDirectionSwept(const NctiDCMEXVec3d& i_direction);
		void InitEvaluatorImp(std::function<void(const NctiDisplayDCM3Swept* geo, double t, double* c, double* cp, double* cpp)> i_imp);
		void InitLimit(Ncti_Double i_low, Ncti_Double i_up, Ncti_Boolean i_isPeriodic);
	public:
		virtual ncti_DCM3_g_type identify()	const override { return NCTI_DCM3_SWEEP_SURFACE; }
		virtual std::string describe() const override;
		virtual void transform(double i_mat[4][4]) override;
	public:
		NctiDisplayDCM3Geometry* curve() const { return m_curve; }
		NctiDCMEXVec3d directionSwept() const { return m_direction_swept; }
		Ncti_Double low() const { return m_low; }
		Ncti_Double up() const { return m_up; }
		Ncti_Boolean isPeriodic() const { return m_periodic; }
		std::function<void(const NctiDisplayDCM3Swept* geo, double t, double* c, double* cp, double* cpp)> evaluatorImp() const {
			return m_evaluator_imp;
		}

		ncti_DCM3_parametric_type sweep_limits(double* o_t_low, double* o_t_up)const;
		void sweep_evaluator(double i_t, double o_pos[3], double o_firstDer[3], double o_secondDer[3]) const;
		void sweep_direction(double o_dir[3]) const;
		void transfromCurve(double i_mat[4][4]);
		void transfromDirect(double i_mat[4][4]);
		void getCurveTransMat(double o_mat[4][4]) const;
		void getDirectTransMat(double o_mat[4][4]) const;
	};
}
#endif