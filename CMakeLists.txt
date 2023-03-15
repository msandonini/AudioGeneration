cmake_minimum_required(VERSION 3.24)
project(AudioGeneration)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(AudioGeneration
        main.cpp
        runtime/MusicNotesFrequencies.h runtime/wav/WaveFile.cpp
        runtime/waveform/Waveform.cpp runtime/waveform/Waveform.h)