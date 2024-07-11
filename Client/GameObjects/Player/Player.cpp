#include "pch.h"
#include "Player.h"

#include "../../../Engine/Component/MovementComponent.h"
#include "../../../Engine/Scenes/CameraScene.h"
#include "../../../Engine/Scenes/AnimationScene.h"
#include "../../../Engine/Scenes/EmptyBoxScene.h"
#include "States/PlayerIdleToWalk.h"
#include "States/PlayerWalkToIdle.h"
#include "../../FSM/States/AnimationState.h"

class AnimationState;

Player::Player()
{
    _animationScene = CreateComponent<AnimationScene>();
    SetRootScene(_animationScene);
    _emptyBoxScene = CreateComponent<EmptyBoxScene>();
    _emptyBoxScene->SetParentScene(_animationScene);
    _emptyBoxScene->SetColor(D2D1::ColorF::Blue);
    _emptyBoxScene->SetRect({-1, -1, 1, 1});

    _movementComponent = CreateComponent<MovementComponent>();
    _movementComponent->SetScene(_rootScene);
    _movementComponent->SetSpeed(400.0f);
}

void Player::Initialize()
{
    _animationScene->LoadBitmapFromFilename(L"../Resources/Images/Woodcutter.png");
    _animationScene->LoadAnimationAssetFromFilename(L"../Resources/Animations/Woodcutter/Woodcutter.csv");
    auto idle = _fsm.CreateState<AnimationState>(Idle, Idle, _animationScene);
    idle->CreateTransition<PlayerTransition::IdleToWalk>(Walk, _movementComponent);
    auto walk = _fsm.CreateState<AnimationState>(Walk, Walk, _animationScene);
    walk->CreateTransition<PlayerTransition::WalkToIdle>(Idle, _movementComponent);
    Character::Initialize();
}

void Player::SetCameraScene(CameraScene* camera)
{
    AddComponent(camera);
    camera->SetParentScene(_rootScene);
}

void Player::Update(const float deltaTime)
{
    SetBoundBox(Rect{{0, 0}, _animationScene->GetBitmapSize()});
    Vector direction = Vector::Zero();
    if (Input::IsKey(VK_UP)) direction += Vector::Up();
    if (Input::IsKey(VK_DOWN)) direction += Vector::Down();
    if (Input::IsKey(VK_LEFT)) direction += Vector::Left();
    if (Input::IsKey(VK_RIGHT)) direction += Vector::Right();
    _movementComponent->SetDirection(direction);
    if (direction.x > 0) _animationScene->SetMirror(false);
    else if (direction.x < 0) _animationScene->SetMirror(true);
    Character::Update(deltaTime);
}
