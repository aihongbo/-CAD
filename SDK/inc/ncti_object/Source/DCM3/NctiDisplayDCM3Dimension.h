#ifndef NctiDisplayDCM3Dimension_H
#define NctiDisplayDCM3Dimension_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Object.h"
#include "NctiDCM3Def.h"
#include <iostream>
namespace NCTI
{
	class NctiDisplayDCM3Geometry;
	class NctiDCM3DirectedData;
	class NctiDisplayDCM3DimSys;
	class NctiDCM3DimInfo;
	class NctiDCMEXVec3d;
	class NctiDCM3PatternConstraint;
	class DECL_NCTI_OBJECT NctiDisplayDCM3Dimension : public NctiDisplayDCM3Object
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Dimension)
	public:
		virtual ~NctiDisplayDCM3Dimension();
		virtual void Init();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NctiDisplayDCM3DimSys* m_pDimSys;
		std::vector< NctiDisplayDCM3Geometry*> m_pConsGeomVec;
		NctiDisplayDCM3Geometry* m_fend1;
		NctiDisplayDCM3Geometry* m_fend2;
		NctiDisplayDCM3Geometry* m_fend3;
		NctiDCM3DimInfo* m_finfo1;
		NctiDCM3DimInfo* m_finfo2;
		ncti_DCM3_d_type	m_dim_type;
		double		m_dim_value;
		double		m_dim_min;
		double		m_dim_max;
		NCTI_DCM3_logical	m_dim_hasmin;
		NCTI_DCM3_logical	m_dim_hasmax;
		ncti_DCM3_alignment	m_dim_align;	// for directed constraints only
		ncti_DCM3_alignment	m_dim_align2;	// for ellipse-ellipse coincident only
		ncti_DCM3_surface_orientation m_dim_orient;
		ncti_DCM3_dimension_to m_fdim_to1;
		ncti_DCM3_dimension_to m_fdim_to2;
		ncti_DCM3_d_type m_frad_type1;
		ncti_DCM3_d_type m_frad_type2;
		NCTI_DCM3_logical m_frigid;
		NctiDCM3PatternConstraint* m_fpatcon;
		NCTI_D_NODE m_fd_node;
	private:
		void initDimension();
	public:
		void InitDimension(ncti_DCM3_d_type i_dt, double i_val, ncti_DCM3_alignment i_align);
		void InitDimension(ncti_DCM3_d_type i_dt, double i_val);
		void InitDimension(ncti_DCM3_d_type i_dt, ncti_DCM3_alignment i_align = NCTI_DCM3_ALIGNMENT_NOT_SPECIFIED);
		void InitDimension(ncti_DCM3_d_type i_dt, NctiDisplayDCM3Geometry* i_g1, NctiDisplayDCM3Geometry* i_g2);
		// used for planar angle dimension - third arg is axis	
		void InitDimension(ncti_DCM3_d_type i_dt, double i_val, NctiDisplayDCM3Geometry* i_g1, NctiDisplayDCM3Geometry* i_g2, NctiDisplayDCM3Geometry* i_g3 = NULL);
		void InitDimension(ncti_DCM3_d_type i_dt, NctiDisplayDCM3Geometry* i_g1, NctiDisplayDCM3Geometry* i_g2, NctiDisplayDCM3Geometry* i_g3);
		void SetConsGeometries(const std::vector<NctiDisplayDCM3Geometry*>& i_GeomVec) { m_pConsGeomVec = i_GeomVec; }
		std::vector< NctiDisplayDCM3Geometry*> GetConsGeometries() const { return  m_pConsGeomVec; }
	public:
		void set_type(ncti_DCM3_d_type i_sdim_type) { m_dim_type = i_sdim_type; }
		ncti_DCM3_d_type type() const { return m_dim_type; }
		void set_dcm_node(NCTI_D_NODE i_dn) { m_fd_node = i_dn; }
		NCTI_D_NODE dcmnode() const { return m_fd_node; }

		void set_value(double i_val);
		double value() const { return m_dim_value; }
		void set_bounds(double i_minv, double i_maxv) { m_dim_min = i_minv; m_dim_hasmin = NCTI_DCM3_TRUE; m_dim_max = i_maxv; m_dim_hasmax = NCTI_DCM3_TRUE; }
		void set_rigid(NCTI_DCM3_logical i_rigid) { m_frigid = i_rigid; }
		void set_min(double i_minv) { m_dim_min = i_minv; m_dim_hasmin = NCTI_DCM3_TRUE; }
		void set_max(double i_maxv) { m_dim_max = i_maxv; m_dim_hasmax = NCTI_DCM3_TRUE; }
		double get_min() const { return m_dim_min; }
		double get_max() const { return m_dim_max; }
		NCTI_DCM3_logical rigid() const { return m_frigid; }
		NCTI_DCM3_logical get_hasmin() const { return m_dim_hasmin; }
		NCTI_DCM3_logical get_hasmax() const { return m_dim_hasmax; }

		void set_surf_orient(ncti_DCM3_surface_orientation i_orient) { m_dim_orient = i_orient; }
		ncti_DCM3_surface_orientation surf_orient() const { return m_dim_orient; }

		void set_alignment(ncti_DCM3_alignment i_align) { m_dim_align = i_align; }
		ncti_DCM3_alignment 	alignment() const { return m_dim_align; }
		void set_alignment2(ncti_DCM3_alignment i_align) { m_dim_align2 = i_align; }
		ncti_DCM3_alignment 	alignment2() const { return m_dim_align2; }

		void set_ends(NctiDisplayDCM3Geometry* i_g1, NctiDisplayDCM3Geometry* i_g2) { m_fend1 = i_g1; m_fend2 = i_g2; }
		NctiDisplayDCM3Geometry* end1() const { return m_fend1; }
		NctiDisplayDCM3Geometry* end2() const { return m_fend2; }
		NctiDisplayDCM3Geometry* end3() const { return m_fend3; }
		void set_end3(NctiDisplayDCM3Geometry* i_g) { m_fend3 = i_g; }

		void set_half_space(NctiDisplayDCM3Geometry* i_ag, ncti_DCM3_half_space i_hsp);
		ncti_DCM3_half_space half_space(NctiDisplayDCM3Geometry* i_ag);

		NctiDCM3DimInfo* get_info(NctiDisplayDCM3Geometry* i_ag, NCTI_DCM3_logical i_create = NCTI_DCM3_FALSE);
		void set_dimension_point(NctiDisplayDCM3Geometry* i_ag, ncti_DCM3_help_points i_hp, NctiDCMEXVec3d i_hpp);
		void update_dimension_point(NctiDisplayDCM3Geometry* i_ag, NctiDCMEXVec3d i_hpp);
		ncti_DCM3_help_points dimension_point(NctiDisplayDCM3Geometry* i_ag, NctiDCMEXVec3d* o_hpp);

		void set_dimension_parameter(NctiDisplayDCM3Geometry* i_ag, double i_hpar, bool i_isUpdated = true);
		double dimension_parameter(NctiDisplayDCM3Geometry* i_ag);

		void set_dimension_parameters(NctiDisplayDCM3Geometry* i_ag, double i_upar, double i_vpar);
		void dimension_parameters(NctiDisplayDCM3Geometry* i_ag, double* o_upar, double* o_vpar);

		void set_dim_to1(ncti_DCM3_dimension_to i_dimto) { m_fdim_to1 = i_dimto; }
		void set_dim_to2(ncti_DCM3_dimension_to i_dimto) { m_fdim_to2 = i_dimto; }
		void set_dim_to(NctiDisplayDCM3Geometry* i_ag, ncti_DCM3_dimension_to i_dimto);
		ncti_DCM3_dimension_to get_dim_to1() const { return m_fdim_to1; }
		ncti_DCM3_dimension_to get_dim_to2() const { return m_fdim_to2; }
		ncti_DCM3_dimension_to get_dim_to(NctiDisplayDCM3Geometry* i_ag);

		void set_rad_type1(ncti_DCM3_d_type i_rt) { m_frad_type1 = i_rt; }
		void set_rad_type2(ncti_DCM3_d_type i_rt) { m_frad_type2 = i_rt; }
		void set_rad_type(NctiDisplayDCM3Geometry* i_ag, ncti_DCM3_d_type i_rt);
		ncti_DCM3_d_type get_rad_type1() const { return m_frad_type1; }
		ncti_DCM3_d_type get_rad_type2() const { return m_frad_type2; }
		ncti_DCM3_d_type get_rad_type(NctiDisplayDCM3Geometry* i_ag);

		void set_pattern_constraint(NctiDCM3PatternConstraint* i_pPatCons) { m_fpatcon = i_pPatCons; }
		NctiDCM3PatternConstraint* get_pattern_constraint() { return m_fpatcon; }

		void set_dcm(NctiDisplayDCM3DimSys* i_pDimSys) { m_pDimSys = i_pDimSys; }
		NctiDisplayDCM3DimSys* get_dcm() const { return m_pDimSys; }
	};
}
#endif
