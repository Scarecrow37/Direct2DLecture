#include "pch.h"
#include "FiniteState.h"
#include "Transition.h"

FiniteState::FiniteState() : _onStateChange(nullptr)
{
}

FiniteState::~FiniteState()
{
    for (const auto & transition : _transitions)
    {
        delete transition.first;
    }
    _transitions.clear();
}

void FiniteState::Enter()
{
}


void FiniteState::Exit()
{
}


void FiniteState::Update(const float deltaTime)
{
    for (const auto& transition : _transitions)
    {
        if (transition.first->operator()(deltaTime))
        {
            _onStateChange(transition.second);
            break;
        }
    }
}


void FiniteState::BindOnStateChange(const std::function<void(int)>& onStateChange)
{
    _onStateChange = onStateChange;
}
