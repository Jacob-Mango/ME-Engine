#pragma once

#include <vector>

#include <glm\glm.hpp>

enum PhysicsObjectType {
	CUBE, SPHERE, TRIANGLE
};

class PhysicsObject {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Velocity;
	glm::vec3 m_Size;

	PhysicsObjectType m_Type;
	
	float m_MaxSpeed;
	float m_Mass;
	float m_Force;
	float m_Magnitude;

	float m_Falltime;

	std::vector<PhysicsObject*> m_Objects;
public:
	PhysicsObject();
	~PhysicsObject();

	void AddObject(PhysicsObject* phys) {
		m_Objects.push_back(phys);
	}

	glm::vec3* GetPosition() {
		return &m_Position;
	}

	glm::vec3* GetRotation() {
		return &m_Rotation;
	}

	glm::vec3* GetVelocity() {
		return &m_Velocity;
	}

	glm::vec3* GetSize() {
		return &m_Size;
	}

	void Simulate(PhysicsObject* colideWith, float delta);
	void OnImpact(PhysicsObject &o1, PhysicsObject &o2);
};

