#pragma once

#include <vector>

#include "PhysicsObject.h"

class PhysicsEngine {
private:
	std::vector<PhysicsObject*> m_Objects;
public:
	PhysicsEngine();
	~PhysicsEngine();

	void AddObject(PhysicsObject* phys) {
		m_Objects.push_back(phys);
	}

	void Simulate(float delta);
};

