#ifndef NctiDesignTransform_H
#define NctiDesignTransform_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDesignModelObject.h"
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDesignTransform : public NctiDesignModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDesignTransform)

	public:
		enum TRANSFORM_TYPE
		{
			TRANSFORM_UNKNOWN = -1,
			TRANSFORM_MOVE = 0,
			TRANSFORM_SCALE = 1,
			TRANSFORM_ROTATE = 2
		};
		virtual ~NctiDesignTransform();
		virtual void Init();
		virtual std::string GeneratePyScript();
		void SetTransformType(TRANSFORM_TYPE BooleanType);
		void SetPoint(NctiPosition pt);
		void SetScale(Ncti_Double scale);
		void SetAngle(Ncti_Double angle);
		void SetVector(NctiVector vec);
		Ncti_Double GetScale() { return m_dScale; }
		Ncti_Double GetAngle() { return m_dAngle; }
		NctiPosition GetPoint() { return m_pt; }
		NctiVector GetVector() { return m_Vector; }
	private:
		NctiPosition m_pt;
		Ncti_Double m_dScale;		//缩放比例
		Ncti_Double m_dAngle;		//旋转角度
		NctiVector m_Vector;
		TRANSFORM_TYPE m_TransformType;
		std::vector<std::string> m_BaseModelNames;
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	};
	
}
#endif // !NctiDesignTransform_H
