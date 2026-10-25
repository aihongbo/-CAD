#ifndef NctiDisplayDCMDimension_H
#define NctiDisplayDCMDimension_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCMDef.h"
#include <iostream>
namespace NCTI
{
	class NctiDisplayDCMGeometry;
	class NctiDCMHelpData;
	class NctiDCMDirectedData;
	class NctiDisplayDCMDimSys;
	class NctiDCMVariable;
	class NctiDCMEXVec2d;

	class DECL_NCTI_OBJECT NctiDisplayDCMDimension : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMDimension)
	public:
		virtual ~NctiDisplayDCMDimension();
		virtual void Init();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		ncti_DCM_d_type	m_dim_type;
		double		m_dim_value;
		NctiDisplayDCMGeometry* m_fend1;
		NctiDCMHelpData* m_fhelp1;
		NctiDisplayDCMGeometry* m_fend2;
		NctiDCMHelpData* m_fhelp2;
		// for symmetry, midpoint (no help NctiDCMPoint)
		NctiDisplayDCMGeometry* m_fend3;
		// for equal distance
		NctiDisplayDCMGeometry* m_fend4;
		NctiDCMDirectedData* m_fdir;
		double m_fwinding_angle; // for arc lengths only
		bool m_fhas_winding_angle; // for arc lengths only
		ncti_DCM_half_space m_fhalf1;
		ncti_DCM_half_space m_fhalf2;
		// For equal distances
		ncti_DCM_ed_alignment m_fed_alignment;
		// For tangent 
		ncti_DCM_tan_alignment m_ftan_alignment;
		// For normal 
		ncti_DCM_norm_alignment m_fnorm_alignment;
		// For symmetry
		ncti_DCM_sym_alignment m_fsym_alignment;
		// For parallel/perpendicular
		ncti_DCM_alignment m_falignment;

		ncti_DCM_d_rigidity m_frigidity;

		// For patterns only 
		int m_fpattern_multiplier1;
		int m_fpattern_multiplier2;

		// Application information
		NctiDisplayDCMDimension* m_fpair1;
		NctiDisplayDCMDimension* m_fpair2;
		bool m_fis_autodimension;
		bool m_fbeing_changed;

		// DCM pointers
		NctiDisplayDCMDimSys* m_fdcm;
		NCTI_D_NODE m_fdcm_node;

		//help
		NctiDCMEXVec2d* m_dir;

		NctiDCMVariable* m_pVar;
		
		std::vector< NctiDisplayDCMGeometry*> m_pConsGeomVec;
	public:
		// Simple constructor
		void InitDimension(ncti_DCM_d_type i_dt = NCTI_DCM_DISTANCE, double i_value = 0.0);
		// Alternative constructor with ends
		void InitDimension(ncti_DCM_d_type i_dt, NctiDisplayDCMGeometry* i_g1, NctiDisplayDCMGeometry* i_g2, double i_value = 0.0);
		// With one or two help points
		void InitDimension(ncti_DCM_d_type i_dt, double i_value, NctiDisplayDCMGeometry* i_g1, NctiDCMEXVec2d* i_hp1,
			NctiDisplayDCMGeometry* i_g2 = NULL, NctiDCMEXVec2d* i_hp2 = NULL);
		// With one help parameter
		void InitDimension(ncti_DCM_d_type i_dt, double i_value, NctiDisplayDCMGeometry* i_g1, double i_hpar);
		// Directed distance
		void InitDimension(double i_value, const NctiDCMEXVec2d* i_dir, NCTI_G_NODE i_gn = NULL,
			ncti_DCM_directed_type i_ty = NCTI_DCM_FIXED_DIRECTION);
		// For 2D patterns only
		void InitDimension(ncti_DCM_d_type i_dt, int i_m1, int i_m2);
	public:
		void initialise(ncti_DCM_d_type i_dt, double i_value);
		void set_ends(NctiDisplayDCMGeometry* i_end1, NctiDisplayDCMGeometry* i_end2 = NULL, NctiDisplayDCMGeometry* i_end3 = NULL, NctiDisplayDCMGeometry* i_end4 = NULL);
		void set_pattern_multipliers(int i_m1, int i_m2);
		int help_point(NctiDisplayDCMGeometry* i_g, NctiDCMEXVec2d* i_hpt);
		void set_help_point(NctiDisplayDCMGeometry* i_g, NctiDCMEXVec2d* i_hpt);
		double help_parameter(NctiDisplayDCMGeometry* i_g);
		ncti_DCM_ellipse_parameter ellipse_help_parameter(NctiDisplayDCMGeometry* i_g);
		void set_help_parameter(NctiDisplayDCMGeometry* i_g, double i_hpar);
		void set_help_parameters(double i_hpar1, double i_hpar2);
		void set_help_parameter_f(double i_hpar);
		void set_help_parameter_e(double i_hpar);
		NctiDCMHelpData* help1() const { return m_fhelp1; }
		NctiDCMHelpData* help2() const { return m_fhelp2; }
		NctiDCMHelpData* get_help_data(NctiDisplayDCMGeometry* i_g) const;

		void set_directed(ncti_DCM_directed_type i_dt, const NctiDCMEXVec2d& i_dir, NCTI_G_NODE i_g = nullptr);
		void set_directed_type(ncti_DCM_directed_type i_t);
		void set_directed_dir(const NctiDCMEXVec2d& i_dir);
		void set_directed_g(NCTI_G_NODE i_gn);
		ncti_DCM_directed_type get_directed(NctiDCMEXVec2d* o_dir, NCTI_G_NODE* o_g) const;

		ncti_DCM_d_type type() const { return m_dim_type; }
		double value() const;

		void set_type(ncti_DCM_d_type i_sdim_type); 
		void set_value(double i_val); 

		void set_winding_angle(double i_angle) { m_fwinding_angle = i_angle; m_fhas_winding_angle = NCTI_DCM_TRUE; }
		double winding_angle() const { return m_fwinding_angle; }
		NCTI_DCM_logical has_winding_angle() const { return m_fhas_winding_angle; }

		NctiDisplayDCMGeometry* end1() const { return m_fend1; }
		NctiDisplayDCMGeometry* end2() const { return m_fend2; }
		NctiDisplayDCMGeometry* end3() const { return m_fend3; }
		NctiDisplayDCMGeometry* end4() const { return m_fend4; }

		void set_half_space(NctiDisplayDCMGeometry* i_ag, ncti_DCM_half_space i_hs);
		void set_half_space1(ncti_DCM_half_space i_hs) { m_fhalf1 = i_hs; }
		void set_half_space2(ncti_DCM_half_space i_hs) { m_fhalf2 = i_hs; }
		ncti_DCM_half_space get_half_space(NctiDisplayDCMGeometry* i_ag);
		
		ncti_DCM_half_space get_half_space1() const { return m_fhalf1; }
		ncti_DCM_half_space get_half_space2() const { return m_fhalf2; }

		int pattern_multiplier1() const { return m_fpattern_multiplier1; }
		int pattern_multiplier2() const { return m_fpattern_multiplier2; }

		void set_pairs(NctiDisplayDCMDimension* i_p1, NctiDisplayDCMDimension* i_p2) { m_fpair1 = i_p1; m_fpair2 = i_p2; }
		NctiDisplayDCMDimension* get_pair1() const { return m_fpair1; }
		NctiDisplayDCMDimension* get_pair2() const { return m_fpair2; }

		void set_ed_alignment(ncti_DCM_ed_alignment i_alignment);
		ncti_DCM_ed_alignment get_ed_alignment() const { return m_fed_alignment; }
		void set_tan_alignment(ncti_DCM_tan_alignment i_alignment);
		ncti_DCM_tan_alignment get_tan_alignment() const { return m_ftan_alignment; }

		void set_norm_alignment(ncti_DCM_norm_alignment i_alignment);
		ncti_DCM_norm_alignment get_norm_alignment() const { return m_fnorm_alignment; }

		void set_sym_alignment(ncti_DCM_sym_alignment i_alignment);
		ncti_DCM_sym_alignment get_sym_alignment() const { return m_fsym_alignment; }

		void set_alignment(ncti_DCM_alignment i_alignment);
		
		ncti_DCM_alignment get_alignment() const { return m_falignment; }

		NCTI_DCM_logical is_autodimension() const { return m_fis_autodimension; }
		void set_autodimension(bool ad) { m_fis_autodimension = ad; }

		//NCTI_D_NODE add_to_dcm(NctiDisplayDCMDimSys* dsp);
 		//void remove_from_dcm();
		NCTI_D_NODE get_dcm_node() const { return m_fdcm_node; }
 		void set_dcm_node(NCTI_D_NODE dn) { m_fdcm_node = dn; }

		ncti_DCM_d_rigidity rigidity();
		void set_rigidity(ncti_DCM_d_rigidity i_dr){m_frigidity = i_dr;}
		void set_being_changed(bool i_t) { m_fbeing_changed = i_t; }
		bool being_changed() const { return m_fbeing_changed; }

		void set_variable(NctiDCMVariable* i_pVar);
		NctiDCMVariable* get_variable() { return m_pVar; }

		void SetConsGeometries(const std::vector<NctiDisplayDCMGeometry*>& i_GeomVec) { m_pConsGeomVec = i_GeomVec; }
		std::vector< NctiDisplayDCMGeometry*> GetConsGeometries() const { return  m_pConsGeomVec; }
	};
}
#endif
