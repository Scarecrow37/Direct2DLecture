#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
    void Update(float deltaTime) override;
protected:
    FiniteStateMachine _fsm;
};
