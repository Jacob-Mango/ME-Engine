#include "Entity.h"

Entity::Entity(GLuint modelID, unsigned int entityID, bool canMove, float speed) : m_ModelID(modelID), m_EntityID(entityID), m_CanMove(canMove), m_Speed(speed) {
	m_PhysicsObject = new PhysicsObject();
	m_Direction = glm::vec4(0);
}

Entity::Entity(glm::vec3 position, glm::vec3 rotation, GLuint modelID, unsigned int entityID, bool canMove, float speed) : m_ModelID(modelID), m_EntityID(entityID), m_CanMove(canMove), m_Speed(speed) {
	m_PhysicsObject = new PhysicsObject();

	m_PhysicsObject->GetPosition()->x = position.x;
	m_PhysicsObject->GetPosition()->y = position.x;
	m_PhysicsObject->GetPosition()->z = position.x;

	m_PhysicsObject->GetRotation()->x = rotation.x;
	m_PhysicsObject->GetRotation()->y = rotation.x;
	m_PhysicsObject->GetRotation()->z = rotation.x;

	m_Direction = glm::vec4(0);
}

Entity::~Entity() {

}

int Entity::Update(std::vector<Terrain::Terrain*> terrains, float delta) {
	m_Speed = 5.0f / 30.0f;
	m_PhysicsObject->GetVelocity()->x += m_Direction.x * m_Speed;
	m_PhysicsObject->GetVelocity()->z += m_Direction.z * m_Speed;

	if (m_CanJump == true) {
		if (m_Direction.y == 1.0f) {
			m_InJump = true;
			m_CanJump = false;
		}
	}

	if (m_InJump == true) {
		float jumpPower = 1.0f;
		m_PhysicsObject->GetVelocity()->y += jumpPower / 30.0f;
		m_InJump = false;
		m_CanJump = true;
	}

	printf("Velocity %d , %d , %d \n", m_Direction.x, m_Direction.y, m_Direction.z);

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