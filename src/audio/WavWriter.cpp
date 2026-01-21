#include "../../include/audio/WavWriter.h"
#include <algorithm>
#include <cmath>

WavWriter::WavWriter(const std::string& filename, int sr, int nc)
    : sampleRate(sr), numChannels(nc), dataSize(0) {
    file.open(filename, std::ios::binary);
    if (file.is_open()) {
        writeHeader();
    }
}

WavWriter::~WavWriter() {
    close();
}

void WavWriter::writeString(const std::string& str) {
    file.write(str.c_str(), str.length());
}

void WavWriter::writeInt(int value, int numBytes) {
    for (int i = 0; i < numBytes; i++) {
        file.put(static_cast<char>(value & 0xFF));
        value >>= 8;
    }
}

void WavWriter::writeHeader() {
    writeString("RIFF");
    writeInt(0, 4);
    writeString("WAVE");

    writeString("fmt ");
    writeInt(16, 4);
    writeInt(1, 2);
    writeInt(numChannels, 2);
    writeInt(sampleRate, 4);
    writeInt(sampleRate * numChannels * 2, 4);
    writeInt(numChannels * 2, 2);
    writeInt(16, 2);

    writeString("data");
    writeInt(0, 4);
}

void WavWriter::updateHeader() {
    if (!file.is_open()) return;

    file.seekp(4);
    writeInt(36 + dataSize, 4);

    file.seekp(40);
    writeInt(dataSize, 4);
}

bool WavWriter::write(const std::vector<float>& samples) {
    if (!file.is_open()) return false;
    
    for (float sample : samples) {
        float clamped = std::max(-1.0f, std::min(1.0f, sample));

        short int16Sample = static_cast<short>(clamped * 32767.0f);

        file.put(static_cast<char>(int16Sample & 0xFF));
        file.put(static_cast<char>((int16Sample >> 8) & 0xFF));
        
        dataSize += 2;
    }
    
    return true;
}

void WavWriter::close() {
    if (file.is_open()) {
        updateHeader();
        file.close();
    }
}