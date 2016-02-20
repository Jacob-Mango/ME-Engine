#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {
}

PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::Simulate(float delta) {
	for (unsigned int i = 0; i < m_Objects.size(); i++) {
		for (unsigned int j = 0; j < m_Objects.size(); j++) {
			if (j == i) continue;
			m_Objects[i]->Simulate(m_Objects[j], delta);
		}
	}
}