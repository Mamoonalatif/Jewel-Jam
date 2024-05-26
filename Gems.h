#pragma once
#include<glut.h>
#include<string>
#include <cstdlib>
#include "GameBoard.h"
using namespace std;
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
	Gems(string c) : type(c) {
		int max_x = static_cast<int>(BOARD_WIDTH - CELL_SIZE); // Maximum valid x-coordinate
		int max_y = static_cast<int>(BOARD_HEIGHT - CELL_SIZE); // Maximum valid y-coordinate

		x = static_cast<float>(rand() % (max_x + 1)); // Generate random x within valid range (0 to max_x)
		y = static_cast<float>(rand() % (max_y + 1)); // Generate random y within valid range (0 to max_y)
		;

	}
	virtual void move() = 0;
	virtual void draw() = 0;
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	int getX() const { return x; }
	int getY() const { return y; }
	string getType() const { return type; }

};

