#pragma once

/**
 * @class Clip
 * @brief Represents a single audio clip containing waveform samples.
 *
 * A Clip stores audio data as an array of float samples at 44.1kHz.
 * Each clip has a position (at) and duration (time) on its track.
 * Memory is managed automatically through RAII and move semantics.
 */
class Clip {
public:
    /** @brief Position on timeline in seconds where clip starts */
    float at;

    /** @brief Duration of the clip in seconds */
    float time;

    /** @brief Raw audio samples at 44.1kHz sample rate */
    float* samples;

    /**
     * @brief Constructs a new clip with allocated sample buffer
     * @param t Duration in seconds (allocates t * 44100 samples)
     */
    Clip(int t);

    /**
     * @brief Destructor that frees sample memory
     */
    ~Clip();

    /** @brief Copy constructor disabled to prevent double-free */
    Clip(const Clip&) = delete;

    /** @brief Copy assignment disabled to prevent double-free */
    Clip& operator=(const Clip&) = delete;

    /**
     * @brief Move constructor for safe ownership transfer
     * @param other Clip to move from (left in valid but empty state)
     */
    Clip(Clip&& other) noexcept;

    /**
     * @brief Move assignment for safe ownership transfer
     * @param other Clip to move from (left in valid but empty state)
     * @return Reference to this clip
     */
    Clip& operator=(Clip&& other) noexcept;
};