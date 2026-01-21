#pragma once

#include <vector>

#include "TerminalSettings.h"
#include "Track.h"
#include "AnsiFormat.h"

/**
 * @class Display
 * @brief Handles rendering of the terminal UI.
 *
 * Renders the header bar, control buttons, and playlist visualization
 * using box-drawing characters: ─ │ ├ ┤ ┬ ┴ ┼ ╭ ╮ ╰ ╯ ◉
 */
class Display {
public:
    /**
     * @brief Render the top header bar with title and controls
     * @param termWidth Current terminal width in columns
     *
     * Displays:
     * - Application title "Kore v0.1"
     * - Play/Pause controls
     * - Function key shortcuts (F1: Quit, F2: File)
     */
    void printTop(const int termWidth);

    /**
     * @brief Render the playlist with all tracks and clips
     * @param playlist Vector of tracks to display
     * @param termWidth Current terminal width in columns
     *
     * Features:
     * - Track numbers and mute indicators (◉)
     * - Visual timeline with clips shown as /--\
     * - Timescale of 2.0s per character
     * - Auto-scales to terminal width
     */
    void printPlaylist(const std::vector<Track>& playlist, const int termWidth);
};