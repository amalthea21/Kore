#pragma once

#include <termios.h>
#include <iostream>

#include "Track.h"

class TerminalFace {
public:
    TerminalFace();
    void restoreTerminal();

    void printTop();
    void printPlaylist(const std::vector<Track>& playlist);
private:
    termios old;
    termios term;

    int terminalWidth();
};