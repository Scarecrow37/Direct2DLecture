#pragma once

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
    float GetMaxX() const;
    float GetMinY() const;
    float GetMaxY() const;

    bool CheckIntersect(const AABB& other) const;

private:
    Vector _center;
    Vector _extend;
};
