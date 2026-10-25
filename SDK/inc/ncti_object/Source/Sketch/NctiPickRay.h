#ifndef NctiPickRay_H
#define NctiPickRay_H
#include "ncti.h"
#include "NctiPosition.h"
#include "NctiUnitVector.h"
namespace NCTI
{
	class NctiVector;
	class NctiPickRay : public NCTI_BASE_CLASS
	{
		NctiPickRay() {};
	public:
		NctiPickRay(const NctiPosition& i_pos, const NctiUnitVector& i_vec);
		NctiPickRay(const NctiPosition& i_pos, const NctiVector& i_vec);
		NctiPosition point() const;
		NctiUnitVector direction() const;
		void set_point(const NctiPosition& i_pos);
		void set_direction(const NctiUnitVector& i_vec);

	protected:
		NctiPosition root_point;
		NctiUnitVector ray_direction;
	};
}
#endif

