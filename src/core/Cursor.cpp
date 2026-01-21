#include "../../include/core/Cursor.h"
#include "../../include/ui/AnsiFormat.h"
#include <iostream>

Cursor::Cursor() : x(0), y(0) {
}

void Cursor::moveUp() {
    if (y > 0) {
        y--;
    }
}

void Cursor::moveDown() {
    y++;
}

void Cursor::moveLeft() {
    if (x > 0) {
        x--;
    }
}

void Cursor::moveRight() {
    x++;
}

void Cursor::moveTo(int newX, int newY) {
    x = newX;
    y = newY;
}

void Cursor::show() const {
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
    std::cout << ANSI::REVERSE << " " << ANSI::RESET;
    std::cout << std::flush;
}

void Cursor::hide() const {
    std::cout << ANSI::HIDE_CURSOR;
    std::cout << std::flush;
}