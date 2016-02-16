#include "Entity.h"

Entity::Entity(GLuint modelID, unsigned int entityID, bool canMove, float speed) : m_ModelID(modelID), m_EntityID(entityID), m_CanMove(canMove), m_Speed(speed) {
	m_Position = glm::vec3(0);
	m_Velocity = glm::vec3(0);
	m_Rotation = glm::vec3(0);
	m_Direction = glm::vec4(0);
}

Entity::Entity(glm::vec3 position, glm::vec3 rotation, GLuint modelID, unsigned int entityID, bool canMove, float speed) : m_Position(position), m_Rotation(rotation), m_ModelID(modelID), m_EntityID(entityID), m_CanMove(canMove), m_Speed(speed) {
	m_Velocity = glm::vec3(0);
	m_Direction = glm::vec4(0);
}

Entity::~Entity() {

}

int Entity::Update() {
	float gravity = 9.81f;
	glm::vec3 d = glm::vec3(m_Direction.x, 0, m_Direction.z);

	if (m_CanJump == true) {
		if (m_Direction.y == 1.0f) {
			m_InJump = true;
			m_CanJump = false;
		}
	} else if (m_InJump == true) {
		m_Velocity.y += 0.5f * gravity / 30.0f;
	}

	m_Velocity += d * (m_Speed * (m_Direction.w + 1));
	m_Direction = glm::vec4(0);

	if (m_CanMove) {
		m_Velocity.y -= gravity / 30.0f * m_AirTime / 10.0f;
		m_AirTime++;

		float h = 0.0f;
		if (m_Position.y + m_Velocity.y < h) {
			m_AirTime = 0;
			m_Velocity.y = 0.0f;
			m_Position.y = h;
			m_InJump = false;
			m_CanJump = true;
		}
	}

	m_Position += m_Velocity;
	m_Velocity *= 0.5f;
	return 0;
}

int Entity::Tick() {
	return 0;
}