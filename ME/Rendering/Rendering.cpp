#include "rendering.h"

namespace Rendering {
	
	int RenderModule::MakeWindow(int width, int height, const char* title) {
		printf("Gets here 1");

		m_Title = title;
		m_Width = width;
		m_Height = height;
		m_CursorFocused = false;
		m_Camera = new Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0));
		if (!glfwInit()) {
			return -1;
		}
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


		printf("Gets here 2");

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) {
			return -2;
		}


		printf("Gets here 3");
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetWindowCloseCallback(m_Window, window_close_callback);
		glfwSetWindowFocusCallback(m_Window, window_loss_focus_callback);
		glfwSwapInterval(0);

		printf("Gets here 4");
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			return -3;
		}
		printf("Gets here 5");

		m_WorldShader = new Shader(ReadFile("Resources\\Shaders\\World.vs").c_str(), ReadFile("Resources\\Shaders\\World.fs").c_str());
		m_PPShader = new Shader(ReadFile("Resources\\Shaders\\PP.vs").c_str(), ReadFile("Resources\\Shaders\\PP.fs").c_str());
		m_GUIShader = new Shader(ReadFile("Resources\\Shaders\\GUI.vs").c_str(), ReadFile("Resources\\Shaders\\GUI.fs").c_str());

		m_PPBuffer = new FrameBuffer(1280, 720);

		glEnable(GL_DEPTH_TEST);

		// glEnable(GL_CULL_FACE);
		// glCullFace(GL_FRONT);
		// glFrontFace(GL_CW);

		glEnable(GL_FRAMEBUFFER_SRGB);
		glEnable(GL_MULTISAMPLE);


		printf("Gets here 6");
		m_GUI = new GUI(glm::vec3(0), glm::vec3(0));

		glGenVertexArrays(1, &m_SquareModelID);
		glBindVertexArray(m_SquareModelID);

		GLfloat vertices[] = {
			0.0f, 1.0f, 0.0f, 
			0.0f, 0.0f, 0.0f, 
			1.0f, 0.0f, 0.0f, 
			1.0f, 1.0f, 0.0f
		}; 

		GLfloat textures[] = {
			0.0f, 1.0f, 
			0.0f, 0.0f, 
			1.0f, 0.0f, 
			1.0f, 1.0f
		};

		m_SquareModelSize = sizeof(vertices) / sizeof(vertices[0]);
		
		GLuint vboID;

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

		glBindVertexArray(0);
		
		m_TerrainTexture = new Texture("Resources\\Data\\1\\1.png");

		return 0;
	}

	int RenderModule::AddModel(const char* source) {
		Model* m = new Model(source);
		if (m->GetSize() > 0) m_Models.push_back(m);
		return 0;
	}

	int RenderModule::AddTexture(const char* source) {	
		Texture* text = new Texture(source);
		m_Textures.push_back(text);
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

		win->m_PPBuffer = new FrameBuffer(width, height);
	}

	void window_close_callback(GLFWwindow *window) {
		RenderModule* win = (RenderModule*)glfwGetWindowUserPointer(window);
		win->Close();
	}

	void window_loss_focus_callback(GLFWwindow* window, int focused) {
		RenderModule* win = (RenderModule*)glfwGetWindowUserPointer(window);
		if (win->m_CursorFocused == true) {
			if (focused == false) win->m_CursorFocused = false;
		}
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

	int RenderModule::RenderWorld(std::vector<Terrain::Terrain*> m_Terrains) {
		// m_PPBuffer->Bind();
		m_WorldShader->Start();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, ToRadians(m_Camera->m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, ToRadians(m_Camera->m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, m_Camera->m_Position);
		m_WorldShader->SetUniformMat4("view", view);
		m_WorldShader->SetUniformMat4("proj", glm::perspective(ToRadians(90.0f), ((float)(m_Width * 1.0f) / (float)(m_Height * 1.0f)), 0.1f, 1000.0f));

		for (unsigned int i = 0; i < m_Models.size(); i++) {
			if (m_Models[i]->GetVAOID() == 3452816845) continue;

			m_Textures[i]->Bind(0);

			std::vector<glm::mat4> matrixes = m_ModelsToRender[m_Models[i]];
			if (matrixes.size() != 0) for (unsigned int j = 0; j < matrixes.size(); j++) {
				m_WorldShader->SetUniformMat4("model", matrixes[j]);

				glBindVertexArray(m_Models[i]->GetVAOID());
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);

				// glDrawElements(GL_TRIANGLES, m_Models[i]->GetSize(), GL_UNSIGNED_INT, 0);

				glDrawArrays(GL_TRIANGLES, 0, m_Models[i]->GetSize());
			}
		}

		for (unsigned int i = 0; i < m_Terrains.size(); i++) {
			Terrain::Terrain* t = m_Terrains[i];
			if (t != nullptr) {
				float d = glm::distance(t->GetPosition(), m_Camera->m_Position);
				m_WorldShader->SetUniformMat4("model", glm::translate(glm::mat4(1.0), t->GetPosition()));
				glBindVertexArray(t->m_VAOID);
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);

				m_TerrainTexture->Bind(0);

				glDrawElements(GL_TRIANGLES, t->m_Size, GL_UNSIGNED_INT, 0);
			}
		}
		glBindVertexArray(0);

		m_WorldShader->Stop();
		m_PPBuffer->UnBind(m_Width, m_Height);
		return 0;
	}

	int RenderModule::RenderPostProccessEffects() {
		m_PPShader->Start();

		float aspect = (float)m_Width / (float)m_Height;
		m_PPShader->SetUniformMat4("proj", glm::ortho(-aspect, aspect, -1.0f, 1.0f, 1.0f, -1.0f));


		glBindVertexArray(m_SquareModelID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glm::mat4 m = glm::mat4(1.0);
		glm::translate(m, glm::vec3(-aspect, 0, 0));
		glm::scale(m, glm::vec3(1 + aspect, 2, 1));
		m_PPShader->SetUniformMat4("model", m);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE0, m_PPBuffer->m_Texture);

		// glDrawArrays(GL_QUADS, 0, m_SquareModelSize);
		
		glBindVertexArray(0);
		m_PPShader->Stop();
		return 0;
	}

	int RenderModule::RenderGUI() {
		m_GUIShader->Start();

		float aspect = (float)m_Width / (float)m_Height;
		m_GUIShader->SetUniformMat4("proj", glm::ortho(-aspect, aspect, -1.0f, 1.0f, 1.0f, -1.0f));

		glBindVertexArray(m_SquareModelID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		for (unsigned int i = 0; i < m_GUI->m_GUIItems.size(); i++) {
			
			
			glm::mat4 m = glm::mat4(1.0);
		   	glm::translate(m, m_GUI->m_GUIItems[i]->m_Position);
			glm::scale(m, m_GUI->m_GUIItems[i]->m_Size);
			m_WorldShader->SetUniformMat4("model", m);


			glDrawElements(GL_QUADS, m_SquareModelSize, GL_UNSIGNED_INT, 0);
			
		}
		glBindVertexArray(0);


		m_GUIShader->Stop();
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

	GUI* RenderModule::GetGUI() {
		return m_GUI;
	}

	void RenderModule::SetGUI(GUI* gui) {
		m_GUI = gui;
	}

	int RenderModule::AddModelToRender(int id, glm::mat4 trans) {
		m_ModelsToRender[m_Models[id]].push_back(trans);
		return 0;
	}

	int RenderModule::AddModelToRender(int id, glm::vec3 position, glm::quat rotation, glm::vec3 scale) {
		glm::mat4 identity = glm::mat4(1.0);
		glm::mat4 translation = glm::translate(identity, position);
		glm::mat4 rot = glm::mat4_cast(rotation);
		glm::mat4 scal = glm::scale(identity, scale);

		return AddModelToRender(id, translation * rot * scal);
	}

	glm::vec2 RenderModule::GetWindowSize() {
		return glm::vec2(m_Width, m_Height);
	}
}