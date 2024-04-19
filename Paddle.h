#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
class Paddle {
public:
    float paddleSize = 0.8f;
    float paddleSpeed = 0.005f;
    float paddleX = -0.95f;
    float paddleY = 0.15f;//change these to make it on edge of screen

    void draw_Paddle() {
        glColor3f(1.0,1.0,1.0);
        glLineWidth(10);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glBegin(GL_QUADS);
            glVertex2f(paddleX + 0.05f, paddleY);
            glVertex2f(paddleX + (paddleSize/10.0f), paddleY);
            glVertex2f(paddleX + (paddleSize/10.0f), paddleY - paddleSize/2.0f);
            glVertex2f(paddleX + 0.05f, paddleY - paddleSize/2.0f);
        glEnd();
    }
};