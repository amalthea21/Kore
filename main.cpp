#include <vector>
#include <thread>

#include "include/TerminalFace.h"
#include "include/Clip.h"
#include "include/Track.h"
#include "include/Cursor.h"
#include "include/AnsiFormat.h"
#include "include/WaveGenerator.h"


int main(int argc, char* argv[]) {
    TerminalFace terminalFace{};
    WaveGenerator waveGenerator{};
    Cursor cursor{};
    std::vector<Track> playlist;

    playlist.push_back(Track{});
    playlist.push_back(Track{});

    // Set initial cursor position
    cursor.moveTo(15, 5);

    int key;

    do {
        std::cout << ANSI::CLEAR_SCREEN;
        std::cout << "\033[H";
        terminalFace.printTop();
        terminalFace.printPlaylist(playlist);

        cursor.show();

        std::cout << std::flush;

        key = terminalFace.readKey();

        switch (key) {
            case TerminalFace::KEY_ARROW_UP:
                cursor.moveUp();
                break;
            case TerminalFace::KEY_ARROW_DOWN:
                cursor.moveDown();
                break;
            case TerminalFace::KEY_ARROW_LEFT:
                cursor.moveLeft();
                break;
            case TerminalFace::KEY_ARROW_RIGHT:
                cursor.moveRight();
                break;
            case ' ':
                int trackY = cursor.getY();
                if (trackY >= 5 && trackY < 5 + playlist.size()) {
                    int trackIndex = trackY - 5;
                    playlist[trackIndex].on = !playlist[trackIndex].on;
                }
                break;
        }

    } while (key != TerminalFace::KEY_F1);

    terminalFace.restoreTerminal();
}