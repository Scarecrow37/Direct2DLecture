#include "pch.h"
#include "Player.h"

#include "../../../Engine/Component/MovementComponent.h"
#include "../../../Engine/Component/SideViewMovementComponent.h"
#include "../../../Engine/Scenes/CameraScene.h"
#include "../../../Engine/Scenes/AnimationScene.h"
#include "../../../Engine/Scenes/EmptyBoxScene.h"
#include "States/PlayerIdleToWalk.h"
#include "States/PlayerWalkToIdle.h"
#include "../../FSM/States/AnimationState.h"
#include "../../../Engine/Scenes/BoxColliderScene.h"
#include "../Platform/Platform.h"

Player::Player()
{
    _positionRenderBox = CreateComponent<EmptyBoxScene>();
    SetRootScene(_positionRenderBox);
    _positionRenderBox->SetColor(D2D1::ColorF::Blue);
    _positionRenderBox->SetRect({0, 0, 2, 2});
    _positionRenderBox->SetCenter(Vector::HalfOne());

    _animationScene = CreateComponent<AnimationScene>();
    _animationScene->SetParentScene(_rootScene);


    _movementComponent = CreateComponent<SideViewMovementComponent>();
    _movementComponent->SetScene(_rootScene);
    _movementComponent->SetSpeed(400.0f);

    _colliderScene = CreateComponent<BoxColliderScene>();
    _colliderScene->SetParentScene(_rootScene);
    _colliderScene->SetNotify(this);
    _colliderScene->SetCollisionType(CollisionType::Block);
    _colliderScene->SetBound({30, 50});
    _colliderScene->SetCenter({0.6f, 1.f});
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
    Move();
    Character::Update(deltaTime);
}

void Player::OnBlock(ColliderScene* ownedCollider, ColliderScene* otherCollider, const Manifold manifold)
{
    if ( dynamic_cast<Platform*>(otherCollider->GetOwner()))
    {
        _movementComponent->CollectLocation(manifold.normal * manifold.penetration);
        _movementComponent->Land();
    }
}

void Player::OnBeginOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
}

void Player::OnEndOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
}

void Player::Move() const
{
    Vector direction = Vector::Zero();
    if (Input::IsKey(VK_UP)) direction += Vector::Up();
    if (Input::IsKey(VK_DOWN)) direction += Vector::Down();
    if (Input::IsKey(VK_LEFT)) direction += Vector::Left();
    if (Input::IsKey(VK_RIGHT)) direction += Vector::Right();
    _movementComponent->SetDirection(direction);
    if (direction.x > 0)
    {
        _animationScene->SetMirror(false);
        _colliderScene->SetCenter({0.6f, 1.f});
    }
    else if (direction.x < 0)
    {
        _animationScene->SetMirror(true);
        _colliderScene->SetCenter({0.4f, 1.f});
    }
    if (Input::IsKeyDown(VK_SPACE)) _movementComponent->Jump();
}

void Player::UpdateBoundBox()
{
    _boundBox.SetExtend(_animationScene->GetDestinationRect().GetExtend());
    _boundBox.SetCenter({GetWorldLocation().x, GetWorldLocation().y - _boundBox.GetExtend().y});
}
