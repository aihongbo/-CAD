#ifndef NctiDisplayDCM3DimSys_H
#define NctiDisplayDCM3DimSys_H
#include "dcl_ncti_object.h"
#include "NctiDisplayDCM3Object.h"
#include <map>
namespace NCTI
{
	class NctiDisplayDCM3Geometry;
	class NctiDCM3Variable;
	class NctiDCM3Equation;
	class DECL_NCTI_OBJECT NctiDisplayDCM3DimSys : public NctiDisplayDCM3Object
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDCM3DimSys)
	public:
		virtual ~NctiDisplayDCM3DimSys();
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();

	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			NCTI_DIM_SYS m_fdcm;
		std::vector<NctiDisplayDCM3Geometry*> m_GeometryVec;
		std::vector<NctiDCM3Variable*> m_VariableVec;
		std::vector<NctiDCM3Equation*> m_EquationVec;
		std::map<std::string, NCTI_D_NODE> m_DNodeMap;
		std::map<std::string, NCTI_P_NODE> m_PNodeMap;
		std::map<std::string, NCTI_R_NODE> m_RNodeMap;
	public:
		NCTI_DIM_SYS GetDimSys() { return m_fdcm; }
		void SetDimSys(NCTI_DIM_SYS i_pfdcm);

		void AddDCM3Geometry(NctiDisplayDCM3Geometry* i_DCMGeometry);
		const std::vector<NctiDisplayDCM3Geometry*>& GetDCM3GeometryVec() const { return m_GeometryVec; }
		void RemoveDCM3Geometry(NctiDisplayDCM3Geometry* i_pDCMGeom); 
		void ClearDCM3GeometryVec() { m_GeometryVec.clear(); }

		void AddDCM3Variable(NctiDCM3Variable* i_DCM3Variable);
		const std::vector<NctiDCM3Variable*>& GetDCM3VariableVec() const { return m_VariableVec; }
		void RemoveDCM3Variable(NctiDCM3Variable* i_pDCM3Var); 
		void ClearDCM3VariableVec() { m_VariableVec.clear(); }

		void AddDCM3Equation(NctiDCM3Equation* i_DCM3Equation);
		const std::vector<NctiDCM3Equation*>& GetDCM3EquationVec() const { return m_EquationVec; }
		void RemoveDCM3Equation(NctiDCM3Equation* i_pDCM3Equation); 
		void ClearDCM3EquationVec() { m_EquationVec.clear(); }

		int DNodeCount() const {return m_DNodeMap.size(); }
		void AddDNode(const std::string& i_name, NCTI_D_NODE i_dnode);
		std::string AddDNode(NCTI_D_NODE i_dnode);
		NCTI_D_NODE GetDNodeByName(const std::string& i_name) const;
		std::vector<NCTI_D_NODE> AllDNodes() const;
		void RemoveDNodeByName(const std::string& i_name) { m_DNodeMap.erase(i_name); }
		void ClearDNodes() { m_DNodeMap.clear(); }

		std::vector<std::string> PNodeNames() const;
		void AddPNode(const std::string& i_name, NCTI_P_NODE i_pnode);
		std::string AddPNode(NCTI_P_NODE i_pnode);
		NCTI_P_NODE GetPNodeByName(const std::string& i_name) const;
		void RemovePNodeByName(const std::string& i_name) { m_PNodeMap.erase(i_name); }
		void ClearPNodes() { m_PNodeMap.clear(); }

		int RNodeCount() const { return m_RNodeMap.size(); }
		void AddRNode(const std::string& i_name, NCTI_R_NODE i_rnode);
		std::string AddRNode(NCTI_R_NODE i_rnode);
		NCTI_R_NODE GetRNodeByName(const std::string& i_name) const;
		std::vector<NCTI_R_NODE> AllRNodes() const;
		void RemoveRNodeByName(const std::string& i_name) { m_RNodeMap.erase(i_name); }
		void ClearRNodes() { m_RNodeMap.clear(); }
	};
}
#endif