#pragma once

#include <glew\glew.h>
#include <GLFW\glfw3.h>

namespace Rendering {

	class Texture {
	private:
		GLuint m_ID;
	public:
		Texture(GLuint id);
		Texture(const char* file);
		~Texture();

		GLuint GetID() {
			return m_ID;
		}

		void Bind(int s);
	};

}