#pragma once
#include "../../../FSM/States/AnimationState.h"

class MovementComponent;

class ChaseState : public AnimationState
{
public:
    ChaseState(int animationIndex, AnimationScene* animationScene, MovementComponent* movementComponent, GameObject* target, GameObject* owner);

    void Update(float deltaTime) override;

private:
    GameObject* _target;
    GameObject* _owner;
    MovementComponent* _movementComponent;
};
