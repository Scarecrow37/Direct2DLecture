#include "pch.h"
#include "Monster.h"

#include "../../../Engine/Component/MovementComponent.h"
#include "../../../Engine/Component/SideViewMovementComponent.h"
#include "../../../Engine/Scenes/AnimationScene.h"
#include "../../../Engine/Scenes/BoxColliderScene.h"
#include "../../../Engine/Scenes/EmptyBoxScene.h"
#include "../../../Engine/Scenes/TextScene.h"
#include "../../FSM/States/AnimationState.h"
#include "../Platform/Platform.h"
#include "States/AttackState.h"
#include "States/ChaseState.h"
#include "States/MonsterToAttack.h"
#include "States/MonsterToWalk.h"
#include "States/MonsterToIdle.h"
#include "States/WaitState.h"

Monster::Monster()
{
    EmptyBoxScene* emptyBoxScene = CreateComponent<EmptyBoxScene>();
    SetRootScene(emptyBoxScene);
    emptyBoxScene->SetColor(D2D1::ColorF::Red);
    emptyBoxScene->SetRect({-1, -1, 1, 1});

    _animationScene = CreateComponent<AnimationScene>();
    _animationScene->SetParentScene(_rootScene);
    _animationScene->SetNotify(this);

    _textScene = CreateComponent<TextScene>();
    _textScene->SetParentScene(_rootScene);
    _textScene->SetText(L"Monster");
    _textScene->SetFontSize(32);
    _textScene->SetTextBound({0, 0, 192, 32});
    _textScene->SetTranslation({0, -200});

    _movementComponent = CreateComponent<SideViewMovementComponent>();
    _movementComponent->SetScene(_rootScene);
    _movementComponent->SetSpeed(100.f);

    _colliderScene = CreateComponent<BoxColliderScene>();
    _colliderScene->SetParentScene(_rootScene);
    _colliderScene->SetNotify(this);
    _colliderScene->SetCollisionType(CollisionType::Block);
    _colliderScene->SetBound({64, 128});
    _colliderScene->SetCenter({0.4f, 1.f});
}

void Monster::Initialize()
{
    _animationScene->LoadBitmapFromFilename(L"../Resources/Images/Mummy.png");
    _animationScene->LoadAnimationAssetFromFilename(L"../Resources/Animations/Mummy/Mummy.csv");

    auto idle = _fsm.CreateState<WaitState>(Idle, Idle, _animationScene, _movementComponent);
    idle->CreateTransition<MonsterTransition::ToWalk>(Walk, _chaseTarget, this);
    idle->CreateTransition<MonsterTransition::ToAttack>(Attack, _chaseTarget, this);
    auto walk = _fsm.CreateState<ChaseState>(Walk, Walk, _animationScene, _movementComponent, _chaseTarget, this);
    walk->CreateTransition<MonsterTransition::ToIdle>(Idle, _chaseTarget, this);
    walk->CreateTransition<MonsterTransition::ToAttack>(Attack, _chaseTarget, this);
    auto attack = _fsm.CreateState<AttackState>(Attack, Attack, _animationScene, _movementComponent);
    //attack->CreateTransition<MonsterTransition::ToIdle>(Idle, _chaseTarget, this);
    //attack->CreateTransition<MonsterTransition::ToWalk>(Walk, _chaseTarget, this);
    Character::Initialize();
}

void Monster::Update(const float deltaTime)
{
    Character::Update(deltaTime);
    SetBoundBox(Rect{{0, 0}, _animationScene->GetBitmapSize()});
    _textScene->SetText(GetStateString());
    if (_movementComponent->GetDirection().x > 0)
    {
        _animationScene->SetMirror(true);
        _colliderScene->SetCenter({0.6f, 1.f});
    }
    else if (_movementComponent->GetDirection().x < 0)
    {
        _animationScene->SetMirror(false);
        _colliderScene->SetCenter({0.4f, 1.f});
    }
}

void Monster::SetChaseTarget(GameObject* chaseTarget)
{
    _chaseTarget = chaseTarget;
}

std::wstring Monster::GetStateString() const
{
    State state = static_cast<State>(_fsm.GetCurrentStateId());
    switch (state)
    {
    case Idle:
        return L"Idle";
    case Walk:
        return L"Walk";
    case Attack:
        return L"Attack";
    case Hurt:
        return L"Hurt";
    case Death:
        return L"Death";
    default:
        return L"Unknown";
    }
}

void Monster::UpdateBoundBox()
{
    _boundBox.SetExtend(_animationScene->GetDestinationRect().GetExtend());
    _boundBox.SetCenter({GetWorldLocation().x, GetWorldLocation().y - _boundBox.GetExtend().y});
}

void Monster::OnBlock(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
    if (dynamic_cast<Platform*>(otherCollider->GetOwner()))
    {
        _movementComponent->CollectLocation(manifold.normal * manifold.penetration);
        _movementComponent->Land();
    }
}

void Monster::OnBeginOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
}

void Monster::OnEndOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
}

void Monster::OnBeginAnimation(std::wstring animationName)
{
}

void Monster::OnEndAnimation(std::wstring animationName)
{
    if (animationName == L"Attack") _fsm.ChangeState(Idle);
}

void Monster::OnBeginAnimationChanged(std::wstring animationName)
{
}

void Monster::OnEndAnimationChanged(std::wstring animationName)
{
}
