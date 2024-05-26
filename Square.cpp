#include "Square.h"
Square::Square(float a, float b, float s) : Gems("Square"), size(s) {
    x = a;
    y = b;
}
void Square::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f); 
    glColor3f(0.6f, 0.8f, 1.0f); 
    glBegin(GL_POLYGON);
    glVertex2f(-size / 2.0f, -size / 2.0f); 
    glVertex2f(size / 2.0f, -size / 2.0f); 
    glVertex2f(size / 2.0f, size / 2.0f); 
    glVertex2f(-size / 2.0f, size / 2.0f); 
    glEnd();
    glPopMatrix();
}
void Square::move() {
   
}
