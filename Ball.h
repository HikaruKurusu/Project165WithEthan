#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "PlayerPaddle.h"
#include "CompPaddle.h"
class Ball {
    float ballRadius;
    float bSpeed;
    float ballX;
    float ballY;
    float ballVelX;
    float ballVelY;
    bool swapDirection;
public:

    Ball(float radius, float speed, float x, float y, float velY) {
        ballRadius = radius;
        bSpeed = speed;
        ballX = x;
        ballY = y;
        ballVelX = -speed;
        ballVelY = velY;
        swapDirection = true;
    }
    ~Ball() {}

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

    float getVelX() {
        return ballVelX;
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

    void paddleBouncePlayer(const PlayerPaddle& paddle) {
        float ballBottom = ballY - ballRadius;

        float paddleTop = paddle.getY();
        float paddleHeight = paddle.getSize()/2.0f;

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
        if(ballVelX < 0)
            ballVelX -= 0.0001f;
        else
            ballVelX += 0.0001f;
    }

    void paddleBounceComp(const CompPaddle& paddle) {
        float ballBottom = ballY - ballRadius;

        float paddleTop = paddle.getY();
        float paddleHeight = paddle.getSize()/2.0f;

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
        if(ballVelX < 0)
            ballVelX -= 0.0001f;
        else
            ballVelX += 0.0001f;
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

