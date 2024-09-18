#pragma once

// Headers
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// Method definitionsfsdfsdgfsedtgrgvbert
int init();
int postInit();

int loadTextures();
int loadShaders();

void tick();
void cleanup();

void errorCallback(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void frameBufferSizeChange(GLFWwindow* window, int width, int height);

// Typedef
typedef unsigned int* TextureBuffer;
typedef unsigned int* ShaderBuffer;
