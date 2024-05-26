#pragma once
#include <GL/glut.h>
#include <string>
#include<cmath>
#include<cstdlib>
using namespace std;
class Menu {
public:
    double Mainmenurectangles[4][7] = {
        {240, 450, 400, 60, 0.102, 0.306, 0.596},
        {240, 350, 400, 60, 0.102, 0.306, 0.596},
        {240, 250, 400, 60, 0.102, 0.306, 0.596},
        {240, 150, 400, 60,  0.102, 0.306, 0.59}
    };
    float otherRectangles[3][4] = {
        {290, 470, 700, 60},
        {290, 370, 700, 60},
        {290, 270, 700, 60}
    };
    float brownR = 0.545f, brownG = 0.271f, brownB = 0.075f;
    float goldenR = 1.0f, goldenG = 0.843f, goldenB = 0.0f;
    void rectangleborder(float x, float y, float width, float height, float red, float green, float blue);
    void rectangle(float x, float y, float width, float height, float red, float green, float blue);
    void text(const string& text, float x, float y, float red, float green, float blue);
    void drawMainMenu();
    void drawPauseMenu();
    void drawend();
    void drawCircle(float, float,float, int);
};
