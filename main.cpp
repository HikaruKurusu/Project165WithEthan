#include "iostream"
#include "dependencies/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "cmath"
#include "Ball.h"
#include "Paddle.h"
using namespace std;

int w = 800;
int h = 600;

Ball ball;
Paddle paddle;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && paddle.paddleY < 1.0f) {
        paddle.paddleY += paddle.paddleSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && paddle.paddleY - paddle.paddleSize/2.0f > -1.0f) {
        //cout << paddle.paddleY << endl;
        paddle.paddleY -= paddle.paddleSpeed;
    }
}

bool checkCollision(Ball ball, Paddle paddle) {
    float ballLeft = ball.ballX - ball.ballRadius;
    float ballRight = ball.ballX + ball.ballRadius;
    float ballTop = ball.ballY + ball.ballRadius;
    float ballBottom = ball.ballY - ball.ballRadius;

    float paddleLeft = paddle.paddleX + 0.05f;
    float paddleRight = paddle.paddleX + (paddle.paddleSize/10.0f);
    float paddleTop = paddle.paddleY;
    float paddleBottom = paddle.paddleY - paddle.paddleSize/2.0f;
    if (ballLeft >= paddleRight) {
		return false;
	}
	if (ballRight <= paddleLeft) {
		return false;
	}
	if (ballTop <= paddleBottom) {
		return false;
	}
	if (ballBottom >= paddleTop) {
		return false;
	}
	return true;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(w, h, "Pong", NULL, NULL);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Input handling
        process_input(window);

        // Update ball position
        ball.ballX += ball.ballVelX;
        ball.ballY += ball.ballVelY;


        // Bounce off the walls and paddles
        if (ball.ballX + ball.ballRadius >= 1.0f || ball.ballX - ball.ballRadius <= -1.0f) {
            ball.ballVelX = -ball.ballVelX;
        }
        if (ball.ballY + ball.ballRadius >= 1.0f || ball.ballY - ball.ballRadius <= -1.0f) {
            ball.ballVelY = -ball.ballVelY;
        }
        if (checkCollision(ball, paddle)) {
            ball.ballVelX = -ball.ballVelX;
        }
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);


        ball.draw_ball();
        paddle.draw_Paddle();
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}