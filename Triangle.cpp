#include "Triangle.h"
Triangle::Triangle(float a, float b, float s) : Gems("Triangle"), size(s) {
    x = a;
    y = b;
}
void Triangle::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f); 
    glColor3f(1.0f, 0.7f, 0.7f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, size / 2.0f);
    glVertex2f(-size / 2.0f, -size / 2.0f); 
    glVertex2f(size / 2.0f, -size / 2.0f); 
    glEnd();
    glPopMatrix();
}
void Triangle::move() {

}