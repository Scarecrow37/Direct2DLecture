#pragma once
#include "../../../../Engine/FSM/Transition.h"


class MovementComponent;

namespace PlayerTransition
{
    class IdleToWalk final : public Transition
    {
    public:
        IdleToWalk(MovementComponent* movementComponent);
        bool operator()(float deltaTime) override;

    private:
        MovementComponent* _movementComponent;
    };
}
