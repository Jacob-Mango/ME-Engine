#pragma once

#include <vector>
#include <string>

#include <glm\\glm.hpp>

#include <glew\\glew.h>
#include <GLFW\\glfw3.h>

#define GUI_PANEL 0x0a
#define GUI_IMAGE 0x0b
#define GUI_BUTTON 0x0c
#define GUI_TEXTBOX 0x0d

namespace Rendering {
		class GUI {
		public:
			glm::vec3 m_Position;
			glm::vec3 m_Size;
			int m_Type = 0;
			std::string m_Text = "";
			GLuint m_BlendTexture = -1;
			GLuint m_TextureA = -1;
			GLuint m_TextureB = -1;
			GLuint m_TextureC = -1;

			std::vector<GUI*> m_GUIItems;

			GUI(glm::vec3 pos, glm::vec3 size, int type = GUI_PANEL) {
				m_Position = pos;
				m_Size = size;
				m_Type = type;
			}
			~GUI();

			void Update();
		};
}