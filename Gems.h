#pragma once
#include"GameBoard.h"
class Gems {
protected:
    float x;
    float y;
    string type;
    int NUM_ROWS = 8;
    int NUM_COLS = 8;
    float CELL_SIZE = 60.0f;
    float BOARD_WIDTH = NUM_COLS * CELL_SIZE;
    float BOARD_HEIGHT = NUM_ROWS * CELL_SIZE;

public:
    Gems(string c);
    virtual void move() = 0;
    virtual void draw() = 0;
    void setX(float x);
    void setY(float y);
    int getX() const;
    int getY() const;
    string getType() const;
    void setType(string type);
};
