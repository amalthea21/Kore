#include "../include/TerminalFace.h"

#pragma region Initialize/Restore Terminal
TerminalFace::TerminalFace() {
    std::cout << "\033[?25l";
    fflush(stdout);

    if (tcgetattr(0, &old) < 0)
        perror("tcgetattr");

    term = old;

    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &term) < 0)
        perror("tcsetattr ICANON");
}

void TerminalFace::restoreTerminal() {
    std::cout << "\033[?25h";

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr restore");
}
#pragma endregion

