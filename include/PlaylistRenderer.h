#pragma once

#include <vector>
#include <string>
#include "Track.h"

class PlaylistRenderer {
public:
    PlaylistRenderer(int sampleRate = 44100);

    bool renderToFile(const std::vector<Track>& playlist, const std::string& filename);

private:
    int sampleRate;

    int calculateTotalSamples(const std::vector<Track>& playlist) const;
    void mixTracks(const std::vector<Track>& playlist, std::vector<float>& output);
};