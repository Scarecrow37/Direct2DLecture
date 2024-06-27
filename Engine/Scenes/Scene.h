#pragma once

class D2DRenderer;

class Scene
{
public:
    Scene();
    explicit Scene(const Scene* parent);
    Scene(const Scene& other) = default;
    Scene(Scene&& other) noexcept = default;
    Scene& operator=(const Scene& other) = default;
    Scene& operator=(Scene&& other) noexcept = default;
    virtual ~Scene() = default;

    virtual void Update(float deltaTime) abstract;
    virtual void Render(const D2DRenderer* renderer) const abstract;

    void SetParentScene(const Scene* parentScene);

    Vector GetScale() const;
    void SetScale(const Vector& scale);

    float GetRotation() const;
    void SetRotation(float rotation);

    Vector GetTranslation() const;
    void SetTranslation(const Vector& translation);

    Matrix GetTransform() const;

    Matrix GetWorldTransform() const;

protected:
    virtual void UpdateTransform();

    const Scene* _parentScene;

    Vector _scale;
    float _rotation;
    Vector _translation;

    Matrix _transform;
    Matrix _worldTransform;
};
