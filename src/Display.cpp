#include "../include/Display.h"

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
    int fixedWidth = 14, startPos, clipLength, endPos, remainingWidth = termWidth - fixedWidth;
    float timescale = 2.0f;

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

        // Create a NEW timeline for each track
        std::vector<char> timeline(remainingWidth, ' ');

        // Clip representation - fill the timeline
        for (const auto& clip : playlist[i].track) {
            startPos = static_cast<int>(clip.at / timescale);
            clipLength = static_cast<int>(clip.time / timescale);

            if (startPos < remainingWidth) {
                endPos = std::min(startPos + clipLength, remainingWidth);

                for (int pos = startPos; pos < endPos; pos++) {
                    if (pos == startPos)
                        timeline[pos] = '/';
                    else if (pos == endPos - 1)
                        timeline[pos] = '\\';
                    else
                        timeline[pos] = '-';
                }
            }
        }

        for (char c : timeline) {
            std::cout << c;
        }

        std::cout << "│";
    }

    std::cout << "\n╰───────────┴";
    for (int i = 0; i < remainingWidth; i++) {
        std::cout << "─";
    }
    std::cout << "╯";
}