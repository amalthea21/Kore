#pragma once

#include <string>

/**
 * @class FileDialog
 * @brief Two-stage dialog for file operations (render/load).
 *
 * Stage 1: Menu with options (Render, Load, Cancel)
 * Stage 2: Path input for selected option (currently only Render)
 *
 * Handles navigation and text input for file operations.
 */
class FileDialog {
public:
    /**
     * @enum Mode
     * @brief Current dialog stage
     */
    enum Mode {
        MENU,        /**< Showing menu with options */
        RENDER_PATH  /**< Getting file path for render */
    };

    /**
     * @enum MenuOption
     * @brief Available menu selections
     */
    enum MenuOption {
        RENDER,  /**< Render playlist to WAV file */
        LOAD,    /**< Load from file (not yet implemented) */
        CANCEL   /**< Cancel and close dialog */
    };

    /**
     * @struct DialogResult
     * @brief Result data when dialog completes
     */
    struct DialogResult {
        bool confirmed;      /**< True if user confirmed an action */
        MenuOption option;   /**< Which option was selected */
        std::string path;    /**< File path entered (for RENDER) */
    };

    /**
     * @brief Construct dialog starting in menu mode with RENDER selected
     *
     * Default path is "output.wav"
     */
    FileDialog();

    /**
     * @brief Render current dialog stage
     * @param termWidth Terminal width for centering
     *
     * Renders either menu or path input based on current mode.
     */
    void render(int termWidth) const;

    /**
     * @brief Handle character input for path field
     * @param c Character to append
     *
     * Only accepts input in RENDER_PATH mode.
     * Path limited to 100 characters.
     */
    void handleInput(char c);

    /**
     * @brief Remove last character from path
     *
     * Only operates in RENDER_PATH mode.
     */
    void handleBackspace();

    /**
     * @brief Move selection up in menu
     *
     * LOAD → RENDER
     * CANCEL → LOAD
     */
    void moveUp();

    /**
     * @brief Move selection down in menu
     *
     * RENDER → LOAD
     * LOAD → CANCEL
     */
    void moveDown();

    /**
     * @brief Confirm current selection or path
     *
     * In MENU mode:
     * - RENDER: Switch to RENDER_PATH mode
     * - LOAD: Complete with confirmed=false (not implemented)
     * - CANCEL: Complete with confirmed=false
     *
     * In RENDER_PATH mode: Complete with confirmed=true
     */
    void confirm();

    /**
     * @brief Cancel dialog immediately
     *
     * Sets complete=true and confirmed=false
     */
    void cancel();

    /**
     * @brief Get final dialog result
     * @return DialogResult with user's choices
     */
    DialogResult getResult() const;

    /**
     * @brief Check if dialog is finished
     * @return True when user has confirmed or cancelled
     */
    bool isComplete() const { return complete; }

    /**
     * @brief Get current dialog mode
     * @return MENU or RENDER_PATH
     */
    Mode getMode() const { return mode; }

private:
    Mode mode;                /**< Current stage of dialog */
    MenuOption selectedOption; /**< Currently highlighted menu item */
    std::string pathInput;    /**< User-entered file path */
    bool complete;            /**< Dialog finished flag */
    bool confirmed;           /**< True if action confirmed, false if cancelled */

    /**
     * @brief Render the menu stage
     * @param termWidth Terminal width for centering
     *
     * Shows three options with current selection highlighted.
     */
    void renderMenu(int termWidth) const;

    /**
     * @brief Render the path input stage
     * @param termWidth Terminal width for centering
     *
     * Shows text input field for file path.
     */
    void renderPathInput(int termWidth) const;
};