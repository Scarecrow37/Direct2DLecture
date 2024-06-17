#pragma once

#include "../Math/Matrix.h"
#include "../Math/Vector.h"


class Scene
{
public:
    Scene();
    virtual ~Scene() = default;
    
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
    void UpdateTransform();
    const Scene* _parentScene;
    Vector _scale;
    float _rotation;
    Vector _translation;
    Matrix _transform;
    Matrix _worldTransform;
};
