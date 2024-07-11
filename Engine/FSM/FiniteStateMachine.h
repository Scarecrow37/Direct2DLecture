#pragma once

#include "FiniteState.h"


class FiniteStateMachine
{
public:
    FiniteStateMachine();
    FiniteStateMachine(const FiniteStateMachine& other) = default;
    FiniteStateMachine(FiniteStateMachine&& other) noexcept = default;
    FiniteStateMachine& operator=(const FiniteStateMachine& other) = default;
    FiniteStateMachine& operator=(FiniteStateMachine&& other) noexcept = default;
    ~FiniteStateMachine();

    void Update(float deltaTime);
    void ChangeState(int id);

    int GetCurrentStateId() const;

    template <typename T, typename... Args>
    T* CreateState(const int id, Args... args)
    {
        if (!std::is_base_of_v<FiniteState, T>) throw Exception(L"T is not derived from FiniteState");
        T* state = new T(args...);
        _states[id] = state;
        _states[id]->BindOnStateChange(std::bind(&FiniteStateMachine::ChangeState, this, std::placeholders::_1));
        return state;
    }

private:
    int _currentStateId;
    std::unordered_map<int, FiniteState*> _states;
};
