#include "pch.h"
#include "WaitState.h"

#include "../../../../Engine/Component/MovementComponent.h"

WaitState::WaitState(int animationIndex, AnimationScene* animationScene, MovementComponent* movementComponent)
    : AnimationState(animationIndex, animationScene), _movementComponent(movementComponent)
{
}

void WaitState::Enter()
{
    AnimationState::Enter();
    _movementComponent->SetDirection(Vector::Zero());
}

void WaitState::Update(const float deltaTime)
{
    AnimationState::Update(deltaTime);
    _movementComponent->SetDirection(Vector::Zero());
}
