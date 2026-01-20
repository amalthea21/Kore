#pragma once

#include <vector>

#include "TerminalSettings.h"
#include "Track.h"
#include "AnsiFormat.h"

class Display { // UI Characters: ─ │ ├ ┤ ┬ ┴ ┼ ╭ ╮ ╰ ╯ ◉
    public:
    void printTop(const int termWidth);
    void printPlaylist(const std::vector<Track>& playlist, const int termWidth);
};