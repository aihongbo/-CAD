#ifndef NctiDCM3Set_H
#define NctiDCM3Set_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Geometry.h"
#include "NctiDCM3Def.h"
#include <vector>
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCM3Set : public NctiDisplayDCM3Geometry
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDCM3Set)
	public:
		virtual ~NctiDCM3Set();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		std::vector<NctiDisplayDCM3Geometry*> m_fmembers;
		ARRAY_4x4 m_finstance_transform;
		ncti_DCM3_dof m_all_dof;

		NctiDisplayModelBody* m_pOriBody;
		std::map<NctiDisplayDCM3Geometry*, long> m_CellIdMap;
	public:
		virtual ncti_DCM3_g_type identify() const override { return NCTI_DCM3_SET; }
		virtual void transform(double i_mat[4][4]) override;
		virtual std::string describe() const override;
	public:
		void set_dof(ncti_DCM3_dof i_dof = NCTI_DCM3_DOF_ALL) { m_all_dof = i_dof; }
		ncti_DCM3_dof get_dof() const { return m_all_dof; }

		void clone_original_body();
		NctiDisplayModelBody* get_original_body() { return m_pOriBody; }

		// Operations to add/remove member geometry
		int add_to_set(NctiDisplayDCM3Geometry* i_gn); 		//associate with set (no dcm operation)
		int remove_from_set(NctiDisplayDCM3Geometry* i_gn);	//disassociate from set (no dcm operation)

		int num() const { return m_fmembers.size(); }
		NctiDisplayDCM3Geometry* member(size_t i_index) const { return m_fmembers[i_index]; }
		NCTI_G_NODE member_gnode(size_t i_index) const { return m_fmembers[i_index]->get_g_node(); }

		void set_instance_transform(double i_mat[4][4]);
		void set_instance_vector(const NctiDCMEXVec3d& i_vec);
		ARRAY_4x4 instance_transform() const { return m_finstance_transform; }

		void set_cell(NctiDisplayDCM3Geometry* i_gn, long i_cellID);
		bool get_cell(NctiDisplayDCM3Geometry* i_gn, long& o_cellID);
	};
}
#endif