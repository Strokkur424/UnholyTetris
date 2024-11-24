#pragma once
#include <glad/GL.h>

struct shader
{
	unsigned int* (*createProgram)(const char*, const char*);
};

extern const struct shader Shader;