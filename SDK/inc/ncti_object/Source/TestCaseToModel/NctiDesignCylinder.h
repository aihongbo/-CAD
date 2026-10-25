#ifndef NctiDesignCylinder_H
#define NctiDesignCylinder_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignCylinder : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignCylinder)
	public:
		virtual ~NctiDesignCylinder();
		virtual void Init();
		virtual std::string GeneratePyScript();
		void SetPoint(NctiPosition pt);
		void SetRadius(Ncti_Double dRadius);
		void SetHeight(Ncti_Double dHeight);
		void SetXAxis(NctiVector vec);
		void SetZAxis(NctiVector vec);
		Ncti_Double GetRadius() { return m_dRadius; }
		Ncti_Double GetHeight() { return m_dHeight; }
		NctiVector GetXAxis() { return m_XAxis; }
		NctiVector GetZAxis() { return m_ZAxis; }
	private:
		NctiPosition m_pt;
		Ncti_Double m_dRadius;
		Ncti_Double m_dHeight;
		NctiVector m_XAxis;
		NctiVector m_ZAxis;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignCylinder_H
