#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
class Ball {
public:
    float ballRadius = 0.02f;
    float bSpeed = 0.005f;
    float ballX = 0.5f;
    float ballY = 0.5f;
    float ballVelX = bSpeed;
    float ballVelY = bSpeed;

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
};

