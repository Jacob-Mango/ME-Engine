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
	
	float m_Force;
	float m_Magnitude;

	std::vector<PhysicsObject*> m_Objects;
public:
	PhysicsObject();
	~PhysicsObject();

	void AddObject(PhysicsObject* phys) {
		m_Objects.push_back(phys);
	}

	void Simulate(PhysicsObject* colideWith, float delta);
};

