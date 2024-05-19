#pragma once
#include "Gems.h"
#include <cmath>
class Triangle : public Gems {
private:
    int sidelength = 30;
public:
    Triangle(float a, float b) : Gems(a, b, "Triangle") {
        
    }
    void draw() override {
        glColor3f(1.0, 0.00, 0.00); 
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y);
        glVertex2f(x + sidelength, y);
        glVertex2f(x + sidelength / 2, y + (sidelength * sqrt(3)) / 2);
        glEnd();
    }
    void move() override {
        x = 0; 
    }
};
