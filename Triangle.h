#include "Gems.h"
class Triangle : public Gems {
private:
    float size; 
public:
    Triangle(float a, float b, float s);
    void draw() override;
    void move() override;
};
