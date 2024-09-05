#include <stdio.h>

#include <glad/gl.h>

#include "main.h"
#include "texture.h"
#include "shaders.h"

// Constants
const char* title = "Unholy Tetris";

// Variables
GLFWwindow* window;

uint32_t width = 640;
uint32_t height = 480;

// Textures
TextureBuffer blockRed = 0;
TextureBuffer blockOrange = 0;
TextureBuffer blockYellow = 0;
TextureBuffer blockGreen = 0;
TextureBuffer blockCyan = 0;
TextureBuffer blockBlue = 0;
TextureBuffer blockPurple = 0;
TextureBuffer blockMagenta = 0;

// Shaders
ShaderBuffer basicVertex = 0;
ShaderBuffer basicFragment = 0;


// Main method
int main()
{

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to intialize glfw - Terminating...\n");
		return -1;
	}

	if (!init()) 
	{
		return -1;
	}

	if (!postInit())
	{
		return -1;
	}

	while (!glfwWindowShouldClose(window)) 
	{
		tick(); 
	}

	cleanup();
	glfwTerminate();
}

// Logical methods
int init()
{
	glfwSetErrorCallback(errorCallback);

	// Window Hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to create window... terminating\n");
		return 0;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	glfwSetKeyCallback(window, keyCallback);

	return 1;
}

int postInit()
{
	if (!loadTextures())
	{
		return 0;
	}

	if (!loadShaders())
	{
		return 0;
	}
}

int loadTextures()
{
	if (!(blockRed = Texture.createTexture("assets/blocks/Red.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: red");
		return 0;
	}

	if (!(blockOrange = Texture.createTexture("assets/blocks/Orange.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: orange");
		return 0;
	}

	if (!(blockYellow = Texture.createTexture("assets/blocks/Yellow.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: yellow");
		return 0;
	}

	if (!(blockGreen = Texture.createTexture("assets/blocks/Green.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: green");
		return 0;
	}

	if (!(blockCyan = Texture.createTexture("assets/blocks/Cyan.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: cyan");
		return 0;
	}

	if (!(blockBlue = Texture.createTexture("assets/blocks/Blue.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: blue");
		return 0;
	}

	if (!(blockPurple = Texture.createTexture("assets/blocks/Purple.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: purple");
		return 0;
	}

	if (!(blockMagenta = Texture.createTexture("assets/blocks/Magenta.png")))
	{
		fprintf(stderr, "Failed to load texture for block with color: magenta");
		return 0;
	}
}

int loadShaders()
{
	if (!(basicVertex = Shader.createShader(GL_VERTEX_SHADER, "assets/shaders/basic_vertex.vert")))
	{
		return 0;
	}

	if (!(basicFragment = Shader.createShader(GL_FRAGMENT_SHADER, "assets/shaders/basic_fragment.frag")))
	{
		return 0;
	}
}

void tick()
{
	glfwPollEvents();

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(0x040204);
	glfwSwapBuffers(window);
}


void cleanup()
{
	glfwDestroyWindow(window);
}

void errorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (action != GLFW_PRESS && action != GLFW_REPEAT)
	{
		return;
	}

	switch (key)
	{
	case GLFW_KEY_UP:
		printf("Pressed the 'up' key!\n");
		break;


	case GLFW_KEY_DOWN:
		printf("Pressed the 'down' key!\n");
		break;


	case GLFW_KEY_LEFT:
		printf("Pressed the 'left' key!\n");
		break;


	case GLFW_KEY_RIGHT:
		printf("Pressed the 'right' key!\n");
		break;

	case GLFW_KEY_SPACE:
		printf("Pressed the 'space' key!\n");
		break;

	default:
		break;
	}
}

void frameBufferSizeChange(GLFWwindow* window, int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
}