//
// Created by Mirco on 15/03/2023.
//

#ifndef AUDIOGENERATION_TRACK_H
#define AUDIOGENERATION_TRACK_H

#include <vector>
#include "waveform/Waveform.h"

namespace Audio {

    class Track {
    private:
        std::vector<Waveform> *track;
        unsigned int channels;
        unsigned int sampleRate;

        double durationSeconds;
    protected:
    public:
        explicit Track(unsigned int channels = 1, unsigned int sampleRate = 44100);

        ~Track();

        void appendNote(float freq, float durationSeconds, int channel = 0);
        void appendChord(float *freqs, int freqsNum, float durationSeconds, int channel);
    };

}

#endif //AUDIOGENERATION_TRACK_H
