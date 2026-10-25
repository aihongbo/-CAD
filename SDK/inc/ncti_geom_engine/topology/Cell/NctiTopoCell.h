#ifndef NctiTopoCell_H
#define NctiTopoCell_H
#include "NctiTopoShape.h"
namespace NCTI
{
	class DECL_NCTI_GEOM_ENGINE NctiTopoCell : public NctiTopoShape
	{
		NCTI_GEOM_FUNCTIONS(NctiTopoCell)
	public:
		NctiTopoCell();
		virtual ~NctiTopoCell();
	private:

	};
}
#endif
