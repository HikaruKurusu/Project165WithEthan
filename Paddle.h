#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
class Paddle {
public:
    int paddleSize;
    float paddleSpeed = 0.005f;
    float paddleX = 0.0f;
    float paddleY = 0.0f;//change these to make it on edge of screen

    void draw_Paddle() {
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(paddleX, paddleY);
        glVertex2f(paddleX + paddleSize, paddleY);
        glVertex2f(paddleX + paddleSize, paddleY + paddleSize);
        glVertex2f(paddleX, paddleY + paddleSize);
        glEnd();
    }
};