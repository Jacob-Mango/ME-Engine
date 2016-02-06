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
			} else {
				textures.push_back(0);
				textures.push_back(0);
			}

			if (hasNormals) {
				normals.push_back(mesh->mNormals[i].x);
				normals.push_back(mesh->mNormals[i].y);
				normals.push_back(mesh->mNormals[i].z);
			} else {
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

		m_Size = indices.size() * sizeof(GLuint);

		glGenVertexArrays(1, &m_VAOID);
		glBindVertexArray(m_VAOID);

		BindIndicesBuffer(indices);

		StoreDataInAttributeList(0, 3, vertices);
		StoreDataInAttributeList(1, 2, textures);
		if (hasNormals)
			StoreDataInAttributeList(2, 3, normals);

		glBindVertexArray(0);
	}

	void Model::BindIndicesBuffer(std::vector<GLuint> data) {
		GLuint vboID;
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(data[0]), data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Model::StoreDataInAttributeList(int attributeNumber, int attributeSize, std::vector<GLfloat> data) {
		GLuint vboID;
		glEnableVertexAttribArray(attributeNumber);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, attributeSize, GL_FLOAT, false, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Model::StoreDataInAttributeList(int attributeNumber, int attributeSize, std::vector<GLuint> data) {
		GLuint vboID;
		glEnableVertexAttribArray(attributeNumber);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, attributeSize, GL_FLOAT, false, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}