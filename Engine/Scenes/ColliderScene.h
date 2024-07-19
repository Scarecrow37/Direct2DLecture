#pragma once

#include "Scene.h"
#include "../Component/Component.h"

enum class ColliderType
{
    None,
    Box,
    Circle,
};

enum class CollisionType
{
    NoCollision,
    Block,
    Overlap
};

class ColliderScene;

class IColliderNotify
{
public:
    IColliderNotify() = default;
    IColliderNotify(const IColliderNotify& other) = default;
    IColliderNotify(IColliderNotify&& other) noexcept = default;
    IColliderNotify& operator=(const IColliderNotify& other) = default;
    IColliderNotify& operator=(IColliderNotify&& other) noexcept = default;
    virtual ~IColliderNotify() = default;

    virtual void OnBlock(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) = 0;
    virtual void OnBeginOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) = 0;
    virtual void OnEndOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold) = 0;
};

class ColliderScene
    : public Scene, public Component
{
public:
    ColliderScene();
    ColliderScene(const ColliderType& colliderType);

    void SetNotify(IColliderNotify* notify);

    CollisionType GetCollisionType() const;
    void SetCollisionType(CollisionType type);

    ColliderType GetColliderType() const;

    void ClearAndBackupCollideState();

    void InsertCollideState(ColliderScene* colliderScene);

    void ProcessOverlap(Manifold manifold);
    void ProcessBlock(ColliderScene* otherColliderScene, Manifold manifold);

    virtual bool IsCollide(ColliderScene* otherColliderScene, Manifold* manifold) = 0;

protected:
    CollisionType _collisionType;
    ColliderType _colliderType;
    IColliderNotify* _notify;

    std::set<ColliderScene*> _currentCollideState;
    std::set<ColliderScene*> _previousCollideState;
};
