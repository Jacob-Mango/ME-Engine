#include "Entity.h"

Entity::Entity(PhysicsEngine* physEngine, GLuint modelID, unsigned int entityID) : Entity(physEngine, glm::vec3(0.0f), glm::vec3(0.0f), modelID, entityID) {
}

Entity::Entity(PhysicsEngine* physEngine, glm::vec3 position, glm::vec3 rotation, GLuint modelID, unsigned int entityID) : m_ModelID(modelID), m_EntityID(entityID) {
	switch (modelID) {
	default:
	case 0:
		m_RigidBody = physEngine->CreateBox(position, rotation, 1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 1:
		m_RigidBody = physEngine->CreateSphere(position, rotation, 1.0f, 1.0f);
		break;
	case 2:
		m_RigidBody = physEngine->CreateCapsule(position, rotation, 1.0f, 1.0f, 1.0f);
		break;
	}
	m_Direction = glm::vec4(0);
}

Entity::~Entity() {

}

int Entity::Update(std::vector<Terrain::Terrain*> terrains, float delta, bool isServer) {
	float speed = 2.0f;
	if (m_Direction.w == 1.0f) speed = 12.4f;
	float xc = m_Direction.x * speed;

	if (m_Direction.y == 1.0f && m_JumpTime == 0) m_JumpTime = 1;

	float yc = (m_JumpTime < 60 && m_JumpTime > 0) ? 0.2f : 0.0f;
	float zc = m_Direction.z * speed;
	
	if (m_JumpTime > 0) {
		m_JumpTime++;
	}

	float epsilon = 0.05f;
	if (m_RigidBody->getLinearVelocity().getY() < epsilon && m_RigidBody->getLinearVelocity().getY() > -epsilon) {
		if (m_JumpTime >= 60) m_JumpTime = 0;
	}

	// std::cout << "Jumptime: " << m_JumpTime << " Linear Velocity Y: " <<  m_RigidBody->getLinearVelocity().getY() << std::endl;

	btVector3 v = btVector3(xc, yc, zc);
	v.setX(v.getX());
	v.setY(v.getY() + m_RigidBody->getLinearVelocity().getY());
	v.setZ(v.getZ());

	//if (isServer) {
		m_RigidBody->setLinearVelocity(v);
	//} 
	//else {
	//}
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