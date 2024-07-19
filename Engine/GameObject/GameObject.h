#pragma once
#include "../FSM/FiniteStateMachine.h"
#include "../Scenes/ColliderScene.h"

class Component;
class Scene;
class World;
class D2DRenderer;

class GameObject
{
public:
    GameObject();
    GameObject(const GameObject& other) = default;
    GameObject(GameObject&& other) noexcept = default;
    GameObject& operator=(const GameObject& other) = default;
    GameObject& operator=(GameObject&& other) noexcept = default;
    virtual ~GameObject();

    void SetOwner(World* ownerWorld);
    void SetRootScene(Scene* rootScene);
    const AABB& GetBoundBox() const;
    void SetBoundBox(const AABB& boundBox);
    void AddComponent(Component* component);
    std::vector<Component*> GetOwnedComponents() const;

    Vector GetWorldLocation() const;

    virtual void Initialize();
    virtual void Update(float deltaTime);
    virtual void LazyUpdate(float deltaTime);
    void Render(const D2DRenderer* renderer) const;

    template <typename T>
    T* CreateComponent()
    {
        if (!std::is_base_of<Component, T>::value) throw Exception(L"T is not derived from Component");
        if (std::is_base_of_v<ColliderScene, T>) _isCollisionable = true;
        T* component = new T();
        AddComponent(component);
        return component;
    }

    bool IsCollisionable() const;

protected:
    virtual void UpdateBoundBox() = 0;
    
    World* _ownerWorld;
    Scene* _rootScene;
    std::vector<Component*> _ownedComponents;
    AABB _boundBox;

private:
    bool _isCollisionable;
};
