#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

class compPaddle {
    public:
        float paddleSize = 0.8f;
        float paddleSpeed;
        float paddleX;
        float paddleY;//change these to make it on edge of screen
        float initialY;
};