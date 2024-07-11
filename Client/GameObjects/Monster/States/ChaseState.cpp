#include "pch.h"
#include "ChaseState.h"

#include "../../../../Engine/Component/MovementComponent.h"
#include "../../../../Engine/GameObject/GameObject.h"


ChaseState::ChaseState(int animationIndex, AnimationScene* animationScene, MovementComponent* movementComponent,
                       GameObject* target, GameObject* owner)
    : AnimationState(animationIndex, animationScene), _target(target), _owner(owner),
      _movementComponent(movementComponent)
{
}

void ChaseState::Update(const float deltaTime)
{
    AnimationState::Update(deltaTime);
    const Vector direction = _target->GetWorldLocation() - _owner->GetWorldLocation();
    const Vector velocity = direction.Normalize();
    _movementComponent->SetDirection(direction.Normalize());
}
