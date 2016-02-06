#pragma once

#include <glew\glew.h>
#include <GLFW\glfw3.h>

class FrameBuffer {
public:
	GLuint texture;
	GLuint depth;

	FrameBuffer();
	~FrameBuffer();
};

