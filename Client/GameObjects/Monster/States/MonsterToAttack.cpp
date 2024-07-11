#include "pch.h"
#include "MonsterToAttack.h"

MonsterTransition::ToAttack::ToAttack(GameObject* target, GameObject* owner)
    : _chaseTarget(target), _owner(owner)
{
}

bool MonsterTransition::ToAttack::operator()(float deltaTime)
{
    Vector targetLocation = _chaseTarget->GetWorldLocation();
    Vector ownerLocation = _owner->GetWorldLocation();
    const Vector distance = targetLocation - ownerLocation;
    return distance.Size() < 50.f;
}
