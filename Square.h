#pragma once
#include "Gems.h"
class Square : public Gems {
private:
    float size;
public:
    Square(float a, float b, float s);
    void draw() override;
    void move() override;
};
