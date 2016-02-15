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
	glm::vec3 d = glm::vec3(m_Direction.x, m_Direction.y, m_Direction.z);

	m_Velocity += d * (m_Speed * ((m_Direction.w * 1.4f) + 1));
	m_Direction = glm::vec4(0);

	if (m_CanMove) {
		m_Velocity.y -= 1.0f / 30.0f;

		if (m_Position.y + m_Velocity.y < 0) {
			m_Position.y = 0;
			m_Velocity.y = m_Velocity.y * 0.95f;
		}
	}

	m_Position += m_Velocity;
	m_Velocity *= 0.5f;
	return 0;
}

int Entity::Tick() {
	return 0;
}