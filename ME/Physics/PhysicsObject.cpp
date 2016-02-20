#include "PhysicsObject.h"

#define DISTANCE(i) (i.x * i.x) + (i.y * i.y) + (i.z * i.z)

PhysicsObject::PhysicsObject() {
	m_Position = glm::vec3(0.0f);
	m_Rotation = glm::vec3(0.0f);
	m_Velocity = glm::vec3(0.0f);
	m_Size = glm::vec3(1.0f);

	m_MaxSpeed = 1.0f;
	m_Mass = 1.0f;
	m_Force = 1.0f;
	m_Magnitude = 1.0f;

	m_Type = SPHERE;
}

PhysicsObject::~PhysicsObject() {
}

// TODO: Add recuring loop checking

void PhysicsObject::Simulate(PhysicsObject* colideWith, float delta) {
	for (unsigned int i = 0; i < m_Objects.size(); i++) {
		m_Objects[i]->Simulate(colideWith, delta);
	}


	float friction = 0.5f;

	m_Velocity.y -= 9.81f * delta * (m_Falltime) / 30.0f;
	m_Falltime += 0.1f;

	float h = 0.0f;
	if (m_Position.y + m_Velocity.y < h) {
		m_Velocity.y = -(m_Velocity.y * friction * 0.1f);
		m_Falltime = 0.0f;
	}

	m_Force = sqrtf(DISTANCE(m_Velocity));
	colideWith->m_Force = sqrtf(DISTANCE(colideWith->m_Velocity));

	if (m_Type == SPHERE) {

		// CHECK COLLISION WITH SPHERE

		if (colideWith->m_Type == SPHERE) {
			float radiusDistance = m_Size.x + colideWith->m_Size.x;
			glm::vec3 direction = ((colideWith->m_Position + colideWith->m_Velocity) - (m_Position + m_Velocity));
			float centerDistance = sqrtf(DISTANCE(direction));
			// direction /= centerDistance;

			float distance = centerDistance - radiusDistance;

			if (distance < 0) {
				OnImpact(*this, *colideWith);
			}
		}
	}


	m_Position += m_Velocity;
	m_Velocity = m_Velocity * glm::vec3(friction);

	// printf("Position %d , %d , %d \n", (int)m_Position.x, (int)m_Position.y, (int)m_Position.z);
}

void PhysicsObject::OnImpact(PhysicsObject &o1, PhysicsObject &o2) {
	if (o1.m_Force < o2.m_Force) {
		o1.m_Velocity = -o1.m_Velocity;
	} else if (o2.m_Force < o1.m_Force) {
		o2.m_Velocity = -o2.m_Velocity;
	} else {
		o1.m_Velocity = -o1.m_Velocity;
		o2.m_Velocity = -o2.m_Velocity;
	}

	o1.m_Velocity = -o1.m_Velocity;
	o2.m_Velocity = -o2.m_Velocity;
}