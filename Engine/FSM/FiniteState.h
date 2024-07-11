#pragma once

struct Transition;

class FiniteState
{
public:
    FiniteState();
    FiniteState(const FiniteState& other) = default;
    FiniteState(FiniteState&& other) noexcept = default;
    FiniteState& operator=(const FiniteState& other) = default;
    FiniteState& operator=(FiniteState&& other) noexcept = default;
    virtual ~FiniteState();

    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();

    void BindOnStateChange(const std::function<void(int)>& onStateChange);

    template <typename T, typename... Args>
    T* CreateTransition(const int stateId, Args... args)
    {
        if (!std::is_base_of_v<Transition, T>) throw Exception(L"T is not derived from Transition");
        T* transition = new T(args...);
        _transitions[transition] = stateId;
        return transition;
    }

private:
    std::unordered_map<Transition*, int> _transitions;
    std::function<void(int)> _onStateChange;
};
