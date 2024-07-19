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

    void SetParentScene(const Scene* parentScene);

    Vector GetScale() const;
    void SetScale(const Vector& scale);

    float GetRotation() const;
    void SetRotation(float rotation);

    Vector GetTranslation() const;
    void SetTranslation(const Vector& translation);

    void SetCenter(const Vector& center);
    Vector GetCenter() const;
    
    Matrix GetTransform() const;

    Matrix GetWorldTransform() const;

    Vector GetWorldLocation() const;
protected:
    virtual void UpdateTransform();
    virtual void UpdateWorldTransform();
    virtual void UpdateCenterTransform() = 0;

    const Scene* _parentScene;

    Vector _scale;
    float _rotation;
    Vector _translation;
    Vector _center;

    Matrix _transform;
    Matrix _worldTransform;
    Matrix _centerMatrix;
};
