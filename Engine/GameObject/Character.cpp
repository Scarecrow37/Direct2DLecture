#include "pch.h"
#include "Character.h"

void Character::Update(const float deltaTime)
{
    _fsm.Update(deltaTime);
    GameObject::Update(deltaTime);
}
