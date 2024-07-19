#pragma once
#include "BitmapScene.h"

class IAnimationNotify
{
public:
    IAnimationNotify() = default;
    IAnimationNotify(const IAnimationNotify& other) = default;
    IAnimationNotify(IAnimationNotify&& other) noexcept = default;
    IAnimationNotify& operator=(const IAnimationNotify& other) = default;
    IAnimationNotify& operator=(IAnimationNotify&& other) noexcept = default;
    virtual ~IAnimationNotify() = default;

    virtual void OnBeginAnimation(std::wstring animationName) = 0;
    virtual void OnEndAnimation(std::wstring animationName) = 0;
    virtual void OnBeginAnimationChanged(std::wstring animationName) = 0;
    virtual void OnEndAnimationChanged(std::wstring animationName) = 0;
};

class AnimationScene : public BitmapScene
{
public:
    AnimationScene();
    AnimationScene(const Scene* parent);
    AnimationScene(const AnimationScene& other) = default;
    AnimationScene(AnimationScene&& other) noexcept = default;
    AnimationScene& operator=(const AnimationScene& other) = default;
    AnimationScene& operator=(AnimationScene&& other) noexcept = default;
    ~AnimationScene() override;

    void SetNotify(IAnimationNotify* notify);

    void LoadAnimationAssetFromFilename(const std::wstring& path);
    void SetAnimation(size_t index);
    void SetAnimation(const std::wstring& animationName);

    void Initialize() override;
    void Update(float deltaTime) override;
    void LazyUpdate(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

    Vector GetAnimationBitmapSize() const;

    bool GetMirror() const;
    void SetMirror(bool isMirror);

    Rect GetSourceRect() const;

    Rect GetDestinationRect() const;

protected:
    void UpdateAnimation(float deltaTime);
    void UpdateTransform() override;
    void UpdateFrame();
    void ResetAnimation();
    virtual void UpdateMirrorTransform();
    void UpdateCenterTransform() override;

private:
    void SetCurrentAnimationInfo(AnimationInfo* animationInfo);
    FrameInfo GetCurrentFrame() const;
    IDSHAnimationAsset* _animationAsset;
    std::wstring _animationAssetPath;

    AnimationInfo* _currentAnimationInfo;
    float _frameElapsedTime;
    size_t _currentFrameIndex;
    Rect _sourceRect;
    Rect _destinationRect;

    bool _isMirror;
    Matrix _mirrorMatrix;

    IAnimationNotify* _notify;
};
