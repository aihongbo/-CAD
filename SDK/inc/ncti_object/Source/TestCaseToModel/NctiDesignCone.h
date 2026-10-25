#ifndef NctiDesignCone_H
#define NctiDesignCone_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignCone : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignCone)
	public:
		virtual ~NctiDesignCone();
		virtual void Init();
		virtual std::string GeneratePyScript();
		void SetPoint(NctiPosition pt);
		void SetHeight(Ncti_Double dHeight);
		void SetAngle(Ncti_Double dAngle);
		void SetRadius(Ncti_Double dTopRadius, Ncti_Double dButtonRadius);
		void SetXAxis(NctiVector vec);
		void SetZAxis(NctiVector vec);
		void GetRadius(Ncti_Double& dTopRadius, Ncti_Double& dButtonRadius);
		Ncti_Double GetHeight();
		Ncti_Double GetAngle();
		NctiPosition GetPoint();
		NctiVector GetXAxis();
		NctiVector GetZAxis();
	private:
		NctiPosition m_pt;
		Ncti_Double m_dHeight;
		Ncti_Double m_dTopRadius;
		Ncti_Double m_dButtonRadius;
		Ncti_Double m_dAngle;
		NctiVector m_XAxis;
		NctiVector m_ZAxis;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignCone_H
