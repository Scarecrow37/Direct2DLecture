#include "pch.h"
#include "MonsterToWalk.h"
#include "../../../../Engine/GameObject/GameObject.h"


MonsterTransition::ToWalk::ToWalk(GameObject* target, GameObject* owner)
    : _chaseTarget(target), _owner(owner)
{
}

bool MonsterTransition::ToWalk::operator()(float deltaTime)
{
    Vector targetLocation = _chaseTarget->GetWorldLocation();
    Vector ownerLocation = _owner->GetWorldLocation();
    const Vector distance = targetLocation - ownerLocation;
    return distance.Size() < 200.f && distance.Size() > 50.f;
}
