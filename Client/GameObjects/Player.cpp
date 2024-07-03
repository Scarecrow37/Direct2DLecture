#include "pch.h"
#include "Player.h"

#include "../../Engine/Component/MovementComponent.h"
#include "../../Engine/Scenes/FillBoxScene.h"
#include "../../Engine/Scenes/CameraScene.h"
#include "../../Engine/Scenes/TextScene.h"

Player::Player() : _count(0)
{
    FillBoxScene* boxScene = CreateComponent<FillBoxScene>();
    SetRootScene(boxScene);
    boxScene->SetColor(D2D1::ColorF::Blue);
    boxScene->SetCenter({0.5f, 0.5f});
    boxScene->SetRect(Rect(0, 0, 100, 100));
    SetBoundBox(boxScene->GetRect());

    _movementComponent = CreateComponent<MovementComponent>();
    _movementComponent->SetScene(_rootScene);
    _movementComponent->SetSpeed(256.0f);

    _textScene = CreateComponent<TextScene>();
    _textScene->SetText(L"Player");
    _textScene->SetFontSize(24.0f);
    _textScene->SetTranslation({0, -64});
    _textScene->SetTextBound(Rect(0, 0, 256,64));
    _textScene->SetCenter({0.5f, 0.5f});
    _textScene->SetParentScene(_rootScene);
}

void Player::SetCameraScene(CameraScene* camera)
{
    AddComponent(camera);
    camera->SetParentScene(_rootScene);
}

void Player::Update(const float deltaTime)
{
    GameObject::Update(deltaTime);
    _textScene->SetText(L"Object Count : " + std::to_wstring(_count));
    Vector direction = Vector::Zero();
    if (Input::IsKey(VK_UP)) direction += Vector::Up();
    if (Input::IsKey(VK_DOWN)) direction += Vector::Down();
    if (Input::IsKey(VK_LEFT)) direction += Vector::Left();
    if (Input::IsKey(VK_RIGHT)) direction += Vector::Right();
    _movementComponent->SetDirection(direction);
}

void Player::SetCount(const size_t count)
{
    _count = count;
}
