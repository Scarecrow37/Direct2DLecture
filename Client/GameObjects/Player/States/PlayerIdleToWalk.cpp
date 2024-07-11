#include "pch.h"
#include "PlayerIdleToWalk.h"
#include "../../../../Engine/Component/MovementComponent.h"


PlayerTransition::IdleToWalk::IdleToWalk(MovementComponent* movementComponent) : _movementComponent(movementComponent)
{
}

bool PlayerTransition::IdleToWalk::operator()(float deltaTime)
{
    return _movementComponent->IsMoving();
}
