#pragma once

#include <string>

class FileDialog {
public:
    enum Mode { MENU, RENDER_PATH };
    enum MenuOption { RENDER, LOAD, CANCEL };

    struct DialogResult {
        bool confirmed;
        MenuOption option;
        std::string path;
    };

    FileDialog();

    void render(int termWidth) const;
    void handleInput(char c);
    void handleBackspace();
    void moveUp();
    void moveDown();
    void confirm();
    void cancel();

    DialogResult getResult() const;
    bool isComplete() const { return complete; }
    Mode getMode() const { return mode; }

private:
    Mode mode;
    MenuOption selectedOption;
    std::string pathInput;
    bool complete;
    bool confirmed;

    void renderMenu(int termWidth) const;
    void renderPathInput(int termWidth) const;
};