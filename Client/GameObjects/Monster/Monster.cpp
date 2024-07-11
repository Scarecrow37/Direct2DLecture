#include "pch.h"
#include "Monster.h"

#include "../../../Engine/Component/MovementComponent.h"
#include "../../../Engine/Scenes/AnimationScene.h"
#include "../../../Engine/Scenes/EmptyBoxScene.h"
#include "../../../Engine/Scenes/TextScene.h"
#include "../../FSM/States/AnimationState.h"
#include "States/AttackState.h"
#include "States/ChaseState.h"
#include "States/MonsterToAttack.h"
#include "States/MonsterToWalk.h"
#include "States/MonsterToIdle.h"
#include "States/WaitState.h"

Monster::Monster()
{
    _animationScene = CreateComponent<AnimationScene>();
    SetRootScene(_animationScene);
    
    EmptyBoxScene* emptyBoxScene = CreateComponent<EmptyBoxScene>();
    emptyBoxScene->SetParentScene(_animationScene);
    emptyBoxScene->SetColor(D2D1::ColorF::Red);
    emptyBoxScene->SetRect({-1, -1,1,1});

    
    _textScene = CreateComponent<TextScene>();
    _textScene->SetParentScene(_animationScene);
    _textScene->SetText(L"Monster");
    _textScene->SetFontSize(32);
    _textScene->SetTextBound({0, 0, 192, 32});
    _textScene->SetTranslation({0, 32});
    
    _movementComponent = CreateComponent<MovementComponent>();
    _movementComponent->SetScene(_animationScene);
    _movementComponent->SetSpeed(100.f);
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
    attack->CreateTransition<MonsterTransition::ToIdle>(Idle, _chaseTarget, this);
    attack->CreateTransition<MonsterTransition::ToWalk>(Walk, _chaseTarget, this);
    Character::Initialize();
}

void Monster::Update(const float deltaTime)
{
    Character::Update(deltaTime);
    SetBoundBox(Rect{{0, 0}, _animationScene->GetBitmapSize()});
    _textScene->SetText(GetStateString());
    if(_movementComponent->GetDirection().x > 0) _animationScene->SetMirror(true);
    else if(_movementComponent->GetDirection().x < 0) _animationScene->SetMirror(false);
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
