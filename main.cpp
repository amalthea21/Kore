#include <unistd.h>
#include <termios.h>

#include "include/TerminalFace.h"
#include "include/Clip.h"

int main(int argc, char* argv[]) {
    TerminalFace terminalFace{};


    terminalFace.restoreTerminal();
}