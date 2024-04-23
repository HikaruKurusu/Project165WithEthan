#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "Paddle.h"
class Ball {
    float ballRadius = 0.02f;
    float bSpeed = 0.003f;
    float ballX = 0.0f;
    float ballY = 0.0f;
    float ballVelX = -bSpeed;
    float ballVelY = 0;
    bool swapDirection = true;
public:
    float getBSpeed() {
        return bSpeed;
    }

    float getX() {
        return ballX;
    }

    float getY() {
        return ballY;
    }

    float getRadius() {
        return ballRadius;
    }

    float getVelY() {
        return ballVelY;
    }

    void setVelY(float v) {
        ballVelY = v;
    }

    void updateVel() {
        ballX += ballVelX;
        ballY += ballVelY;
    }


    void draw_ball() {
        int numSegments = 100;
        float angleIncrement = 2 * M_PI / numSegments;
        float angle;
        float x;
        float y;
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f); //change color
        for (int i = 0; i <= numSegments; i++) {
            angle = i * angleIncrement;
            x = ballX + ballRadius * cos(angle);
            y = ballY + ballRadius * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }

    void paddleBounce(Paddle paddle) {
        float ballBottom = ballY - ballRadius;

        float paddleTop = paddle.paddleY;
        float paddleHeight = paddle.paddleSize/2.0f;

        float paddleRangeUpper = paddleTop - paddleHeight / 3.0f;
	    float paddleRangeMiddle = paddleTop - (paddleHeight * 2.0f) / 3.0f;

        if (ballBottom > paddleRangeUpper){
            ballVelY = 0.75f * bSpeed;
            ballVelX = -ballVelX;
        }
        else if (ballBottom > paddleRangeMiddle) {
            ballVelX = -ballVelX;
        }
        else {
            ballVelY = -0.75f * bSpeed;
            ballVelX = -ballVelX;
        }
        bSpeed += 0.0001f;
    }

    void resetBall() {
        ballX = 0.0f;
        ballY = 0.0f;
        if (swapDirection) {
            bSpeed = 0.003f;
            ballVelX = bSpeed;
            swapDirection = !swapDirection;
            
        }
        else {
            bSpeed = 0.003f;
            ballVelX = -bSpeed;
            swapDirection = !swapDirection;

            
        }
        ballVelY = 0.0f;
    }
};

