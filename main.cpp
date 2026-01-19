#include <unistd.h>
#include <termios.h>
#include <vector>

#include "include/TerminalFace.h"
#include "include/Clip.h"
#include "include/Track.h"
#include "include/AnsiFormat.h"

int main(int argc, char* argv[]) {
    TerminalFace terminalFace{};
    std::vector<Track> playlist;

    playlist.emplace_back();
    playlist.emplace_back();

    playlist[0].on = true;
    playlist[1].on = false;

    terminalFace.printTop();
    terminalFace.printPlaylist(playlist);

    terminalFace.restoreTerminal();
}