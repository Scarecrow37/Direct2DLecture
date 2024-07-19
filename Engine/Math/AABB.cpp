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

bool AABB::CheckIntersect(const AABB& other, Manifold* manifold) const
{
    manifold->contactCount = 0;
    Vector n = other.GetCenter() - GetCenter();
    float xOverlap = GetExtend().x + other.GetExtend().x - abs(n.x);
    float yOverlap = GetExtend().y + other.GetExtend().y - abs(n.y);
    if (xOverlap < 0 || yOverlap < 0) return false;
        manifold->contactCount = 2;
    if (xOverlap < yOverlap)
    {
        if (n.x < 0) manifold->normal = Vector::Left();
        else manifold->normal = Vector::Right();
        manifold->penetration = xOverlap;
        manifold->contactPoints[0] = Vector{(n.x < 0 ? GetMinX() : GetMaxX()), max(GetMinY(), other.GetMinY())};
        manifold->contactPoints[1] = Vector(manifold->contactPoints[0].x, min(GetMaxY(), other.GetMaxY()));
    }
    else
    {
        if (n.y < 0) manifold->normal = Vector::Up();
        else manifold->normal = Vector::Down();
        manifold->penetration = yOverlap;
        manifold->contactPoints[0] = Vector{max(GetMinX(), other.GetMinX()), (n.y < 0 ? GetMinY() : GetMaxY())};
        manifold->contactPoints[1] = Vector{min(GetMaxX(), other.GetMaxX()), manifold->contactPoints[0].y};
    }
    return true;
    
}


Rect AABB::GetRect() const
{
    return Rect(GetMinX(), GetMinY(), GetMaxX(), GetMaxY());
}
