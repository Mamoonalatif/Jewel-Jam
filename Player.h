#pragma once
#include"GameBoard.h"
class Player {
    string name;
    float score;
public:
    Player(string n, float s);
    void addscore(int s);
    string getName() const;
    float getScore() const;
};


