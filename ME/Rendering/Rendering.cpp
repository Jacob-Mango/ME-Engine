#include "rendering.h"

namespace Rendering {
	
	int RenderModule::CreateWindow(int width, int height, const char* title) {
		m_Title = title;
		m_Width = width;
		m_Height = height;
		m_CursorFocused = false;
		if (!glfwInit()) {
			return -1;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) {
			return -2;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0);

		if (glewInit() != GLEW_OK) {
			return -3;
		}
		return 0;
	}

	int RenderModule::LoadModels(std::vector<std::string> dirs) {
		return 0;
	}

	int RenderModule::LoadTextures(std::vector<std::string> dirs) {
		return 0;
	}

	void window_resize(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
		RenderModule* win = (RenderModule*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		RenderModule* win = (RenderModule*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		RenderModule* win = (RenderModule*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)	{
		RenderModule* win = (RenderModule*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}

	int RenderModule::PrepareRender() {
		glClearColor(0.9f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return 0;
	}

	int RenderModule::RenderWorld() {
		return 0;
	}

	int RenderModule::RenderPostProccessEffects() {
		return 0;
	}

	int RenderModule::EndRender() {
		for (int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);

		if (m_CursorFocused) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		} else {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			return -1;
		}
		return 0;
	}

	glm::vec2 RenderModule::GetMousePosition() const {
		return glm::vec2(mx, my);
	}

	bool RenderModule::IsCursorFocused() const {
		return m_CursorFocused;
	}

	void RenderModule::SetCursor(bool r) {
		m_CursorFocused = r;
	}
}