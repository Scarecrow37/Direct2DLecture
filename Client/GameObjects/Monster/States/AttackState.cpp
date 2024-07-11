#include "pch.h"
#include "AttackState.h"

#include "../../../../Engine/Component/MovementComponent.h"

AttackState::AttackState(int animationIndex, AnimationScene* animationScene, MovementComponent* movementComponent)
    : AnimationState(animationIndex, animationScene),
      _movementComponent(movementComponent)
{
}

void AttackState::Update(float deltaTime)
{
    AnimationState::Update(deltaTime);
    _movementComponent->SetDirection(Vector::Zero());
}
