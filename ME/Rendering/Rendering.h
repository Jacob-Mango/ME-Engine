#pragma once

#define MAX_KEYS		1024
#define MAX_BUTTONS		32

#define M_PI 3.14159265358979323846

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include "Shader.h"
#include "Model.h"
#include "..\Utils\File.h"

static float ToRadians(float r) {
	return r / 180 * (float) M_PI;
}

namespace Rendering {

	struct Camera {
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

		Camera(glm::vec3 position, glm::vec3 rotation) {
			m_Position = position;
			m_Rotation = rotation;
		}
	};

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
		double mdx, mdy;
		bool m_CursorFocused;

		std::vector<Model*> m_Models;
		std::unordered_map<Model*, std::vector<glm::mat4>> m_ModelsToRender;

		Shader* m_WorldShader; 
		Shader* m_PPShader;
		Camera* m_Camera;
	public:
		int MakeWindow(int width, int height, const char* title);

		int AddModel(const char* source);
		int AddModelToRender(int id, glm::mat4 trans);

		int PrepareRender();
		int RenderWorld();
		int RenderPostProccessEffects();
		int EndRender();

		Camera* GetCamera();

		glm::vec2 GetWindowSize();

		bool IsKeyPressed(unsigned int keycode) const;
		bool IsKeyTyped(unsigned int keycode) const;
		bool IsMouseButtonPressed(unsigned int button) const;
		bool IsMouseButtonClicked(unsigned int button) const;
		glm::vec2 GetMousePosition() const; 
		glm::vec2 GetMouseDelta() const;
		bool IsCursorFocused() const;
		void SetCursor(bool r);
	private:
		friend void window_resize(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};
}