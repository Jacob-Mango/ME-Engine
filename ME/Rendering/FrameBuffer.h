#pragma once

#include <glew\glew.h>
#include <GLFW\glfw3.h>

class FrameBuffer {
public:
	GLuint m_Buffer;
	GLuint m_Texture;
	GLuint m_DepthTexture;
	GLuint m_DepthBuffer;

	int m_Width;
	int m_Height;

	FrameBuffer(int width, int height);
	~FrameBuffer();

	void Bind();
	void UnBind(float width, float height);
};

