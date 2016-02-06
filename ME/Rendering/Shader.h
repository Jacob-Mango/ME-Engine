#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <glew\glew.h>
#include <GLFW\glfw3.h>

namespace Rendering {

	class Shader {
	private:
		const char* m_VertSrc;
		const char* m_FragSrc;
		GLuint m_ShaderID;
		GLuint m_VertID;
		GLuint m_FragID;
	public:
		Shader(const char* vert, const char* frag);
		~Shader();

		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1fv(const GLchar* name, float* value, int count);
		void SetUniform1i(const GLchar* name, int value);
		void SetUniform1iv(const GLchar* name, int* value, int count);
		void SetUniform2f(const GLchar* name, const glm::vec2& vector);
		void SetUniform3f(const GLchar* name, const glm::vec3& vector);
		void SetUniform4f(const GLchar* name, const glm::vec4& vector);
		void SetUniformMat4(const GLchar* name, const glm::mat4& matrix);

		void Start() const;
		void Stop() const;
	private:
		GLint GetUniformLocation(const GLchar* name);
	};

}