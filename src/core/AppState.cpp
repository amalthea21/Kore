#include "../../include/core/AppState.h"

void AppState::createClipFromDialog(WaveGenerator waveGenerator) {
    if (selectedTrackForClip < 0 ||
        selectedTrackForClip >= playlist.size()) {
        return;
        }

    if (!clipDialog) {
        return;
    }

    auto params = clipDialog->getParams();

    if (!params.confirmed) {
        clipDialog.reset();
        selectedTrackForClip = -1;
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

    playlist[selectedTrackForClip].track.push_back(std::move(newClip));

    clipDialog.reset();
    selectedTrackForClip = -1;
}


void AppState::handleFileDialog() {
    if (!fileDialog) {
        return;
    }

    auto result = fileDialog->getResult();

    if (!result.confirmed) {
        fileDialog.reset();
        return;
    }

    if (result.option == FileDialog::RENDER) {
        PlaylistRenderer renderer(44100);
        renderer.renderToFile(playlist, result.path);
    }

    fileDialog.reset();
}

void AppState::deleteHandler() {
    int trackY = cursor.getY();

    if (trackY >= 6 && trackY < 6 + playlist.size()) {
        int trackIndex = trackY - 6;
        playlist.erase(playlist.begin() + trackIndex);

        if (cursor.getY() >= 6 + playlist.size() && playlist.size() > 0) {
            cursor.moveUp();
        }
    }
}

void AppState::selectHandler() {
    int cursorX = cursor.getX();
    int cursorY = cursor.getY();

    if (cursorY == 2 && cursorX >= 3 && cursorX <= 5) { // Play
        isPlaying = true;
    }
    else if (cursorY == 2 && cursorX >= 7 && cursorX <= 9) { // Pause
        isPlaying = false;
    }
    else if (cursorY >= 6 && cursorY < 6 + playlist.size()) {
        int trackIndex = cursorY - 6;

        if (cursorX >= 14) {  // In the timeline area
            clipDialog = std::make_unique<ClipDialog>();
            selectedTrackForClip = trackIndex;
        } else {  // On the mute/solo button
            playlist[trackIndex].on = !playlist[trackIndex].on;
        }
    }
    else if (cursorY == 5 + playlist.size() + 1) {
        playlist.push_back(Track{});
    }
}

void AppState::handleFileDialogResult() {
    if (fileDialog) {
        return;
    }

    auto result = fileDialog->getResult();

    if (!result.confirmed) {
        fileDialog.reset();
        return;
    }

    if (result.option == FileDialog::RENDER) {
        PlaylistRenderer renderer(44100);
        renderer.renderToFile(playlist, result.path);
    }

    fileDialog.reset();
}