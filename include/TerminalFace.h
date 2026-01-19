#pragma once

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

#include "AnsiFormat.h"
#include "Track.h"

class TerminalFace {
public:
    TerminalFace();
    void restoreTerminal();
    void printTrack(Track track);

private:
    termios old;
    termios term;
};