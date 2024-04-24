#include "iostream"
#include "dependencies/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "cmath"
#include "Ball.h"
#include <string> 
using namespace std;

int w = 800;
int h = 600;

Ball ball = Ball(0.02f, 0.003f, 0.0f, 0.0f, 0);
Paddle playerPaddle = Paddle(0.0039f, -0.95f, 0.15f);
Paddle compPaddle = Paddle(ball.getBSpeed()/3 * 2, -playerPaddle.paddleX, playerPaddle.paddleY);

//window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && playerPaddle.paddleY < 1.0f) {
        playerPaddle.paddleY += playerPaddle.paddleSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && playerPaddle.paddleY - playerPaddle.paddleSize/2.0f > -1.0f) {
        playerPaddle.paddleY -= playerPaddle.paddleSpeed;
    }
}

bool checkCollision(Ball ball, Paddle paddle, bool left) {
    float ballLeft = ball.getX() - ball.getRadius();
    float ballRight = ball.getX() + ball.getRadius();
    float ballTop = ball.getY() + ball.getRadius();
    float ballBottom = ball.getY() - ball.getRadius();

    float paddleLeft;
    float paddleRight;
    float paddleTop = paddle.paddleY;
    float paddleBottom = paddle.paddleY - paddle.paddleSize/2.0f;

    if(left){
        paddleLeft = paddle.paddleX + 0.05f;
        paddleRight = paddle.paddleX + (paddle.paddleSize/10.0f);    
    }
    else {
        paddleLeft = paddle.paddleX - 0.05f;
        paddleRight = paddle.paddleX - (paddle.paddleSize/10.0f);
    }
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
void drawLineDownMiddle() {
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(5); // Adjust the line width if needed

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_QUADS);
        // Vertical part of 1 (scaled down by 0.25)
        glVertex2f(0.0f, 1.2f);   // Top-left
        glVertex2f(0.003f, 1.2f); // Top-right
        glVertex2f(0.003f, -1.2f); // Bottom-right
        glVertex2f(0.0f, -1.2f);  // Bottom-left
    glEnd();
}


int main() {
        int AICount = 0;
        int playerCount = 0;
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
        ball.updateVel();


        // Bounce off the walls and paddles
        if (ball.getX() + ball.getRadius() >= 1.0f) {
            ball.resetBall();
            playerPaddle.resetPaddle();
            compPaddle.resetPaddle();
            playerCount++;
            std::cout<<"PLAYER WINS" << " " << playerCount <<std::endl;
            if(playerCount == 5) {
                cout<<"Player WINS!!!!" <<endl;
                glfwTerminate();
                return -1;
            }
            
        } else if(ball.getX() - ball.getRadius() <= -1.0f) {
            ball.resetBall();
            playerPaddle.resetPaddle();
            compPaddle.resetPaddle();
            AICount++;
            std::cout<<"AI Score" << " " << AICount <<std::endl;
            if(AICount == 5) {
                cout<<"AI WINS!!!!" <<endl;
                glfwTerminate();
                return -1;
            }
        }
        if (ball.getY() + ball.getRadius() >= 1.0f || ball.getY() - ball.getRadius() <= -1.0f) {
            ball.setVelY(-ball.getVelY());
        }
        if (checkCollision(ball, playerPaddle, true)) {
            ball.paddleBounce(playerPaddle);
        }
        if (checkCollision(ball, compPaddle, false)) {
            ball.paddleBounce(compPaddle);
        }

        // computer paddle logic
        if (compPaddle.paddleY - compPaddle.paddleSize/4.0f > ball.getY() && compPaddle.paddleY - compPaddle.paddleSize/2.0f > -1.0f) {
            compPaddle.paddleY -= compPaddle.paddleSpeed;
            
        }
        if (compPaddle.paddleY - compPaddle.paddleSize/4.0f < ball.getY() && compPaddle.paddleY < 1.0f) {
            compPaddle.paddleY += compPaddle.paddleSpeed;
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        ball.draw_ball();
        playerPaddle.draw_Paddle_left();
        compPaddle.draw_Paddle_right();
        drawLineDownMiddle();
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

