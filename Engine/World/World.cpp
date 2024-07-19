#include "pch.h"
#include "World.h"
#include "../GameObject/GameObject.h"
#include "../Scenes/ColliderScene.h"

World::World(const AABB& defaultCullingBound)
    : _cullingBound(nullptr), _defaultCullingBound(defaultCullingBound), _renderingObjectCount(0),
      _previousRenderingObjectCount(0)
{
}

World::~World()
{
    for (const auto& gameObject : _gameObjects)
    {
        delete gameObject;
    }
    _gameObjects.clear();
}

void World::Initialize() const
{
    for (const auto& gameObject : _gameObjects)
    {
        gameObject->Initialize();
    }
}

void World::Update(const float deltaTime)
{
    ResetRenderingObjectCount();
    for (const auto& gameObject : _gameObjects)
    {
        gameObject->Update(deltaTime);
    }
    UpdateCollision();
}

void World::LazyUpdate(float deltaTime)
{
    for (const auto& gameObject : _gameObjects)
    {
        gameObject->LazyUpdate(deltaTime);
    }
}

void World::Render(const D2DRenderer* renderer)
{
    const AABB cullingBound = _cullingBound ? *_cullingBound : _defaultCullingBound;
    for (const auto& gameObject : _gameObjects)
    {
        Manifold manifold = {};
        if (cullingBound.CheckIntersect(gameObject->GetBoundBox(), &manifold))
        {
            IncreaseRenderingObjectCount();
            gameObject->Render(renderer);
        }
    }
}

void World::Clear()
{
    _gameObjects.clear();
}

void World::SetCullingBound(AABB* bound)
{
    _cullingBound = bound;
}

void World::AddGameObject(GameObject* gameObject)
{
    gameObject->SetOwner(this);
    _gameObjects.push_back(gameObject);
}

size_t World::GetRenderingObjectCount() const
{
    return _previousRenderingObjectCount;
}

void World::IncreaseRenderingObjectCount()
{
    _renderingObjectCount++;
}

void World::ResetRenderingObjectCount()
{
    _previousRenderingObjectCount = _renderingObjectCount;
    _renderingObjectCount = 0;
}

void World::UpdateCollision() const
{
    std::vector<ColliderScene*> colliders;
    for (const auto& gameObject : _gameObjects)
    {
        if (!gameObject->IsCollisionable()) continue;

        const std::vector<Component*> components = gameObject->GetOwnedComponents();
        for (auto& component : components)
        {
            ColliderScene* collider = dynamic_cast<ColliderScene*>(component);
            if (collider == nullptr) continue;
            if (collider->GetCollisionType() == CollisionType::NoCollision) continue;
            collider->ClearAndBackupCollideState();
            colliders.push_back(collider);
        }
    }

    Manifold manifold = {};
    for (size_t sourceIndex = 0; sourceIndex < colliders.size(); ++sourceIndex)
    {
        for (size_t targetIndex = sourceIndex + 1; targetIndex < colliders.size(); ++targetIndex)
        {
            ColliderScene* source = colliders[sourceIndex];
            ColliderScene* target = colliders[targetIndex];
            if (source->GetOwner() == target->GetOwner()) continue;
            if (!source->IsCollide(target, &manifold)) continue;
            if (source->GetCollisionType() == CollisionType::Block && target->GetCollisionType() ==
                CollisionType::Block)
            {
                source->ProcessBlock(target, manifold);
                target->ProcessBlock(source, manifold);
            }
            else
            {
                source->InsertCollideState(target);
                target->InsertCollideState(source);
            }
        }
    }

    for (const auto& collider : colliders)
    {
        collider->ProcessOverlap(manifold);
    }
}
