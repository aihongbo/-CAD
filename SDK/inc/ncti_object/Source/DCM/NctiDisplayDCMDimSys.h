#ifndef NctiDisplayDCMDimSys_H
#define NctiDisplayDCMDimSys_H
#include "dcl_ncti_object.h"
#include "NctiDisplayGModelObject.h"
#include "NctiDCMDef.h"
#include <map>
namespace NCTI
{
	class NctiDCMVariable;
	class NctiDCMEquation;
	class NctiDisplayDCMGeometry;
	class DECL_NCTI_OBJECT NctiDisplayDCMDimSys : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCMDimSys)
	public:
		virtual ~NctiDisplayDCMDimSys();
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			NCTI_DIM_SYS m_fdcm;
		std::vector<NctiDisplayDCMGeometry*> m_DCMGeometryVec;
		std::vector<NctiDCMVariable*> m_VariableVec;
		std::vector<NctiDCMEquation*> m_EquationVec;
		std::map<std::string, NCTI_D_NODE> m_DNodeMap;
		std::map<std::string, NCTI_P_NODE> m_PNodeMap;
		std::map<std::string, NCTI_R_NODE> m_RNodeMap;
		std::map<std::string, NCTI_V_NODE> m_VNodeMap;

		double m_tol_linear;
		double m_tol_angular;
		bool m_autoconstrain;
	public:
		NCTI_DIM_SYS GetDimSys() const { return m_fdcm; }
		void SetDimSys(NCTI_DIM_SYS i_pfdcm);

		void SetTolerances(const Ncti_Double i_tol_linear, const Ncti_Double i_tol_angular);
		void GetTolerances(Ncti_Double& o_tol_linear, Ncti_Double& o_tol_angular);

		void SetAtuoConstrain(bool i_boo);
		bool IsAtuoConstrain() const { return m_autoconstrain; }

		void AddDCMGeometry(NctiDisplayDCMGeometry* i_DCMGeometry);
		const std::vector<NctiDisplayDCMGeometry*>& GetDCMGeometryVec() const { return m_DCMGeometryVec; }
		void RemoveDCMGeometry(NctiDisplayDCMGeometry* i_pDCMGeom);
		void ClearDCMGeometryVec() { m_DCMGeometryVec.clear(); }

		void AddDCMVariable(NctiDCMVariable* i_DCMVariable);
		const std::vector<NctiDCMVariable*>& GetDCMVariableVec() const { return m_VariableVec; }
		void RemoveDCMVariable(NctiDCMVariable* i_pDCMVar); 
		void ClearDCMVariableVec() { m_VariableVec.clear(); }

		void AddDCMEquation(NctiDCMEquation* i_DCMEquation);
		const std::vector<NctiDCMEquation*>& GetDCMEquationVec() const { return m_EquationVec; }
		void RemoveDCMEquation(NctiDCMEquation* i_pDCMEquation);
		void ClearDCMEquationVec() { m_EquationVec.clear(); }

		int DNodeCount() const { return m_DNodeMap.size(); }
		std::vector< NCTI_D_NODE> GetAllDNodes() const;
		void AddDNode(const std::string& i_name, NCTI_D_NODE i_dnode);
		std::string AddDNode(NCTI_D_NODE i_dnode);
		NCTI_D_NODE GetDNodeByName(const std::string& i_name) const;
		void RemoveDNodeByName(const std::string& i_name) { m_DNodeMap.erase(i_name); }
		void RemoveDNode(NCTI_D_NODE i_dn);
		void ClearDNodes() { m_DNodeMap.clear(); }

		void AddPNode(const std::string& i_name, NCTI_P_NODE i_pnode);
		std::string AddPNode(NCTI_P_NODE i_pnode);
		NCTI_P_NODE GetPNodeByName(const std::string& i_name) const; 
		void RemovePNodeByName(const std::string& i_name) { m_PNodeMap.erase(i_name); }
		void RemoveRNode(NCTI_R_NODE i_rn);
		void ClearPNodes() { m_PNodeMap.clear(); }

		int RNodeCount() const { return m_RNodeMap.size(); }
		std::vector< NCTI_R_NODE> GetAllRNodes() const;
		void AddRNode(const std::string& i_name, NCTI_R_NODE i_rnode);
		std::string AddRNode(NCTI_R_NODE i_rnode);
		NCTI_R_NODE GetRNodeByName(const std::string& i_name) const;
		void RemoveRNodeByName(const std::string& i_name) { m_RNodeMap.erase(i_name); }
		void ClearRNodes() { m_RNodeMap.clear(); }
	};
}
#endif