#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
class Paddle{
public:
    Paddle(float speed, float posX, float posY);
    ~Paddle();

    virtual void draw_Paddle() = 0;

    virtual void resetPaddle() = 0;
};