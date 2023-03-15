//
// Created by Mirco on 15/03/2023.
//

#include "_Waveform.h"

#include <iostream>
#include <cmath>

//TODO-DEBUG
#ifndef M_PI
#define M_PI 3.14
#endif


_Waveform::_Waveform(int sampleRate, int duration, float freq, int form) {
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


_Waveform::_Waveform(float *wave, int sampleRate, float freq, int duration) {
    this->sampleRate = sampleRate;
    this->freq = freq;
    this->duration = duration;

    this->form = WAVEFORM_UNKNOWN;

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

_Waveform::_Waveform(float **waves, int wavesNum, int sampleRate, int duration) {
    this->sampleRate = sampleRate;
    this->freq = -1;
    this->duration = duration;

    this->form = WAVEFORM_MIXED;

    int samplesNum = (int) (sampleRate * duration);

    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
    this->wave = new float[samplesNum];
    for (int i = 0; i < samplesNum; i ++) {
        this->wave[i] = 0;
    }

    float tot;
    for (int i = 0; i < samplesNum; ++i) {
        tot = 0;

        for (int j = 0; j < wavesNum; ++j) {
            tot += waves[j][i];
        }

        this->wave[i] = tot;
    }
}

_Waveform::_Waveform(_Waveform &other) {
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

_Waveform::~_Waveform() {
    if (this->wave != nullptr) {
        delete[] this->wave;
        this->wave = nullptr;
    }
}


float *_Waveform::getWave() const {
    return wave;
}

int _Waveform::getSampleRate() const {
    return sampleRate;
}


float _Waveform::getFreq() const {
    return freq;
}

int _Waveform::getDuration() const {
    return duration;
}

int _Waveform::getForm() const {
    return form;
}

void _Waveform::generateSinWave() {
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
void _Waveform::generateSquareWave() {
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

void _Waveform::generateSawtoothWave() {
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

void _Waveform::generateTriangleWave() {
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
