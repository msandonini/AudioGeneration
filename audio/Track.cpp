//
// Created by Mirco on 15/03/2023.
//

#include "Track.h"

Audio::Track::Track(unsigned int channels, unsigned int sampleRate) {
    if (channels < 1)
        throw std::exception();

    track = new std::vector<Waveform>[channels];

    this->channels = channels;
    this->sampleRate = sampleRate;
}

Audio::Track::~Track() {
    delete[] track;
}

void Audio::Track::appendNote(float freq, float durationSeconds, int channel) {
    Waveform wf = *new Waveform(sampleRate, durationSeconds);
    this->durationSeconds += durationSeconds;
}

void Audio::Track::appendChord(float *freqs, int freqsNum, float durationSeconds, int channel) {

}
