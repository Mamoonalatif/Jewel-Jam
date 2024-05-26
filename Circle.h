#pragma once
#include"Gems.h"
class Circle : public Gems {
private:
    float radius; 
    float color[3]; 
public:
    Circle(float a, float b, float r) : Gems("Circle"), radius(r) {
        x = a;
        y = b;
       
        color[0] = 1.0f; 
        color[1] = 0.0f; 
        color[2] = 1.0f; 
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f); 
        glColor3fv(color); /
        glBegin(GL_POLYGON);
        
        for (int i = 0; i < 360; i++) {
            float theta = i * 3.1415926f / 180.0f;
            glVertex2f(radius * cos(theta), radius * sin(theta));
        }
        glEnd();
        glPopMatrix();
    }

    void move() override {
        
    }
};


