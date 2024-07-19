#pragma once

class D2DRenderer;
class GameObject;

class Component
{
public:
    Component();
    explicit Component(GameObject* owner);
    Component(const Component& other) = default;
    Component(Component&& other) noexcept = default;
    Component& operator=(const Component& other) = default;
    Component& operator=(Component&& other) noexcept = default;
    virtual ~Component();

    void SetOwner(GameObject* owner);
    GameObject* GetOwner() const;

    virtual void Initialize() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void LazyUpdate(float deltaTime) = 0;
    virtual void Render(const D2DRenderer* renderer) const = 0;

private:
    GameObject* _owner;
};
