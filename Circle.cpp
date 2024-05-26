#include"Circle.h"
Circle::Circle(float a, float b, float r) : Gems("Circle"), radius(r) {
    x = a;
    y = b;
}
void Circle::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.75f, 0.25f, 0.75f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.1415926f / 180.0f;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
    glPopMatrix();

}
void Circle::move() {
}

