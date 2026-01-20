#pragma once

#include <termios.h>
#include <iostream>
#include <string>

#include "Track.h"

class TerminalFace {
public:
    enum Key {
        KEY_UNKNOWN = 0,
        KEY_ESC = 27,
        KEY_F1 = 1001,
        KEY_F2 = 1002,
        KEY_F3 = 1003,
        KEY_F4 = 1004,
        KEY_F5 = 1005,
        KEY_F6 = 1006,
        KEY_F7 = 1007,
        KEY_F8 = 1008,
        KEY_F9 = 1009,
        KEY_F10 = 1010,
        KEY_F11 = 1011,
        KEY_F12 = 1012,
        KEY_ARROW_UP = 1100,
        KEY_ARROW_DOWN = 1101,
        KEY_ARROW_LEFT = 1102,
        KEY_ARROW_RIGHT = 1103,
        KEY_DELETE = 1200,
        KEY_INSERT = 1201,
        KEY_HOME = 1202,
        KEY_END = 1203,
        KEY_PAGE_UP = 1204,
        KEY_PAGE_DOWN = 1205,
        KEY_CTRL_A = 1,
        KEY_CTRL_B = 2,
        KEY_CTRL_C = 3,
        KEY_CTRL_D = 4,
        KEY_CTRL_E = 5,
        KEY_CTRL_F = 6,
        KEY_CTRL_G = 7,
        KEY_CTRL_H = 8,
        KEY_CTRL_I = 9,
        KEY_CTRL_J = 10,
        KEY_CTRL_K = 11,
        KEY_CTRL_L = 12,
        KEY_CTRL_M = 13,
        KEY_CTRL_N = 14,
        KEY_CTRL_O = 15,
        KEY_CTRL_P = 16,
        KEY_CTRL_Q = 17,
        KEY_CTRL_R = 18,
        KEY_CTRL_S = 19,
        KEY_CTRL_T = 20,
        KEY_CTRL_U = 21,
        KEY_CTRL_V = 22,
        KEY_CTRL_W = 23,
        KEY_CTRL_X = 24,
        KEY_CTRL_Y = 25,
        KEY_CTRL_Z = 26
    };

    TerminalFace();
    void restoreTerminal();

    int readKey();

    void printTop();
    void printPlaylist(const std::vector<Track>& playlist);
private:
    termios old;
    termios term;

    int terminalWidth();
};