#include "Shader.h"

namespace Rendering {

	Shader::Shader(const char* vertSrc, const char* fragSrc) : m_VertSrc(vertSrc), m_FragSrc(fragSrc) {
		m_ShaderID = glCreateProgram();
		m_VertID = glCreateShader(GL_VERTEX_SHADER);
		m_FragID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(m_VertID, 1, &vertSrc, NULL);
		glCompileShader(m_VertID);

		GLint result;
		glGetShaderiv(m_VertID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(m_VertID, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(m_VertID, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
			glDeleteShader(m_VertID);
		}

		glShaderSource(m_FragID, 1, &fragSrc, NULL);
		glCompileShader(m_FragID);

		glGetShaderiv(m_FragID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(m_FragID, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(m_FragID, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
			glDeleteShader(m_FragID);
		}

		glAttachShader(m_ShaderID, m_VertID);
		glAttachShader(m_ShaderID, m_FragID);

		glLinkProgram(m_ShaderID);
		glValidateProgram(m_ShaderID);
	}

	Shader::~Shader() {
		glDeleteShader(m_VertID);
		glDeleteShader(m_FragID);
		glDeleteProgram(m_ShaderID);
	}

	GLint Shader::GetUniformLocation(const GLchar* name) {
		GLint result = glGetUniformLocation(m_ShaderID, name);
		if (result == -1)
			std::cout << "Uniform " << name << " could not be found!" << std::endl;

		return result;
	}

	void Shader::SetUniform1f(const GLchar* name, float value) {
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const GLchar* name, float* value, int count) {
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const GLchar* name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const GLchar* name, int* value, int count) {
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const GLchar* name, const glm::vec2& vector) {
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniform3f(const GLchar* name, const glm::vec3& vector) {
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const GLchar* name, const glm::vec4& vector) {
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat4(const GLchar* name, const glm::mat4& matrix) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::Start() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::Stop() const {
		glUseProgram(0);
	}
}