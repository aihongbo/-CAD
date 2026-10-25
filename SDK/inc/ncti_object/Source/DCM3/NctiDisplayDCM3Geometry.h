#ifndef NctiDisplayDCM3Geometry_H
#define NctiDisplayDCM3Geometry_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Object.h"
#include "NctiDCMEXVec3d.h"
#include "NctiDCM3Def.h"
namespace NCTI
{
	class NctiDisplayDCM3DimSys;
	class NctiDisplayModelBody;
	class NctiDCM3Set;
	/**
	* @brief the base class of constraint geometries
	* @details create a constraint geometry
	* @see NctiDisplayGModelObject
	*/
	class DECL_NCTI_OBJECT NctiDisplayDCM3Geometry : public NctiDisplayDCM3Object
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3Geometry)
			//NCTI_DISPLAYOBJECT_REQUIRE_INSTANCE_REDRAW
	public:
		virtual ~NctiDisplayDCM3Geometry();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_G_NODE m_gnode;
		NctiDisplayDCM3DimSys* m_DimSys;
		Ncti_Char* m_flabel;
		NctiDisplayModelBody* m_ModelBody;
		NctiDCM3Set* m_fowner;
		ncti_DCM3_g_node_status m_status;
		NctiDisplayDCM3Geometry* m_base;
	protected:
		Ncti_Boolean m_IsModify;
		Ncti_Boolean m_IsTransform;
		Ncti_Boolean m_IsDrag;
		Ncti_Double m_transformmat[4][4];
		Ncti_Double m_lastTransformmat[4][4];
	public:
		/**
		* @brief reset transformation status and matrix
		*/
		virtual void ResetTransform();
		/**
		* @brief reset last transformation matrix and the offsets of internal freedoms
		*/
		virtual void ResetLastTransform();
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
		void SetDrag(bool i_boo) { m_IsDrag = i_boo;}
		/**
		* @brief get draged status
		* @return Ncti_Boolean
		*/
		Ncti_Boolean IsDrag() const { return m_IsDrag; }
		/**
		* @brief get changed status
		* @return Ncti_Boolean
		*/
		Ncti_Boolean IsChanged() const { return m_IsTransform||m_IsModify; }
		/**
		* @brief get transform status
		* @return Ncti_Boolean
		*/
		Ncti_Boolean Get_transformType() { return m_IsTransform; }
		/**
		* @brief set transform status
		* @param[in] i_isTransform, is transformed or not
		*/
		void Set_transformType(Ncti_Boolean i_isTransform) { m_IsTransform = i_isTransform; }
		/**
		* @brief get transform matrix
		* @param[out] o_mat, transform matrix
		*/
		void Get_transformmat(Ncti_Double o_mat[4][4]);
		/**
		* @brief get last transform matrix
		* @param[out] o_mat, transform matrix
		*/
		void Get_lasTransformmat(Ncti_Double o_mat[4][4]);
	public:
		/**
		* @brief get geometry type
		* @return ncti_DCM3_g_type
		*/
		virtual ncti_DCM3_g_type identify() const {return NCTI_DCM3_UNKNOWN;}
		/**
		* @brief transform circular pattern element data, previous matrix will be covered
		* @param[in] i_mat, transform matrix
		*/
		virtual void transform(Ncti_Double i_mat[4][4]);
		/**
		* @brief get the json describe string of the current object data
		* @return std::string
		*/
		virtual std::string describe() const;
		/**
		* @brief set radius or major radius, only required for circles/ellipses/spheres/cyinders/torus
		* @param[in] i_radius, radius or major radius
		*/
		virtual void set_radius(double i_radius) { }
		/**
		* @brief set minor radius, only required for ellipses/torus
		* @param[in] i_radius, minor radius
		*/
		virtual void set_minor_radius(double i_radius) { }
		/**
		* @brief get radius or major radius
		* @return double
		*/
		virtual double radius() const { return 0; }
		/**
		* @brief get minor radius
		* @return double
		*/
		virtual double minor_radius() const { return 0; }
		/**
		* @brief get radius or major radius offset value
		* @return double
		*/
		virtual double radius_offset() const { return 0; }
		/**
		* @brief get minor radius offset value
		* @return double
		*/
		virtual double minor_radius_offset() const { return 0; }
		
	public:
		/**
		* @brief get the rigid set where the geometry is located
		* @return NctiDCM3Set object pointer
		*/
		NctiDCM3Set* get_owner() const { return m_fowner; }
		/**
		* @brief set the rigid set where the geometry is located
		* @param[in] i_set, rigid set
		*/
		void set_owner(NctiDCM3Set* i_set) { m_fowner = i_set; }
		/**
		* @brief get the base geometry where the geometry is belong to
		* @return NctiDisplayDCM3Geometry object pointer
		*/
		NctiDisplayDCM3Geometry* get_base() const { return m_base; }
		/**
		* @brief set the base geometry where the geometry is belong to
		* @param[in] i_base, geometry object pointer
		*/
		void set_base(NctiDisplayDCM3Geometry* i_base) { m_base = i_base; }
		/**
		* @brief set the geometry status
		* @param[in] i_status, geometry node status
		*/
		void set_status(ncti_DCM3_g_node_status i_status) { m_status = i_status; }
		/**
		* @brief get the geometry status
		* @return ncti_DCM3_g_node_status
		*/
		ncti_DCM3_g_node_status status() const { return m_status; }
		/**
		* @brief get the geometry node
		* @return NCTI_G_NODE, geometry node pointer
		*/
		NCTI_G_NODE get_g_node()  { return m_gnode; }
		/**
		* @brief set the geometry node
		* @param[in] i_gn, eometry node pointer
		*/
		void set_g_node(NCTI_G_NODE i_gn);
		/**
		* @brief get dimension system
		* @return NctiDisplayDCM3DimSys object pointer
		*/
		NctiDisplayDCM3DimSys* get_dcm() const { return m_DimSys; }
		/**
		* @brief set dimension system
		* @param[in] i_pDimSys, NctiDisplayDCM3DimSys object pointer
		*/
		void set_dcm(NctiDisplayDCM3DimSys* i_pDimSys);
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
		NctiDisplayModelBody* GetModelBody() { return m_ModelBody; }
	};
}
#endif
