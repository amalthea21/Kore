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
#include "include/EventSystem.h"

struct AppState {
    Cursor cursor;
    std::vector<Track> playlist;
    bool isPlaying = false;
    std::unique_ptr<ClipDialog> clipDialog;
    std::unique_ptr<FileDialog> fileDialog;
    int selectedTrackForClip = -1;
};

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

void eventHandler(EventSystem::EventWithChar eventData, AppState &state, WaveGenerator &waveGenerator) {
    auto event = eventData.event;

    if (state.fileDialog && !state.fileDialog->isComplete()) {
        switch (event) {
            case EventSystem::CURSOR_UP:
                state.fileDialog->moveUp();
                return;
            case EventSystem::CURSOR_DOWN:
                state.fileDialog->moveDown();
                return;
            case EventSystem::BACKSPACE:
                state.fileDialog->handleBackspace();
                return;
            case EventSystem::CONFIRM:
                state.fileDialog->confirm();
                if (state.fileDialog->isComplete()) {
                    handleFileDialogResult(state);
                }
                return;
            case EventSystem::CANCEL:
                state.fileDialog->cancel();
                handleFileDialogResult(state);
                return;
            case EventSystem::CHAR_INPUT:
                state.fileDialog->handleInput(eventData.character);
                return;
            default:
                return;
        }
    }

    if (state.clipDialog && !state.clipDialog->isComplete()) {
        switch (event) {
            case EventSystem::TAB:
                state.clipDialog->nextField();
                return;
            case EventSystem::BACKSPACE:
                state.clipDialog->handleBackspace();
                return;
            case EventSystem::CONFIRM:
                state.clipDialog->confirm();
                createClipFromDialog(state, waveGenerator);
                return;
            case EventSystem::CANCEL:
                state.clipDialog->cancel();
                createClipFromDialog(state, waveGenerator);
                return;
            case EventSystem::CHAR_INPUT:
                state.clipDialog->handleInput(eventData.character);
                return;
            default:
                return;
        }
    }

    switch (event) {
        case EventSystem::CURSOR_UP: state.cursor.moveUp(); break;
        case EventSystem::CURSOR_DOWN: state.cursor.moveDown(); break;
        case EventSystem::CURSOR_LEFT: state.cursor.moveLeft(); break;
        case EventSystem::CURSOR_RIGHT: state.cursor.moveRight(); break;

        case EventSystem::SELECT: selectHandler(state); break;
        case EventSystem::DELETE: deleteHandler(state); break;

        case EventSystem::PLAY: state.isPlaying = true; break;
        case EventSystem::PAUSE: state.isPlaying = false; break;

        case EventSystem::FILE_MENU:
            state.fileDialog = std::make_unique<FileDialog>();
            break;

        case EventSystem::CREATE_CLIP:
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
    EventSystem eventSystem{};
    EventSystem::EventWithChar key;

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

        key = eventSystem.getEvent(terminalSettings.readKey());

        eventHandler(key, appState, waveGenerator);

    } while (key.event != EventSystem::QUIT);

    terminalSettings.restoreTerminal();
}