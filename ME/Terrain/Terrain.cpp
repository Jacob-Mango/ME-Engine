#include "Terrain.h"

namespace Terrain {

	Terrain::Terrain(glm::vec2 relPos, float heightMap[T_VERTEXCOUNT * T_VERTEXCOUNT]) {
		m_Position = glm::vec3(m_RelativePosition, 1.0) * glm::vec3(T_SIZE);
		m_RelativePosition = relPos;

		for (int i = 0; i < T_FRAGMENTS; i++) {
			for (int x = 0; x < T_VERTEXCOUNT / T_FRAGMENTS; x++) {
				for (int y = 0; y < T_VERTEXCOUNT / T_FRAGMENTS; y++) {
					int j = x; // +(i * (T_VERTEXCOUNT / T_FRAGMENTS));
					int k = y; // +(i * (T_VERTEXCOUNT / T_FRAGMENTS));
					m_HeightMap[i][x * y * (T_VERTEXCOUNT / T_FRAGMENTS)] = heightMap[(j * k * T_VERTEXCOUNT)];
				}
			}
		}

		CreateModels();
	}


	Terrain::~Terrain() {
		delete lod0;
		delete lod1;
		delete lod2;

		delete sizes0;
		delete sizes1;
		delete sizes2;

		delete m_HeightMap;
	}

	void Terrain::CreateModels() {
		for (int k = 0; k < T_FRAGMENTS; k++) {
			for (int l = 1; l < 4; l++) {
				const int count = (T_VERTEXCOUNT / T_FRAGMENTS) * (T_VERTEXCOUNT / T_FRAGMENTS);
				float vertices[count * 3];
				float normals[count * 3];
				float uv[count * 2];
				int indices[6 * (T_VERTEXCOUNT / T_FRAGMENTS - 1) * (T_VERTEXCOUNT / T_FRAGMENTS - 1)];
				int vertexPointer = 0;
				for (int i = 0; i < T_VERTEXCOUNT / T_FRAGMENTS / l; i++) {
					for (int j = 0; j < T_VERTEXCOUNT / T_FRAGMENTS / l; j++) {
						vertices[vertexPointer * 3] = (float)j*l / ((float)(T_VERTEXCOUNT / T_FRAGMENTS / l) - 1) * T_SIZE;
						vertices[vertexPointer * 3 + 1] = m_HeightMap[k][i * l* j *l / (int)(T_VERTEXCOUNT / T_FRAGMENTS / l)];
						vertices[vertexPointer * 3 + 2] = (float)i*l / ((float)(T_VERTEXCOUNT / T_FRAGMENTS / l) - 1) * T_SIZE;
						normals[vertexPointer * 3] = 0;
						normals[vertexPointer * 3 + 1] = 1;
						normals[vertexPointer * 3 + 2] = 0;
						uv[vertexPointer * 2] = j*l / (float)(T_VERTEXCOUNT / T_FRAGMENTS / l);
						uv[vertexPointer * 2 + 1] = i*l / (float)(T_VERTEXCOUNT / T_FRAGMENTS / l);
						vertexPointer++;
					}
				}
				int pointer = 0;
				for (int gz = 0; gz < (T_VERTEXCOUNT / T_FRAGMENTS / l) - 1; gz++) {
					for (int gx = 0; gx < (T_VERTEXCOUNT / T_FRAGMENTS / l) - 1; gx++) {
						int topLeft = (gz * (T_VERTEXCOUNT / T_FRAGMENTS / l)) + gx;
						int topRight = topLeft + 1;
						int bottomLeft = ((gz + 1) * (T_VERTEXCOUNT / T_FRAGMENTS / l)) + gx;
						int bottomRight = bottomLeft + 1;

						indices[pointer++] = topLeft;
						indices[pointer++] = bottomLeft;
						indices[pointer++] = topRight;
						indices[pointer++] = topRight;
						indices[pointer++] = bottomLeft;
						indices[pointer++] = bottomRight;

					}
				}
				int m = l - 1;
				GLuint glId = 0;
				glGenVertexArrays(1, &glId);
				if (m == 0) {
					lod0[k] = glId;
					glBindVertexArray(lod0[k]);
					sizes0[k] = sizeof(indices) * sizeof(indices[0]) / l;
				} else if (m == 1) {
					lod1[k] = glId;
					glBindVertexArray(lod1[k]);
					sizes1[k] = sizeof(indices) * sizeof(indices[0]) / l;
				} else if (m == 2) {
					lod2[k] = glId;
					glBindVertexArray(lod2[k]);
					sizes2[k] = sizeof(indices) * sizeof(indices[0]) / l;
				}
				

				GLuint vboID;
				glGenBuffers(1, &vboID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(indices[0]) / l, indices, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glGenBuffers(1, &vboID);
				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(vertices[0]) / l, vertices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

				glEnableVertexAttribArray(1);
				glGenBuffers(1, &vboID);
				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, sizeof(uv) * sizeof(uv[0]) / l, uv, GL_STATIC_DRAW);
				glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

				glEnableVertexAttribArray(2);
				glGenBuffers(1, &vboID);
				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, sizeof(normals) * sizeof(normals[0]) / l, normals, GL_STATIC_DRAW);
				glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

				glBindVertexArray(0);
			}
		}
	}
}