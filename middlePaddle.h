#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "compPaddle.h"
#ifndef MIDDLEPADDLE_H
#define MIDDLEPADDLE_H
class middlePaddle: protected CompPaddle{
    float paddleSize = 0.8f;
    float paddleSpeed;
    float paddleX;
    float paddleY; 
    float initialY;
public:
    middlePaddle(float speed, float posX, float posY) : CompPaddle(speed, posX, posY) {
    // Other initialization code for middlePaddle if needed
    }
    ~middlePaddle() {}
    void middleMovement(){
        if(paddleY - paddleSize/2.0f > -1.0f) {
            paddleY -= 10;
        } else if(paddleY < 1.0f) {
            paddleY += 10;
        }
    }
};
#endif