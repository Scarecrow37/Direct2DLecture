#pragma once

struct Transition
{
    Transition() = default;
    Transition(const Transition& other) = default;
    Transition(Transition&& other) noexcept = default;
    Transition& operator=(const Transition& other) = default;
    Transition& operator=(Transition&& other) noexcept = default;
    virtual ~Transition() = default;
    virtual bool operator()(float deltaTime) = 0;
};
