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
#include "include/AppState.h"

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
                    state.handleFileDialogResult();
                }
                return;
            case EventSystem::CANCEL:
                state.fileDialog->cancel();
                state.handleFileDialogResult();
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
                state.createClipFromDialog(waveGenerator);
                return;
            case EventSystem::CANCEL:
                state.clipDialog->cancel();
                state.createClipFromDialog(waveGenerator);
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

        case EventSystem::SELECT: state.selectHandler(); break;
        case EventSystem::DELETE: state.deleteHandler(); break;

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