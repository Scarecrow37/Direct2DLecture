#pragma once

class ILoader
{
public:
    virtual ~ILoader() = default;
    virtual void Load(const wchar_t* path, void* container) const = 0;
};
