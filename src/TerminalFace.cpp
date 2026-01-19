#include "../include/TerminalFace.h"

#include <unistd.h>
#include <cstdio>
#include <string>
#include <sys/ioctl.h>

#include "../include/AnsiFormat.h"

#pragma region Terminal
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
    const int elementCount = 3;

    struct element {
        std::string str;
        int row;
    };

    std::vector<std::string> lines(2);
    element interface[elementCount] {};

    interface[0].row = 0;
    interface[0].str = " ▶ : ‖ ";

    interface[1].row = 0;
    interface[1].str = " Quit: F1 ";

    interface[2].row = 0;
    interface[2].str = " File: F2";

    for (int i = 0; i < elementCount; i++) {
        std::string content = interface[i].str;

        int displayWidth = 0;
        for (size_t j = 0; j < content.length(); ) {
            unsigned char c = content[j];
            if ((c & 0x80) == 0) {
                // ASCII character (1 byte)
                displayWidth++;
                j++;
            } else if ((c & 0xE0) == 0xC0) {
                // 2-byte UTF-8
                displayWidth++;
                j += 2;
            } else if ((c & 0xF0) == 0xE0) {
                // 3-byte UTF-8
                displayWidth++;
                j += 3;
            } else {
                // 4-byte UTF-8
                displayWidth++;
                j += 4;
            }
        }

        std::string topBorder = "╭─" + content + "─╮";

        std::string bottomBorder = "╰";
        for (int j = 0; j < displayWidth + 2; j++) {
            bottomBorder += "─";
        }
        bottomBorder += "╯";

        lines[0] += topBorder;
        lines[1] += bottomBorder;

        if (i < 1) {
            lines[0] += " ";
            lines[1] += " ";
        }
    }

    for (size_t i = 0; i < lines.size(); i++) {
        std::cout << lines[i] << std::endl;
    }
}

void TerminalFace::printPlaylist(const std::vector<Track>& playlist) {
    int termWidth = terminalWidth();

    int fixedWidth = 14;
    int remainingWidth = termWidth - fixedWidth;
    if (remainingWidth < 0) remainingWidth = 0;

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
    std::cout << "╯" << std::endl;
}
#pragma endregion