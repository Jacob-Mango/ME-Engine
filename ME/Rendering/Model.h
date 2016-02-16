#pragma once

#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>  

namespace Rendering {
	struct Vertex {
		glm::vec3* Position;
		glm::vec2* TexCoords;
		glm::vec3* Normal;

		Vertex(glm::vec3* position, glm::vec2* texCoord, glm::vec3* normal) {
			Position = position;
			TexCoords = texCoord;

			if (normal != NULL) {
				Normal = normal;
			}
		}

		Vertex(glm::vec3* position, glm::vec2* texCoord) {
			(position, texCoord, NULL);
		}

		Vertex() {

		}
	};

	class Model {
	private:
		GLuint m_VAOID;
		GLuint m_Size;
	public:
		Model(const char* source);
		~Model();

		GLuint GetVAOID(); 
		GLuint GetSize();
	private:
		void Load(const aiMesh* mesh, bool hasNormals);
	public:
		static void BindIndicesBuffer(GLuint data[]);
		static void StoreDataInAttributeList(int attributeNumber, int attributeSize, GLfloat data[]);
		static void StoreDataInAttributeList(int attributeNumber, int attributeSize, GLuint data[]);

		static void BindIndicesBuffer(std::vector<GLuint> data);
		static void StoreDataInAttributeList(int attributeNumber, int attributeSize, std::vector<GLfloat> data);
		static void StoreDataInAttributeList(int attributeNumber, int attributeSize, std::vector<GLuint> data);
	};

}