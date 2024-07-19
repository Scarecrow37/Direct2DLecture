#pragma once
#include "../../../Engine/GameObject/Character.h"
#include "../../../Engine/Scenes/AnimationScene.h"

class BoxColliderScene;
class SideViewMovementComponent;
class TextScene;
class MovementComponent;
class AnimationScene;

class Monster : public Character, public IColliderNotify, public IAnimationNotify
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

protected:
    void UpdateBoundBox() override;

public:
    void OnBlock(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;
    void OnBeginOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;
    void OnEndOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;
    void OnBeginAnimation(std::wstring animationName) override;
    void OnEndAnimation(std::wstring animationName) override;
    void OnBeginAnimationChanged(std::wstring animationName) override;
    void OnEndAnimationChanged(std::wstring animationName) override;

private:
    GameObject* _chaseTarget;
    AnimationScene* _animationScene;
    SideViewMovementComponent* _movementComponent;
    BoxColliderScene* _colliderScene;
    TextScene* _textScene;
};
