#pragma once
#include "../../../Engine/FSM/FiniteState.h"

class AnimationScene;

class AnimationState : public FiniteState
{
public:
    AnimationState(int animationIndex, AnimationScene* animationScene);
    void Enter() override;

private:
    int _animationIndex;
    AnimationScene* _animationScene;
};
