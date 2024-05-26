#pragma once
#include"Gems.h"
class Circle : public Gems {
private:
    float radius;
public:
    Circle(float a, float b, float r);
    void draw() override;
    void move() override;
};

