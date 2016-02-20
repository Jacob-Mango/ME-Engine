#include "Entity.h"

Entity::Entity(GLuint modelID, unsigned int entityID, bool canMove, float speed) : m_ModelID(modelID), m_EntityID(entityID), m_CanMove(canMove), m_Speed(speed) {
	m_Position = glm::vec3(0);
	m_Velocity = glm::vec3(0);
	m_Force = glm::vec3(0);
	m_Rotation = glm::vec3(0);
	m_Direction = glm::vec4(0);
}

Entity::Entity(glm::vec3 position, glm::vec3 rotation, GLuint modelID, unsigned int entityID, bool canMove, float speed) : m_Position(position), m_Rotation(rotation), m_ModelID(modelID), m_EntityID(entityID), m_CanMove(canMove), m_Speed(speed) {
	m_Velocity = glm::vec3(0);
	m_Force = glm::vec3(0);
	m_Direction = glm::vec4(0);
}

Entity::~Entity() {

}

int Entity::Update(std::vector<Terrain::Terrain*> terrains, float delta) {
	glm::vec3 d = glm::vec3(m_Direction.x, m_Direction.y, m_Direction.z);

	d.y -= 9.8f / (powf(30, -1));

	if (m_CanJump == true) {
		if (m_Direction.y == 1.0f) {
			m_InJump = true;
			m_CanJump = false;
		}
	}

	if (m_InJump == true) {
		float jumpPower = 1.0f;
		d.y += jumpPower / 30.0f;
	}

	m_Velocity = m_Velocity * (1 - delta * m_Speed) + d * (delta * m_Speed);

	m_Direction = glm::vec4(0);

	if (m_CanMove) {
		m_AirTime++;

		float xzh = GetTerrainHeight(m_Position.x + m_Velocity.x, m_Position.z + m_Velocity.z, terrains);

		float xh = GetTerrainHeight(m_Position.x + m_Velocity.x, m_Position.z, terrains);
		float zh = GetTerrainHeight(m_Position.x, m_Position.z + m_Velocity.z, terrains);

		float h = GetTerrainHeight(m_Position.x, m_Position.z, terrains);

		if (m_Position.y + m_Velocity.y < xzh) {
			m_AirTime = 0;
			m_Velocity.y = -m_Velocity.y;
			m_Position.y = xzh;
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

float Entity::GetTerrainHeight(float x, float z, std::vector<Terrain::Terrain*> terrains) {
	float y = 0;
	int xx = (int)(x / T_SIZE);
	int zz = (int)(z / T_SIZE);



	for (unsigned int i = 0; i < terrains.size(); i++) {
		if (terrains[i]->GetRelativePosition().x == xx && terrains[i]->GetRelativePosition().y == zz) {
			y = terrains[i]->GetSmoothHeight(x, z);
			break;
		}
	}
	return y;
}