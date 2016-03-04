#include "Player.h"

Player::Player(PhysicsEngine* phys, const char* username, int entityID) : Player(phys, nullptr, username, entityID) {
}

Player::Player(PhysicsEngine* phys, sockaddr_in* address, const char* username, int entityID) : Entity(phys, 2, entityID, nullptr), m_Username(username), m_Address(address) {
	GetPhysicsObject()->setSleepingThresholds(0.0, 0.0);
	GetPhysicsObject()->setAngularFactor(0.0);
	GetPhysicsObject()->setRestitution(0.001);
	GetPhysicsObject()->setRollingFriction(1.0);
	GetPhysicsObject()->setFriction(1.0);

	class PlayerEvent : public Event {

	};

	Entity::m_Event = new PlayerEvent();
}

Player::~Player() {
}
