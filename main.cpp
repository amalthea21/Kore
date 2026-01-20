#include <vector>

#include "include/TerminalFace.h"
#include "include/Clip.h"
#include "include/Track.h"
#include "include/Cursor.h"
#include "include/AnsiFormat.h"
#include "include/WaveGenerator.h"

struct AppState {
    Cursor cursor;
    std::vector<Track> playlist;
};

enum Event {
    QUIT,
    CURSOR_UP, CURSOR_DOWN, CURSOR_LEFT, CURSOR_RIGHT,
    SELECT, DELETE
};

Event getEvent(int key) {
    switch (key) {
        case TerminalFace::KEY_F1: return QUIT;

        case TerminalFace::KEY_ARROW_UP: return CURSOR_UP;
        case TerminalFace::KEY_ARROW_DOWN: return CURSOR_DOWN;
        case TerminalFace::KEY_ARROW_LEFT: return CURSOR_LEFT;
        case TerminalFace::KEY_ARROW_RIGHT: return CURSOR_RIGHT;

        case ' ': return SELECT;
        case TerminalFace::KEY_DELETE: return DELETE;
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
    int trackY = state.cursor.getY();

    // Check if cursor is on existing tracks
    if (trackY >= 5 && trackY < 5 + state.playlist.size()) {
        int trackIndex = trackY - 5;
        state.playlist[trackIndex].on = !state.playlist[trackIndex].on;
    }
    else if (trackY == 5 + state.playlist.size()) {
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
    }
}

int main(int argc, char* argv[]) {
    TerminalFace terminalFace{};
    WaveGenerator waveGenerator{};

    AppState state{};
    state.playlist.push_back(Track{});
    state.playlist.push_back(Track{});
    state.cursor.moveTo(15, 5);

    Event key;

    do {
        std::cout << ANSI::CLEAR_SCREEN;
        std::cout << "\033[H";
        terminalFace.printTop();
        terminalFace.printPlaylist(state.playlist);

        state.cursor.show();

        std::cout << std::flush;

        key = getEvent(terminalFace.readKey());
        eventHandler(key, state);

    } while (key != QUIT);

    terminalFace.restoreTerminal();
}