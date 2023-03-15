//
// Created by Mirco on 15/03/2023.
//

#include "Track.h"

Track::Track(unsigned int channels) {
    if (channels < 1)
        throw std::exception();

    this->channels = channels;
}

Track::~Track() {
    delete[] track;
}

void Track::append(Waveform &wf) {

}
