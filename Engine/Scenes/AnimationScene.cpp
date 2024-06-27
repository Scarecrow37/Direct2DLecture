#include "pch.h"
#include "AnimationScene.h"

#include "../Renderer/D2DRenderer.h"

AnimationScene::AnimationScene() : AnimationScene(nullptr)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene constructor start.");
    Logger::Log(LogLevel::Trace, L"AnimationScene constructor end.");
}

AnimationScene::AnimationScene(const Scene* parent)
    : BitmapScene(parent),
      _animationAsset(nullptr),
      _currentAnimationInfo(nullptr),
      _frameElapsedTime(0.f),
      _currentFrameIndex(0),
      _previousFrameIndex(0),
      _sourceRect(Rect::Zero()),
      _destinationRect(Rect::Zero()),
      _mirror(false),
      _mirrorMatrix(Matrix::Identity())
{
    Logger::Log(LogLevel::Trace, L"AnimationScene constructor start.");
    Logger::Log(LogLevel::Trace, L"AnimationScene constructor end.");
}

AnimationScene::~AnimationScene()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene destructor start.");
    ResourceManager::ReleaseDSHAnimationAsset(_path);
    Logger::Log(LogLevel::Trace, L"AnimationScene destructor end.");
}

void AnimationScene::LoadAnimationAssetFromFilename(const std::wstring& path)
{
    try
    {
        Logger::Log(LogLevel::Trace, L"AnimationScene load start.");
        _path = path;
        ResourceManager::CreateDSHAnimationAsset(_path, &_animationAsset);
        Logger::Log(LogLevel::Trace, L"AnimationScene load end.");
    }
    catch (const Exception& exception)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        throw Exception(L"AnimationScene load fail.");
    }
}

void AnimationScene::SetAnimation(const std::wstring& animationName, const bool mirror)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation start.");
    if (_animationAsset == nullptr)
        throw
            Exception(L"AnimationAsset is not loaded, AnimationScene set animation fail.");
    _currentAnimationInfo = _animationAsset->GetAnimationInfo(animationName);
    if (_currentAnimationInfo == nullptr)
        throw Exception( L"AnimationInfo is not found, AnimationScene set animation fail.");
    _animationName = animationName;
    _mirror = mirror;
    _frameElapsedTime = 0.f;
    _currentFrameIndex = _previousFrameIndex = 0;
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation end.");
}

void AnimationScene::Update(const float deltaTime)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update start.");
    UpdateAnimation(deltaTime);
    UpdateTransform();
    Logger::Log(LogLevel::Trace, L"AnimationScene update end.");
}

void AnimationScene::Render(const D2DRenderer* renderer) const
{
    Logger::Log(LogLevel::Trace, L"AnimationScene render start.");
    if (_bitmap == nullptr || _animationAsset == nullptr)
    {
        Logger::Log(LogLevel::Warning, L"Bitmap or AnimationAsset is not loaded.");
        return;
    }
    renderer->SetTransform(_centerMatrix * _mirrorMatrix * _worldTransform * renderer->GetCameraMatrix());
    renderer->DrawBitmap(_bitmap, _destinationRect, _sourceRect);
    Logger::Log(LogLevel::Trace, L"AnimationScene render end.");
}

void AnimationScene::UpdateAnimation(const float deltaTime)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update animation start.");
    if (_currentAnimationInfo == nullptr) return;
    _frameElapsedTime += deltaTime;
    const float duration = _currentAnimationInfo->frames[_currentFrameIndex].duration;
    if (_frameElapsedTime >= duration)
    {
        _frameElapsedTime -= duration;
        _previousFrameIndex = _currentFrameIndex;
        _currentFrameIndex = (_currentFrameIndex + 1) % _currentAnimationInfo->frames.size();
    }
    const FrameInfo& currentFrame = _currentAnimationInfo->frames[_currentFrameIndex];
    _sourceRect = currentFrame.source;
    _destinationRect = Rect(Vector::Zero(), _sourceRect.GetSize());
    Logger::Log(LogLevel::Trace, L"AnimationScene update animation end.");
}

void AnimationScene::UpdateTransform()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update transform start.");
    BitmapScene::UpdateTransform();
    const FrameInfo& currentFrame = _currentAnimationInfo->frames[_currentFrameIndex];
    _mirrorMatrix = _mirror
                        ? Matrix::Scale({-1.f, 1.f})
                        * Matrix::Translation(currentFrame.center)
                        : Matrix::Scale({1.f, 1.f})
                        * Matrix::Translation({-currentFrame.center.x, currentFrame.center.y});
    Logger::Log(LogLevel::Trace, L"AnimationScene update transform end.");
}
