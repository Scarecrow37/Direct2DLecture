#pragma once
#include "../../../Engine/GameObject/Character.h"

class TextScene;class MovementComponent;class AnimationScene;class Monster : public Character
{
    enum State
    {
        Idle,
        Walk,
        Attack,
        Hurt,
        Death
    };
public:
    Monster();

    void Initialize() override;
    void Update(float deltaTime) override;

    void SetChaseTarget(GameObject* chaseTarget);

    std::wstring GetStateString() const;

private:
    GameObject* _chaseTarget;
    AnimationScene* _animationScene;
    MovementComponent* _movementComponent;
    TextScene* _textScene;
};
