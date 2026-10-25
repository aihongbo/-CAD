#ifndef NctiDisplayDCMGeometry_H
#define NctiDisplayDCMGeometry_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCMDef.h"
#include "NctiDCMEXVec2d.h"
namespace NCTI
{
	class NctiDCMExExtensionData;
	class DECL_NCTI_OBJECT NctiHelpNode
	{
		NCTI_G_NODE m_g;
		NCTI_D_NODE m_d;

	public:
		NctiHelpNode(NCTI_G_NODE gi, NCTI_D_NODE di) { m_g = gi, m_d = di; }
		NCTI_G_NODE geometry() { return m_g; }
		NCTI_D_NODE dimension() { return m_d; }
	};
	class NctiDCMParametric;
	class NctiDisplayDCMDimSys;
	class NctiDisplayModelBody;
	class NctiDCMSet;
	class DECL_NCTI_OBJECT NctiDisplayDCMGeometry : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMGeometry)
			//NCTI_DISPLAYOBJECT_REQUIRE_INSTANCE_REDRAW
	public:
		virtual ~NctiDisplayDCMGeometry();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			ncti_g_node_status m_fstat;
		NCTI_G_NODE m_gnode;
		NctiDisplayDCMDimSys* m_DimSys;
		Ncti_Char* m_flabel;
		NctiDisplayModelBody* m_ModelBody;
		NctiDCMSet* m_fowner;
		NctiDisplayDCMGeometry* m_base;

		NctiDCMExExtensionData* m_f_lower_ext_data;
		NctiDCMExExtensionData* m_f_upper_ext_data;
	protected:
		Ncti_Boolean m_IsModify;
		Ncti_Boolean m_IsTransform;
		Ncti_Boolean m_IsDrag;
		Ncti_Double m_transformmat[3][3];
		Ncti_Double m_lastTransformmat[3][3];
	public:
		/**
		* @brief reset transformation status and matrix
		*/
		virtual void  ResetTransform();
		/**
		* @brief reset last transformation matrix and the offsets of internal freedoms
		*/
		virtual void  ResetLastTransform();
		/**
		* @brief reset modify status
		*/
		void ResetModify();
		/**
		* @brief get modify status
		* @return Ncti_Boolean
		*/
		Ncti_Boolean IsModify() { return m_IsModify; }
		/**
		* @brief mark as modified status
		*/
		void Modify() { m_IsModify = true; }
		/**
		* @brief mark as draged status if geometry is draged
		* @param[in] i_boo, is draged or not
		*/
		void SetDrag(bool boo) { m_IsDrag = boo; }
		/**
		* @brief get draged status
		* @return Ncti_Boolean
		*/
		Ncti_Boolean IsDrag() const { return m_IsDrag; }
		/**
		* @brief get changed status
		* @return Ncti_Boolean
		*/
		Ncti_Boolean IsChanged() const { return m_IsTransform || m_IsModify; }
		/**
		* @brief get transform status
		* @return Ncti_Boolean
		*/
		Ncti_Boolean Get_transformType() const { return m_IsTransform; }
		/**
		* @brief set transform status
		* @param[in] i_isTransform, is transformed or not
		*/
		void Set_transformType(Ncti_Boolean i_isTransform) { m_IsTransform = i_isTransform; }
		/**
		* @brief get transform matrix
		* @param[out] o_mat, transform matrix
		*/
		void Get_transformmat(Ncti_Double o_mat[3][3]) const;
		/**
		* @brief get last transform matrix
		* @param[out] o_mat, transform matrix
		*/
		void Get_lastTransformmat(Ncti_Double o_mat[3][3]) const;
	public:
		/**
		* @brief get geometry type
		* @return ncti_DCM3_g_type
		*/
		virtual ncti_DCM_g_type identify() const { return NCTI_DCM_UNKNOWN; }
		/**
		* @brief get extension geometry type
		* @return NctiDCMEXGType
		*/
		virtual NctiDCMEXGType type() const { return EX_UNKNOWN; }
		/**
		* @brief transform circular pattern element data, previous matrix will be covered
		* @param[in] i_mat, transform matrix
		*/
		virtual void transform(Ncti_Double i_mat[3][3]);
		/**
		* @brief get the json describe string of the current object data
		* @return std::string
		*/
		virtual std::string describe() const;
	public:
		/**
		* @brief get the base geometry where the geometry is belong to
		* @return NctiDisplayDCM3Geometry object pointer
		*/
		NctiDisplayDCMGeometry* get_base() const { return m_base; }
		/**
		* @brief set the base geometry where the geometry is belong to
		* @param[in] i_base, geometry object pointer
		*/
		void set_base(NctiDisplayDCMGeometry* i_base) { m_base = i_base; }
		/**
		* @brief get the rigid set where the geometry is located
		* @return NctiDCM3Set object pointer
		*/
		NctiDCMSet* get_owner() const { return m_fowner; }
		/**
		* @brief set the rigid set where the geometry is located
		* @param[in] i_set, rigid set
		*/
		void set_owner(NctiDCMSet* i_set) { m_fowner = i_set; }
		/**
		* @brief set the geometry status
		* @param[in] i_status, geometry node status
		*/
		void set_status(ncti_g_node_status i_stat);
		/**
		* @brief get the geometry status
		* @return ncti_DCM3_g_node_status
		*/
		ncti_g_node_status status() const { return m_fstat; }
		/**
		* @brief get the geometry node
		* @return NCTI_G_NODE, geometry node pointer
		*/
		NCTI_G_NODE get_g_node()  const { return m_gnode; }
		/**
		* @brief set the geometry node
		* @param[in] i_gn, eometry node pointer
		*/
		void set_g_node(NCTI_G_NODE i_gn);
		/**
		* @brief get dimension system
		* @return NctiDisplayDCM3DimSys object pointer
		*/
		NctiDisplayDCMDimSys* get_dcm() const { return m_DimSys; }
		void set_dcm(NctiDisplayDCMDimSys* i_pDimSys);
		/**
		* @brief set the geometry label
		* @param[in] i_new_label, geometry label
		*/
		void set_label(const Ncti_Char* i_new_label);
		/**
		* @brief get the geometry label
		* @return Ncti_Char*
		*/
		const Ncti_Char* label_c_str() const { return m_flabel; }
		/**
		* @brief set model body which the geometry is connected
		* @param[in] i_pModelBody, model body object pointer
		*/
		void SetModelBody(NctiDisplayModelBody* i_pModelBody);
		/**
		* @brief get model body which the geometry is connected
		* @return NctiDisplayModelBody object pointer
		*/
		NctiDisplayModelBody* GetModelBody() const { return m_ModelBody; }
		/**
		* @brief get extension data
		* @param[in] i_end, parametric curve extension min or max end
		* @return NctiDCMExExtensionData object pointer
		*/
		NctiDCMExExtensionData* get_ext_data(ncti_DCM_para_ext_end i_end) const;
		/**
		* @brief get extension data
		* @param[in] i_end, parametric curve extension min or max end
		* @param[in] i_end, parametric curve extension end type
		*/
		void set_ext_data(ncti_DCM_para_ext_end i_end, const NctiDCMExExtensionData& i_ex_data);
		/**
		* @brief remove extension data
		* @param[in] i_end, parametric curve extension min or max end
		* @return bool
		*/
		bool remove_extension(ncti_DCM_para_ext_end i_end);
	};
}
#endif
