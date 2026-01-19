#pragma once

#include <vector>

#include "Clip.h"

class Track {
    std::vector<Clip> track;
    bool on = true;
};