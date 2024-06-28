#pragma once
#include "BitmapScene.h"

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

    void LoadAnimationAssetFromFilename(const std::wstring& path);
    void SetAnimation(size_t index, bool isMirror = false);
    void SetAnimation(const std::wstring& animationName, bool isMirror = false);

    void Update(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

    Vector GetAnimationBitmapSize() const;

    bool GetMirror() const;
    void SetMirror(bool isMirror);

    Rect GetSourceRect() const;

    Rect GetDestinationRect() const;
    void SetDestinationRect(const Rect& destinationRect);
    void ResetDestinationRect();

protected:
    void UpdateAnimation(float deltaTime);
    void UpdateTransform() override;
    void UpdateFrame();
    void ResetAnimation(bool isMirror);

private:
    IDSHAnimationAsset* _animationAsset;
    std::wstring _animationAssetPath;

    AnimationInfo* _currentAnimationInfo;
    float _frameElapsedTime;
    size_t _currentFrameIndex;
    Rect _sourceRect;
    Rect _destinationRect;
    bool _isChangedDestinationRect;

    bool _isMirror;
    Matrix _mirrorMatrix;
};
