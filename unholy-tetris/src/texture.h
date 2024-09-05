#pragma once

struct texture
{
	unsigned int* (*createTexture)(const char*);
};

extern const struct texture Texture;