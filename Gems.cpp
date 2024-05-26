#include"Gems.h"
Gems::Gems(string c) : type(c) {
    int max_x = static_cast<int>(BOARD_WIDTH - CELL_SIZE);
    int max_y = static_cast<int>(BOARD_HEIGHT - CELL_SIZE);

    x = static_cast<float>(rand() % (max_x + 1));
    y = static_cast<float>(rand() % (max_y + 1));
}
void Gems::setX(float x) { this->x = x; }
void Gems::setY(float y) { this->y = y; }
int Gems::getX() const { return x; }
int Gems::getY() const { return y; }
string Gems::getType() const { return type; }
void Gems::setType(string type) { this->type = type; }
