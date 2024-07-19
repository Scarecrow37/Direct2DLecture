#include "pch.h"
#include "SideViewMovementComponent.h"

#include "../Scenes/Scene.h"

const float SideViewMovementComponent::Gravity = 9.8f;

SideViewMovementComponent::SideViewMovementComponent()
    : _isJumping(false), _jumpSpeed(500.f), _gravityScale(100.f), _axisYMaxSpeed(600.f), _axisYSpeed(0),
      _scaledGravity(Gravity * _gravityScale)
{
}

void SideViewMovementComponent::Update(const float deltaTime)
{
    const Vector location = _scene->GetTranslation();

    _velocity.x = (_direction * _speed).x;

    _axisYSpeed += _scaledGravity * deltaTime;
    _axisYSpeed = min(_axisYSpeed, _axisYMaxSpeed);
    _velocity.y = (Vector::Down() * _axisYSpeed).y;

    _newLocation = location + _velocity * deltaTime;
    _newLocation.y = max(_newLocation.y, 0.f);
    if (_newLocation.y <= 0.f) Land();

    _scene->SetTranslation(_newLocation);
}

void SideViewMovementComponent::Jump()
{
    if (_isJumping) return;
    _isJumping = true;
    _axisYSpeed = _jumpSpeed * -1;
}

void SideViewMovementComponent::SetDirection(const Vector& direction)
{
    _direction.x = direction.x;
    _direction.y = 0.f;
    _direction = _direction.Normalize();
}

void SideViewMovementComponent::Land()
{
    if (_isJumping && _axisYSpeed > 0.f)
    {
        _isJumping = false;
        _axisYSpeed = 0.f;
    }
}

bool SideViewMovementComponent::IsJumping() const
{
    return _isJumping;
}
