#include "iostream"
#include "dependencies/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "cmath"
#include "Ball.h"
#include "PlayerPaddle.h"
#include "CompPaddle.h"
#include "middlePaddle.h"
#include <string>
using namespace std;

int w = 800;
int h = 600;

Ball ball = Ball(0.02f, 0.003f, 0.0f, 0.0f, 0);
PlayerPaddle playerPaddle = PlayerPaddle(0.0039f, -0.95f, 0.15f);
CompPaddle compPaddle = CompPaddle(ball.getBSpeed()/3 * 2, -playerPaddle.getX(), playerPaddle.getY());
CompPaddle* middlePaddle = new MiddlePaddle(compPaddle.getSpeed(), 0, 0);




//window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && playerPaddle.getY() < 1.0f) {
        playerPaddle.setY(playerPaddle.getY() + playerPaddle.getSpeed());
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && playerPaddle.getY() - playerPaddle.getSize()/2.0f > -1.0f) {
        playerPaddle.setY(playerPaddle.getY() - playerPaddle.getSpeed());
    }
}

bool checkCollision(Ball ball, PlayerPaddle paddle, bool left) {
    float ballLeft = ball.getX() - ball.getRadius();
    float ballRight = ball.getX() + ball.getRadius();
    float ballTop = ball.getY() + ball.getRadius();
    float ballBottom = ball.getY() - ball.getRadius();

    float paddleLeft;
    float paddleRight;
    float paddleTop = paddle.getY();
    float paddleBottom = paddle.getY() - paddle.getSize()/2.0f;

    if(left){
        paddleLeft = paddle.getX() + 0.05f;
        paddleRight = paddle.getX() + (paddle.getSize()/10.0f);    
    }
    else {
        paddleLeft = paddle.getX() - 0.05f;
        paddleRight = paddle.getX() - (paddle.getSize()/10.0f);
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

bool checkCollision(Ball ball, CompPaddle paddle, bool left) {
    float ballLeft = ball.getX() - ball.getRadius();
    float ballRight = ball.getX() + ball.getRadius();
    float ballTop = ball.getY() + ball.getRadius();
    float ballBottom = ball.getY() - ball.getRadius();

    float paddleLeft;
    float paddleRight;
    float paddleTop = paddle.getY();
    float paddleBottom = paddle.getY() - paddle.getSize()/2.0f;

    if(left){
        paddleLeft = paddle.getX() + 0.05f;
        paddleRight = paddle.getX() + (paddle.getSize()/10.0f);    
    }
    else {
        paddleLeft = paddle.getX() - 0.05f;
        paddleRight = paddle.getX() - (paddle.getSize()/10.0f);
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

        // Update middle paddle position
        dynamic_cast<MiddlePaddle*>(middlePaddle)->middleMovement();
        


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
            ball.paddleBouncePlayer(playerPaddle);
        }
        if (checkCollision(ball, compPaddle, false)) {
            ball.paddleBounceComp(compPaddle);
        } // test

        // computer paddle logic
        if (compPaddle.getY() - compPaddle.getSize()/4.0f > ball.getY() && compPaddle.getY() - compPaddle.getSize()/2.0f > -1.0f) {
            compPaddle.setY(compPaddle.getY() - compPaddle.getSpeed());
            
        }
        if (compPaddle.getY() - compPaddle.getSize()/4.0f < ball.getY() && compPaddle.getY() < 1.0f) {
            compPaddle.setY(compPaddle.getY() + compPaddle.getSpeed());
        }

        //move middle paddle
        if (checkCollision(ball, *middlePaddle, false)) {
            ball.paddleBounceComp(*middlePaddle);
        } // test
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        ball.draw_ball();
        playerPaddle.draw_Paddle();
        compPaddle.draw_Paddle();
        middlePaddle->draw_Paddle();
        drawLineDownMiddle();
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

