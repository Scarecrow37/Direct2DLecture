#include "pch.h"
#include "MonsterToIdle.h"
#include "../../../../Engine/GameObject/GameObject.h"

MonsterTransition::ToIdle::ToIdle(GameObject* target, GameObject* owner)
    : _chaseTarget(target), _owner(owner)
{
}

bool MonsterTransition::ToIdle::operator()(float deltaTime)
{
    Vector targetLocation = _chaseTarget->GetWorldLocation();
    Vector ownerLocation = _owner->GetWorldLocation();
    const Vector distance = targetLocation - ownerLocation;
    return distance.Size() > 200.f;
}
