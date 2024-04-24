#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "CompPaddle.h"
#ifndef MIDDLEPADDLE_H
#define MIDDLEPADDLE_H
class MiddlePaddle: public CompPaddle{
    float paddleSize = 0.8f;
    float paddleSpeed;
    float paddleX;
    float paddleY; 
    float initialY;
    bool movingDown = true;
public:
    MiddlePaddle(float speed, float posX, float posY) : CompPaddle(speed, posX, posY) {
    // Other initialization code for middlePaddle if needed
    }
    ~MiddlePaddle() {}
    void middleMovement(){
        if(paddleY - paddleSize/2.0f > -1.0f && movingDown) {
            std::cout << "moving up" << std::endl;
            paddleY -= 0.002f;
        } else if(paddleY < 1.0f) {
            std::cout << "moving down" << std::endl;
            if (!movingDown) {
                movingDown = !movingDown;
            }
            paddleY += 0.002f;
        }
        else {
            movingDown = !movingDown;
        }
    }
};
#endif