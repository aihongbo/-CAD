#ifndef NCTIAIMODELEXTRUSIONIDENTIFIEROBJECT_H
#define NCTIAIMODELEXTRUSIONIDENTIFIEROBJECT_H

#include "ncti_base.h"

namespace NCTI
{
    struct NctiAiExtrusionIdentifierObject
    {
        Ncti_Long extrusionFaceId;
        std::vector<Ncti_Long> secondaryFaceId;
    };
}

#endif // !NCTIAIMODELSYSTEMOBJECT_H

