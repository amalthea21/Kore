cmake_minimum_required(VERSION 3.31.6)
project(Kore)

set(CMAKE_CXX_STANDARD 26)

add_executable(Kore main.cpp
        include/ui/AnsiFormat.h

        include/audio/Clip.h
        src/audio/Clip.cpp

        include/core/Cursor.h
        src/core/Cursor.cpp

        include/util/TerminalSettings.h
        src/util/TerminalSettings.cpp

        include/audio/Track.h
        src/audio/Track.cpp

        include/audio/WaveGenerator.h
        src/audio/WaveGenerator.cpp

        src/ui/Display.cpp
        include/ui/Display.h

        include/ui/ClipDialog.h
        src/ui/ClipDialog.cpp

        src/audio/WavWriter.cpp
        include/audio/WavWriter.h

        include/audio/PlaylistRenderer.h
        src/audio/PlaylistRenderer.cpp

        include/ui/FileDialog.h
        src/ui/FileDialog.cpp

        src/core/EventSystem.cpp
        include/core/EventSystem.h
        src/core/AppState.cpp
        include/core/AppState.h
)
