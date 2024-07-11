#include "pch.h"
#include "PlayerWalkToIdle.h"
#include "../../../../Engine/Component/MovementComponent.h"

PlayerTransition::WalkToIdle::WalkToIdle(MovementComponent* movementComponent) : _movementComponent(movementComponent)
{
}

bool PlayerTransition::WalkToIdle::operator()(float deltaTime)
{
    return !_movementComponent->IsMoving();
}
