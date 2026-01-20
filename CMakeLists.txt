cmake_minimum_required(VERSION 3.31.6)
project(Kore)

set(CMAKE_CXX_STANDARD 26)

add_executable(Kore main.cpp
        src/TerminalFace.cpp
        include/TerminalFace.h
        src/Clip.cpp
        include/Clip.h
        include/AnsiFormat.h
        src/Track.cpp
        include/Track.h
        src/WaveGenerator.cpp
        include/WaveGenerator.h
)
