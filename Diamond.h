#include "Gems.h"
class Diamond : public Gems {
private:
    float size;
public:
    Diamond(float a, float b, float s);
    void draw() override;
    void move() override;
};
