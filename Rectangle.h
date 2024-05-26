#include "Gems.h"
class Rectangle : public Gems {
private:
    float width; 
    float height; 
public:
    Rectangle(float a, float b, float w, float h);
    void draw() override;
    void move() override;
};
