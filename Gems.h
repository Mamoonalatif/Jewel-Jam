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
	void setx(float a) { x = a; }
	void sety(float b) { y = b; }
	int getX() const { return x; }
	int getY() const { return y; }
	string getType() const { return type; }

};
