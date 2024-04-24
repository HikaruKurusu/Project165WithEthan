#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
class Paddle{
protected:
    float paddleSize = 0.8f;
    float paddleSpeed;
    float paddleX;
    float paddleY; 
    float initialY;
public:
    ~Paddle();

    virtual float getY() const = 0;

    virtual float getX() = 0;

    virtual float getSize() const = 0;

    virtual void draw_Paddle() = 0;

    virtual void resetPaddle() = 0;
};