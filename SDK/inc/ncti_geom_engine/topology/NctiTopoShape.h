#ifndef NctiTopoShape_H
#define NctiTopoShape_H
#include "NctiGEObject.h"
#include <vector>
#include "NctiTransf.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiTopoShape : public NctiGEObject
	{
		NCTI_GEOM_FUNCTIONS(NctiTopoShape)
	public:
		NctiTopoShape();
		virtual ~NctiTopoShape();
	protected:
		virtual void OnAddShape(NctiTopoShape* i_pShape){}
	public:
		void AddShape(NctiTopoShape* i_pShape);
	public:
		NCTI_MODEL_TAG GetLinkVoid() { return m_LinkVoid; }
		const std::vector<NctiTopoShape*>& GetShapeVec() { return m_TopoShapeVec; }
		NCTI_GE_ATT_DEF(size_t, m_ShapeHash)
	private:
		NCTI_GE_ATT_DEF(NCTI_MODEL_TAG, m_LinkVoid)
		std::vector<NctiTopoShape*> m_TopoShapeVec;
		NCTI_GE_ATT_DEF(Ncti_Orientation, m_Orientation)
		NCTI_GE_ATT_DEF(NctiTransf, m_Tranf)
	};
}
#endif
