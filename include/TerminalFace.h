#pragma once

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

class TerminalFace {
public:
    TerminalFace();
    void restoreTerminal();

private:
    termios old;
    termios term;
};