#pragma once
#include "Component.h"

class Scene;

class MovementComponent : public Component
{
public:
    MovementComponent();
    void Update(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

    void SetScene(Scene* scene);

    void SetSpeed(float speed);
    float GetSpeed() const;

    Vector GetDirection() const;
    void SetDirection(const Vector& direction);

private:
    Scene* _scene;

    float _speed;
    Vector _direction;
};
