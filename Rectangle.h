#include "Gems.h"
#include <GL/glut.h>

class Rectangle : public Gems {
private:
    float width; 
    float height; 
    float color[3]; s
public:
    Rectangle(float a, float b, float w, float h) : Gems("Rectangle"), width(w), height(h) {
        x = a;
        y = b;
        
        color[0] = 0.0f;
        color[1] = 1.0f; 
        color[2] = 0.0f;
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f); 
        glColor3fv(color); 
        glBegin(GL_POLYGON);
        
        glVertex2f(-width / 2.0f, -height / 2.0f); 
        glVertex2f(width / 2.0f, -height / 2.0f); 
        glVertex2f(width / 2.0f, height / 2.0f); 
        glVertex2f(-width / 2.0f, height / 2.0f); 
        glEnd();
        glPopMatrix();
    }

    void move() override {
        // Implement movement logic for rectangle if needed
    }
};

