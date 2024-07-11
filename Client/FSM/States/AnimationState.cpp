#include "pch.h"
#include "AnimationState.h"

#include "../../../Engine/Scenes/AnimationScene.h"

AnimationState::AnimationState(const int animationIndex, AnimationScene* animationScene):
    _animationIndex(animationIndex),
    _animationScene(animationScene)
{
}

void AnimationState::Enter()
{
    FiniteState::Enter();
    _animationScene->SetAnimation(_animationIndex);
}
