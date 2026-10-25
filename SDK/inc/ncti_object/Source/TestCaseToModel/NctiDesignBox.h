#ifndef NctiDesignBox_H
#define NctiDesignBox_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignBox : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignBox)
	public:
		virtual ~NctiDesignBox();
		virtual void Init();
		virtual std::string GeneratePyScript();
		void SetPoint(NctiPosition pt);
		void SetLength(Ncti_Double dLength);
		void SetWidth(Ncti_Double dWidth);
		void SetHeight(Ncti_Double dHeight);
		void SetXAxis(NctiVector vec);
		void SetZAxis(NctiVector vec);
		NctiPosition GetPoint() { return m_pt; }
		Ncti_Double GetLength() { return m_dLength; }
		Ncti_Double GetWidth() { return m_dWidth; }
		Ncti_Double GetHeight() { return m_dHeight; }
		NctiVector GetXAxis() { return m_XAxis; }
		NctiVector GetZAxis() { return m_ZAxis; }
	private:
		NctiPosition m_pt;
		Ncti_Double m_dLength;
		Ncti_Double m_dWidth;
		Ncti_Double m_dHeight;
		NctiVector m_XAxis;
		NctiVector m_ZAxis;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignBox_H
