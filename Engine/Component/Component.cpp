#include "pch.h"
#include "Component.h"

Component::Component()
    :Component(nullptr)
{
}

Component::Component(GameObject* owner)
    :_owner(owner)
{
}

Component::~Component() = default;

void Component::SetOwner(GameObject* owner)
{
    _owner = owner;
}

GameObject* Component::GetOwner() const
{
    return _owner;
}