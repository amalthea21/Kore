#pragma once

#include <string>
#include <fstream>
#include <vector>

class WavWriter {
public:
    WavWriter(const std::string& filename, int sampleRate = 44100, int numChannels = 1);
    ~WavWriter();
    
    bool write(const std::vector<float>& samples);
    void close();
    
private:
    std::ofstream file;
    int sampleRate;
    int numChannels;
    int dataSize;
    
    void writeHeader();
    void updateHeader();
    void writeInt(int value, int numBytes);
    void writeString(const std::string& str);
};