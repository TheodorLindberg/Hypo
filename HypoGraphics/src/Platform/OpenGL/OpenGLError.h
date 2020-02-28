#pragma once
#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLCrearError();\
	x;\
	HYPO_CORE_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "")

void GLCrearError();
bool GLLogCall(const char* function, const char* file, int line);

static void GLCrearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error] (" << error << "):" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
