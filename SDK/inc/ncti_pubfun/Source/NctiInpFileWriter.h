#ifndef NctiInpFileWriter_H
#define NctiInpFileWriter_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <vector>
#include <sstream>
namespace NCTI
{
	class NctiDisplayGridMesh;
	class NctiDisplayStep;
	class NctiFeModel;
	struct NctiFeMesh;
	class DECL_NCTI_PUBFUN NctiInpFileWriter
	{
	public:
		NctiInpFileWriter();
		~NctiInpFileWriter();

	public:
		static bool Write(const char* filename, 
			const std::vector<NctiDisplayGridMesh*>& gridMesheVec,
			const std::vector<NctiDisplayStep*>& stepObjVec,
			const Ncti_Boolean& bReducedIntegration);
	private:
		void AppendHeading(std::ostringstream& oss, const NctiFeModel& feModel);
		void AppendNodes(std::ostringstream& oss, NctiFeMesh* feMesh);
		void AppendElements(std::ostringstream& oss, NctiFeMesh* feMesh, const Ncti_Boolean& bReducedIntegration);
		void AppendNodeSets(std::ostringstream& oss, NctiFeMesh* feMesh, bool bAssembly);
		void AppendElementSets(std::ostringstream& oss, NctiFeMesh* feMesh, bool bAssembly);
		void AppendSurfaces(std::ostringstream& oss, NctiFeMesh* feMesh, bool bAssembly);
		void AppendSections(std::ostringstream& oss, NctiFeMesh* feMesh);
		void AppendCoupling(std::ostringstream& oss, NctiFeMesh* feMesh);
		void AppendMaterials(std::ostringstream& oss, const NctiFeModel& feModel);
		void AppendSteps(std::ostringstream& oss, const NctiFeModel& feModel);
	};
}
#endif
