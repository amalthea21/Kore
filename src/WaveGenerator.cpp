#include <math.h>

#include "../include/WaveGenerator.h"

float* WaveGenerator::Generate(Type type, float time, float frequency) {
    const int SAMPLE_RATE = 44100;
    int numSamples = static_cast<int>(SAMPLE_RATE * time);
    float* samples = new float[numSamples];

    for (int i = 0; i < numSamples; i++) {
        float t = static_cast<float>(i) / SAMPLE_RATE;
        float phase = 2.0f * M_PI * frequency * t;

        switch (type) {
            case Type::SINE:
                samples[i] = std::sin(phase);
                break;

            case Type::SQUARE:
                samples[i] = std::sin(phase) >= 0.0f ? 1.0f : -1.0f;
                break;

            case Type::TRIANGLE:
                float normalizedPhase = std::fmod(phase / (2.0f * M_PI), 1.0f);
                if (normalizedPhase < 0.5f) {
                    samples[i] = 4.0f * normalizedPhase - 1.0f;
                } else {
                    samples[i] = 3.0f - 4.0f * normalizedPhase;
                }
                break;
        }
    }

    return samples;
}