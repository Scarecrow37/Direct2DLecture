#include "pch.h"
#include "Camera.h"

void Camera::SetCullingBound(const AABB& bound)
{
    _cullingBound = bound;
}

AABB* Camera::GetCullingBound()
{
    return &_cullingBound;
}
