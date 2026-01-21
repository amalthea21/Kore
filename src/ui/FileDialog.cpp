#include "../../include/ui/FileDialog.h"
#include "../../include/ui/AnsiFormat.h"
#include <iostream>

FileDialog::FileDialog()
    : mode(MENU), selectedOption(RENDER), pathInput("output.wav"),
      complete(false), confirmed(false) {
}

void FileDialog::render(int termWidth) const {
    if (mode == MENU) {
        renderMenu(termWidth);
    } else if (mode == RENDER_PATH) {
        renderPathInput(termWidth);
    }
}

void FileDialog::renderMenu(int termWidth) const {
    int dialogWidth = 50;
    int startX = (termWidth - dialogWidth) / 2;

    std::cout << "\n";
    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "╭";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "╮\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│" << ANSI::BOLD << "                File Menu"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 28; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "├";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "┤\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  ";
    if (selectedOption == RENDER) {
        std::cout << ANSI::BG_BLUE << ANSI::WHITE << "> Render to WAV file";
        for (int i = 0; i < 26; i++) std::cout << " ";
        std::cout << ANSI::RESET;
    } else {
        std::cout << "  Render to WAV file";
        for (int i = 0; i < 26; i++) std::cout << " ";
    }
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  ";
    if (selectedOption == LOAD) {
        std::cout << ANSI::BG_BLUE << ANSI::WHITE << "> Load from file" << ANSI::DIM << " (Coming soon)";
        for (int i = 0; i < 17; i++) std::cout << " ";
        std::cout << ANSI::RESET;
    } else {
        std::cout << ANSI::DIM << "  Load from file (Coming soon)";
        for (int i = 0; i < 17; i++) std::cout << " ";
        std::cout << ANSI::RESET;
    }
    std::cout << "│\n";

    // Cancel option
    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  ";
    if (selectedOption == CANCEL) {
        std::cout << ANSI::BG_BLUE << ANSI::WHITE << "> Cancel";
        for (int i = 0; i < 40; i++) std::cout << " ";
        std::cout << ANSI::RESET;
    } else {
        std::cout << "  Cancel";
        for (int i = 0; i < 40; i++) std::cout << " ";
    }
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "├";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "┤\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│ " << ANSI::DIM << "↑↓: Navigate  Enter: Select  ESC: Cancel"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 47; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "╰";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "╯\n";
}

void FileDialog::renderPathInput(int termWidth) const {
    int dialogWidth = 60;
    int startX = (termWidth - dialogWidth) / 2;

    std::cout << "\n";
    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "╭";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "╮\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│" << ANSI::BOLD << "              Render to WAV File"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 35; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "├";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "┤\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  File path:                                          │\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│  " << ANSI::BG_BLUE << ANSI::WHITE << pathInput;
    int remaining = 54 - pathInput.length();
    for (int i = 0; i < remaining; i++) std::cout << " ";
    std::cout << ANSI::RESET << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "├";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "┤\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│ " << ANSI::DIM << "Enter: Confirm  ESC: Cancel"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 31; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "│ " << ANSI::DIM << "Example: /path/to/file.wav or output.wav"
              << ANSI::RESET;
    for (int i = 0; i < dialogWidth - 45; i++) std::cout << " ";
    std::cout << "│\n";

    for (int i = 0; i < startX; i++) std::cout << " ";
    std::cout << "╰";
    for (int i = 0; i < dialogWidth - 2; i++) std::cout << "─";
    std::cout << "╯\n";
}

void FileDialog::moveUp() {
    if (mode == MENU) {
        if (selectedOption == LOAD) {
            selectedOption = RENDER;
        } else if (selectedOption == CANCEL) {
            selectedOption = LOAD;
        }
    }
}

void FileDialog::moveDown() {
    if (mode == MENU) {
        if (selectedOption == RENDER) {
            selectedOption = LOAD;
        } else if (selectedOption == LOAD) {
            selectedOption = CANCEL;
        }
    }
}

void FileDialog::handleInput(char c) {
    if (mode == RENDER_PATH && pathInput.length() < 100) {
        pathInput += c;
    }
}

void FileDialog::handleBackspace() {
    if (mode == RENDER_PATH && !pathInput.empty()) {
        pathInput.pop_back();
    }
}

void FileDialog::confirm() {
    if (mode == MENU) {
        if (selectedOption == RENDER) {
            mode = RENDER_PATH;
        } else if (selectedOption == LOAD) {
            complete = true;
            confirmed = false;
        } else if (selectedOption == CANCEL) {
            complete = true;
            confirmed = false;
        }
    } else if (mode == RENDER_PATH) {
        complete = true;
        confirmed = true;
    }
}

void FileDialog::cancel() {
    complete = true;
    confirmed = false;
}

FileDialog::DialogResult FileDialog::getResult() const {
    return {
        confirmed,
        selectedOption,
        pathInput
    };
}