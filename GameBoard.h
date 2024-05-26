#pragma once
#include "Gems.h"
#include "Circle.h"
#include "Diamond.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"
#include <cstdlib>
#include <ctime>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include<string>
using namespace std;
class GameBoard {
private:
    Gems* gem[8][8];
    const int NUM_ROWS = 8;
    const int NUM_COLS = 8;
    const float CELL_SIZE = 60.0f;
    const float BOARD_WIDTH = NUM_COLS * CELL_SIZE;
    const float BOARD_HEIGHT = NUM_ROWS * CELL_SIZE;
    const float BOARD_OFFSET_X = (1280 - BOARD_WIDTH) / 2.0f;
    const float BOARD_OFFSET_Y = CELL_SIZE;
    int selectedRow1 = -1;
    int selectedCol1 = -1;
    int selectedRow2 = -1;
    int selectedCol2 = -1;

public:
    GameBoard();
    void initializeBoard();
    Gems* createRandomGem(int row, int col);
    void generateBoard();
    void drawBoard(); 
    void swapGems(int row1, int col1, int row2, int col2);
    void removeMatches();
    vector<pair<int, int>> findMatches();
    void fillBoard();
    bool isMatch(int row, int col);
    bool checkRowMatch(int row, int col);
    bool checkColumnMatch(int row, int col);
};
