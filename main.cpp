#include <unistd.h>
#include <termios.h>

#include "include/TerminalFace.h"
#include "include/Clip.h"
#include "include/Track.h"

int main(int argc, char* argv[]) {
    TerminalFace terminalFace{};
    Track track;



    terminalFace.restoreTerminal();
}