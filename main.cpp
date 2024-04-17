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


        // Bounce off the walls
        if (ball.ballX + ball.ballRadius >= 1.0f || ball.ballX - ball.ballRadius <= -1.0f) {
            ball.ballVelX = -ball.ballVelX;
        }
        if (ball.ballY + ball.ballRadius >= 1.0f || ball.ballY - ball.ballRadius <= -1.0f) {
            ball.ballVelY = -ball.ballVelY;
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);


        ball.draw_ball();
        // paddle.draw_Paddle();
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}