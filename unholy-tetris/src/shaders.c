#include <stdio.h>
#include <stdlib.h>

#include "shaders.h"

static unsigned int* createShader(GLenum shaderType, const char* path)
{
	// Load source code from file
	FILE* file = fopen(path, "r");

	if (!file)
	{
		fprintf(stderr, "File %s not found!", path);
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	char* source;
	if (!(source = malloc(fileSize + 1))) 
	{
		fprintf(stderr, "Failed to allocate memory for shader source for %s", path);
		return 0;
	}

	if (!fread(source, fileSize, 1, file))
	{
		fprintf(stderr, "Failed to read contents of shader source from %s", path);
		free(source);
		return 0;
	}

	if (!fclose(file)) {
		fprintf(stderr, "Failed to close file %s", path);
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
		fprintf(stderr, exception);
	}

	// Free memory for shader source
	free(source);
}

const struct shader Shader = {
	.createShader = createShader
};