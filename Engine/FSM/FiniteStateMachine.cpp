#include "pch.h"
#include "FiniteStateMachine.h"
#include "FiniteState.h"

FiniteStateMachine::FiniteStateMachine(): _currentStateId(0)
{
}

FiniteStateMachine::~FiniteStateMachine()
{
    for (auto& state : _states)
    {
        delete state.second;
        state.second = nullptr;
    }
    _states.clear();
}

void FiniteStateMachine::Update(const float deltaTime)
{
    if (_states.empty()) return;
    _states[_currentStateId]->Update(deltaTime);
}

void FiniteStateMachine::ChangeState(const int id)
{
    _states[_currentStateId]->Exit();
    _currentStateId = id;
    _states[_currentStateId]->Enter();
}

int FiniteStateMachine::GetCurrentStateId() const
{
    return _currentStateId;
}
