#include <vector>

#include "include/TerminalSettings.h"
#include "include/Clip.h"
#include "include/Track.h"
#include "include/Cursor.h"
#include "include/AnsiFormat.h"
#include "include/WaveGenerator.h"
#include "include/Display.h"

struct AppState {
    Cursor cursor;
    std::vector<Track> playlist;
    bool isPlaying = false;
};

enum Event {
    QUIT,
    CURSOR_UP, CURSOR_DOWN, CURSOR_LEFT, CURSOR_RIGHT,
    SELECT, DELETE,
    PLAY, PAUSE
};

Event getEvent(int key) {
    switch (key) {
        case TerminalSettings::KEY_F1: return QUIT;

        case TerminalSettings::KEY_ARROW_UP: return CURSOR_UP;
        case TerminalSettings::KEY_ARROW_DOWN: return CURSOR_DOWN;
        case TerminalSettings::KEY_ARROW_LEFT: return CURSOR_LEFT;
        case TerminalSettings::KEY_ARROW_RIGHT: return CURSOR_RIGHT;

        case ' ': return SELECT;
        case TerminalSettings::KEY_DELETE: return DELETE;
    }
}

void deleteHandler(AppState &state) {
    int trackY = state.cursor.getY();

    if (trackY >= 5 && trackY < 5 + state.playlist.size()) {
        int trackIndex = trackY - 5;
        state.playlist.erase(state.playlist.begin() + trackIndex);

        if (state.cursor.getY() >= 5 + state.playlist.size() && state.playlist.size() > 0) {
            state.cursor.moveUp();
        }
    }
}

void selectHandler(AppState &state) {
    int cursorX = state.cursor.getX();
    int cursorY = state.cursor.getY();

    if (cursorY == 2 && cursorX >= 3 && cursorX <= 5) { // Play
        state.isPlaying = true;
    }
    else if (cursorY == 2 && cursorX >= 7 && cursorX <= 9) { // Pause
        state.isPlaying = false;
    }
    else if (cursorY >= 6 && cursorY < 5 + state.playlist.size()) { // Mute/Solo tracks
        int trackIndex = cursorY - 5;
        state.playlist[trackIndex].on = !state.playlist[trackIndex].on;
    }
    else if (cursorY == 6 + state.playlist.size()) { // Add tracks
        state.playlist.push_back(Track{});
    }
}

void eventHandler(Event event, AppState &state) {
    switch (event) {
        case CURSOR_UP: state.cursor.moveUp(); break;
        case CURSOR_DOWN: state.cursor.moveDown(); break;
        case CURSOR_LEFT: state.cursor.moveLeft(); break;
        case CURSOR_RIGHT: state.cursor.moveRight(); break;
        case SELECT: selectHandler(state); break;
        case DELETE: deleteHandler(state); break;
        case PLAY: state.isPlaying = true; break;
        case PAUSE: state.isPlaying = false; break;
    }
}

int main(int argc, char* argv[]) {
    TerminalSettings terminalSettings{};
    Display display;
    WaveGenerator waveGenerator{};
    AppState appState{};

    appState.playlist.push_back(Track{});
    appState.playlist.push_back(Track{});
    appState.cursor.moveTo(15, 5);

    Event key;

    do {
        std::cout << ANSI::CLEAR_SCREEN;
        std::cout << "\033[H";
        display.printTop(terminalSettings.terminalWidth());
        display.printPlaylist(appState.playlist, terminalSettings.terminalWidth());

        appState.cursor.show();

        std::cout << std::flush;

        key = getEvent(terminalSettings.readKey());
        eventHandler(key, appState);

    } while (key != QUIT);

    terminalSettings.restoreTerminal();
}