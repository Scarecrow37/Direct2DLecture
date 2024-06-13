#pragma once
#include "../../Interfaces/IInitialize.h"
#include "../../Interfaces/IUpdate.h"

class ITimeSystem : public IInitialize, public IUpdate
{
public:
    virtual float GetDeltaTime() const = 0;
};
