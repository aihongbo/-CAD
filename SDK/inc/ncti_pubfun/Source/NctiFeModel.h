#ifndef NctiFeModel_H
#define NctiFeModel_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <vector>
#include <set>
#include <sstream>
#include <NctiPhyParaDef.h>
#include <map>
#include <ctime> 
namespace NCTI
{
	class NctiDisplayGridMesh;
	class NctiDisplayLoadObject;
	class NctiDisplaySinglePointConstraint;
	class NctiDisplayPressure;
	class NctiDisplayConcentratedForces;
	class NctiDisplayLoadMoment;
	class NctiDisplayLoadGravity;
	class NctiDisplayInertiaRelief;
	class NctiDisplayStep;
	class NctiDisplayFBStep;
	class NctiDisplayOutput;
	class NctiDisplayMaterialAttribute;
	class NctiDisplaySet;
	class NctiDisplaySection;
	class NctiDisplayCoupling;
	class NctiDisplayTie;
	class NctiPosition;

	struct NctiFeSurface
	{
		std::string Name;
		std::string Type;
		std::vector<std::string> SurfSets;
		std::vector<std::string> EleBoundaryIds;//单元的面或边标识，面：S1、S2...,边：E1、E2...
		//NctiDisplayPressure* Pressure{nullptr};
		NctiDisplaySet* Set{nullptr};
	};

	struct NctiFeMesh
	{
		const NctiDisplayGridMesh* GridMesh{nullptr};
		std::map<Ncti_UInteger, NctiPosition> Nodes;//节点编号-位置
		Ncti_LongLong LastNodeNum;//
		std::map<Ncti_UInteger, std::vector<Ncti_UInteger>> Elements;//单元编号-节点编号数组
		std::map<std::string, std::set<Ncti_UInteger>> ElementTypes;//单元类型-单元编号数组
		std::map<std::string, std::set<Ncti_UInteger>> Nsets;
		std::map<std::string, std::set<Ncti_UInteger>> Elsets;
		std::vector<NctiFeSurface> Surfaces;
		//std::string MatName;
		//std::string SectionType;
		std::vector<NctiDisplaySet*> SetVec;
		std::vector<NctiDisplaySection*> SectionVec;
		std::vector<NctiDisplayCoupling*> CouplingVec;
		std::vector<std::string> SectionTypes;
		std::vector<std::string> SectionSetNames;
	};

	struct NctiFeLoad
	{
		Ncti_LoadType LoadType{ NCTI_CONCENTRATED_FORCE };
		std::vector<Ncti_UInteger> IDs;
		std::vector<std::vector<Ncti_UInteger>> DirectionsVec;
		std::vector <std::vector<Ncti_Double>> ForcesVec;
		Ncti_Boolean IsSet{ false };
		std::string SetName;
		std::string LoadName;
	};

	struct NctiFeBoundary
	{
		std::vector<Ncti_UInteger> NodeIds;
		std::vector<Ncti_UInteger> Components;
		std::vector<Ncti_Double> Values;
		Ncti_Boolean IsSet{ false };
		std::string SetName;
		std::string BCName;
	};

	struct NctiFeOutput
	{
		std::string OutputType;
		std::vector<std::string> NodeVars;
		std::vector<std::string> ElementVars;
		std::map<std::string, std::string> OutputOptionMap;
		std::map<std::string, std::string> NodeOptionMap;
		std::map<std::string, std::string> ElementOptionMap;
	};
	struct NctiStep
	{
		std::string Name;
		std::string Type;
		std::vector<NctiFeBoundary> Boundaries;
		std::vector<NctiFeOutput> OutputVec;
		std::vector<NctiFeLoad> Loads;
		std::vector<double> StepValues;
		bool Nlgeom{ false };
	};
	struct NctiStaticStep : NctiStep
	{
		NctiStaticStep()
		{
			Type = "STATIC";
		}
	};

	struct NctiFBStep : NctiStep
	{
		NctiFBStep()
		{
			Type = "";
		}
		Ncti_FrequencyMode Mode{ NCTI_ORDER };
		Ncti_UInteger Order{ 0 };
		std::pair<Ncti_Double, Ncti_Double> Range;
		std::map<std::string, std::string> OptionMap;
	};

	struct NctiFrequencyStep : NctiFBStep
	{
		NctiFrequencyStep()
		{
			Type = "FREQUENCY";
		}
	};

	struct NctiBuckleStep : NctiFBStep
	{
		NctiBuckleStep()
		{
			Type = "BUCKLE";
		}
	};

	class DECL_NCTI_PUBFUN NctiFeModel
	{
		std::vector<NctiDisplayGridMesh*> m_gridMeshes;
		std::vector<NctiDisplayStep*> m_stepObjs;
	public:
		NctiFeModel(const std::vector<NctiDisplayGridMesh*>& gridMesheVec,
			const std::vector<NctiDisplayStep*>& stepObjVec);
		~NctiFeModel();

		const std::string& ModelName() const { return m_modelName; }
		const std::tm& DateTime() const { return m_dateTime;}
		const std::vector<NctiFeMesh*>& Meshs() const { return m_meshs; }
		//const std::map<Ncti_UInteger, NctiPosition>& Nodes() const { return m_nodes; }
		//const std::map<Ncti_UInteger, std::vector<Ncti_UInteger>>& Elements() const { return m_elements; }
		//const std::map<std::string, std::set<Ncti_UInteger>>& ElementTypes() const { return m_elementTypes; }
		//const std::map<std::string, std::set<Ncti_UInteger>>& Nsets() const { return m_Nsets; }
		//const std::map<std::string, std::set<Ncti_UInteger>>& Elsets() const { return m_Elsets; }
		//const std::vector<NctiFeSurface>& Surfaces() const { return m_surfaces; }
		//const std::vector<std::string>& SectionTypes() const { return m_sectionTypes; }
		const std::vector<NctiStep*>& Steps() const { return m_steps; }
		const std::vector<NctiDisplayTie*>& Ties() const { return m_ties; }
		std::vector<NctiDisplayMaterialAttribute*> m_MatVec;

	private:
		std::string m_modelName;
		std::tm m_dateTime;
		std::vector<NctiFeMesh*> m_meshs;
		//std::map<Ncti_UInteger,NctiPosition> m_nodes;//节点编号-位置
		//std::map<Ncti_UInteger, std::vector<Ncti_UInteger>> m_elements;//单元编号-节点编号数组
		//std::map<std::string, std::set<Ncti_UInteger>> m_elementTypes;//单元类型-单元编号集合
		//std::map<std::string, std::set<Ncti_UInteger>> m_Nsets;//节点集合名称-节点编号集合
		//std::map<std::string, std::set<Ncti_UInteger>> m_Elsets;//单元集合名称-单元编号集合
		//std::vector<NctiFeSurface> m_surfaces;
		//std::set<std::string> m_matNames;
		//std::vector<std::string> m_sectionTypes;
		std::vector<NctiStep*> m_steps;
		std::vector<NctiDisplayTie*> m_ties;
	private:
		void Init();
		void GetHeading();
		void GetNodes();
		void GetElements();
		//void GetNodeSets();
		//void GetElementSets();
		void GetSurfaces();
		void GetMaterials();
		void GetSections();
		void GetSteps();
		void GetSets();
		void GetLoads(NctiStep* o_pStep, const std::vector<NctiDisplayLoadObject*>& loadObjs);
		void GetBoundaries(NctiStep* o_pStep, const std::vector<NctiDisplaySinglePointConstraint*>& spcObjs);
		void GetOutputs(NctiStep* o_pStep, const std::vector<NctiDisplayOutput*>& outputObjs);
		void GetTie();
	private:
		void GetConcentratedForces(const NctiDisplayConcentratedForces* i_pForces, NctiStep* o_pStep);
		void GetMoment(const NctiDisplayLoadMoment* i_pMoment, NctiStep* o_pStep);
		void GetPressure(const NctiDisplayPressure* i_pPressure, NctiStep* o_pStep);
		void GetGravity(const NctiDisplayLoadGravity* i_pGravity, NctiStep* o_pStep);
		void GetInertiaRelief(const NctiDisplayInertiaRelief* i_pRelief, NctiStep* o_pStep);
	private:
		void GetFrequency(const NctiDisplayFBStep* i_pStepObj, NctiFBStep* o_pStep);
	};
}
#endif
