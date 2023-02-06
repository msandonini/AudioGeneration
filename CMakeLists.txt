cmake_minimum_required(VERSION 3.24)
project(AudioGeneration)

set(CMAKE_CXX_STANDARD 23)

add_executable(AudioGeneration
        main.cpp
        runtime/MusicNotesFrequencies.h runtime/wav/WaveFile.cpp)