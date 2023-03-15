//
// Created by Mirco on 03/02/2023.
//

// TODO: throw exceptions when channel is invalid

#include "WaveFile.h"
#include <cmath>
#include <iostream>

//TODO-DEBUG
#ifndef M_PI
#define M_PI 3.14
#endif

WaveFile::WaveFile(uint16_t numChannels, uint32_t sampleRate) {
    this->header = {
            {'R', 'I', 'F', 'F'},
            0,
            {'W', 'A', 'V', 'E'},
            {'f', 'm', 't', ' '},
            16,
            1,
            numChannels,
            sampleRate,
            sampleRate * numChannels * 2,
            ((uint16_t) (numChannels * 2)),
            16,
            {'d', 'a', 't', 'a'},
            0
    };

    samples = vector<vector<short>>();
    for (int i = 0; i < numChannels; ++i) {
        samples.push_back(vector<short>());
    }
}

// TODO: make transition from audio to silence (so that pop doesn't happen)
void WaveFile::addPause(float durationSeconds, int channel) {
    if (channel > this->header.numChannels)
        return;

    int samplesNum = (int) ((float)this->header.sampleRate * durationSeconds);

    for (int i = 0; i < samplesNum; i++) {
        this->samples.at(channel - 1).push_back(0);
    }

    std::cout << "Added pause" << std::endl;
    std::cout << "\tChannel: " << channel << std::endl;
    std::cout << "\tDuration: " << durationSeconds << " seconds" << std::endl;
}

void WaveFile::addSinWave(float freqHz, float durationSeconds, int channel, int amp) {
    if (channel > this->header.numChannels)
        return;

    int samplesNum = (int) ((float)this->header.sampleRate * durationSeconds);

    for (int i = 0; i < samplesNum; i++)
    {
        short sample = amp * sin(getPhaseFromCounter(i, freqHz));

        this->samples.at(channel - 1).push_back(sample);
    }

    std::cout << "Added sin wave" << std::endl;
    std::cout << "\tChannel: " << channel << std::endl;
    std::cout << "\tFrequency: " << freqHz << std::endl;
    std::cout << "\tSamples number: " << samplesNum << std::endl;
    std::cout << "\tDuration: " << durationSeconds << " seconds" << std::endl;
}

void WaveFile::addSquareWave(float freqHz, float durationSeconds, int channel, int amp) {
    if (channel > this->header.numChannels)
        return;

    int samplesNum = (int) ((float)this->header.sampleRate * durationSeconds);

    for (int i = 0; i < samplesNum; i++)
    {
        short sample = amp * (sin(getPhaseFromCounter(i, freqHz)) > 0 ? 1 : -1);
        this->samples.at(channel - 1).push_back(sample);
    }

    std::cout << "Added square wave" << std::endl;
    std::cout << "\tChannel: " << channel << std::endl;
    std::cout << "\tFrequency: " << freqHz << std::endl;
    std::cout << "\tSamples number: " << samplesNum << std::endl;
    std::cout << "\tDuration seconds: " << durationSeconds << std::endl;
}

// TODO: implement
void WaveFile::addSawtoothWave(float freqHz, float durationSeconds,int channel, int amp) {
    if (channel > this->header.numChannels)
        return;

    int samplesNum = (int) ((float)this->header.sampleRate * durationSeconds);

    for (int i = 0; i < samplesNum; i++)
    {
        short sample = amp * (2 * abs(2 * (i * freqHz / header.sampleRate) - floor(2 * (i * freqHz / header.sampleRate))) - 1);
        this->samples.at(channel - 1).push_back(sample);
    }
}

// TODO: implement
void WaveFile::addTriangleWave(float freqHz, float durationSeconds, int channel, int amp) {
    if (channel > this->header.numChannels)
        return;

    int samplesNum = (int) ((float)this->header.sampleRate * durationSeconds);

    for (int i = 0; i < samplesNum; i++)
    {
        double cutPhase = getPhaseFromCounter(i, freqHz) / M_PI;

        short sample = amp * (2 * fabs(2 * (cutPhase - round(cutPhase))) - 1);
        this->samples.at(channel - 1).push_back(sample);
    }
}

void WaveFile::adjustChannelsSizes() {
    std::cout << "Adjusting channel sizes" << std::endl;

    size_t maxSize = this->samples.at(0).size();
    int maxChannel = 1;

    for (int i = 0; i < this->samples.size(); ++i) {
        size_t size = this->samples.at(i).size();
        if (size > maxSize) {
            maxSize = size;
            maxChannel = i + 1;
        }
    }

    std::cout << "\tLargest channel: " << maxChannel << " - size: " << maxSize << std::endl;

    int logged = 0;
    for (int i = 0; i < this->samples.size(); ++i) {
        while (this->samples.at(i).size() < maxSize) {
            if (logged != i) {
                std::cout << "\tChannel " << i << "'s size: " << this->samples.at(i).size() << std::endl;
                logged = i;
            }

            this->samples.at(i).push_back(0);
        }
    }

    for (int i = 0; i < this->samples.size(); ++i) {
        std::cout << "\t\tChannel " << i << " size: " << this->samples.at(i).size() << std::endl;
    }
}


// TODO: Make multi-channel
void WaveFile::save(string fpath) {
    std::cout << "Saving wave file" << std::endl;

    adjustChannelsSizes();

    std::cout << "Adjusting header" << std::endl;

    header.subChunk2Size = this->samples.at(0).size() * header.numChannels * (header.bitsPerSample / 8);
    header.chunkSize = 36 + header.subChunk2Size;
    header.byteRate = header.sampleRate * header.numChannels * (header.bitsPerSample / 8);

    std::cout << "Writing header" << std::endl;

    ofstream file(fpath, std::ios::binary | std::ios::out);
    file.write((char*)&header, sizeof(header));

    std::cout << "Writing data" << std::endl;

    for (int i = 0; i < this->samples.at(0).size(); ++i) {
        for (auto & ch : this->samples) {
            short sample = ch.at(i);
            writeLittleEndian(file, sample);
        }
    }

    file.close();

    std::cout << "File saved at position: " << fpath << std::endl;
}

double WaveFile::getPhaseFromCounter(int counter, float frequency) {
    return 2 * M_PI * counter * frequency / header.sampleRate;
}

float WaveFile::getDurationSeconds() {
    return this->samples.at(0).size() / header.sampleRate;
}

float WaveFile::getTotalSamplesNumber(int channel) {
    return this->samples.at(channel - 1).size();
}

void WaveFile::writeLittleEndian(ofstream &file, uint16_t sample) {
    char data[2];
    data[0] = sample & 0xff;
    data[1] = (sample >> 8) & 0xff;
    file.write(data, sizeof(data));
}

void WaveFile::writeFile(_Waveform wf, string fpath) {
    // Mono
    _WavHeader header = {
            {'R', 'I', 'F', 'F'},
            0,
            {'W', 'A', 'V', 'E'},
            {'f', 'm', 't', ' '},
            16,
            1,
            1,
            static_cast<uint32_t>(wf.getSampleRate()),
            static_cast<uint32_t>(wf.getSampleRate() * 2),
            ((uint16_t) (2)),
            16,
            {'d', 'a', 't', 'a'},
            0
    };

    header.subChunk2Size = (wf.getSampleRate() * wf.getDuration()) * header.numChannels * (header.bitsPerSample / 8);
    header.chunkSize = 36 + header.subChunk2Size;
    header.byteRate = header.sampleRate * header.numChannels * (header.bitsPerSample / 8);

    std::cout << "Writing header" << std::endl;

    ofstream file(fpath, std::ios::binary | std::ios::out);
    file.write((char*)&header, sizeof(header));

    std::cout << "Calculating max to get amplitude" << std::endl;
    float max = 0;

    for (int i = 0; i < (wf.getSampleRate() * wf.getDuration()); i ++) {
        if (wf.getWave()[i] > max) {
            max = wf.getWave()[i];
        }
    }
    std::cout << "Max: " << max << std::endl;

    max *= INT16_MAX * 0.1;

    std::cout << "Amp multiplier: " << max << std::endl;

    std::cout << "Writing data" << std::endl;

    for (int i = 0; i < (wf.getSampleRate() * wf.getDuration()); i ++) {
        auto sample = (short) (wf.getWave()[i] * max);
        writeLittleEndian(file, sample);
    }

    file.close();

    std::cout << "File saved at position: " << fpath << std::endl;
}
