#pragma once
#include "Gems.h"
#include <GL/glut.h>
#include <cmath>

class Square : public Gems {
private:
    float size; 
    float color[3]; 
public:
    Square(float a, float b, float s) : Gems("Square"), size(s) {
        x = a;
        y = b;
        
        color[0] = 0.0f; 
        color[1] = 1.0f; 
        color[2] = 1.0f; 
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f); 
        glColor3fv(color); 
        glBegin(GL_POLYGON);
        
        glVertex2f(-size / 2.0f, -size / 2.0f);
        glVertex2f(size / 2.0f, -size / 2.0f); 
        glVertex2f(size / 2.0f, size / 2.0f); 
        glVertex2f(-size / 2.0f, size / 2.0f);
        glEnd();
        glPopMatrix();
    }

    void move() override {
        // Implement movement logic for square if needed
    }
};
