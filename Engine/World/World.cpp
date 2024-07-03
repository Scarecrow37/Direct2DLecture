#include "pch.h"
#include "World.h"
#include "../GameObject/GameObject.h"

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

void World::Update(const float deltaTime)
{
    ResetRenderingObjectCount();
    for (const auto& gameObject : _gameObjects)
    {
        gameObject->Update(deltaTime);
    }
}

void World::Render(const D2DRenderer* renderer)
{
    const AABB cullingBound = _cullingBound ? *_cullingBound : _defaultCullingBound;
    for (const auto& gameObject : _gameObjects)
    {
        if (cullingBound.CheckIntersect(gameObject->GetBoundBox()))
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
