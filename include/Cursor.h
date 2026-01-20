#pragma once

class Cursor {
public:
    Cursor();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveTo(int x, int y);

    int getX() const { return x; }
    int getY() const { return y; }

    void show() const;
    void hide() const;

private:
    int x;
    int y;
};