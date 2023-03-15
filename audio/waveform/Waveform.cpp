//
// Created by Mirco on 15/03/2023.
//

#include "Waveform.h"
#include <cmath>

namespace Audio {
    void Waveform::makeSin(float freq) {
        int samplesNum = getSamplesNum();

        delete[] this->samples;
        this->samples = new float[samplesNum];

        for (int i = 0; i < samplesNum; i++)
        {
            float time = (float) i / (float) this->sampleRate;
            this->samples[i] = sinf((float)(2 * M_PI * freq * time));
        }
    }

    void Waveform::makeSquare(float freq) {
        int samplesNum = getSamplesNum();

        delete[] this->samples;
        this->samples = new float[samplesNum];

        for (int i = 0; i < samplesNum; i++)
        {
            float time = (float) i / (float) this->sampleRate;
            this->samples[i] = (float)(sinf((float)(2 * M_PI * freq * time)) > 0 ? 1 : -1) * amp;
        }
    }

    void Waveform::makeSawtooth(float freq) {
        int samplesNum = getSamplesNum();

        delete[] this->samples;
        this->samples = new float[samplesNum];

        for (int i = 0; i < samplesNum; i++) {
            this->samples[i] = 2 *
                    fabsf(2 * ((float) i * freq / (float) this->sampleRate) -
                    floorf(2 * ((float) i * freq / (float) this->sampleRate))) - 1;
        }
    }

    void Waveform::makeTriangular(float freq) {
        int samplesNum = getSamplesNum();

        delete[] this->samples;
        this->samples = new float[samplesNum];

        for (int i = 0; i < samplesNum; i++) {
            float time = (float) i / (float) this->sampleRate;

            float cutPhase = 2 * time * freq / (float) this->sampleRate;
            this->samples[i] = 2 * fabsf(2 * (cutPhase - roundf(cutPhase))) - 1;
        }
    }

    Waveform::Waveform(int sampleRate, float durationSeconds, float amp) {
        this->sampleRate = sampleRate;
        this->durationSeconds = durationSeconds;
        this->amp = amp;

        samples = new float[getSamplesNum()];
    }

    Waveform::~Waveform() {
        delete[] samples;
    }

    int Waveform::getSampleRate() const {
        return sampleRate;
    }

    float Waveform::getDurationSeconds() const {
        return durationSeconds;
    }

    float Waveform::getAmp() const {
        return amp;
    }

    float *Waveform::getSamples() const {
        return samples;
    }

    int Waveform::getSamplesNum() const {
        return (int)((float) sampleRate * durationSeconds);
    }
} // Audio