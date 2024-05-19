#pragma once
#include <cstdlib>
#include <ctime>
#include"Triangle.h"
#include"Gems.h"
class GameBoard {
    public:
   Gems* gem[10][10];
    float progress;
    int level;
    int lives;
    const int NUM_ROWS = 8;
    const int NUM_COLS = 8;
    const float CELL_SIZE = 60.0f;
    const float BOARD_WIDTH = NUM_COLS * CELL_SIZE;
    const float BOARD_HEIGHT = NUM_ROWS * CELL_SIZE;
    const float BOARD_OFFSET_X = (1280 - BOARD_WIDTH) / 2.0f;
    const float BOARD_OFFSET_Y = CELL_SIZE;
public:
    GameBoard() : progress(0), level(1), lives(3) {
        srand(time(0)); 
        placeTriangles();
 
    }
    void generateboard() {
        glClear(GL_COLOR_BUFFER_BIT);
        //Outer Border
        glColor3f(0.5f, 0.2f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(BOARD_OFFSET_X - 2, BOARD_OFFSET_Y - 2);
        glVertex2f(BOARD_OFFSET_X + BOARD_WIDTH + 2, BOARD_OFFSET_Y - 2);
        glVertex2f(BOARD_OFFSET_X + BOARD_WIDTH + 2, BOARD_OFFSET_Y + BOARD_HEIGHT + 2);
        glVertex2f(BOARD_OFFSET_X - 2, BOARD_OFFSET_Y + BOARD_HEIGHT + 2);
        glEnd();
        float x_start = BOARD_OFFSET_X;
        float y_start = BOARD_OFFSET_Y;
        float cell_size = CELL_SIZE;
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                float x_offset = x_start + j * cell_size;
                float y_offset = y_start + i * cell_size;
                //Squares
                glColor3f(0.8f, 0.6f, 0.4f); 
                glBegin(GL_POLYGON);
                glVertex2f(x_offset, y_offset);
                glVertex2f(x_offset + cell_size, y_offset);
                glVertex2f(x_offset + cell_size, y_offset + cell_size);
                glVertex2f(x_offset, y_offset + cell_size);
                glEnd();
                //Inner borders
                glColor3f(0.7f, 0.5f, 0.3f); 
                glLineWidth(1.0f);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x_offset, y_offset);
                glVertex2f(x_offset + cell_size, y_offset);
                glVertex2f(x_offset + cell_size, y_offset + cell_size);
                glVertex2f(x_offset, y_offset + cell_size);
                glEnd();
            }
        }

        glFlush();
    }
    void placeTriangles() {
        const int sidelength = 30;
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                float x_offset = BOARD_OFFSET_X + j * CELL_SIZE + (CELL_SIZE - sidelength) / 2.0f;
                float y_offset = BOARD_OFFSET_Y + i * CELL_SIZE + (CELL_SIZE - sidelength) / 2.0f;
                gem[i][j] = new Triangle(x_offset, y_offset);
            }
        }
    }


    
};
