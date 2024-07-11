#pragma once
#include "../../../Engine/GameObject/Character.h"

class EmptyBoxScene;class AnimationScene;
class MovementComponent;
class TextScene;


class CameraScene;

class Player : public Character
{
    enum State
    {
        Idle,
        Walk,
    };

public:
    Player();

    void Initialize() override;

    void SetCameraScene(CameraScene* camera);

    void Update(float deltaTime) override;

private:
    AnimationScene* _animationScene;
    MovementComponent* _movementComponent;
    EmptyBoxScene* _emptyBoxScene;
};
