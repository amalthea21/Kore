cmake_minimum_required(VERSION 3.31.6)
project(Kore)

set(CMAKE_CXX_STANDARD 26)

add_executable(Kore main.cpp
        include/AnsiFormat.h

        include/Clip.h
        src/Clip.cpp

        include/Cursor.h
        src/Cursor.cpp

        include/TerminalSettings.h
        src/TerminalSettings.cpp

        include/Track.h
        src/Track.cpp

        include/WaveGenerator.h
        src/WaveGenerator.cpp

        src/Display.cpp
        include/Display.h

        include/ClipDialog.h
        src/ClipDialog.cpp

        src/WavWriter.cpp
        include/WavWriter.h

        include/PlaylistRenderer.h
        src/PlaylistRenderer.cpp

        include/FileDialog.h
        src/FileDialog.cpp

        src/EventSystem.cpp
        include/EventSystem.h
        src/AppState.cpp
        include/AppState.h
)
