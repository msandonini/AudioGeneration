//
// Created by Mirco on 15/03/2023.
//

#ifndef AUDIOGENERATION_TRACK_H
#define AUDIOGENERATION_TRACK_H

#include <vector>
#include "waveform/Waveform.h"

class Track {
private:
    std::vector<Waveform> *track;
    unsigned int channels;
protected:
public:
    Track(unsigned int channels = 1);
    ~Track();

    void append(Waveform &wf);
};


#endif //AUDIOGENERATION_TRACK_H
