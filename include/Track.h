#pragma once

#include <vector>

#include "Clip.h"

class Track {
public:
    std::vector<Clip> track;
    bool on = true;

    Track() = default;
    Track(const Track&) = delete;
    Track& operator=(const Track&) = delete;
    Track(Track&&) = default;
    Track& operator=(Track&&) = default;
};