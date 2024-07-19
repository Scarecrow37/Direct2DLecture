#pragma once
#include "../../../Engine/GameObject/Character.h"

class BoxColliderScene;
class EmptyBoxScene;
class AnimationScene;
class SideViewMovementComponent;
class TextScene;


class CameraScene;

class Player
    : public Character, public IColliderNotify
{
    enum State
    {
        Idle,
        Walk,
    };

public:
    Player();

    void Initialize() override;

    void SetCameraScene(CameraScene* camera);

    void Update(float deltaTime) override;
    
    void OnBlock(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;
    void OnBeginOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;
    void OnEndOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;

protected:
    void Move() const;
    void UpdateBoundBox() override;
    
private:
    AnimationScene* _animationScene;
    SideViewMovementComponent* _movementComponent;
    EmptyBoxScene* _positionRenderBox;
    BoxColliderScene* _colliderScene;
};
