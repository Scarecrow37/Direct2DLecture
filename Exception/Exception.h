#pragma once
#include <exception>
#include <string>

class Exception final : public std::exception
{
public:
    Exception() = default;
    explicit Exception(std::wstring message);
    explicit Exception(const wchar_t* message);

    const wchar_t* UnicodeWhat() const noexcept;

private:
    static std::string ConvertToMultibyte(const std::wstring& string);

    std::wstring _message;
    std::string _multibyteMessage;
};
