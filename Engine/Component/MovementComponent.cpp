#include "pch.h"
#include "MovementComponent.h"

#include "../Scenes/Scene.h"

MovementComponent::MovementComponent()
    : _scene(nullptr), _direction(Vector::Zero()), _velocity(Vector::Zero()), _speed(1.f), _isCollectedLocation(false)
{
}

void MovementComponent::Initialize()
{
}

void MovementComponent::Update(const float deltaTime)
{
    _velocity = _direction * _speed;
    if (_velocity.Size() > 0)
    {
        _newLocation = _scene->GetTranslation() + _velocity * deltaTime;
        _scene->SetTranslation(_newLocation);
    }
}

void MovementComponent::LazyUpdate(float deltaTime)
{
    if (_isCollectedLocation)
    {
        _scene->SetTranslation(_collectedLocation);
        _isCollectedLocation = false;
        _collectedLocation = Vector::Zero();
    }
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
    _direction = direction.Normalize();
}

bool MovementComponent::IsMoving() const
{
    return _direction * _speed != Vector::Zero();
}

void MovementComponent::CollectLocation(const Vector location)
{
    _collectedLocation = _newLocation - location;
    _isCollectedLocation = true;
}


