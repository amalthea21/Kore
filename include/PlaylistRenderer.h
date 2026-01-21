#pragma once

#include <vector>
#include <string>
#include "Track.h"

/**
 * @class PlaylistRenderer
 * @brief Renders multi-track playlists to WAV audio files.
 *
 * Mixes all enabled tracks together, placing clips at their
 * specified positions on the timeline. Automatically normalizes
 * output to prevent clipping when multiple tracks are combined.
 *
 * Process:
 * 1. Calculate total duration from all clips
 * 2. Mix clips from enabled tracks into single buffer
 * 3. Normalize to [-1.0, 1.0] range if necessary
 * 4. Write to WAV file
 */
class PlaylistRenderer {
public:
    /**
     * @brief Construct renderer with specified sample rate
     * @param sampleRate Sample rate in Hz (default: 44100)
     */
    PlaylistRenderer(int sampleRate = 44100);

    /**
     * @brief Render playlist to WAV file
     * @param playlist Vector of tracks to render
     * @param filename Output file path
     * @return True on success, false if playlist empty or no clips
     *
     * Only renders tracks with on=true. Muted tracks are skipped.
     * Output is automatically normalized if any samples exceed [-1.0, 1.0].
     */
    bool renderToFile(const std::vector<Track>& playlist, const std::string& filename);

private:
    int sampleRate; /**< Sample rate for output file */

    /**
     * @brief Calculate total samples needed for playlist
     * @param playlist Tracks to analyze
     * @return Number of samples (sample_rate * max_end_time)
     *
     * Finds the furthest clip end position (at + time) and
     * converts to sample count at current sample rate.
     */
    int calculateTotalSamples(const std::vector<Track>& playlist) const;

    /**
     * @brief Mix all tracks into output buffer with normalization
     * @param playlist Tracks to mix
     * @param output Output buffer (must be pre-allocated to correct size)
     *
     * Process:
     * 1. Zero output buffer
     * 2. For each enabled track:
     *    - Place each clip's samples at position (at * sample_rate)
     *    - Add samples to existing output (mixing)
     * 3. Find peak amplitude across all samples
     * 4. If peak > 1.0, normalize entire output by (1.0 / peak)
     */
    void mixTracks(const std::vector<Track>& playlist, std::vector<float>& output);
};