#include "Rectangle.h"
#include "Gems.h"
Rectangle::Rectangle(float a, float b, float w, float h) : Gems("Rectangle"), width(w), height(h) {
    x = a;
    y = b;
}
void Rectangle::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-width / 2.0f, -height / 2.0f);
    glVertex2f(width / 2.0f, -height / 2.0f);
    glVertex2f(width / 2.0f, height / 2.0f);
    glVertex2f(-width / 2.0f, height / 2.0f);
    glEnd();
    glPopMatrix();
}
void Rectangle::move() {
    // Implementation of move function (if applicable)
}
