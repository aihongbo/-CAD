#ifndef NctiDCM3Variable_H
#define NctiDCM3Variable_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Object.h"
#include "NctiDCM3Def.h"
#include <set>
namespace NCTI
{
	class NctiDisplayDCM3Dimension;
	class NctiDisplayDCM3Geometry;
	class NctiDCM3Equation;
	class DECL_NCTI_OBJECT NctiDCM3Variable : public NctiDisplayDCM3Object
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3Variable)
	public:
		virtual ~NctiDCM3Variable();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		double m_value;
		bool m_value_seted;
		const char* m_name;
		double* m_bindValue;
		NCTI_DR_NODE m_dim_node;
		NCTI_V_NODE m_vnode;
		std::set<NctiDCM3Equation*> m_owners;
		ncti_DCM3_g_node_status m_status;
		NctiDisplayDCM3Dimension* m_pDimension;
	public:
		void InitVariable(const char* i_name, double i_val);
		void InitVariable(const char* i_name, Ncti_Address i_node, NctiDisplayDCM3Dimension* i_pDim);
	public:
		virtual std::string describe() const;
	public:
		void AddOwner(NctiDCM3Equation* i_pEquation);
		void RemoveFromOwner();
		bool BindComponent(NctiDisplayDCM3Geometry* i_pGeom, ncti_DCM3_geometry_component i_component);

		void set_status(ncti_DCM3_g_node_status i_status) { m_status = i_status; }
		ncti_DCM3_g_node_status status() const { return m_status; }
		bool has_value() const { return m_value_seted; }
		double value() const;
		void set_value(double i_val);
		NCTI_V_NODE vnode() { return m_vnode; }
		void set_vnode(NCTI_V_NODE i_vn);
		Ncti_Address dim_node() const { return m_dim_node; }
		NctiDisplayDCM3Dimension* dimension() const { return m_pDimension; }
		const char* name() { return m_name; }

	
	};
}
#endif