#include <vector>
#include <thread>

#include "include/TerminalFace.h"
#include "include/Clip.h"
#include "include/Track.h"
#include "include/AnsiFormat.h"
#include "include/WaveGenerator.h"

int main(int argc, char* argv[]) {
    TerminalFace terminalFace{};
    WaveGenerator waveGenerator{};
    std::vector<Track> playlist;

    playlist.push_back(Track{});
    playlist.push_back(Track{});

    int key;

    do {
        std::cout << ANSI::CLEAR_SCREEN;
        terminalFace.printTop();
        terminalFace.printPlaylist(playlist);
        std::cout << std::flush;

        key = terminalFace.readKey();
    } while (key != TerminalFace::KEY_F1);

    terminalFace.restoreTerminal();
}