#include "Display.h"

void Display::printTop(const int termWidth) {
    std::string top = " Kore v0.1";
    top.resize(termWidth, ' ');

    std::cout << ANSI::BG_WHITE << ANSI::BLACK << top << ANSI::RESET << std::endl;

    std::cout << "\n╭─ ▶ : ‖ ─╮  ╭─ Quit: F1 ─╮  ╭─ File: F2 ─╮"
                 "\n╰─────────╯  ╰────────────╯  ╰────────────╯"
                 "\n"
              << std::endl;
}

void Display::printPlaylist(const std::vector<Track>& playlist, const int termWidth) {
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