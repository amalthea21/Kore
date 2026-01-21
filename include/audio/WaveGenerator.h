#pragma once

/**
 * @class WaveGenerator
 * @brief Generates synthesized waveforms at 44.1kHz sample rate.
 *
 * Supports sine, square, and triangle wave generation.
 * All waveforms are generated at the specified frequency and duration.
 */
class WaveGenerator {
public:
    /**
     * @enum Type
     * @brief Available waveform types for synthesis
     */
    enum Type {
        SINE,      /**< Smooth sinusoidal wave */
        SQUARE,    /**< Square wave (instant transitions) */
        TRIANGLE   /**< Linear triangular wave */
    };

    /**
     * @brief Generate a waveform with specified parameters
     * @param type Waveform shape (SINE, SQUARE, or TRIANGLE)
     * @param time Duration in seconds
     * @param frequency Frequency in Hz (e.g., 440.0 for A4)
     * @return Pointer to newly allocated sample array (caller must delete[])
     * @note Returns array of size (44100 * time) samples
     */
    float* Generate(Type type, float time, float frequency);
};