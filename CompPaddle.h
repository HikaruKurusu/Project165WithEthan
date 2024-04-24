#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "Paddle.h"
#include "Ball.h"
class CompPaddle: protected Paddle{
    float paddleSize = 0.8f;
    float paddleSpeed;
    float paddleX;
    float paddleY; 
    float initialY;
public:
    CompPaddle(float speed, float posX, float posY) {
        paddleSpeed = speed;
        paddleX = posX;
        paddleY = posY;
        initialY = posY;
    }
    ~CompPaddle() {}

    float getY() const {
        return paddleY;
    }

    float getX() const{
        return paddleX;
    }

    float getSize() const{
        return paddleSize;
    }

    void setY(float y){
        paddleY = y;
    }

    float getSpeed() const {
        return paddleSpeed;
    }

    void draw_Paddle() {
        glColor3f(1.0,1.0,1.0);
        glLineWidth(10);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glBegin(GL_QUADS);
            glVertex2f(paddleX - 0.05f, paddleY);
            glVertex2f(paddleX - (paddleSize/10.0f), paddleY);
            glVertex2f(paddleX - (paddleSize/10.0f), paddleY - paddleSize/2.0f);
            glVertex2f(paddleX - 0.05f, paddleY - paddleSize/2.0f);
        glEnd();
    }

    void resetPaddle() {
        paddleY = initialY;
    }

    void paddleLogic(Ball ball) {
        if (compPaddle.paddleY - compPaddle.paddleSize/4.0f > ball.getY() && compPaddle.paddleY - compPaddle.paddleSize/2.0f > -1.0f) {
            compPaddle.paddleY -= compPaddle.paddleSpeed;
            
        }
        if (compPaddle.paddleY - compPaddle.paddleSize/4.0f < ball.getY() && compPaddle.paddleY < 1.0f) {
            compPaddle.paddleY += compPaddle.paddleSpeed;
        }
    }
};