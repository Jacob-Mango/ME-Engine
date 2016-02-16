#include "Player.h"

Player::Player(const char* username, int entityID) : Entity(0, entityID, false, 1.0f / 30.0f), m_Username(username) {
}

Player::Player(sockaddr_in address, const char* username, int entityID) : Entity(0, entityID, true, 1.0f / 30.0f), m_Username(username), m_Address(address) {
}

Player::~Player() {
}
