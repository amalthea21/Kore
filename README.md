# **🎼 Kore** 

Kore is a lightweight, keyboard-driven DAW, running entirely in the terminal

<br>

## 📋 **Prerequisites**:

### 🖥️ **System Requirements**:

- **Linux/Unix**: Kore is designed for Linux and Unix-like systems (uses POSIX terminal APIs)
- **Terminal**: Any ANSI-Compatible terminal emulator

### 🛠️ **Build tools**:

- **CMake**: Version 3.31.6 or higher
- **C++ Compiler**: with C++26 support (GCC 13+ or Clang 16+)
- **Make build system**

### 📚 **System Libraries**:

- `termios.h`: Terminal I/O
- `unistd.h`: POSIX operating system API
- `sys/ioctl.h`: Device control operations

<br>

## ✨ **Features**:
- 🎨 **Terminal UI**: Clean User Interface
- ⌨️ **Keyboard Navigation**: Navigate quickly through your projects
- 🎹 **Multi-Track Playlist**: Mute tracks and place clips in them cannonically
- 🎵 **Clip System**: Create Clips with various types of notes, shapes, fading...

<br>

## 🏗️ **Architecture**:

- 🛤️ **Track**: Container for audio clips, with mute/solo controls

- 🎵 **Wave Generator**: Takes in parameters such as frequency, time or shape, and
  generates an according sample in a 44.1kHz standard

<br>

## 🛠️ **Building/Running**:

Kore is being develpoled with Linux in mind. For windows, you may have to do changes

to TerminalSettings.cpp, as it uses the termios and unistd.h Library.

<br>

Prerequisites:
- CMake


For building the project, run these commands sequentially:

```
Kore: mkdir build
Kore: cd build
Kore/build: cmake ..
Kore/build: make
```

### Running;

For running it, run this:

```
Kore/build: ./Kore
```

Note: Kore requires a terminal with ANSI escape sequence support. Most modern Linux 

terminal emulators (GNOME Terminal, Konsole, xterm, etc.) support this out of the box.

<br>

## 🐧 **Platform Support**:

Currently, Kore is Linux/Unix only due to its use of POSIX-specific terminal handling 

libraries (termios, unistd).

<br>

Windows support via WSL (Windows Subsystem for Linux) may work but is untested. 

Native Windows support would require platform-specific terminal handling code.
