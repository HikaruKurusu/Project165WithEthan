#include <iostream>
#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
// using namespace std;
#include <string>
#include <sstream>
#include <fstream>
#include "VAO.h"

// settings
unsigned int scrWidth = 800;
unsigned int scrHeight = 600;
const char* title = "Pong";
GLuint shaderProgram;

/*
	initialization methods
*/

// initialize GLFW
void initGLFW(unsigned int versionMajor, unsigned int versionMinor) {
	glfwInit();

	// pass in window params
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// macos specific parameter
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

// create window
void createWindow(GLFWwindow*& window, 
	const char* title, unsigned int width, unsigned int height, 
	GLFWframebuffersizefun framebufferSizeCallback) {
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

// load GLAD library
bool loadGlad() {
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

/*
	shader methods
*/

// read file
std::string readFile(const char* filename) {
	std::ifstream file;
	std::stringstream buf;

	std::string ret = "";

	// open file
	file.open(filename);

	if (file.is_open()) {
		// read buffer
		buf << file.rdbuf();
		ret = buf.str();
	}
	else {
		std::cout << "Could not open " << filename << std::endl;
	}

	// close file
	file.close();

	return ret;
}

// generate shader
int genShader(const char* filepath, GLenum type) {
	std::string shaderSrc = readFile(filepath);
	const GLchar* shader = shaderSrc.c_str();

	// build and compile shader
	int shaderObj = glCreateShader(type);
	glShaderSource(shaderObj, 1, &shader, NULL);
	glCompileShader(shaderObj);

	// check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
		std::cout << "Error in shader compilation: " << infoLog << std::endl;
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
