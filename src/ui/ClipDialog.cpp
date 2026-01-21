#include "../../include/ui/ClipDialog.h"
#include "../../include/ui/AnsiFormat.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

// Note to frequency mapping (A4 = 440Hz standard)
const std::map<std::string, float> ClipDialog::noteFrequencies = {
    {"C0", 16.35f}, {"C#0", 17.32f}, {"D0", 18.35f}, {"D#0", 19.45f},
    {"E0", 20.60f}, {"F0", 21.83f}, {"F#0", 23.12f}, {"G0", 24.50f},
    {"G#0", 25.96f}, {"A0", 27.50f}, {"A#0", 29.14f}, {"B0", 30.87f},

    {"C1", 32.70f}, {"C#1", 34.65f}, {"D1", 36.71f}, {"D#1", 38.89f},
    {"E1", 41.20f}, {"F1", 43.65f}, {"F#1", 46.25f}, {"G1", 49.00f},
    {"G#1", 51.91f}, {"A1", 55.00f}, {"A#1", 58.27f}, {"B1", 61.74f},

    {"C2", 65.41f}, {"C#2", 69.30f}, {"D2", 73.42f}, {"D#2", 77.78f},
    {"E2", 82.41f}, {"F2", 87.31f}, {"F#2", 92.50f}, {"G2", 98.00f},
    {"G#2", 103.83f}, {"A2", 110.00f}, {"A#2", 116.54f}, {"B2", 123.47f},

    {"C3", 130.81f}, {"C#3", 138.59f}, {"D3", 146.83f}, {"D#3", 155.56f},
    {"E3", 164.81f}, {"F3", 174.61f}, {"F#3", 185.00f}, {"G3", 196.00f},
    {"G#3", 207.65f}, {"A3", 220.00f}, {"A#3", 233.08f}, {"B3", 246.94f},

    {"C4", 261.63f}, {"C#4", 277.18f}, {"D4", 293.66f}, {"D#4", 311.13f},
    {"E4", 329.63f}, {"F4", 349.23f}, {"F#4", 369.99f}, {"G4", 392.00f},
    {"G#4", 415.30f}, {"A4", 440.00f}, {"A#4", 466.16f}, {"B4", 493.88f},

    {"C5", 523.25f}, {"C#5", 554.37f}, {"D5", 587.33f}, {"D#5", 622.25f},
    {"E5", 659.25f}, {"F5", 698.46f}, {"F#5", 739.99f}, {"G5", 783.99f},
    {"G#5", 830.61f}, {"A5", 880.00f}, {"A#5", 932.33f}, {"B5", 987.77f},
};

ClipDialog::ClipDialog()
    : currentField(AT), atInput("0"), timeInput("2"), noteInput("A4"),
      complete(false), confirmed(false) {
}

void ClipDialog::render(int termWidth) const {
    int dialogWidth = 50;
    int startX = (termWidth - dialogWidth) / 2;

    std::cout << "\n";
    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "╭";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "╮\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│" << ANSI::BOLD << "           Create New Clip"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 29; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "├";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "┤\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  Position (s): ";
    if (currentField == AT) {
        std::cout << ANSI::BG_BLUE << ANSI::WHITE << atInput;
        for (int i = atInput.length(); i < 10; i++) std::cout << " ";
        std::cout << ANSI::RESET;
    } else {
        std::cout << atInput;
        for (int i = atInput.length(); i < 10; i++) std::cout << " ";
    }
    for (int i = 0; i < dialogWidth - 28; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  Duration (s): ";
    if (currentField == TIME) {
        std::cout << ANSI::BG_BLUE << ANSI::WHITE << timeInput;
        for (int i = timeInput.length(); i < 10; i++) std::cout << " ";
        std::cout << ANSI::RESET;
    } else {
        std::cout << timeInput;
        for (int i = timeInput.length(); i < 10; i++) std::cout << " ";
    }
    for (int i = 0; i < dialogWidth - 28; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  Note:         ";
    if (currentField == NOTE) {
        std::cout << ANSI::BG_BLUE << ANSI::WHITE << noteInput;
        for (int i = noteInput.length(); i < 10; i++) std::cout << " ";
        std::cout << ANSI::RESET;
    } else {
        std::cout << noteInput;
        for (int i = noteInput.length(); i < 10; i++) std::cout << " ";
    }
    for (int i = 0; i < dialogWidth - 28; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "├";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "┤\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│ " << ANSI::DIM << "Tab: Next field  Enter: Confirm  ESC: Cancel"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 49; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│ " << ANSI::DIM << "Note examples: A4, C#5, D3, or frequency (Hz)"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 52; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "╰";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "╯\n";
}

void ClipDialog::nextField() {
    currentField = static_cast<Field>((currentField + 1) % 3);
}

void ClipDialog::prevField() {
    currentField = static_cast<Field>((currentField + 2) % 3);
}

void ClipDialog::handleInput(char c) {
    std::string* current = nullptr;

    switch (currentField) {
        case AT: current = &atInput; break;
        case TIME: current = &timeInput; break;
        case NOTE: current = &noteInput; break;
    }

    if (current && current->length() < 10) {
        if (currentField == AT || currentField == TIME) {
            if ((c >= '0' && c <= '9') || c == '.') {
                *current += c;
            }
        } else {
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') || c == '#' || c == '.') {
                *current += c;
            }
        }
    }
}

void ClipDialog::handleBackspace() {
    std::string* current = nullptr;

    switch (currentField) {
        case AT: current = &atInput; break;
        case TIME: current = &timeInput; break;
        case NOTE: current = &noteInput; break;
    }

    if (current && !current->empty()) {
        current->pop_back();
    }
}

void ClipDialog::confirm() {
    complete = true;
    confirmed = true;
}

void ClipDialog::cancel() {
    complete = true;
    confirmed = false;
}

ClipDialog::ClipParams ClipDialog::getParams() const {
    return {
        parseAt(),
        parseTime(),
        parseNote(),
        confirmed
    };
}

float ClipDialog::parseAt() const {
    try {
        return std::stof(atInput);
    } catch (...) {
        return 0.0f;
    }
}

float ClipDialog::parseTime() const {
    try {
        float t = std::stof(timeInput);
        return t > 0 ? t : 1.0f;
    } catch (...) {
        return 1.0f;
    }
}

float ClipDialog::parseNote() const {
    std::string upperNote = noteInput;
    std::transform(upperNote.begin(), upperNote.end(), upperNote.begin(), ::toupper);

    auto it = noteFrequencies.find(upperNote);
    if (it != noteFrequencies.end()) {
        return it->second;
    }

    try {
        float freq = std::stof(noteInput);
        return freq > 0 ? freq : 440.0f;
    } catch (...) {
        return 440.0f;
    }
}

std::string ClipDialog::getFieldValue(Field field) const {
    switch (field) {
        case AT: return atInput;
        case TIME: return timeInput;
        case NOTE: return noteInput;
        default: return "";
    }
}

void ClipDialog::setFieldValue(Field field, const std::string& value) {
    switch (field) {
        case AT: atInput = value; break;
        case TIME: timeInput = value; break;
        case NOTE: noteInput = value; break;
    }
}