cmake_minimum_required(VERSION 3.24)
project(AudioGeneration)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(AudioGeneration
        main.cpp
        audio/MusicNotesFrequencies.h audio/wav/WaveFile.cpp
        audio/waveform/Waveform.cpp audio/waveform/Waveform.h audio/Track.cpp audio/Track.h)