#include "../include/Clip.h"

Clip::Clip(int t) : time(t), samples(new float[t * 44100]) {

}

Clip::~Clip() {
    delete[] samples;
}