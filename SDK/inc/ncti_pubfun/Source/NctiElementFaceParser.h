#ifndef NctiElementFaceParser_H
#define NctiElementFaceParser_H
#include <vector>
#include <set>
#include <sstream>
#include <ncti_base.h>
namespace NCTI
{
	class NctiElementFaceParser
	{
	public:
		struct FaceTypeInfo
		{
			NctiElementType ElementType;
			std::string FaceType;
			std::vector<Ncti_UInteger> NodeIndexs;
		};

	private:
		NctiElementFaceParser();
		~NctiElementFaceParser();

		bool Find(const NctiElementType elemType, const std::vector<Ncti_UInteger>& nodeIndexs, FaceTypeInfo& info) const;
		
	public:
		static NctiElementFaceParser& instance();
		bool GetElementFaceType(const Ncti_UInteger elementId, const std::vector<Ncti_UInteger>& faceNodeIds, std::string& o_faceType);
	};
}
#endif
