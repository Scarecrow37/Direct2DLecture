﻿#pragma once

#include "../Math/Matrix.h"
#include "../Math/Vector.h"

class Scene
{
public:
    Scene(const std::shared_ptr<ILoggerUnicode>& logger);
    explicit Scene(const std::shared_ptr<ILoggerUnicode>& logger, const Scene* parent);
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

    Matrix GetTransform() const;

    Matrix GetWorldTransform() const;

protected:
    virtual void UpdateTransform();

    std::shared_ptr<ILoggerUnicode> _logger;

    const Scene* _parentScene;

    Vector _scale;
    float _rotation;
    Vector _translation;

    Matrix _transform;
    Matrix _worldTransform;
};
