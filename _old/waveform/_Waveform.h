//
// Created by Mirco on 15/03/2023.
//

#ifndef AUDIOGENERATION__WAVEFORM_H
#define AUDIOGENERATION__WAVEFORM_H

const int WAVEFORM_UNKNOWN = -2;
const int WAVEFORM_MIXED = -1;
const int WAVEFORM_SIN = 0;
const int WAVEFORM_SQUARE = 1;
const int WAVEFORM_SAWTOOTH = 2;
const int WAVEFORM_TRIANGLE = 3;

class _Waveform {
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
    _Waveform(int sampleRate, int duration, float freq, int form);
    _Waveform(float *wave, int sampleRate, float freq, int duration);
    _Waveform(float **waves, int wavesNum, int sampleRate, int duration);
    _Waveform(_Waveform &other);
    ~_Waveform();

    [[nodiscard]] float *getWave() const;

    [[nodiscard]] int getSampleRate() const;

    [[nodiscard]] float getFreq() const;

    [[nodiscard]] int getDuration() const;

    [[nodiscard]] int getForm() const;
};


#endif //AUDIOGENERATION__WAVEFORM_H
