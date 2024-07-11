#include "pch.h"
#include "MovementComponent.h"

#include "../Scenes/Scene.h"

MovementComponent::MovementComponent()
    : _scene(nullptr), _speed(1.f), _direction(Vector::Zero())
{
}

void MovementComponent::Initialize()
{
}

void MovementComponent::Update(const float deltaTime)
{
    const Vector newLocation = (_scene)->GetTranslation() + _direction * (_speed * deltaTime);
    (_scene)->SetTranslation(newLocation);
}

void MovementComponent::Render(const D2DRenderer* renderer) const
{
}

void MovementComponent::SetScene(Scene* scene)
{
    _scene = scene;
}

void MovementComponent::SetSpeed(const float speed)
{
    _speed = speed;
}

float MovementComponent::GetSpeed() const
{
    return _speed;
}

Vector MovementComponent::GetDirection() const
{
    return _direction;
}

void MovementComponent::SetDirection(const Vector& direction)
{
    _direction = direction;
}

bool MovementComponent::IsMoving() const
{
    return _direction * _speed != Vector::Zero();
}
