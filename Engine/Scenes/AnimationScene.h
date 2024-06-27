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
    void SetAnimation(size_t index, bool mirror = false);
    void SetAnimation(const std::wstring& animationName, bool mirror = false);

    void Update(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

protected:
    void UpdateAnimation(float deltaTime);
    void UpdateTransform() override;

private:
    IDSHAnimationAsset* _animationAsset;
    std::wstring _path;

    AnimationInfo* _currentAnimationInfo;
    float _frameElapsedTime;
    size_t _currentFrameIndex;
    Rect _sourceRect;
    Rect _destinationRect;

    bool _mirror;
    Matrix _mirrorMatrix;
};
