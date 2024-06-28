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
      _sourceRect(Rect::Zero()),
      _destinationRect(Rect::Zero()),
      _isChangedDestinationRect(false),
      _isMirror(false),
      _mirrorMatrix(Matrix::Identity())
{
    Logger::Log(LogLevel::Trace, L"AnimationScene constructor start.");
    Logger::Log(LogLevel::Trace, L"AnimationScene constructor end.");
}

AnimationScene::~AnimationScene()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene destructor start.");
    ResourceManager::ReleaseDSHAnimationAsset(_animationAssetPath);
    Logger::Log(LogLevel::Trace, L"AnimationScene destructor end.");
}

void AnimationScene::LoadAnimationAssetFromFilename(const std::wstring& path)
{
    if (_animationAsset != nullptr)
    {
        Logger::Log(LogLevel::Warning, L"AnimationAsset is already loaded.");
        return;
    }
    try
    {
        Logger::Log(LogLevel::Trace, L"AnimationScene load start.");
        _animationAssetPath = path;
        ResourceManager::CreateDSHAnimationAsset(_animationAssetPath, &_animationAsset);
        SetAnimation(0);
        Logger::Log(LogLevel::Trace, L"AnimationScene load end.");
    }
    catch (const Exception& exception) // NOLINT(bugprone-empty-catch)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        _animationAsset = nullptr;
        _animationAssetPath.clear();
    }
}

void AnimationScene::SetAnimation(const size_t index, const bool isMirror)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation start.");
    if (_animationAsset == nullptr)
        throw
            Exception(L"AnimationAsset is not loaded, AnimationScene set animation fail.");
    _currentAnimationInfo = _animationAsset->GetAnimationInfo(index);
    if (_currentAnimationInfo == nullptr)
        throw Exception(
            L"AnimationInfo is not found, AnimationScene set animation fail.");
    ResetAnimation(isMirror);
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation end.");
}

void AnimationScene::SetAnimation(const std::wstring& animationName, const bool isMirror)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation start.");
    if (_animationAsset == nullptr)
        throw
            Exception(L"AnimationAsset is not loaded, AnimationScene set animation fail.");
    _currentAnimationInfo = _animationAsset->GetAnimationInfo(animationName);
    if (_currentAnimationInfo == nullptr)
        throw Exception(
            L"AnimationInfo is not found, AnimationScene set animation fail.");
    ResetAnimation(isMirror);
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
    if (_bitmap == nullptr) Logger::Log(LogLevel::Information, L"Bitmap is not loaded.");
    if (_animationAsset == nullptr) Logger::Log(LogLevel::Information, L"AnimationAsset is not loaded.");
    if (_bitmap == nullptr || _animationAsset == nullptr) return;
    renderer->SetTransform(_centerMatrix * _mirrorMatrix * _worldTransform * renderer->GetCameraMatrix());
    renderer->DrawBitmap(_bitmap, _destinationRect, _sourceRect);
    Logger::Log(LogLevel::Trace, L"AnimationScene render end.");
}

Vector AnimationScene::GetAnimationBitmapSize() const
{
    return _sourceRect.GetSize();
}

bool AnimationScene::GetMirror() const
{
    return _isMirror;
}

void AnimationScene::SetMirror(const bool isMirror)
{
    _isMirror = isMirror;
}

Rect AnimationScene::GetSourceRect() const
{
    return _sourceRect;
}

Rect AnimationScene::GetDestinationRect() const
{
    return _destinationRect;
}

void AnimationScene::SetDestinationRect(const Rect& destinationRect)
{
    _isChangedDestinationRect = true;
    _destinationRect = destinationRect;
}

void AnimationScene::ResetDestinationRect()
{
    _isChangedDestinationRect = false;
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
        _currentFrameIndex++;
        if (_currentFrameIndex >= _currentAnimationInfo->frames.size())
            _currentFrameIndex = _currentAnimationInfo->isLoop ? 0 : _currentFrameIndex - 1;
    }
    UpdateFrame();
    Logger::Log(LogLevel::Trace, L"AnimationScene update animation end.");
}

void AnimationScene::UpdateTransform()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update transform start.");
    BitmapScene::UpdateTransform();
    if (_currentAnimationInfo != nullptr)
    {
        const FrameInfo& currentFrame = _currentAnimationInfo->frames[_currentFrameIndex];
        _mirrorMatrix = _isMirror
                            ? Matrix::Scale({-1.f, 1.f})
                            * Matrix::Translation(currentFrame.center)
                            : Matrix::Scale({1.f, 1.f})
                            * Matrix::Translation({-currentFrame.center.x, currentFrame.center.y});
    }
    Logger::Log(LogLevel::Trace, L"AnimationScene update transform end.");
}

void AnimationScene::UpdateFrame()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update frame start.");
    const FrameInfo& currentFrame = _currentAnimationInfo->frames[_currentFrameIndex];
    _sourceRect = currentFrame.source;
    if (!_isChangedDestinationRect) _destinationRect = Rect(Vector::Zero(), _sourceRect.GetSize());
    Logger::Log(LogLevel::Trace, L"AnimationScene update frame end.");
}

void AnimationScene::ResetAnimation(const bool isMirror)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene reset animation start.");
    _isMirror = isMirror;
    _frameElapsedTime = 0.f;
    _currentFrameIndex = 0;
    UpdateFrame();
    Logger::Log(LogLevel::Trace, L"AnimationScene reset animation end.");
}
