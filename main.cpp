#include <vector>
#include <memory>

#include "include/TerminalSettings.h"
#include "include/Clip.h"
#include "include/Track.h"
#include "include/Cursor.h"
#include "include/AnsiFormat.h"
#include "include/WaveGenerator.h"
#include "include/Display.h"
#include "include/ClipDialog.h"
#include "include/FileDialog.h"
#include "include/PlaylistRenderer.h"

struct AppState {
    Cursor cursor;
    std::vector<Track> playlist;
    bool isPlaying = false;
    std::unique_ptr<ClipDialog> clipDialog;
    std::unique_ptr<FileDialog> fileDialog;
    int selectedTrackForClip = -1;
};

enum Event {
    QUIT,
    CURSOR_UP, CURSOR_DOWN, CURSOR_LEFT, CURSOR_RIGHT,
    SELECT, DELETE,
    PLAY, PAUSE,
    CREATE_CLIP, FILE_MENU, CONFIRM, CANCEL,
    TAB, BACKSPACE,
    CHAR_INPUT
};

struct EventWithChar {
    Event event;
    char character;
};

EventWithChar getEvent(int key) {
    EventWithChar result;
    result.character = 0;

    switch (key) {
        case TerminalSettings::KEY_F1: result.event = QUIT; break;
        case TerminalSettings::KEY_F2: result.event = FILE_MENU; break;

        case TerminalSettings::KEY_ARROW_UP: result.event = CURSOR_UP; break;
        case TerminalSettings::KEY_ARROW_DOWN: result.event = CURSOR_DOWN; break;
        case TerminalSettings::KEY_ARROW_LEFT: result.event = CURSOR_LEFT; break;
        case TerminalSettings::KEY_ARROW_RIGHT: result.event = CURSOR_RIGHT; break;
        case ' ': result.event = SELECT; break;
        case TerminalSettings::KEY_DELETE: result.event = DELETE; break;
        case 'c': case 'C': result.event = CREATE_CLIP; break;
        case '\r': case '\n': result.event = CONFIRM; break;
        case TerminalSettings::KEY_ESC: result.event = CANCEL; break;
        case '\t': result.event = TAB; break;
        case 127: case 8: result.event = BACKSPACE; break;
        default:
            if (key >= 32 && key <= 126) {
                result.event = CHAR_INPUT;
                result.character = static_cast<char>(key);
            } else {
                result.event = QUIT;
            }
            break;
    }

    return result;
}

void createClipFromDialog(AppState &state, WaveGenerator &waveGenerator) {
    if (state.selectedTrackForClip < 0 ||
        state.selectedTrackForClip >= state.playlist.size()) {
        return;
    }

    if (!state.clipDialog) {
        return;
    }

    auto params = state.clipDialog->getParams();

    if (!params.confirmed) {
        state.clipDialog.reset();
        state.selectedTrackForClip = -1;
        return;
    }

    Clip newClip(static_cast<int>(params.time));
    newClip.at = params.at;
    newClip.time = params.time;

    newClip.samples = waveGenerator.Generate(
        WaveGenerator::SINE,
        newClip.time,
        params.frequency
    );

    state.playlist[state.selectedTrackForClip].track.push_back(std::move(newClip));

    state.clipDialog.reset();
    state.selectedTrackForClip = -1;
}

void handleFileDialogResult(AppState &state) {
    if (!state.fileDialog) {
        return;
    }

    auto result = state.fileDialog->getResult();

    if (!result.confirmed) {
        state.fileDialog.reset();
        return;
    }

    if (result.option == FileDialog::RENDER) {
        PlaylistRenderer renderer(44100);
        renderer.renderToFile(state.playlist, result.path);
    }

    state.fileDialog.reset();
}

void deleteHandler(AppState &state) {
    int trackY = state.cursor.getY();

    if (trackY >= 6 && trackY < 6 + state.playlist.size()) {
        int trackIndex = trackY - 6;
        state.playlist.erase(state.playlist.begin() + trackIndex);

        if (state.cursor.getY() >= 6 + state.playlist.size() && state.playlist.size() > 0) {
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
    else if (cursorY >= 6 && cursorY < 6 + state.playlist.size()) {
        int trackIndex = cursorY - 6;

        if (cursorX >= 14) {  // In the timeline area
            state.clipDialog = std::make_unique<ClipDialog>();
            state.selectedTrackForClip = trackIndex;
        } else {  // On the mute/solo button
            state.playlist[trackIndex].on = !state.playlist[trackIndex].on;
        }
    }
    else if (cursorY == 6 + state.playlist.size() + 1) {
        state.playlist.push_back(Track{});
    }
}

void eventHandler(EventWithChar eventData, AppState &state, WaveGenerator &waveGenerator) {
    Event event = eventData.event;

    if (state.fileDialog && !state.fileDialog->isComplete()) {
        switch (event) {
            case CURSOR_UP:
                state.fileDialog->moveUp();
                return;
            case CURSOR_DOWN:
                state.fileDialog->moveDown();
                return;
            case BACKSPACE:
                state.fileDialog->handleBackspace();
                return;
            case CONFIRM:
                state.fileDialog->confirm();
                if (state.fileDialog->isComplete()) {
                    handleFileDialogResult(state);
                }
                return;
            case CANCEL:
                state.fileDialog->cancel();
                handleFileDialogResult(state);
                return;
            case CHAR_INPUT:
                state.fileDialog->handleInput(eventData.character);
                return;
            default:
                return;
        }
    }

    if (state.clipDialog && !state.clipDialog->isComplete()) {
        switch (event) {
            case TAB:
                state.clipDialog->nextField();
                return;
            case BACKSPACE:
                state.clipDialog->handleBackspace();
                return;
            case CONFIRM:
                state.clipDialog->confirm();
                createClipFromDialog(state, waveGenerator);
                return;
            case CANCEL:
                state.clipDialog->cancel();
                createClipFromDialog(state, waveGenerator);
                return;
            case CHAR_INPUT:
                state.clipDialog->handleInput(eventData.character);
                return;
            default:
                return;
        }
    }

    switch (event) {
        case CURSOR_UP: state.cursor.moveUp(); break;
        case CURSOR_DOWN: state.cursor.moveDown(); break;
        case CURSOR_LEFT: state.cursor.moveLeft(); break;
        case CURSOR_RIGHT: state.cursor.moveRight(); break;

        case SELECT: selectHandler(state); break;
        case DELETE: deleteHandler(state); break;

        case PLAY: state.isPlaying = true; break;
        case PAUSE: state.isPlaying = false; break;

        case FILE_MENU:
            state.fileDialog = std::make_unique<FileDialog>();
            break;

        case CREATE_CLIP:
            if (state.cursor.getY() >= 6 &&
                state.cursor.getY() < 6 + state.playlist.size()) {
                state.clipDialog = std::make_unique<ClipDialog>();
                state.selectedTrackForClip = state.cursor.getY() - 6;
            }
            break;
        default:
            break;
    }
}

int main(int argc, char* argv[]) {
    TerminalSettings terminalSettings{};
    Display display;
    WaveGenerator waveGenerator{};
    AppState appState{};
    EventWithChar key;

    appState.playlist.push_back(Track{});
    appState.playlist.push_back(Track{});

    appState.cursor.moveTo(15, 6);

    do {
        std::cout << ANSI::CLEAR_SCREEN;
        std::cout << "\033[H";
        display.printTop(terminalSettings.terminalWidth());
        display.printPlaylist(appState.playlist, terminalSettings.terminalWidth());

        if (appState.fileDialog && !appState.fileDialog->isComplete()) {
            appState.fileDialog->render(terminalSettings.terminalWidth());
        } else if (appState.clipDialog && !appState.clipDialog->isComplete()) {
            appState.clipDialog->render(terminalSettings.terminalWidth());
        } else {
            appState.cursor.show();
        }

        std::cout << std::flush;

        key = getEvent(terminalSettings.readKey());
        eventHandler(key, appState, waveGenerator);

    } while (key.event != QUIT);

    terminalSettings.restoreTerminal();
}