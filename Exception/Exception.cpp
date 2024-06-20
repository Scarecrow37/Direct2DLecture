#include "Exception.h"

#include <codecvt>

Exception::Exception(std::wstring message):
    exception(ConvertToMultibyte(message).c_str()), _message(std::move(message))
{
}

Exception::Exception(const wchar_t* message):
    Exception(std::wstring(message))
{
}

const wchar_t* Exception::UnicodeWhat() const noexcept
{
    return _message.c_str();
}

std::string Exception::ConvertToMultibyte(const std::wstring& string)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(string);
}
