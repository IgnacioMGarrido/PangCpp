#ifndef _IDYNAMIC_MOVEMENT_
#define _IDYNAMIC_MOVEMENT_
#include "../../../../../../common/core.h"

class IDynamicMovementComp
{
public:
    virtual const vec2& GetPos() const = 0;
};

#endif