#include "Model.h"

namespace Rendering {

	Model::Model(const char* source) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(source, aiProcess_Triangulate);
		if (scene) {
			Load(scene->mMeshes[0], scene->mMeshes[0]->HasNormals());
		} else {
			std::cout << "Error, could not load model " << source << std::endl;
		}
	}


	Model::~Model() {
	}

	GLuint Model::GetVAOID() {
		return m_VAOID;
	}

	GLuint Model::GetSize() {
		return m_Size;
	}

	void Model::Load(const aiMesh* mesh, bool hasNormals) {
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> textures;
		std::vector<GLfloat> normals;
		std::vector<GLuint> indices;

		glm::vec3* position = new glm::vec3();
		glm::vec2* texture = new glm::vec2();
		glm::vec3* normal = new glm::vec3();

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			vertices.push_back(mesh->mVertices[i].x);
			vertices.push_back(mesh->mVertices[i].y);
			vertices.push_back(mesh->mVertices[i].z);;


			if (mesh->mTextureCoords[0]) {
				textures.push_back(mesh->mTextureCoords[0][i].x);
				textures.push_back(mesh->mTextureCoords[0][i].y);
			}
			else {
				textures.push_back(0);
				textures.push_back(0);
			}

			if (hasNormals) {
				normals.push_back(mesh->mNormals[i].x);
				normals.push_back(mesh->mNormals[i].y);
				normals.push_back(mesh->mNormals[i].z);
			}
			else {
				normals.push_back(0);
				normals.push_back(1);
				normals.push_back(0);
			}
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		m_Size = indices.size();

		glGenVertexArrays(1, &m_VAOID);
		glBindVertexArray(m_VAOID);

#define old
#ifdef old

		GLuint vboID;

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

		glEnableVertexAttribArray(1);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(textures[0]), textures.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

		if (hasNormals) {

			glEnableVertexAttribArray(2);

			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), normals.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);
		}
#else

		BindIndicesBuffer(indices);

		StoreDataInAttributeList(0, 3, vertices);
		StoreDataInAttributeList(1, 2, textures);
		if (hasNormals)
			StoreDataInAttributeList(2, 3, normals);
#endif

		glBindVertexArray(0);
	}

	void Model::BindIndicesBuffer(std::vector<GLuint> data) {
		BindIndicesBuffer(data.data());
	}

	void Model::StoreDataInAttributeList(int attributeNumber, int attributeSize, std::vector<GLfloat> data) {
		StoreDataInAttributeList(attributeNumber, attributeSize, data.data());
	}

	void Model::StoreDataInAttributeList(int attributeNumber, int attributeSize, std::vector<GLuint> data) {
		StoreDataInAttributeList(attributeNumber, attributeSize, data.data());
	}

	void Model::BindIndicesBuffer(GLuint data[]) {
		GLuint vboID;
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	}

	void Model::StoreDataInAttributeList(int attributeNumber, int attributeSize, GLfloat data[]) {
		GLuint vboID;
		glEnableVertexAttribArray(attributeNumber);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, attributeSize, GL_FLOAT, false, 0, 0);
	}

	void Model::StoreDataInAttributeList(int attributeNumber, int attributeSize, GLuint data[]) {
		GLuint vboID;
		glEnableVertexAttribArray(attributeNumber);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, attributeSize, GL_UNSIGNED_INT, false, 0, 0);
	}
}