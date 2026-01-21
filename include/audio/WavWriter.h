#pragma once

#include <string>
#include <fstream>
#include <vector>

/**
 * @class WavWriter
 * @brief Writes audio samples to WAV file format.
 *
 * Creates standard 16-bit PCM WAV files with configurable
 * sample rate and channel count. Handles header creation
 * and automatic finalization on destruction.
 *
 * Usage:
 * @code
 * WavWriter writer("output.wav", 44100, 1);
 * std::vector<float> samples = {0.1, 0.2, 0.3};
 * writer.write(samples);
 * writer.close(); // or let destructor handle it
 * @endcode
 */
class WavWriter {
public:
    /**
     * @brief Create WAV file writer
     * @param filename Output file path
     * @param sampleRate Sample rate in Hz (default: 44100)
     * @param numChannels Number of audio channels (default: 1 for mono)
     *
     * Opens file and writes initial WAV header with placeholder sizes.
     */
    WavWriter(const std::string& filename, int sampleRate = 44100, int numChannels = 1);

    /**
     * @brief Destructor ensures file is properly closed
     *
     * Automatically calls close() to update header if not already closed.
     */
    ~WavWriter();

    /**
     * @brief Write audio samples to file
     * @param samples Vector of float samples in range [-1.0, 1.0]
     * @return True on success, false if file not open
     *
     * Converts float samples to 16-bit signed integers.
     * Samples outside [-1.0, 1.0] are clamped.
     */
    bool write(const std::vector<float>& samples);

    /**
     * @brief Finalize and close WAV file
     *
     * Updates WAV header with final data size.
     * Safe to call multiple times (subsequent calls do nothing).
     */
    void close();

private:
    std::ofstream file;  /**< Output file stream */
    int sampleRate;      /**< Sample rate in Hz */
    int numChannels;     /**< Number of audio channels */
    int dataSize;        /**< Total bytes written to data chunk */

    /**
     * @brief Write initial WAV header with placeholder sizes
     */
    void writeHeader();

    /**
     * @brief Update header with final data size before closing
     */
    void updateHeader();

    /**
     * @brief Write integer in little-endian format
     * @param value Integer value to write
     * @param numBytes Number of bytes (1, 2, or 4)
     */
    void writeInt(int value, int numBytes);

    /**
     * @brief Write raw string bytes
     * @param str String to write
     */
    void writeString(const std::string& str);
};