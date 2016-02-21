#include "Player.h"

Player::Player(PhysicsEngine* phys, const char* username, int entityID) : Entity(phys, 1, entityID), m_Username(username) {
}

Player::Player(PhysicsEngine* phys, sockaddr_in address, const char* username, int entityID) : Entity(phys, 1, entityID), m_Username(username), m_Address(address) {
}

Player::~Player() {
}
