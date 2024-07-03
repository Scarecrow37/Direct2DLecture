#pragma once

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

    virtual void Update(float deltaTime);
    void Render(const D2DRenderer* renderer) const;

    template <typename T>
    T* CreateComponent()
    {
        if (!std::is_base_of<Component, T>::value) throw Exception(L"T is not derived from Component");
        T* component = new T();
        AddComponent(component);
        return component;
    }

protected:
    World* _ownerWorld;
    Scene* _rootScene;
    std::vector<Component*> _ownedComponents;
    AABB _boundBox;
};
