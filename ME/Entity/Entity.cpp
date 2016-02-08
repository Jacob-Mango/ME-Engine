#include "Entity.h"

Entity::Entity(GLuint modelID, int entityID) : m_ModelID(modelID), m_EntityID(entityID) {
	m_Position = glm::vec3(0);
	m_Velocity = glm::vec3(0);
	m_Rotation = glm::vec3(0);
}

Entity::Entity(glm::vec3 position, glm::vec3 rotation, GLuint modelID, int entityID) : m_Position(position), m_Rotation(rotation), m_ModelID(modelID), m_EntityID(entityID) {
	m_Velocity = glm::vec3(0);
}

Entity::~Entity() {

}

int Entity::Update() {
	return 0;
}

int Entity::Tick() {
	return 0;
}