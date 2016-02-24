#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <bullet\\src\\btBulletDynamicsCommon.h>

#include <glm\glm.hpp>

#include <glew\glew.h>

#include "../Terrain/Terrain.h"

#include "../Physics/PhysicsEngine.h"

class Entity {
private:
	btRigidBody* m_RigidBody;

	glm::vec4 m_Direction;

	GLuint m_ModelID;
	unsigned int m_EntityID;

	int m_JumpTime = 0;
public: 
	Entity(PhysicsEngine* physEngine, GLuint modelID, unsigned int entityID);
	Entity(PhysicsEngine* physEngine, glm::vec3 position, glm::vec3 rotation, GLuint modelID, unsigned int entityID);
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
		btTransform t;
		m_RigidBody->getMotionState()->getWorldTransform(t);
		btVector3 i = t.getOrigin();
		return glm::vec3(i.getX(), i.getY(), i.getZ()); ;
	}

	glm::quat GetRotation() {
		btTransform t;
		m_RigidBody->getMotionState()->getWorldTransform(t);
		btQuaternion i = t.getRotation();
		return glm::quat(i.getW(), i.getX(), i.getY(), i.getZ());;
	}

	btRigidBody* GetPhysicsObject() {
		return m_RigidBody;
	}

	void SetEntityID(unsigned int id) {
		m_EntityID = id;
	}

	void SetDirection(glm::vec4 r) {
		m_Direction = r;
	}

	float GetTerrainHeight(float x, float z, std::vector<Terrain::Terrain*> terrains);
};