#pragma once

class Camera
{
public:
    Camera() = default;
    Camera(const Camera& other) = default;
    Camera(Camera&& other) noexcept = default;
    Camera& operator=(const Camera& other) = default;
    Camera& operator=(Camera&& other) noexcept = default;
    virtual ~Camera() = default;

    void SetCullingBound(const AABB& bound);
    AABB* GetCullingBound();

    virtual void UpdateCullingBound() = 0;
    virtual Matrix GetCameraMatrix() const = 0;

protected:
    AABB _cullingBound;
};
