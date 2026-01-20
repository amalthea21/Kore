# **🎼 Kore** 

Kore is a lightweight, keyboard-driven DAW, running entirely in the terminal

<br><br>

## ✨ **Features**:
- 🎨 **Terminal UI**: Clean User Interface
- ⌨️ **Keyboard Navigation**: Navigate quickly through your projects
- 🎹 **Multi-Track Playlist**: Mute tracks and place clips in them cannonically
- 🎵 **Clip System**: Create Clips with various types of notes, shapes, fading...

## 🏗️ **Architecture**:

- 🛤️ **Track**: Container for audio clips, with mute/solo controls

- 🎵 **Wave Generator**: Takes in parameters such as frequency, time or shape, and
  generates an according sample in a 44.1kHz standard

## 🛠️ **Building/Running:

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
