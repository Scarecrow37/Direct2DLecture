#pragma once
#include "../../../../Engine/FSM/Transition.h"
#include "../../../../Engine/GameObject/GameObject.h"

namespace MonsterTransition
{
    class ToAttack final : public Transition
    {
    public:
        ToAttack(GameObject* target, GameObject* owner);
        bool operator()(float deltaTime) override;

    private:
        GameObject* _chaseTarget;
        GameObject* _owner;
    };
}
