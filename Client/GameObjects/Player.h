#pragma once
#include "../../Engine/GameObject/GameObject.h"

class MovementComponent;
class TextScene;


class CameraScene;

class Player : public GameObject
{
public:
    Player();
    void SetCameraScene(CameraScene* camera);

    void Update(float deltaTime) override;

    void SetCount(size_t count);

private:
    MovementComponent* _movementComponent;
    TextScene* _textScene;
    size_t _count;
};
