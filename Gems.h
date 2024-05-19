#pragma once
#include<glut.h>
#include<string>
using namespace std;
class Gems {
protected:
	float x = 100;
	float y = 100;
	string type;
public:
	Gems() : x(0), y(0), type("") {}
	Gems(float a, float b, string c) : x(a), y(b), type(c) {}
	virtual void move() = 0;
	virtual void draw() = 0;
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	int getX() const { return x; }
	int getY() const { return y; }
	string getType() const { return type; }

};

