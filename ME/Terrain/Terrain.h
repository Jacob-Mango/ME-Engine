#pragma once

#include <math.h>
#include <vector>
#include <iostream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include "..\Rendering\Model.h"
#include "../Physics/PhysicsEngine.h"

#include <stdlib.h>

#define T_SIZE 16
#define T_MULSIZE 4
#define T_VERTEXCOUNT T_SIZE * T_MULSIZE

#define randf() static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

namespace Terrain {

	class Terrain {
	public:
		GLuint m_VAOID;
		unsigned int m_Size;

		float m_HeightMap[(int)((T_VERTEXCOUNT) * (T_VERTEXCOUNT))];
	private:
		glm::vec3 m_Position;
		glm::vec2 m_RelativePosition;
	public:
		Terrain(PhysicsEngine* phys, glm::vec2 relPos, bool isServer, float heightMap[T_VERTEXCOUNT * T_VERTEXCOUNT]);
		Terrain(PhysicsEngine* phys, glm::vec2 relPos, bool isServer, unsigned long seed);
		~Terrain();

		glm::vec3 GetPosition() {
			return m_Position;
		}

		glm::vec2 GetRelativePosition() {
			return m_RelativePosition;
		}

		glm::vec3 GetNormal(int i, int j);
		float GetSmoothHeight(float x, float y);
		float GetHeight(int x, int y);

		float BarryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
	private:
		void CreateModels();
	};

}