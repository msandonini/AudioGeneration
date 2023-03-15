//
// Created by Mirco on 15/03/2023.
//

#include "Waveform.h"

#include <iostream>
#include <cmath>

Waveform::Waveform(int sampleRate, int duration, float freq, int form) {
    this->sampleRate = sampleRate;
    this->duration = duration;
    this->freq = freq;
    this->form = form;

    switch (form) {
        case WAVEFORM_SIN:
            generateSinWave();
            break;
        case WAVEFORM_SQUARE:
            generateSquareWave();
            break;
        case WAVEFORM_TRIANGLE:
            generateTriangleWave();
            break;
        case WAVEFORM_SAWTOOTH:
            generateSawtoothWave();
            break;
        default:
            std::cerr << "Invalid wave form" << std::endl;
            break;
    }
}

Waveform::Waveform(const float *wave, int sampleRate, float freq, int duration) {
    this->sampleRate = sampleRate;
    this->freq = freq;
    this->duration = duration;

    int samplesNum = (int) (sampleRate * duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];

    for (int i = 0; i < samplesNum; ++i) {
        this->wave[i] = wave[i];
    }
}

Waveform::Waveform(const float **waves, int wavesNum, int sampleRate, float freq, int duration) {
    this->sampleRate = sampleRate;
    this->freq = freq;
    this->duration = duration;

    this->form = WAVEFORM_MIXED;

    int samplesNum = (int) (sampleRate * duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];

    for (int i = 0; i < samplesNum; ++i) {
        float tot = 0;

        for (int j = 0; j < wavesNum; ++j) {
            tot += waves[i][j];
        }

        this->wave[i] = tot;
    }
}

Waveform::Waveform(const Waveform &other) {
    this->sampleRate = other.sampleRate;
    this->freq = other.freq;
    this->duration = other.duration;

    this->form = other.form;

    int samplesNum = (int) (this->sampleRate * this->duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];

    for (int i = 0; i < samplesNum; ++i) {
        this->wave[i] = other.wave[i];
    }
}

Waveform::~Waveform() {
    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
}


float *Waveform::getWave() const {
    return wave;
}

int Waveform::getSampleRate() const {
    return sampleRate;
}


float Waveform::getFreq() const {
    return freq;
}

int Waveform::getDuration() const {
    return duration;
}

int Waveform::getForm() const {
    return form;
}

void Waveform::generateSinWave() {
    int samplesNum = (int) (this->sampleRate * this->duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];

    for (int i = 0; i < samplesNum; i++)
    {
        float time = (float) i / (float) this->sampleRate;
        this->wave[i] = sin(2 * M_PI * this->freq * time);
    }
}
void Waveform::generateSquareWave() {
    int samplesNum = (int) (this->sampleRate * this->duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];

    for (int i = 0; i < samplesNum; i++)
    {
        float time = (float) i / (float) this->sampleRate;
        this->wave[i] = (sin(2 * M_PI * this->freq * time) > 0 ? 1 : -1);
    }
}

void Waveform::generateSawtoothWave() {
    int samplesNum = (int) (this->sampleRate * this->duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];

    for (int i = 0; i < samplesNum; i++) {
        this->wave[i] = 2 * fabsf(2 * ((float) i * this->freq / (float) this->sampleRate) - floorf(2 * ((float) i * this->freq / (float) this->sampleRate))) - 1;
    }
}

void Waveform::generateTriangleWave() {
    int samplesNum = (int) (this->sampleRate * this->duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];

    for (int i = 0; i < samplesNum; i++) {
        float time = (float) i / (float) this->sampleRate;

        float cutPhase = 2 * time * this->freq / (float) this->sampleRate;

        this->wave[i] = 2 * fabsf(2 * (cutPhase - roundf(cutPhase))) - 1;
    }
}