#pragma once
#include <glad/GL.h>

struct shader
{
	unsigned int* (*createShader)(GLenum, const char*);
};

extern const struct shader Shader;