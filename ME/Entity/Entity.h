#pragma once

#include <vector>
#include <string>

#include <glm\glm.hpp>

#include <glew\glew.h>

class Entity {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	glm::vec3 m_Rotation;

	GLuint m_ModelID;
	int m_EntityID;
public: 
	Entity(GLuint modelID, int entityID);
	Entity(glm::vec3 position, glm::vec3 rotation, GLuint modelID, int entityID);
	~Entity();

	int Update();
	int Tick();

	int GetEntityID() {
		return m_EntityID;
	}

	GLuint GetModelID() {
		return m_ModelID;
	}

	glm::vec3 GetPosition() {
		return m_Position;
	}

	glm::vec3 GetVelocity() {
		return m_Velocity;
	}

	glm::vec3 GetRotation() {
		return m_Rotation;
	}

	void SetEntityID(int id) {
		m_EntityID = id;
	}

	void SetPosition(glm::vec3 r) {
		m_Position = r;
	}

	void SetVelocity(glm::vec3 r) {
		m_Velocity = r;
	}

	void SetRotation(glm::vec3 r) {
		m_Rotation = r;
	}
};