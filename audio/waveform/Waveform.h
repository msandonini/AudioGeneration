//
// Created by Mirco on 15/03/2023.
//

#ifndef AUDIOGENERATION_WAVEFORM_H
#define AUDIOGENERATION_WAVEFORM_H

const int WAVEFORM_UNKNOWN = -2;
const int WAVEFORM_MIXED = -1;
const int WAVEFORM_SIN = 0;
const int WAVEFORM_SQUARE = 1;
const int WAVEFORM_SAWTOOTH = 2;
const int WAVEFORM_TRIANGLE = 3;

class Waveform {
private:
    float *wave = nullptr;

    int sampleRate;
    float freq;
    int duration;

    int form;
protected:
    void generateSinWave();
    void generateSquareWave();
    void generateSawtoothWave();
    void generateTriangleWave();
public:
    Waveform(int sampleRate, int duration, float freq, int form);
    Waveform(float *wave, int sampleRate, float freq, int duration);
    Waveform(float **waves, int wavesNum, int sampleRate, int duration);
    Waveform(Waveform &other);
    ~Waveform();

    [[nodiscard]] float *getWave() const;

    [[nodiscard]] int getSampleRate() const;

    [[nodiscard]] float getFreq() const;

    [[nodiscard]] int getDuration() const;

    [[nodiscard]] int getForm() const;
};


#endif //AUDIOGENERATION_WAVEFORM_H
