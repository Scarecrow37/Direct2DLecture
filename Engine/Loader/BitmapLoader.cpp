#include "BitmapLoader.h"

#include <exception>
#include <string>

#include "../Renderer/D2DRenderer.h"

BitmapLoader::BitmapLoader(const D2DRenderer* renderer): _renderer(renderer)
{
}

void BitmapLoader::Load(const wchar_t* path, void* container) const
{
    try
    {
        _renderer->BitmapFromFile(path, static_cast<ID2D1Bitmap**>(container));
    }
    catch (const std::exception& exception)
    {
        std::wstring pathString(path);
        std::string message;
        message.assign(pathString.begin(), pathString.end());
        throw std::exception(message.append(" load fail. ").append(exception.what()).c_str());
    }
}
