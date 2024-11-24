#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shaders.h"

static unsigned int createShader(GLenum shaderType, const char* path)
{
	// Load source code from file
	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Couldn't open file %s!\n", path);
		return 0;
	}

	// Get size of file in bytes
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	// Allocate fileSize bytes to source buffer
	char* source = malloc(fileSize);
	if (!source)
	{
		fprintf(stderr, "Failed to allocate memory for shader source for %s\n", path);
		return 0;
	}

	memset(source, 0, fileSize);

	// Read and save all information
	size_t out = fread(source, 1, fileSize, file);
	if (out > fileSize)
	{
		fprintf(stderr, "Failed to read contents of shader source from %s\n", path);
		free(source);
		return 0;
	}

	if (fclose(file))
	{
		fprintf(stderr, "Failed to close file %s\n", path);
	}

	// Load ogl shader
	unsigned int shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int  success;
	char exception[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, exception);
		fprintf(stderr, "Shader compilation for shader %s failed. Error output:\n", path);
		fprintf(stderr, "%s\n", exception);
		fprintf(stderr, "=== Shader Source Code ===\n%s\n=== Shader Source Code ===\n\n", source);
		free(source);
		return 0;
	}

	// Free memory for shader source
	free(source);
	return shader;
}

static unsigned int* createProgram(const char* vertexPath, const char* fragmentPath)
{
	unsigned int vertex = createShader(GL_VERTEX_SHADER, vertexPath);
	if (!vertex)
	{
		return 0;
	}

	unsigned int fragment = createShader(GL_FRAGMENT_SHADER, fragmentPath);
	if (!fragment)
	{
		return 0;
	}

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	int  success;
	char exception[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, exception);
		fprintf(stderr, "Shader linking for shaders [%s] failed. Error output:\n", vertexPath);
		fprintf(stderr, "%s\n", exception);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return program;
}

const struct shader Shader = {
	.createProgram = createProgram
};