#include "rendering.h"

namespace Rendering {
	
	int RenderModule::MakeWindow(int width, int height, const char* title) {
		m_Title = title;
		m_Width = width;
		m_Height = height;
		m_CursorFocused = false;
		m_Camera = new Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0));
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

		m_WorldShader = new Shader(ReadFile("Resources\\Shaders\\World.vs").c_str(), ReadFile("Resources\\Shaders\\World.fs").c_str());

		glEnable(GL_DEPTH_TEST);

		// glEnable(GL_CULL_FACE);
		// glCullFace(GL_FRONT);
		// glFrontFace(GL_CW);

		glEnable(GL_FRAMEBUFFER_SRGB);
		glEnable(GL_MULTISAMPLE);

		return 0;
	}

	int RenderModule::AddModel(const char* source) {
		m_Models.push_back(new Model(source));
		return 0;
	}

	bool RenderModule::IsKeyPressed(unsigned int keycode) const {
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool RenderModule::IsKeyTyped(unsigned int keycode) const {
		if (keycode >= MAX_KEYS)
			return false;
		return m_KeyTyped[keycode];
	}

	bool RenderModule::IsMouseButtonPressed(unsigned int button) const {
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseButtons[button];
	}

	bool RenderModule::IsMouseButtonClicked(unsigned int button) const {
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseClicked[button];
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
		win->mdx = win->mx - xpos;
		win->mdy = win->my - ypos;
		win->mx = xpos;
		win->my = ypos;
	}

	int RenderModule::PrepareRender() {
		m_ModelsToRender.clear();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return 0;
	}

	int RenderModule::RenderWorld() {
		m_WorldShader->Start();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, ToRadians(m_Camera->m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, ToRadians(m_Camera->m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, -m_Camera->m_Position);
		m_WorldShader->SetUniformMat4("view", view);
		m_WorldShader->SetUniformMat4("proj", glm::perspective(90.0f, (float)m_Width / (float)m_Height, 0.1f, 1000.0f));

		for (unsigned int i = 0; i < m_Models.size(); i++) {
				std::vector<glm::mat4> matrixes = m_ModelsToRender[m_Models[i]];
				for (unsigned int j = 0; j < matrixes.size(); j++) {
					m_WorldShader->SetUniformMat4("model", matrixes[j]);

					glBindVertexArray(m_Models[i]->GetVAOID());
					glEnableVertexAttribArray(0);
					glEnableVertexAttribArray(1);
					glEnableVertexAttribArray(2);

					glDrawArrays(GL_TRIANGLES, 0, m_Models[i]->GetSize());
				}
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);

		m_WorldShader->Stop();
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

	glm::vec2 RenderModule::GetMouseDelta() const {
		return glm::vec2(mdx, mdy);
	}

	bool RenderModule::IsCursorFocused() const {
		return m_CursorFocused;
	}

	void RenderModule::SetCursor(bool r) {
		m_CursorFocused = r;
	}

	Camera* RenderModule::GetCamera() {
		return m_Camera;
	}

	int RenderModule::AddModelToRender(int id, glm::mat4 trans) {
		m_ModelsToRender[m_Models[id]].push_back(trans);
		return 0;
	}

	glm::vec2 RenderModule::GetWindowSize() {
		return glm::vec2(m_Width, m_Height);
	}
}