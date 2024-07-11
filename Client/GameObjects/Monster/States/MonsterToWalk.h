#pragma once
#include "../../../../Engine/FSM/Transition.h"
#include "../../../../Engine/GameObject/GameObject.h"


class Scene;

namespace MonsterTransition
{
    class ToWalk final : public Transition
    {
    public:
        ToWalk(GameObject* target, GameObject* owner);
        bool operator()(float deltaTime) override;

    private:
        GameObject* _chaseTarget;
        GameObject* _owner;
    };
}
