#include "Menu.h"
void Menu::rectangleborder(float x, float y, float width, float height, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
void Menu::rectangle(float x, float y, float width, float height, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
void Menu::text(const string& text, float x, float y, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}
void Menu::drawMainMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
    rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
    rectangle(200, 620, 900, 60, brownR, brownG, brownB);
    for (int i = 0; i < 4; i++) {
        rectangle(Mainmenurectangles[i][0], Mainmenurectangles[i][1], Mainmenurectangles[i][2], Mainmenurectangles[i][3],
            brownR, brownG, brownB);
    }
    text("JEWEL JAM", 550, 640, goldenR, goldenG, goldenB);
    text("PLAY", 390, 470, goldenR, goldenG, goldenB);
    text("INSTRUCTIONS", 350, 370, goldenR, goldenG, goldenB);
    text("HIGHSCORE", 365, 270, goldenR, goldenG, goldenB);
    text("QUIT GAME", 370, 170, goldenR, goldenG, goldenB);
    // Draw head in brown
    glColor3f(0.545, 0.271, 0.075);
    drawCircle(1000.0, 450.0, 50.0, 100);
    /// Draw body in brown
    glColor3f(0.545, 0.271, 0.075);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 60 * cos(theta), 330.0 + 100 * sin(theta));
    }
    glEnd();
    glColor3f(0.9569, 0.8471, 0.6824); // Body within body
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 40 * cos(theta), 330.0 + 70 * sin(theta));
    }
    glEnd();
    // Draw ears 
    glColor3f(0.545, 0.271, 0.075);
    drawCircle(950.0, 500.0, 20.0, 100);
    drawCircle(1050.0, 500.0, 20.0, 100);
    // Draw eyes 
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(985.0, 470.0, 10.0, 100);
    drawCircle(1015.0, 470.0, 10.0, 100);
    // Draw pupils 
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(985.0, 470.0, 5.0, 100);
    drawCircle(1015.0, 470.0, 5.0, 100);
    // Draw nose 
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 8 * cos(theta), 440.0 + 5 * sin(theta));
    }
    glEnd();
    // Draw mouth 
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 210; i <= 330; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 20 * cos(theta), 435.0 + 10 * sin(theta));
    }
    glEnd();
    // Draw tongue 
    glColor3f(1.0, 0.5, 0.5);
    glBegin(GL_POLYGON);
    for (int i = 180; i <= 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(1000.0 + 8 * cos(theta), 425.0 + 4 * sin(theta));
    }
    glEnd();
    // Draw arms 
    glColor3f(0.545, 0.271, 0.075);
    drawCircle(940.0, 380.0, 20.0, 100);
    drawCircle(1060.0, 380.0, 20.0, 100);
    // Draw legs 
    drawCircle(970.0, 220.0, 20.0, 100);
    drawCircle(1030.0, 220.0, 20.0, 100);
    glutSwapBuffers();
}
void Menu::drawPauseMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
    rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
    rectangle(200, 620, 900, 60, brownR, brownG, brownB);
    for (int i = 0; i < 3; i++) {
        rectangle(otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2], otherRectangles[i][3],
            brownR, brownG, brownB);
    }
    text("PAUSE MENU", 550, 640, goldenR, goldenG, goldenB);
    text("RESUME", 570, 485, goldenR, goldenG, goldenB);
    text("RESTART", 570, 385, goldenR, goldenG, goldenB);
    text("QUIT TO MAIN MENU", 500, 285, goldenR, goldenG, goldenB);
    glFlush();
    glutSwapBuffers();
}
void Menu::drawend() {
    glClear(GL_COLOR_BUFFER_BIT);
    rectangleborder(100, 100, 1080, 530, brownR, brownG, brownB);
    rectangle(200, 620, 900, 60, brownR, brownG, brownB);
    for (int i = 0; i < 3; i++) {
        rectangle(otherRectangles[i][0], otherRectangles[i][1], otherRectangles[i][2], otherRectangles[i][3],
            brownR, brownG, brownB);
    }
    text("GAME OVER", 580, 640, goldenR, goldenG, goldenB);
    text("RETRY", 585, 485, goldenR, goldenG, goldenB);
    text("MAIN MENU", 560, 385, goldenR, goldenG, goldenB);
    text("QUIT", 590, 285, goldenR, goldenG, goldenB);

    glFlush();
    glutSwapBuffers();
}
void Menu::drawCircle(float cx, float cy, float radius, int numSegments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.14159f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
