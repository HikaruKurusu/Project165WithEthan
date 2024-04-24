#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
class Paddle{
public:
    ~Paddle();

    virtual float getY() const = 0;

    virtual float getX() const = 0;

    virtual float getSize() const = 0;

    virtual float getSpeed() const = 0;

    virtual void draw_Paddle() = 0;

    virtual void resetPaddle() = 0;
};