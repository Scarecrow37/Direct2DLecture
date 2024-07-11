#pragma once
#include "../../../../Engine/FSM/Transition.h"

class MovementComponent;
namespace PlayerTransition
{
    class WalkToIdle : public Transition
    {
    public:
        WalkToIdle(MovementComponent* movementComponent);
        bool operator()(float deltaTime) override;

    private:
        MovementComponent* _movementComponent;
    };
}
