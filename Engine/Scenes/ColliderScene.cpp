#include "pch.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
    : ColliderScene(ColliderType::None)
{
}

ColliderScene::ColliderScene(const ColliderType& colliderType)
    : _collisionType(CollisionType::NoCollision), _colliderType(colliderType)
{
}

void ColliderScene::SetNotify(IColliderNotify* notify)
{
    _notify = notify;
}

CollisionType ColliderScene::GetCollisionType() const
{
    return _collisionType;
}

void ColliderScene::SetCollisionType(const CollisionType type)
{
    _collisionType = type;
}

ColliderType ColliderScene::GetColliderType() const
{
    return _colliderType;
}

void ColliderScene::ClearAndBackupCollideState()
{
    _previousCollideState = std::move(_currentCollideState);
    _currentCollideState.clear();
}

void ColliderScene::InsertCollideState(ColliderScene* colliderScene)
{
    _currentCollideState.insert(colliderScene);
}

void ColliderScene::ProcessOverlap(Manifold manifold)
{
    for (auto& colliderScene : _currentCollideState)
    {
        if (_previousCollideState.find(colliderScene) == _previousCollideState.end())
        {
            _notify->OnBeginOverlap(this, colliderScene, manifold);
        }
    }
    for (auto& colliderScene : _previousCollideState)
    {
        if (_currentCollideState.find(colliderScene) == _currentCollideState.end())
        {
            _notify->OnEndOverlap(this, colliderScene, manifold);
        }
    }
}

void ColliderScene::ProcessBlock(ColliderScene* otherColliderScene, Manifold manifold)
{
    _notify->OnBlock(this, otherColliderScene, manifold);
}
