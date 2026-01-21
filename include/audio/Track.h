#pragma once

#include <vector>

#include "Clip.h"

/**
 * @class Track
 * @brief Represents a single audio track in the playlist.
 *
 * A Track contains multiple audio clips and can be muted/unmuted.
 * Tracks are displayed in the terminal UI with visual indicators
 * showing their state and timeline.
 */
class Track {
public:
    /** @brief Container holding all clips on this track */
    std::vector<Clip> track;

    /** @brief Track enable state (true = unmuted, false = muted) */
    bool on = true;

    /** @brief Default constructor */
    Track() = default;

    /** @brief Copy constructor disabled to prevent accidental copies */
    Track(const Track&) = delete;

    /** @brief Copy assignment disabled to prevent accidental copies */
    Track& operator=(const Track&) = delete;

    /** @brief Move constructor for efficient track transfers */
    Track(Track&&) = default;

    /** @brief Move assignment for efficient track transfers */
    Track& operator=(Track&&) = default;
};