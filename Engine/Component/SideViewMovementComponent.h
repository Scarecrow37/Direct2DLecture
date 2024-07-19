#pragma once
#include "MovementComponent.h"

class SideViewMovementComponent
    : public MovementComponent
{
    static const float Gravity;
public:
    SideViewMovementComponent();

    void Update(float deltaTime) override;
    void Jump();
    void SetDirection(const Vector& direction) override;
    void Land();

    bool IsJumping() const;

private:
    bool _isJumping;
    float _jumpSpeed;
    float _gravityScale;
    float _axisYMaxSpeed;
    float _axisYSpeed;
    float _scaledGravity;
};
