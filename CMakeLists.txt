cmake_minimum_required(VERSION 3.31.6)
project(Kore)

set(CMAKE_CXX_STANDARD 26)

add_executable(Kore main.cpp
        include/AnsiFormat.h

        include/Clip.h
        src/Clip.cpp

        include/Cursor.h
        src/Cursor.cpp

        include/TerminalFace.h
        src/TerminalFace.cpp

        include/Track.h
        src/Track.cpp

        include/WaveGenerator.h
        src/WaveGenerator.cpp
)
