#include "Terrain.h"

namespace Terrain {

	Terrain::Terrain(glm::vec2 relPos, float heightMap[T_VERTEXCOUNT * T_VERTEXCOUNT], bool isServer) {
		m_Position = glm::vec3(relPos.x, 0.0, relPos.y) * glm::vec3(T_SIZE);
		m_RelativePosition = relPos;

		for (int i = 0; i < T_VERTEXCOUNT; i++) {
			m_HeightMap[i] = heightMap[i];
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
		GLfloat uv[count * 2];
		GLuint indices[6 * (T_VERTEXCOUNT - 1) * (T_VERTEXCOUNT - 1)];

		int vertexPointer = 0;
		for (int i = 0; i < T_VERTEXCOUNT; i++){
			for (int j = 0; j < T_VERTEXCOUNT; j++){
				vertices[vertexPointer * 3] = (GLfloat)j / ((GLfloat)T_VERTEXCOUNT - 1) * T_SIZE;
				vertices[vertexPointer * 3 + 1] = 0;
				vertices[vertexPointer * 3 + 2] = (GLfloat)i / ((GLfloat)T_VERTEXCOUNT - 1) * T_SIZE;
				normals[vertexPointer * 3] = 0;
				normals[vertexPointer * 3 + 1] = 1;
				normals[vertexPointer * 3 + 2] = 0;
				uv[vertexPointer * 2] = (GLfloat)j / ((GLfloat)T_VERTEXCOUNT - 1);
				uv[vertexPointer * 2 + 1] = (GLfloat)i / ((GLfloat)T_VERTEXCOUNT - 1);
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

		glEnableVertexAttribArray(2);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

		glBindVertexArray(0);
	}
}