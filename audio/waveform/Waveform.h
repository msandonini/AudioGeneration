//
// Created by Mirco on 15/03/2023.
//

#ifndef AUDIOGENERATION_WAVEFORM_H
#define AUDIOGENERATION_WAVEFORM_H

#include <limits>

namespace Audio {

    class Waveform {
    private:
        int sampleRate;
        float durationSeconds;
        float amp;

        float *samples = nullptr;
    protected:
        void makeSin(float freq);
        void makeSquare(float freq);
        void makeSawtooth(float freq);
        void makeTriangular(float freq);
    public:
        Waveform(int sampleRate, float durationSeconds, float amp = std::numeric_limits<float>::max());
        ~Waveform();

        [[nodiscard]] int getSampleRate() const;

        [[nodiscard]] float getDurationSeconds() const;

        [[nodiscard]] int getSamplesNum() const;

        [[nodiscard]] float getAmp() const;

        [[nodiscard]] float *getSamples() const;
    };

} // Audio

#endif //AUDIOGENERATION_WAVEFORM_H
