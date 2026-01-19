#include "../include/TerminalFace.h"

#pragma region Initialize/Restore Terminal
TerminalFace::TerminalFace() {
    std::cout << ANSI::HIDE_CURSOR << ANSI::RESET << std::endl;
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
    std::cout << ANSI::SHOW_CURSOR << ANSI::RESET << std::endl;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr restore");
}
#pragma endregion