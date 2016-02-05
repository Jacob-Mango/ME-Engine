#pragma once

#include <vector>
#include <string>

#include <glm\glm.hpp>

#define RENDER_ENGINE_OPENGL
#define MAX_KEYS		1024
#define MAX_BUTTONS		32

#ifdef RENDER_ENGINE_OPENGL
#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include "GLShader.h"

namespace Rendering {
	class RenderModule {
	private:
		int m_Width;
		int m_Height;
		const char* m_Title;
		GLFWwindow* m_Window;

		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		double mx, my;
		bool m_CursorFocused;

		std::vector<GLuint> m_Models;
		std::vector<glm::mat4> m_ModelMatrices;
		std::vector<std::vector<glm::mat4>> m_ModelAnimMatrices;
	public:
		int CreateWindow(int width, int height, const char* title);

		int LoadModels(std::vector<std::string> dirs);
		int LoadTextures(std::vector<std::string> dirs);

		int PrepareRender();
		int RenderWorld();
		int RenderPostProccessEffects();
		int EndRender();

		Shader* GetShader();

		glm::vec2 GetMousePosition() const;
		bool IsCursorFocused() const;
		void SetCursor(bool r);
	private:
		friend void window_resize(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};
}
#endif

#ifdef RENDER_ENGINE_DIRECTX
namespace Rendering {
	class RenderModule {
	}
}
#endif