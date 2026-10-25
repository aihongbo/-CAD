#ifndef NctiDisplayPlane_H
#define NctiDisplayPlane_H
#include "NctiDisplayGModelObject.h"
namespace NCTI
{
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiDisplayPlane : public NctiDisplayGModelObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayPlane)
	public:
		virtual ~NctiDisplayPlane();
		virtual void GetCoordinate(NctiPosition& o_cOrigin, NctiUnitVector& o_cXAxis, NctiUnitVector& o_YAxis) = 0;
		virtual void SetCoordinate(const NctiPosition& i_posOrigin, const NctiUnitVector& i_uvecXAxis, const NctiUnitVector& i_uvecYAxis);
		Ncti_Double ComputeDistanceToPoint(NctiPosition& i_posTarget); 
		virtual NctiTransf	GetTransform();
	};
}
#endif