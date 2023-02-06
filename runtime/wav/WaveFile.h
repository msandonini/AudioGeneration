//
// Created by Mirco on 03/02/2023.
//

#ifndef AUDIOGENERATION_WAVEFILE_H
#define AUDIOGENERATION_WAVEFILE_H

#include <cstdint>
#include <fstream>
#include <vector>
#include <map>

// TODO: Remove standard namespace and apply custom one
using namespace std;

class WaveFile {
private:
    typedef struct {
        char chunkID[4];
        uint32_t chunkSize;
        char format[4];
        char subChunk1ID[4];
        uint32_t subChunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        char subChunk2ID[4];
        uint32_t subChunk2Size;
    } _WavHeader;

    // TODO: Convert to multi-channel;
    _WavHeader header;
    vector<vector<short>> samples;

    void writeLittleEndian(ofstream &file, uint16_t sample);
    double getPhaseFromCounter(int counter, float frequency);
/*
    void writeSinWave(float freqHz, int durationSeconds);
    void writeSquareWave(float freqHz, int durationSeconds);
    void writeSawToothWave(float freqHz, int durationSeconds);
    void writeTriangleWave(float freqHz, int durationSeconds);
*/
public:
    explicit WaveFile(uint16_t numChannels = 1, uint32_t sampleRate = 44100);

    void addPause(float durationSeconds, int channel = 1);
    void addSinWave(float freqHz, float durationSeconds, int channel = 1, int amp = INT16_MAX);
    void addSquareWave(float freqHz, float durationSeconds, int channel = 1, int amp = INT16_MAX);
    void addSawtoothWave(float freqHz, float durationSeconds, int channel = 1, int amp = INT16_MAX);
    void addTriangleWave(float freqHz, float durationSeconds, int channel = 1, int amp = INT16_MAX);

    void adjustChannelsSizes();

    void save(string fpath);

    float getDurationSeconds();
    float getTotalSamplesNumber(int channel = 1);
};

#endif //AUDIOGENERATION_WAVEFILE_H
