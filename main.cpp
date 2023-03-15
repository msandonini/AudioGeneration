#include <iostream>

#include "_old/wav/WaveFile.h"
#include "audio/MusicNotesFrequencies.h"

using namespace std;

int main() {
    string fpath = "../output/test.wav";

    /*
    cout << "Creating wave" << endl;

    WaveFile wave(3);

    cout << "Adding data to the wave" << endl;
    */

    /*// C
    wave.addSinWave(Audio::Tuning::f440hz::t4::C, 2, 1);
    wave.addSinWave(Audio::Tuning::f440hz::t4::E, 2, 2);
    wave.addSinWave(Audio::Tuning::f440hz::t4::G, 2, 3);
    //*/
    /*// C-
    wave.addSinWave(Audio::Tuning::f440hz::t4::C, 2, 1);
    wave.addSinWave(Audio::Tuning::f440hz::t4::Dsh, 2, 2);
    wave.addSinWave(Audio::Tuning::f440hz::t4::G, 2, 3);
    //*/

    /*
    int amp = INT16_MAX / 2;

    wave.addSinWave(Audio::Tuning::f440hz::t4::C, 2, 1, amp);
    wave.adjustChannelsSizes();

    wave.addSinWave(Audio::Tuning::f440hz::t4::E, 2, 2, amp);
    wave.adjustChannelsSizes();

    wave.addSinWave(Audio::Tuning::f440hz::t4::G, 2, 3, amp);
    wave.adjustChannelsSizes();

    wave.addSinWave(Audio::Tuning::f440hz::t4::C, 2, 1, amp);
    wave.addSinWave(Audio::Tuning::f440hz::t4::E, 2, 2, amp);
    wave.addSinWave(Audio::Tuning::f440hz::t4::G, 2, 3, amp);

    wave.addPause(1);

    cout << "Wave duration: " << to_string(wave.getDurationSeconds()) << " seconds" << endl;
    cout << "Total number of samples: " << wave.getTotalSamplesNumber() << std::endl;

    wave.save(fpath);
    */

    _Waveform waveform1(44100, 1, Audio::Tuning::f440hz::t4::C, WAVEFORM_SIN);
    _Waveform waveform2(44100, 1, Audio::Tuning::f440hz::t4::E, WAVEFORM_SIN);
    _Waveform waveform3(44100, 1, Audio::Tuning::f440hz::t4::G, WAVEFORM_SIN);

    auto **mat = new float*[3];
    mat[0] = waveform1.getWave();
    mat[1] = waveform2.getWave();
    mat[2] = waveform3.getWave();

    _Waveform waveform(mat, 3, 44100, 1);

    WaveFile::writeFile(waveform, fpath);

    return 0;
}