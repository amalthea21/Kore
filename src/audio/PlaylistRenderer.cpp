#include "../../include/audio/PlaylistRenderer.h"
#include "../../include/audio/WavWriter.h"
#include <algorithm>
#include <cmath>

PlaylistRenderer::PlaylistRenderer(int sr) : sampleRate(sr) {}

int PlaylistRenderer::calculateTotalSamples(const std::vector<Track>& playlist) const {
    float maxEndTime = 0.0f;
    
    for (const auto& track : playlist) {
        for (const auto& clip : track.track) {
            float clipEndTime = clip.at + clip.time;
            maxEndTime = std::max(maxEndTime, clipEndTime);
        }
    }
    
    return static_cast<int>(maxEndTime * sampleRate);
}

void PlaylistRenderer::mixTracks(const std::vector<Track>& playlist, std::vector<float>& output) {
    std::fill(output.begin(), output.end(), 0.0f);

    for (const auto& track : playlist) {
        if (!track.on) continue;
        
        for (const auto& clip : track.track) {
            int startSample = static_cast<int>(clip.at * sampleRate);
            int numClipSamples = static_cast<int>(clip.time * sampleRate);

            for (int i = 0; i < numClipSamples; i++) {
                int outputIndex = startSample + i;

                if (outputIndex >= 0 && outputIndex < output.size()) {
                    output[outputIndex] += clip.samples[i];
                }
            }
        }
    }

    float maxAmplitude = 0.0f;
    for (float sample : output) {
        maxAmplitude = std::max(maxAmplitude, std::abs(sample));
    }
    
    if (maxAmplitude > 1.0f) {
        float normalizeFactor = 1.0f / maxAmplitude;
        for (float& sample : output) {
            sample *= normalizeFactor;
        }
    }
}

bool PlaylistRenderer::renderToFile(const std::vector<Track>& playlist, const std::string& filename) {
    if (playlist.empty()) {
        return false;
    }

    int totalSamples = calculateTotalSamples(playlist);
    if (totalSamples == 0) {
        return false;
    }

    std::vector<float> output(totalSamples);

    mixTracks(playlist, output);

    WavWriter writer(filename, sampleRate, 1);
    bool success = writer.write(output);
    writer.close();
    
    return success;
}