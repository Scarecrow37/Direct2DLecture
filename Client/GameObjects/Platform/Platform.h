#pragma once
#include "../../../Engine/GameObject/GameObject.h"

class FillBoxScene;class EmptyBoxScene;
class BoxColliderScene;

class Platform final
    : public GameObject, public IColliderNotify
{
public:
    Platform();
    
    void OnBlock(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;
    void OnBeginOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;
    void OnEndOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) override;

protected:
    void UpdateBoundBox() override;

private:
    EmptyBoxScene* _positionRenderBox;
    FillBoxScene* _platformRenderBox;
    BoxColliderScene* _colliderScene;
};
