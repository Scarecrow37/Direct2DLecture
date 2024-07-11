#pragma once
#include "../../../../Engine/FSM/Transition.h"

class MovementComponent;

namespace MonsterTransition
{
    class ToIdle : public Transition
    {
    public:
        ToIdle(GameObject* target, GameObject* owner);
        bool operator()(float deltaTime) override;

    private:
        GameObject* _chaseTarget;
        GameObject* _owner;

    };
}
