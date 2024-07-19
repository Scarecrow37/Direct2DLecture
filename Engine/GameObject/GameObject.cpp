#include "pch.h"
#include "GameObject.h"
#include "../Component/Component.h"
#include "../Scenes/Scene.h"

GameObject::GameObject()
    : _ownerWorld(nullptr), _rootScene(nullptr)
{
}

GameObject::~GameObject()
{
    for (const auto& component : _ownedComponents)
    {
        delete component;
    }
    _ownedComponents.clear();
}

void GameObject::SetOwner(World* ownerWorld)
{
    _ownerWorld = ownerWorld;
}

void GameObject::SetRootScene(Scene* rootScene)
{
    _rootScene = rootScene;
}

const AABB& GameObject::GetBoundBox() const
{
    return _boundBox;
}

void GameObject::SetBoundBox(const AABB& boundBox)
{
    _boundBox = boundBox;
}

void GameObject::AddComponent(Component* component)
{
    component->SetOwner(this);
    _ownedComponents.push_back(component);
}

std::vector<Component*> GameObject::GetOwnedComponents() const
{
    return _ownedComponents;
}

Vector GameObject::GetWorldLocation() const
{
    return _rootScene->GetWorldLocation();
}

void GameObject::Initialize()
{
    for (const auto& component : _ownedComponents)
    {
        component->Initialize();
    }
}

void GameObject::Update(const float deltaTime)
{
    for (const auto& component : _ownedComponents)
    {
        component->Update(deltaTime);
    }
    UpdateBoundBox();
}

void GameObject::LazyUpdate(float deltaTime)
{
    for (const auto& component : _ownedComponents)
    {
        component->LazyUpdate(deltaTime);
    }
}

void GameObject::Render(const D2DRenderer* renderer) const
{
    for (const auto& component : _ownedComponents)
    {
        component->Render(renderer);
    }
}

bool GameObject::IsCollisionable() const
{
    return _isCollisionable;
}
