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

void AnimationScene::SetNotify(IAnimationNotify* notify)
{
    _notify = notify;
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

void AnimationScene::SetAnimation(const size_t index)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation start.");
    if (_animationAsset == nullptr)
        throw
            Exception(L"AnimationAsset is not loaded, AnimationScene set animation fail.");
    SetCurrentAnimationInfo(_animationAsset->GetAnimationInfo(index));
    if (_currentAnimationInfo == nullptr)
        throw Exception(
            L"AnimationInfo is not found, AnimationScene set animation fail.");
    ResetAnimation();
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation end.");
}

void AnimationScene::SetAnimation(const std::wstring& animationName)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation start.");
    if (_animationAsset == nullptr)
        throw
            Exception(L"AnimationAsset is not loaded, AnimationScene set animation fail.");
    SetCurrentAnimationInfo(_animationAsset->GetAnimationInfo(animationName));
    if (_currentAnimationInfo == nullptr)
        throw Exception(
            L"AnimationInfo is not found, AnimationScene set animation fail.");
    ResetAnimation();
    Logger::Log(LogLevel::Trace, L"AnimationScene set animation end.");
}

void AnimationScene::Initialize()
{
}

void AnimationScene::Update(const float deltaTime)
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update start.");
    UpdateAnimation(deltaTime);
    UpdateTransform();
    Logger::Log(LogLevel::Trace, L"AnimationScene update end.");
}

void AnimationScene::LazyUpdate(float deltaTime)
{
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
        {
            if (_notify) _notify->OnEndAnimation(_currentAnimationInfo->name);
            if (_currentAnimationInfo->isLoop)
            {
                _currentFrameIndex = 0;
                if (_notify) _notify->OnBeginAnimation(_currentAnimationInfo->name);
            }
            else _currentFrameIndex = _currentFrameIndex - 1;
        }
    }
    UpdateFrame();
    Logger::Log(LogLevel::Trace, L"AnimationScene update animation end.");
}

void AnimationScene::UpdateTransform()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update transform start.");
    UpdateCenterTransform();
    UpdateMirrorTransform();
    UpdateWorldTransform();
    Logger::Log(LogLevel::Trace, L"AnimationScene update transform end.");
}

void AnimationScene::UpdateFrame()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update frame start.");
    const FrameInfo& currentFrame = GetCurrentFrame();
    _sourceRect = currentFrame.source;
    _destinationRect = Rect(Vector::Zero(), _sourceRect.GetSize());
    _center = Vector{currentFrame.center.x / _sourceRect.GetSize().x, currentFrame.center.y / _sourceRect.GetSize().y};
    Logger::Log(LogLevel::Trace, L"AnimationScene update frame end.");
}

void AnimationScene::ResetAnimation()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene reset animation start.");
    _frameElapsedTime = 0.f;
    _currentFrameIndex = 0;
    UpdateFrame();
    Logger::Log(LogLevel::Trace, L"AnimationScene reset animation end.");
}


void AnimationScene::UpdateMirrorTransform()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update mirror transform start.");
    _mirrorMatrix = _isMirror
                        ? Matrix::Scale({-1.f, 1.f})
                        : Matrix::Scale({1.f, 1.f});
    Logger::Log(LogLevel::Trace, L"AnimationScene update mirror transform end.");
}

void AnimationScene::UpdateCenterTransform()
{
    Logger::Log(LogLevel::Trace, L"AnimationScene update center transform start.");
    _centerMatrix = Matrix::Translation({
        _destinationRect.GetSize().x * -_center.x, _destinationRect.GetSize().y * -_center.y
    });
    Logger::Log(LogLevel::Trace, L"AnimationScene update center transform end.");
}

void AnimationScene::SetCurrentAnimationInfo(AnimationInfo* animationInfo)
{
    if (_notify && _currentAnimationInfo) _notify->OnBeginAnimationChanged(_currentAnimationInfo->name);
    _currentAnimationInfo = animationInfo;
    if (_notify && _currentAnimationInfo) _notify->OnEndAnimationChanged(_currentAnimationInfo->name);
}

FrameInfo AnimationScene::GetCurrentFrame() const
{
    return _currentAnimationInfo->frames[_currentFrameIndex];
}
