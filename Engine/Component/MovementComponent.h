#pragma once

#include "Component.h"

class Scene;

class MovementComponent : public Component
{
public:
    MovementComponent();
    void Initialize() override;
    void Update(float deltaTime) override;
    void LazyUpdate(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

    void SetScene(Scene* scene);

    void SetSpeed(float speed);
    float GetSpeed() const;

    Vector GetDirection() const;
    virtual void SetDirection(const Vector& direction);

    bool IsMoving() const;

    void CollectLocation(Vector location);

protected:
    Scene* _scene;

    Vector _direction;
    Vector _velocity;
    float _speed;

    Vector _newLocation;
    Vector _collectedLocation;
    bool _isCollectedLocation;
};
