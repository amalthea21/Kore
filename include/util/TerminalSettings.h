#pragma once

#include <termios.h>
#include <iostream>
#include <string>

#include "../audio/Track.h"

/**
 * @class TerminalSettings
 * @brief Manages raw terminal mode and keyboard input.
 *
 * Configures the terminal for non-canonical, non-echo mode
 * to enable real-time keyboard input handling. Automatically
 * restores original terminal settings on destruction.
 */
class TerminalSettings {
public:
    /**
     * @enum Key
     * @brief Enumeration of special keyboard keys and sequences
     *
     * Maps ANSI escape sequences to named constants for easier handling.
     * Includes function keys (F1-F12), arrow keys, control keys, and more.
     */
    enum Key {
        KEY_UNKNOWN = 0,    /**< Unrecognized key sequence */
        KEY_ESC = 27,       /**< Escape key */
        KEY_F1 = 1001,      /**< Function key F1 */
        KEY_F2 = 1002,      /**< Function key F2 */
        KEY_F3 = 1003,      /**< Function key F3 */
        KEY_F4 = 1004,      /**< Function key F4 */
        KEY_F5 = 1005,      /**< Function key F5 */
        KEY_F6 = 1006,      /**< Function key F6 */
        KEY_F7 = 1007,      /**< Function key F7 */
        KEY_F8 = 1008,      /**< Function key F8 */
        KEY_F9 = 1009,      /**< Function key F9 */
        KEY_F10 = 1010,     /**< Function key F10 */
        KEY_F11 = 1011,     /**< Function key F11 */
        KEY_F12 = 1012,     /**< Function key F12 */
        KEY_ARROW_UP = 1100,    /**< Up arrow key */
        KEY_ARROW_DOWN = 1101,  /**< Down arrow key */
        KEY_ARROW_LEFT = 1102,  /**< Left arrow key */
        KEY_ARROW_RIGHT = 1103, /**< Right arrow key */
        KEY_DELETE = 1200,      /**< Delete key */
        KEY_INSERT = 1201,      /**< Insert key */
        KEY_HOME = 1202,        /**< Home key */
        KEY_END = 1203,         /**< End key */
        KEY_PAGE_UP = 1204,     /**< Page Up key */
        KEY_PAGE_DOWN = 1205,   /**< Page Down key */
        KEY_CTRL_A = 1,   /**< Ctrl+A */
        KEY_CTRL_B = 2,   /**< Ctrl+B */
        KEY_CTRL_C = 3,   /**< Ctrl+C */
        KEY_CTRL_D = 4,   /**< Ctrl+D */
        KEY_CTRL_E = 5,   /**< Ctrl+E */
        KEY_CTRL_F = 6,   /**< Ctrl+F */
        KEY_CTRL_G = 7,   /**< Ctrl+G */
        KEY_CTRL_H = 8,   /**< Ctrl+H */
        KEY_CTRL_I = 9,   /**< Ctrl+I (Tab) */
        KEY_CTRL_J = 10,  /**< Ctrl+J */
        KEY_CTRL_K = 11,  /**< Ctrl+K */
        KEY_CTRL_L = 12,  /**< Ctrl+L */
        KEY_CTRL_M = 13,  /**< Ctrl+M (Enter) */
        KEY_CTRL_N = 14,  /**< Ctrl+N */
        KEY_CTRL_O = 15,  /**< Ctrl+O */
        KEY_CTRL_P = 16,  /**< Ctrl+P */
        KEY_CTRL_Q = 17,  /**< Ctrl+Q */
        KEY_CTRL_R = 18,  /**< Ctrl+R */
        KEY_CTRL_S = 19,  /**< Ctrl+S */
        KEY_CTRL_T = 20,  /**< Ctrl+T */
        KEY_CTRL_U = 21,  /**< Ctrl+U */
        KEY_CTRL_V = 22,  /**< Ctrl+V */
        KEY_CTRL_W = 23,  /**< Ctrl+W */
        KEY_CTRL_X = 24,  /**< Ctrl+X */
        KEY_CTRL_Y = 25,  /**< Ctrl+Y */
        KEY_CTRL_Z = 26   /**< Ctrl+Z */
    };

    /**
     * @brief Initialize terminal in raw mode
     *
     * Configures terminal for:
     * - Non-canonical mode (character-by-character input)
     * - No echo (keypresses not displayed)
     * - Immediate input availability
     * - Clears screen and hides cursor
     */
    TerminalSettings();

    /**
     * @brief Restore original terminal settings
     *
     * Should be called before program exit to ensure
     * terminal returns to normal mode. Shows cursor.
     */
    void restoreTerminal();

    /**
     * @brief Get current terminal width
     * @return Width in columns
     * @note Uses ioctl TIOCGWINSZ to query terminal size
     */
    int terminalWidth();

    /**
     * @brief Read and parse a single keypress
     * @return Key code from the Key enum
     *
     * Handles:
     * - Single characters (ASCII 32-126)
     * - ANSI escape sequences for special keys
     * - Control characters (Ctrl+A through Ctrl+Z)
     *
     * @note Blocks until a key is pressed
     */
    int readKey();

private:
    termios old;  /**< Original terminal settings for restoration */
    termios term; /**< Current raw mode terminal settings */
};