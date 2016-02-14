#pragma once

#include <math.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <glew\glew.h>
#include <GLFW\glfw3.h>

#define T_SIZE 16
#define T_VERTEXCOUNT T_SIZE * 4

namespace Terrain {

	class Terrain {
	public:
		GLuint m_VAOID;
		unsigned int m_Size;
	private:
		glm::vec3 m_Position;
		glm::vec2 m_RelativePosition;

		float m_HeightMap[(int)(T_VERTEXCOUNT * T_VERTEXCOUNT)];
	public:
		Terrain(glm::vec2 relPos, float heightMap[T_VERTEXCOUNT * T_VERTEXCOUNT]);
		~Terrain();

		glm::vec3 GetPosition() {
			return m_Position;
		}

		glm::vec2 GetRelativePosition() {
			return m_RelativePosition;
		}
	private:
		void CreateModels();
	};

}