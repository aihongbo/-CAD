#ifndef NctiDisplayDCM3Spun_H
#define NctiDisplayDCM3Spun_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
#include <functional>
namespace NCTI
{
	class NctiDCMEXVec3d;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Spun : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Spun)
	public:
		virtual ~NctiDisplayDCM3Spun();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1);
		NctiDisplayDCM3Geometry* m_curve;
		NctiDCMEXVec3d m_spinPoint, m_spinDirect;
		Ncti_Double m_low, m_up;
		Ncti_Boolean m_periodic;
		std::function<void(const NctiDisplayDCM3Spun* geo, double t, double* c, double* cp, double* cpp)> m_evaluator_imp;

		Ncti_Double m_directTransMat[4][4];

	public:
		void InitCurve(NctiDisplayDCM3Geometry* i_curve);
		void InitEvaluatorImp(std::function<void(const NctiDisplayDCM3Spun* geo, double t, double* c, double* cp, double* cpp)> i_imp);
		void InitSpinPoint(const NctiDCMEXVec3d& i_point);
		void InitSpinDirect(const NctiDCMEXVec3d& i_direct);
		void InitLimit(Ncti_Double i_low, Ncti_Double i_up, Ncti_Boolean i_isPeriodic);
	public:
		virtual ncti_DCM3_g_type identify()	const override{ return NCTI_DCM3_SPIN_SURFACE; }
		virtual void ResetTransform() override;
		virtual std::string describe() const override;
		virtual void transform(double i_mat[4][4]) override;
	public:
		NctiDisplayDCM3Geometry* curve() const { return m_curve; }
		std::function<void(const NctiDisplayDCM3Spun* geo, double t, double* c, double* cp, double* cpp)> evaluatorImp() const {
			return m_evaluator_imp;
		}
		NctiDCMEXVec3d spinPoint() const { return m_spinPoint; }
		NctiDCMEXVec3d spinDirect()const { return m_spinDirect; }
		Ncti_Double low() const { return m_low; }
		Ncti_Double up() const { return m_up; }
		Ncti_Boolean isPeriodic() const { return m_periodic; }

		ncti_DCM3_parametric_type limits(double* i_t_low, double* i_t_up)const;
		void evaluator(double i_t, double o_pos[3], double o_firstDer[3], double o_secondDer[3]) const;
		void transfromCurve(double i_mat[4][4]);
		void transfromDirect(double i_mat[4][4]);
		void axis(double o_pos[3], double o_dir[3]) const;
		void getCurveTransMat(double o_mat[4][4]) const;
		void getDirectTransMat(double o_mat[4][4]) const;
	};
}
#endif