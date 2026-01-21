#include "../../include/audio/Clip.h"

Clip::Clip(int t) : time(t), samples(new float[t * 44100]) {

}

Clip::~Clip() {
    delete[] samples;
}

Clip::Clip(Clip&& other) noexcept
    : time(other.time), samples(other.samples) {
    other.samples = nullptr;  // Prevent double-delete
}

Clip& Clip::operator=(Clip&& other) noexcept {
    if (this != &other) {
        delete[] samples;
        time = other.time;
        samples = other.samples;
        other.samples = nullptr;
    }
    return *this;
}