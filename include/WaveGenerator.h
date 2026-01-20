#pragma once

class WaveGenerator {
public:
    enum Type { SINE, SQUARE, TRIANGLE };

    float* Generate(Type type, float time, float frequency);
};