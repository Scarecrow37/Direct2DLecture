#include "BitmapScene.h"

#include "../Loader/ILoader.h"
#include "../Renderer/D2DRenderer.h"

BitmapScene::BitmapScene(const wchar_t* path, const ILoader* loader)
    : _center(0.f, 0.f), _path(path), _loader(loader), _bitmap(nullptr)
{
}

BitmapScene::~BitmapScene()
{
    if (_bitmap != nullptr)
    {
        _bitmap->Release();
        _bitmap = nullptr;
    }
}

void BitmapScene::Initialize()
{
    Load();
}

void BitmapScene::Load()
{
    try
    {
        _loader->Load(_path, &_bitmap);
        const Vector size(_bitmap->GetSize());
        _center = size / 2.f;
    }
    catch (...)
    {
        throw;
    }
}

void BitmapScene::SetCenter(const Vector& center)
{
    _center = center;
}

Vector BitmapScene::GetCenter() const
{
    return _center;
}


void BitmapScene::UpdateTransform()
{
    const Matrix centerMatrix = Matrix::Translation(_center);
    const Matrix inverseCenterMatrix = centerMatrix.Inverse();
    Scene::UpdateTransform();
    _transform = inverseCenterMatrix * _transform;
    if (_parentScene) _worldTransform = _parentScene->GetWorldTransform() * _transform;
    else _worldTransform = _transform;
}

void BitmapScene::Update(const float deltaTime)
{
    UpdateTransform();
}

void BitmapScene::Render(D2DRenderer* renderer)
{
    renderer->SetTransform(_worldTransform);
    renderer->DrawBitmap(_bitmap);
}
