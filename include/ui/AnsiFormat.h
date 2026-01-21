#pragma once

#include <string>

/**
 * @namespace ANSI
 * @brief ANSI escape sequences for terminal formatting and control.
 *
 * Provides constants for text styling, colors, backgrounds, and
 * cursor control. Use by writing these strings to std::cout.
 *
 * Example usage:
 * @code
 * std::cout << ANSI::BOLD << ANSI::RED << "Error!" << ANSI::RESET;
 * std::cout << ANSI::CLEAR_SCREEN << ANSI::HIDE_CURSOR;
 * @endcode
 *
 * @note Requires ANSI-compatible terminal (most modern terminals)
 */
namespace ANSI {
    // ==================== Cursor Control ====================

    /** @brief Hide the terminal cursor */
    const std::string HIDE_CURSOR = "\033[?25l";

    /** @brief Show the terminal cursor */
    const std::string SHOW_CURSOR = "\033[?25h";

    // ==================== Screen Control ====================

    /** @brief Clear entire screen and move cursor to home */
    const std::string CLEAR_SCREEN = "\033[2J";

    /** @brief Reset all formatting to defaults */
    const std::string RESET = "\033[0m";

    // ==================== Text Styles ====================

    /** @brief Bold/bright text */
    const std::string BOLD = "\033[1m";

    /** @brief Dimmed/faint text */
    const std::string DIM = "\033[2m";

    /** @brief Italic text (not widely supported) */
    const std::string ITALIC = "\033[3m";

    /** @brief Underlined text */
    const std::string UNDERLINE = "\033[4m";

    /** @brief Blinking text (often disabled in modern terminals) */
    const std::string BLINK = "\033[5m";

    /** @brief Reverse video (swap foreground/background) */
    const std::string REVERSE = "\033[7m";

    /** @brief Hidden text (foreground = background) */
    const std::string HIDDEN = "\033[8m";

    /** @brief Strikethrough text */
    const std::string STRIKETHROUGH = "\033[9m";

    // ==================== Foreground Colors ====================

    /** @brief Black text */
    const std::string BLACK = "\033[30m";

    /** @brief Red text */
    const std::string RED = "\033[31m";

    /** @brief Green text */
    const std::string GREEN = "\033[32m";

    /** @brief Yellow text */
    const std::string YELLOW = "\033[33m";

    /** @brief Blue text */
    const std::string BLUE = "\033[34m";

    /** @brief Magenta text */
    const std::string MAGENTA = "\033[35m";

    /** @brief Cyan text */
    const std::string CYAN = "\033[36m";

    /** @brief White text */
    const std::string WHITE = "\033[37m";

    // ==================== Bright Foreground Colors ====================

    /** @brief Bright black (dark gray) text */
    const std::string BRIGHT_BLACK = "\033[90m";

    /** @brief Bright red text */
    const std::string BRIGHT_RED = "\033[91m";

    /** @brief Bright green text */
    const std::string BRIGHT_GREEN = "\033[92m";

    /** @brief Bright yellow text */
    const std::string BRIGHT_YELLOW = "\033[93m";

    /** @brief Bright blue text */
    const std::string BRIGHT_BLUE = "\033[94m";

    /** @brief Bright magenta text */
    const std::string BRIGHT_MAGENTA = "\033[95m";

    /** @brief Bright cyan text */
    const std::string BRIGHT_CYAN = "\033[96m";

    /** @brief Bright white text */
    const std::string BRIGHT_WHITE = "\033[97m";

    // ==================== Background Colors ====================

    /** @brief Black background */
    const std::string BG_BLACK = "\033[40m";

    /** @brief Red background */
    const std::string BG_RED = "\033[41m";

    /** @brief Green background */
    const std::string BG_GREEN = "\033[42m";

    /** @brief Yellow background */
    const std::string BG_YELLOW = "\033[43m";

    /** @brief Blue background */
    const std::string BG_BLUE = "\033[44m";

    /** @brief Magenta background */
    const std::string BG_MAGENTA = "\033[45m";

    /** @brief Cyan background */
    const std::string BG_CYAN = "\033[46m";

    /** @brief White background */
    const std::string BG_WHITE = "\033[47m";

    // ==================== Bright Background Colors ====================

    /** @brief Bright black (dark gray) background */
    const std::string BG_BRIGHT_BLACK = "\033[100m";

    /** @brief Bright red background */
    const std::string BG_BRIGHT_RED = "\033[101m";

    /** @brief Bright green background */
    const std::string BG_BRIGHT_GREEN = "\033[102m";

    /** @brief Bright yellow background */
    const std::string BG_BRIGHT_YELLOW = "\033[103m";

    /** @brief Bright blue background */
    const std::string BG_BRIGHT_BLUE = "\033[104m";

    /** @brief Bright magenta background */
    const std::string BG_BRIGHT_MAGENTA = "\033[105m";

    /** @brief Bright cyan background */
    const std::string BG_BRIGHT_CYAN = "\033[106m";

    /** @brief Bright white background */
    const std::string BG_BRIGHT_WHITE = "\033[107m";
}