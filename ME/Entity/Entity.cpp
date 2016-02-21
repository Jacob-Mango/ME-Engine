#include "Entity.h"

Entity::Entity(PhysicsEngine* physEngine, GLuint modelID, unsigned int entityID) : m_ModelID(modelID), m_EntityID(entityID) {
	if (modelID == 1) {
		m_RigidBody = physEngine->CreateSphere(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), 1.0f, 1.0f);
	} else if (modelID == 2) {
		m_RigidBody = physEngine->CreateBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f, 1.0f);
	} else {
		m_RigidBody = physEngine->CreateSphere(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), 1.0f, 1.0f);
	}
	m_Direction = glm::vec4(0);
}

Entity::Entity(PhysicsEngine* physEngine, glm::vec3 position, glm::vec3 rotation, GLuint modelID, unsigned int entityID) : m_ModelID(modelID), m_EntityID(entityID) {
	if (modelID == 1) {
		m_RigidBody = physEngine->CreateSphere(position, rotation, 1.0f, 80.0f);
	} else if (modelID == 2) {
		m_RigidBody = physEngine->CreateBox(position, rotation, 1.0f, 1.0f, 1.0f, 80.0f);
	} else {
		m_RigidBody = physEngine->CreateSphere(position, rotation, 1.0f, 1.0f);
	}
	m_Direction = glm::vec4(0);
}

Entity::~Entity() {

}

int Entity::Update(std::vector<Terrain::Terrain*> terrains, float delta) {
	float speed = 10.0f / 30.0f;
	float xc = m_Direction.x * speed;
	float yc = (m_Direction.y == 1.0f) ? speed : 0.0f;
	float zc = m_Direction.z * speed;

	// m_RigidBody->applyForce(btVector3(xc, yc, zc), btVector3(0, 0, 0));

	m_RigidBody->setLinearVelocity(m_RigidBody->getLinearVelocity() + btVector3(xc, yc, zc));
	
	m_Direction = glm::vec4(0, 0, 0, 0);
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