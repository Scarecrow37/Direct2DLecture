#include "pch.h"
#include "AABB.h"

AABB::AABB()
    : AABB(Vector::Zero(), Vector::Zero())
{
}

AABB::AABB(const Rect& rect)
    : AABB(rect.GetCenter(), rect.GetExtend())
{
}

AABB::AABB(const Vector& center, const Vector& extend)
    : _center(center), _extend(extend)
{
}

void AABB::SetCenter(const Vector& center)
{
    _center = center;
}

Vector AABB::GetCenter() const
{
    return _center;
}

void AABB::SetExtend(const Vector& extend)
{
    _extend = extend;
}

Vector AABB::GetExtend() const
{
    return _extend;
}

float AABB::GetMinX() const
{
    return _center.x - _extend.x;
}

float AABB::GetMaxX() const
{
    return _center.x + _extend.x;
}

float AABB::GetMinY() const
{
    return _center.y - _extend.y;
}

float AABB::GetMaxY() const
{
    return _center.y + _extend.y;
}

bool AABB::CheckIntersect(const AABB& other) const
{
    return !(
        GetMaxX() < other.GetMinX() ||
        GetMinX() > other.GetMaxX() ||
        GetMaxY() < other.GetMinY() ||
        GetMinY() > other.GetMaxY()
    );
}
