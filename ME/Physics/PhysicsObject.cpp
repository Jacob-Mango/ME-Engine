#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() {
}

PhysicsObject::~PhysicsObject() {
}

// TODO: Add recuring loop checking

void PhysicsObject::Simulate(PhysicsObject* colideWith, float delta) {
	for (unsigned int i = 0; i < m_Objects.size(); i++) {
		m_Objects[i]->Simulate(colideWith, delta);
	}

	if (colideWith->m_Type == SPHERE && m_Type == SPHERE) {
		float radiusDistance = m_Size.x + colideWith->m_Size.x;
		glm::vec3 direction = ((colideWith->m_Position + colideWith->m_Velocity) - (m_Position + m_Velocity));
		float centerDistance = direction.length();
		direction /= centerDistance;

		float distance = centerDistance - radiusDistance;

		if (distance < 0) {
			colideWith->m_Velocity = -colideWith->m_Velocity;
			m_Velocity = -m_Velocity;
		}
	}
}