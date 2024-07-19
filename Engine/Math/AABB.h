#pragma once

struct Manifold
{
    unsigned int contactCount;
    Vector contactPoints[2];
    Vector normal;
    float penetration;
};


class AABB
{
public:
    AABB();
    AABB(const Rect& rect);
    AABB(const Vector& center, const Vector& extend);

    void SetCenter(const Vector& center);
    Vector GetCenter() const;
    
    void SetExtend(const Vector& extend);
    Vector GetExtend() const;

    float GetMinX() const;
    float GetMinY() const;
    float GetMaxX() const;
    float GetMaxY() const;

    bool CheckIntersect(const AABB& other, Manifold* manifold) const;

    Rect GetRect() const;

private:
    Vector _center;
    Vector _extend;
};
