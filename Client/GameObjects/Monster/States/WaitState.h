#pragma once
#include "../../../FSM/States/AnimationState.h"

class MovementComponent;

class WaitState : public AnimationState
{
public:
    WaitState(int animationIndex, AnimationScene* animationScene, MovementComponent* movementComponent);

    void Enter() override;
    void Update(float deltaTime) override;

private:
    MovementComponent* _movementComponent;
};
