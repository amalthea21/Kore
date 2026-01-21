#pragma once

/**
 * @class Cursor
 * @brief Manages terminal cursor position and rendering.
 *
 * Handles cursor movement and display in the terminal UI.
 * Coordinates are 0-indexed with (0,0) at top-left.
 */
class Cursor {
public:
    /**
     * @brief Constructs cursor at origin (0, 0)
     */
    Cursor();

    /**
     * @brief Move cursor up one row (decreases y)
     * @note Does nothing if already at top (y = 0)
     */
    void moveUp();

    /**
     * @brief Move cursor down one row (increases y)
     */
    void moveDown();

    /**
     * @brief Move cursor left one column (decreases x)
     * @note Does nothing if already at left edge (x = 0)
     */
    void moveLeft();

    /**
     * @brief Move cursor right one column (increases x)
     */
    void moveRight();

    /**
     * @brief Move cursor to absolute position
     * @param x Column position (0-indexed)
     * @param y Row position (0-indexed)
     */
    void moveTo(int x, int y);

    /**
     * @brief Get current column position
     * @return X coordinate
     */
    int getX() const { return x; }

    /**
     * @brief Get current row position
     * @return Y coordinate
     */
    int getY() const { return y; }

    /**
     * @brief Render cursor at current position as reversed block
     */
    void show() const;

    /**
     * @brief Hide terminal cursor (ANSI escape sequence)
     */
    void hide() const;

private:
    int x; /**< Column position */
    int y; /**< Row position */
};