#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <glm\glm.hpp>

#include <glew\glew.h>

#include "../Terrain/Terrain.h"
#include "../Physics/PhysicsObject.h"

class Entity {
private:
	PhysicsObject* m_PhysicsObject;

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

	glm::vec3* GetPosition() {
		return m_PhysicsObject->GetPosition();
	}

	glm::vec3* GetVelocity() {
		return m_PhysicsObject->GetVelocity();
	}

	glm::vec3* GetRotation() {
		return m_PhysicsObject->GetRotation();
	}

	PhysicsObject* GetPhysicsObject() {
		return m_PhysicsObject;
	}

	float GetSpeed() {
		return m_Speed;
	}

	void SetEntityID(unsigned int id) {
		m_EntityID = id;
	}

	void SetDirection(glm::vec4 r) {
		m_Direction = r;
	}

	float GetTerrainHeight(float x, float z, std::vector<Terrain::Terrain*> terrains);
};