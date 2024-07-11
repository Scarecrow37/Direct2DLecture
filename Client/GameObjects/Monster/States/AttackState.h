#pragma once
#include "../../../FSM/States/AnimationState.h"

class MovementComponent;

class AttackState : public AnimationState
{
public:
    AttackState(int animationIndex, AnimationScene* animationScene, MovementComponent* movementComponent);

    void Update(float deltaTime) override;

private:
    MovementComponent* _movementComponent;
};
