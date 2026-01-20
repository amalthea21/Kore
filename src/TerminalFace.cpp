#include "../include/TerminalFace.h"

#include <unistd.h>
#include <cstdio>
#include <string>
#include <sys/ioctl.h>

#include "../include/AnsiFormat.h"

#pragma region Terminal
TerminalFace::TerminalFace() {
    std::cout << ANSI::CLEAR_SCREEN << ANSI::HIDE_CURSOR << ANSI::RESET;
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
    std::cout << ANSI::SHOW_CURSOR << ANSI::RESET;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr restore");
}

int TerminalFace::readKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1)
        return KEY_UNKNOWN;

    if (c == 27) { // Escape Sequences
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return KEY_ESC;

        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return KEY_ESC;

        if (seq[0] == '[') {
            if (seq[1] >= '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1)
                    return KEY_UNKNOWN;

                if (seq[2] == '~') {
                    switch (seq[1]) {
                        case '1': return KEY_HOME;
                        case '2': return KEY_INSERT;
                        case '3': return KEY_DELETE;
                        case '4': return KEY_END;
                        case '5': return KEY_PAGE_UP;
                        case '6': return KEY_PAGE_DOWN;
                    }
                }
            } else {
                // Arrow keys
                switch (seq[1]) {
                    case 'A': return KEY_ARROW_UP;
                    case 'B': return KEY_ARROW_DOWN;
                    case 'C': return KEY_ARROW_RIGHT;
                    case 'D': return KEY_ARROW_LEFT;
                    case 'H': return KEY_HOME;
                    case 'F': return KEY_END;
                }
            }
        } else if (seq[0] == 'O') {
            // Function keys F1-F4
            switch (seq[1]) {
                case 'P': return KEY_F1;
                case 'Q': return KEY_F2;
                case 'R': return KEY_F3;
                case 'S': return KEY_F4;
            }
        }

        return KEY_ESC;
    }

    if (c >= 1 && c <= 26) {
        return c;
    }

    return c;
}

int TerminalFace::terminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

#pragma endregion

#pragma region UI
/* UI Characters: ─ │ ├ ┤ ┬ ┴ ┼ ╭ ╮ ╰ ╯ ◉
 * TODO: Dynamic Length of UI Elements
 */

void TerminalFace::printTop() {
    std::string top = " Kore v0.1";
    int termWidth = terminalWidth();
    top.resize(termWidth, ' ');

    std::cout << ANSI::BG_WHITE << ANSI::BLACK << top << ANSI::RESET << std::endl;

    std::cout << "\n╭─ ▶ : ‖ ─╮  ╭─ Quit: F1 ─╮  ╭─ File: F2 ─╮"
                 "\n╰─────────╯  ╰────────────╯  ╰────────────╯"
                 "\n"
              << std::endl;
}

void TerminalFace::printPlaylist(const std::vector<Track>& playlist) {
    int termWidth = terminalWidth();

    int fixedWidth = 14;
    int remainingWidth = termWidth - fixedWidth;
    if (remainingWidth < 0) remainingWidth = 0;

    if (playlist.empty())
        return;

    std::cout << "╭───────────┬";
    for (int i = 0; i < remainingWidth; i++) {
        std::cout << "─";
    }
    std::cout << "╮";

    for (int i = 0; i < playlist.size(); i++) {

        std::string circle;

        if (playlist[i].on)
            circle = ANSI::GREEN + " ◉ " + ANSI::RESET;
        else
            circle = " ◉ ";

        std::cout << "\n├ Track " << i+1 << circle << "│";
        for (int j = 0; j < remainingWidth; j++) {
            std::cout << " ";
        }
        std::cout << "│";
    }

    std::cout << "\n╰───────────┴";
    for (int i = 0; i < remainingWidth; i++) {
        std::cout << "─";
    }
    std::cout << "╯";
}
#pragma endregion