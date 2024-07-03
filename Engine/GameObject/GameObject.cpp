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

void GameObject::Update(const float deltaTime)
{
    for (const auto& component : _ownedComponents)
    {
        component->Update(deltaTime);
    }
    if (_rootScene) _boundBox.SetCenter(_rootScene->GetWorldLocation());
}

void GameObject::Render(const D2DRenderer* renderer) const
{
    for (const auto& component : _ownedComponents)
    {
        component->Render(renderer);
    }
}
