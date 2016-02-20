#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <glm\glm.hpp>

#include <glew\glew.h>

#include "../Terrain/Terrain.h"

class Entity {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	glm::vec3 m_Force;
	glm::vec3 m_Rotation;
	glm::vec4 m_Direction;

	float m_Speed;

	GLuint m_ModelID;
	unsigned int m_EntityID;

	int m_AirTime = 0;
	bool m_CanMove = false;
	bool m_InJump = false;
	bool m_CanJump = true;
public: 
	Entity(GLuint modelID, unsigned int entityID, bool canMove, float speed);
	Entity(glm::vec3 position, glm::vec3 rotation, GLuint modelID, unsigned int entityID, bool canMove, float speed);
	~Entity();

	int Update(std::vector<Terrain::Terrain*> terrains, float delta);
	int Tick();

	unsigned int GetEntityID() {
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

	float GetSpeed() {
		return m_Speed;
	}

	void SetEntityID(unsigned int id) {
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

	void SetDirection(glm::vec4 r) {
		m_Direction = r;
	}

	float GetTerrainHeight(float x, float z, std::vector<Terrain::Terrain*> terrains);
};