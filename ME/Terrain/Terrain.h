#pragma once

#include <math.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <glew\glew.h>
#include <GLFW\glfw3.h>

#define T_SIZE 64
#define T_VERTEXCOUNT 64 * 4
#define T_FRAGMENTS 16

namespace Terrain {

	class Terrain {
	public:
		GLuint lod0[T_FRAGMENTS];
		GLuint lod1[T_FRAGMENTS];
		GLuint lod2[T_FRAGMENTS];

		GLuint sizes0[T_FRAGMENTS];
		GLuint sizes1[T_FRAGMENTS];
		GLuint sizes2[T_FRAGMENTS];
	private:
		glm::vec3 m_Position;
		glm::vec2 m_RelativePosition;

		float m_HeightMap[T_FRAGMENTS][(int)(T_VERTEXCOUNT / T_FRAGMENTS) * (int)(T_VERTEXCOUNT / T_FRAGMENTS)];
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