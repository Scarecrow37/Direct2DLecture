#pragma once

struct FrameInfo
{
    D2D1_RECT_F source;
    D2D1_VECTOR_2F center;
    FLOAT duration;
};

struct AnimationInfo
{
    bool isLoop;
    std::vector<FrameInfo> frames;
};
