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
    bool movingDown = true;
public:
    MiddlePaddle(float speed, float posX, float posY) : CompPaddle(speed, posX, posY) {
    // Other initialization code for middlePaddle if needed
        paddleSpeed = speed;
        paddleX = posX;
        paddleY = posY;
    }
    ~MiddlePaddle() {}
    void middleMovement(){
        if(getY() - getSize()/2.0f > -1.0f && movingDown) {
            setY(getY() - 0.002f);
        } else if(getY() < 1.0f) {
            if (movingDown) {
                movingDown = !movingDown;
            }
            setY(getY() + 0.002f);
        }
        else {
            movingDown = !movingDown;
        }
    }
};
#endif