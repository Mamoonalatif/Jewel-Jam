#pragma once
#include <cstdlib>
#include <ctime>

class GameBoard {
private:
    float progress;
    int level;
    int lives;

public:
    GameBoard() : progress(0), level(1), lives(3) {
        std::srand(std::time(0)); // Seed for randomness
        generateboard();
    }

    void generateboard() {
        const int WINDOW_WIDTH = 1280;
        const int WINDOW_HEIGHT = 730;
        const int NUM_ROWS = 8;
        const int NUM_COLS = 8;
        const float CELL_SIZE = 60.0f;
        const float BOARD_WIDTH = NUM_COLS * CELL_SIZE;
        const float BOARD_HEIGHT = NUM_ROWS * CELL_SIZE;
        const float BOARD_OFFSET_X = (WINDOW_WIDTH - BOARD_WIDTH) / 2.0f;
        const float BOARD_OFFSET_Y = CELL_SIZE; // Position the board at the bottom

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw outer border (brown, thick line)
        glColor3f(0.5f, 0.2f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(BOARD_OFFSET_X - 2, BOARD_OFFSET_Y - 2);
        glVertex2f(BOARD_OFFSET_X + BOARD_WIDTH + 2, BOARD_OFFSET_Y - 2);
        glVertex2f(BOARD_OFFSET_X + BOARD_WIDTH + 2, BOARD_OFFSET_Y + BOARD_HEIGHT + 2);
        glVertex2f(BOARD_OFFSET_X - 2, BOARD_OFFSET_Y + BOARD_HEIGHT + 2);
        glEnd();

        // Pre-calculate offsets for loop efficiency
        float x_start = BOARD_OFFSET_X;
        float y_start = BOARD_OFFSET_Y;
        float cell_size = CELL_SIZE;

        // Draw squares (light brown) and borders (darker brown, thin line)
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                float x_offset = x_start + j * cell_size;
                float y_offset = y_start + i * cell_size;

                // Draw filled square
                glColor3f(0.8f, 0.6f, 0.4f); // Light brown
                glBegin(GL_POLYGON);
                glVertex2f(x_offset, y_offset);
                glVertex2f(x_offset + cell_size, y_offset);
                glVertex2f(x_offset + cell_size, y_offset + cell_size);
                glVertex2f(x_offset, y_offset + cell_size);
                glEnd();

                // Draw inner border
                glColor3f(0.7f, 0.5f, 0.3f); // Darker brown
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

    
};
