#pragma once

#include <memory>
#include <vector>

#include "Track.h"
#include "ClipDialog.h"
#include "Cursor.h"
#include "FileDialog.h"
#include "WaveGenerator.h"
#include "PlaylistRenderer.h"

class AppState {
public:
    Cursor cursor;
    std::vector<Track> playlist;
    bool isPlaying = false;
    std::unique_ptr<ClipDialog> clipDialog;
    std::unique_ptr<FileDialog> fileDialog;
    int selectedTrackForClip = -1;

    void createClipFromDialog(WaveGenerator waveGenerator);
    void handleFileDialog();
    void deleteHandler();
    void selectHandler();
    void handleFileDialogResult();
};