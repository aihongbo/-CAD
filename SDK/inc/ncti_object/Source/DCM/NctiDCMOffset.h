#ifndef NctiDCMOffset_H
#define NctiDCMOffset_H
#include "dcl_ncti_object.h"
#include "NctiDCMParametric.h"
#include "NctiDCMDef.h"
#include <ostream>
namespace NCTI
{
	class NctiDCMEXVec2d;
	class NctiDisplayDCMPoint;
	class NctiDisplayDCMLine;
	class NctiDisplayDCMCircle;
	class NctiDisplayDCMSpline;
	class NctiDisplayDCMConic;
	class NctiDisplayDCMEllipse;
	class DECL_NCTI_OBJECT NctiDCMOffset : public NctiDCMParametric
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCMOffset)
	public:
		virtual ~NctiDCMOffset();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

		NctiDisplayDCMGeometry* m_fbase;
		double m_fdistance;
		NctiDCMEXVec2d m_offsetDir;
		ncti_DCM_offset_side m_fapplication_side;
	public:
		void InitOffset(NctiDisplayDCMGeometry* i_pGeom, double i_distance, ncti_DCM_offset_side i_side = NCTI_DCM_OFFSET_RIGHT);
	public:
		virtual std::string describe() const override;
		virtual NctiDCMEXGType type() const override { return EX_OFFSETCURVE; }
		// Parametric functions
		virtual NctiDCMEXVec2d direction() const override;
		virtual NctiDCMEXVec2d position(double i_param) override;
		virtual NctiDCMEXVec2d first_der(double i_param) override;
		virtual NctiDCMEXVec2d second_der(double i_param) override;

	public:
		// offset specific functions
		double distance() const { return m_fdistance; }
		double distance_to_root() const;
		ncti_DCM_offset_side dcm_side() const;
		ncti_DCM_offset_side application_side() const { return m_fapplication_side; }
		void set_distance(double i_dist); 
		void set_offset_side(bool i_right);
		void set_offset_dir(const NctiDCMEXVec2d& dir);
		NctiDCMEXVec2d offset_dir() const { return m_offsetDir; }

		NctiDisplayDCMGeometry* get_offset_base() const { return m_fbase; }
	};
}
#endif