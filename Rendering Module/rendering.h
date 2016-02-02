#pragma once

#include <vector>
#include <string>

#include <glm\glm.hpp>

#define RENDER_ENGINE OPENGL

#if RENDER_ENGINE == OPENGL
#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include "Shader.h"

namespace Rendering {
	class RenderModule {
	private:
		int m_Width;
		int m_Height;
		std::string m_Title;

		std::vector<GLuint> m_Models;
		std::vector<glm::mat4> m_ModelMatrices;
		std::vector<std::vector<glm::mat4>> m_ModelAnimMatrices;
	public:
		void LoadModels(std::vector<std::string> dirs);
		void LoadTextures(std::vector<std::string> dirs);

		void PrepareRender();
		void RenderWorld();
		void RenderPostProccessEffects();

		Shader* GetShader();
	};
}
#endif