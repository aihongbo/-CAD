#ifndef NctiDesignFillet_H
#define NctiDesignFillet_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignFillet : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignFillet)
	public:
		virtual ~NctiDesignFillet();
		virtual void Init();
		virtual std::string GeneratePyScript();
		void SetModelName(std::string ModelName);
		bool SetFillet(
			const std::string& name, 
			const std::vector<Ncti_Long>& edgeIDVec, 
			const std::vector<Ncti_Double>& radiusVec);
		const std::vector<Ncti_Double>& GetRadius() { return m_RadiusVec; }
		const std::string& GetModelName() { return m_ModelName; }
	private:
		std::string m_ModelName;
		std::vector<Ncti_Long> m_EdgeIDVec;
		std::vector<Ncti_Double> m_RadiusVec;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignFillet_H
