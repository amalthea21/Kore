#pragma once

#include <memory>
#include <vector>

#include "Track.h"
#include "ClipDialog.h"
#include "Cursor.h"
#include "FileDialog.h"
#include "WaveGenerator.h"
#include "PlaylistRenderer.h"

/**
 * @class AppState
 * @brief Central application state container and controller.
 *
 * The AppState class serves as the main data repository for the application,
 * managing the current playlist, UI dialogs, playback state, and user selections.
 * It coordinates between UI components, audio generation, and file operations.
 */
class AppState {
public:
    /** @brief Current cursor position for navigation and selection */
    Cursor cursor;

    /** @brief Collection of audio tracks in the current playlist */
    std::vector<Track> playlist;

    /** @brief Current playback state (true if audio is playing) */
    bool isPlaying = false;

    /** @brief Dialog for creating and editing audio clips */
    std::unique_ptr<ClipDialog> clipDialog;

    /** @brief Dialog for file operations (open/save) */
    std::unique_ptr<FileDialog> fileDialog;

    /** @brief Index of the track selected for clip operations (-1 if none) */
    int selectedTrackForClip = -1;

    /**
     * @brief Creates a new audio clip from dialog data
     * @param waveGenerator Wave generator instance for creating audio content
     *
     * Processes the current clipDialog state to generate and add a new clip
     * to the selected track using the provided wave generator.
     */
    void createClipFromDialog(WaveGenerator waveGenerator);

    /**
     * @brief Initiates and manages the file dialog process
     *
     * Opens the file dialog for user file selection and handles the
     * subsequent file loading or saving operations.
     */
    void handleFileDialog();

    /**
     * @brief Handles deletion of selected items
     *
     * Processes DELETE events to remove selected clips or tracks
     * from the playlist based on current cursor position.
     */
    void deleteHandler();

    /**
     * @brief Handles selection of tracks or clips
     *
     * Processes SELECT events to choose tracks for editing,
     * clip creation, or other operations.
     */
    void selectHandler();

    /**
     * @brief Processes the result of file dialog operations
     *
     * Called after file dialog completion to handle the selected
     * file(s) and update application state accordingly.
     */
    void handleFileDialogResult();
};