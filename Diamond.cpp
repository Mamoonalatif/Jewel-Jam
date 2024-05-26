#include "Diamond.h"
Diamond::Diamond(float a, float b, float s) : Gems("Diamond"), size(s) {
    x = a;
    y = b;
}
void Diamond::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f); 
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, size / 2.0f);
    glVertex2f(-size / 2.0f, 0.0f); 
    glVertex2f(0.0f, -size / 2.0f); 
    glVertex2f(size / 2.0f, 0.0f); 
    glEnd();
    glPopMatrix();
}

void Diamond::move() {
}
