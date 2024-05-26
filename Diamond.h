#pragma once
#include "Gems.h"
#include <GL/glut.h>

class Diamond : public Gems {
private:
    float size;
    float color[3]; 
public:
    Diamond(float a, float b, float s) : Gems("Diamond"), size(s) {
        x = a;
        y = b;
        
        color[0] = 1.0f; 
        color[1] = 1.0f; 
        color[2] = 0.0f;
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f); 
        glColor3fv(color); 
        glBegin(GL_POLYGON);
       
        glVertex2f(0.0f, size / 2.0f);
        glVertex2f(-size / 2.0f, 0.0f);
        glVertex2f(0.0f, -size / 2.0f); 
        glVertex2f(size / 2.0f, 0.0f); 
        glEnd();
        glPopMatrix();
    }

    void move() override {
        // Implement movement logic for diamond if needed
    }
};

