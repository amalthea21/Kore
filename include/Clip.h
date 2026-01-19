#pragma once

class Clip {
public:
    float time;
    float* samples;

    Clip(int t);
    ~Clip();

    Clip(const Clip&) = delete;
    Clip& operator=(const Clip&) = delete;
    Clip(Clip&& other) noexcept;
    Clip& operator=(Clip&& other) noexcept;
};