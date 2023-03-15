cmake_minimum_required(VERSION 3.24)
project(AudioGeneration)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(AudioGeneration
        main.cpp
        audio/MusicNotesFrequencies.h audio/ChordsFrequencies.h
        _old/wav/WaveFile.cpp _old/wav/WaveFile.h
        _old/waveform/_Waveform.cpp _old/waveform/_Waveform.h
        audio/Track.cpp audio/Track.h
        audio/waveform/Waveform.cpp audio/waveform/Waveform.h
        )