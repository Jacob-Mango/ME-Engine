#include "Terrain.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Terrain {

	namespace Generator {

		float GeneratedHeight(unsigned int x, unsigned int y, unsigned long seed);
		float GetInterpolatedNoise(float x, float z, unsigned long seed);
		float Interpolate(float a, float b, float blend);
		float GetSmoothNoise(int x, int z, unsigned long seed);
		float GetNoise(unsigned int x, unsigned int y, unsigned long seed);

		float GeneratedHeight(unsigned int x, unsigned int y, unsigned long seed, float amplitude, int octaves, float roughness) {
			float total = 0;
			float d = (float)pow(2, octaves - 1);
			for (int i = 0; i < octaves; i++) {
				float freq = (float)(pow(2, i) / d);
				float amp = (float)pow(roughness, i) * amplitude;
				total += GetInterpolatedNoise(x * freq, y * freq, seed) * amp;
			}
			return total;
		}

		float GetInterpolatedNoise(float x, float z, unsigned long seed) {
			int intX = (int)x;
			int intZ = (int)z;
			float fracX = x - intX;
			float fracZ = z - intZ;

			float v1 = GetSmoothNoise(intX, intZ, seed);
			float v2 = GetSmoothNoise(intX + 1, intZ, seed);
			float v3 = GetSmoothNoise(intX, intZ + 1, seed);
			float v4 = GetSmoothNoise(intX + 1, intZ + 1, seed);
			float i1 = Interpolate(v1, v2, fracX);
			float i2 = Interpolate(v3, v4, fracX);
			return Interpolate(i1, i2, fracZ);
		}

		float Interpolate(float a, float b, float blend) {
			double theta = blend * M_PI;
			float f = (float)(1.0f - cos(theta)) * 0.5f;
			return a * (1.0f - f) + b * f;
		}

		float GetSmoothNoise(int x, int z, unsigned long seed) {
			float corners = (GetNoise(x - 1, z - 1, seed) + GetNoise(x + 1, z - 1, seed) + GetNoise(x - 1, z + 1, seed) + GetNoise(x + 1, z + 1, seed)) / 16.0f;
			float sides = (GetNoise(x - 1, z, seed) + GetNoise(x + 1, z, seed) + GetNoise(x, z - 1, seed) + GetNoise(x, z + 1, seed)) / 8.0f;
			float center = GetNoise(x, z, seed) / 4.0f;
			return corners + sides + center;
		}

		float GetNoise(unsigned int x, unsigned int y, unsigned long seed) {
			srand(x * 49632 + y * 325176 + seed);
			return randf();
		}

	}

	Terrain::Terrain(glm::vec2 relPos, bool isServer, float heightMap[T_VERTEXCOUNT * T_VERTEXCOUNT]) {
		m_Position = glm::vec3(relPos.x, 0.0, relPos.y) * glm::vec3(T_SIZE);
		m_RelativePosition = relPos;


		for (int i = 0; i < T_VERTEXCOUNT * T_VERTEXCOUNT; i++) {
			m_HeightMap[i] = heightMap[i];
		}
		

		if (!isServer) {
			CreateModels();
		}
	}

	Terrain::Terrain(glm::vec2 relPos, bool isServer, unsigned long seed) {
		m_Position = glm::vec3(relPos.x, 0.0, relPos.y) * glm::vec3(T_SIZE);
		m_RelativePosition = relPos;

		for (int x = 0; x < T_VERTEXCOUNT; x++) {
			for (int y = 0; y < T_VERTEXCOUNT; y++) {
				float xC = (m_Position.x * T_MULSIZE) - 1.0f;
				float yC = (m_Position.z * T_MULSIZE) - 1.0f;

				if (x == 0) xC -= 1.0f;
				if (y == 0) yC -= 1.0f;

				float terrain = Generator::GeneratedHeight(x + xC, y + yC, seed, 20.0f, 6, 0.1f);
				float distortian = Generator::GeneratedHeight(x + xC, y + yC, seed, 1.0f, 4, 0.7f);
				m_HeightMap[x + y * T_VERTEXCOUNT] = 0.0f; // (terrain + distortian) / 2.0f;
			}
		}

		if (!isServer) {
			CreateModels();
		}
	}


	Terrain::~Terrain() {
		delete m_HeightMap;
	}

	void Terrain::CreateModels() {
		const int count = T_VERTEXCOUNT * T_VERTEXCOUNT;
		GLfloat vertices[count * 3];
		GLfloat normals[count * 3];
		GLfloat uvs[count * 2];
		GLuint indices[6 * (T_VERTEXCOUNT - 1) * (T_VERTEXCOUNT - 1)];

		int vertexPointer = 0;
		for (int i = 0; i < T_VERTEXCOUNT; i++){
			for (int j = 0; j < T_VERTEXCOUNT; j++){
				vertices[vertexPointer * 3] = (GLfloat)j / ((GLfloat)T_VERTEXCOUNT - 1) * T_SIZE;
				vertices[vertexPointer * 3 + 1] = m_HeightMap[j + i * T_VERTEXCOUNT];
				vertices[vertexPointer * 3 + 2] = (GLfloat)i / ((GLfloat)T_VERTEXCOUNT - 1) * T_SIZE;

				glm::vec3 normal = GetNormal(i, j);

				normals[vertexPointer * 3] = normal.x;
				normals[vertexPointer * 3 + 1] = normal.y;
				normals[vertexPointer * 3 + 2] = normal.z;
				uvs[vertexPointer * 2] = (GLfloat)j / ((GLfloat)T_VERTEXCOUNT - 1);
				uvs[vertexPointer * 2 + 1] = (GLfloat)i / ((GLfloat)T_VERTEXCOUNT - 1);
				vertexPointer++;
			}
		}
		int pointer = 0;
		for (int gz = 0; gz < T_VERTEXCOUNT - 1; gz++){
			for (int gx = 0; gx < T_VERTEXCOUNT - 1; gx++){
				int topLeft = (gz*T_VERTEXCOUNT) + gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1)*T_VERTEXCOUNT) + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}

		glGenVertexArrays(1, &m_VAOID);
		glBindVertexArray(m_VAOID);
		m_Size = sizeof(indices) / sizeof(indices[0]);

#define old

#ifdef old

		GLuint vboID;

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

		glEnableVertexAttribArray(1);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

		glEnableVertexAttribArray(2);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

#else
		Rendering::Model::BindIndicesBuffer(indices);
		Rendering::Model::StoreDataInAttributeList(0, 3, vertices);
		Rendering::Model::StoreDataInAttributeList(1, 2, uvs);
		Rendering::Model::StoreDataInAttributeList(2, 3, normals);
#endif
		glBindVertexArray(0);
	}

	glm::vec3 Terrain::GetNormal(int i, int j) {
		float heightL = 0.0f;
		float heightR = 0.0f;
		float heightD = 0.0f;
		float heightU = 0.0f;
		if (j > 0)
			heightL = m_HeightMap[(-1 + j) + (+0 + i) * T_VERTEXCOUNT];
		else
			heightL = m_HeightMap[(+0 + j) + (+0 + i) * T_VERTEXCOUNT];

		if (j < T_VERTEXCOUNT - 1)
			heightR = m_HeightMap[(+1 + j) + (+0 + i) * T_VERTEXCOUNT]; 
		else
			heightR = m_HeightMap[(+0 + j) + (+0 + i) * T_VERTEXCOUNT];

		if (i > 0)
			heightD = m_HeightMap[(+0 + j) + (-1 + i) * T_VERTEXCOUNT]; 
		else
			heightD = m_HeightMap[(+0 + j) + (+0 + i) * T_VERTEXCOUNT];

		if (i < T_VERTEXCOUNT - 1)
			heightU = m_HeightMap[(+0 + j) + (+1 + i) * T_VERTEXCOUNT];
		else
			heightU = m_HeightMap[(+0 + j) + (+0 + i) * T_VERTEXCOUNT];

		glm::vec3 normal = glm::vec3(heightL - heightR, 1.0f, heightD - heightU);
		normal /= glm::vec3(sqrtf((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z)));

		return normal;
	}

	float Terrain::GetSmoothHeight(float x, float y) {
		float terrainX = x - m_Position.x;
		float terrainY = y - m_Position.z;

		float gridSquareSize = (float)T_SIZE / (float)((float)T_VERTEXCOUNT - 1.0f);

		int gx = (int)floor(terrainX / gridSquareSize);
		int gy = (int)floor(terrainY / gridSquareSize);

		if (gx >= T_VERTEXCOUNT - 1.0f || gy >= T_VERTEXCOUNT - 1.0f || gx < 0.0f || gy < 0.0f) return 0.0f;

		float xx = fmodf(terrainX, gridSquareSize);
		float yy = fmodf(terrainY, gridSquareSize);

		float xCoord = xx / gridSquareSize;
		float yCoord = yy / gridSquareSize;

		float ret = 0;
		if (xCoord <= (1 - yCoord)) {
			ret = BarryCentric(glm::vec3(0.0f, GetHeight(gx, gy), 0.0f), glm::vec3(1.0f, GetHeight(gx + 1.0f, gy), 0.0f), glm::vec3(0.0f, GetHeight(gx, gy + 1.0f), 1.0f), glm::vec2(xCoord, yCoord));
		} else {
			ret = BarryCentric(glm::vec3(1.0f, GetHeight(gx + 1.0f, gy), 0.0f), glm::vec3(1.0f, GetHeight(gx + 1.0f, gy + 1.0f), 1.0f), glm::vec3(0.0f, GetHeight(gx, gy + 1.0f), 1.0f), glm::vec2(xCoord, yCoord));
		}
		return ret;
	}

	float Terrain::GetHeight(int x, int y) {
		return m_HeightMap[x + y * T_VERTEXCOUNT];
	}

	float Terrain::BarryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}
}