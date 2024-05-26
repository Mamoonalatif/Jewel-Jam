#include "Gems.h"
#include <GL/glut.h>

class Triangle : public Gems {
private:
    float size; 
    float color[3]; 
public:
    Triangle(float a, float b, float s) : Gems("Triangle"), size(s) {
        x = a;
        y = b;
       
        color[0] = 0.0f; 
        color[1] = 0.0f; 
        color[2] = 1.0f; 
    }

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f); 
        glColor3fv(color); 
        glBegin(GL_TRIANGLES);

        glVertex2f(0.0f, size / 2.0f); 
        glVertex2f(-size / 2.0f, -size / 2.0f);
        glVertex2f(size / 2.0f, -size / 2.0f);
        glEnd();
        glPopMatrix();
    }

    void move() override {
        // Implement movement logic for triangle if needed
    }
};
