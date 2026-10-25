#ifndef NctiDesignChamfer_H
#define NctiDesignChamfer_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignChamfer : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignChamfer)
	public:
		virtual ~NctiDesignChamfer();
		virtual void Init();
		virtual std::string GeneratePyScript();
		//圆角
		bool SetFillet(
			const std::string& name, 
			const std::vector<Ncti_Long>& edgeIDVec, 
			const std::vector<Ncti_Double>& angleVec);
		//斜角
		bool SetBevelAngle(
			const std::string& name,
			const std::vector<Ncti_Long>& edgeIDVec,
			const std::vector<Ncti_Long>& faceIDVec,
			const std::vector<Ncti_Double>& distanceVec);
	private:
		std::string m_ModelName;
		std::vector<Ncti_Long> m_EdgeIDVec;
		std::vector<Ncti_Long> m_FaceIDVec;
		std::vector<Ncti_Double> m_DistanceVec;
		std::vector<Ncti_Double> m_AngleVec;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignChamfer_H
