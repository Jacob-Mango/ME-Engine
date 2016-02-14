#include "Player.h"

Player::Player(const char* username, int entityID) : Entity(1, entityID), m_Username(username) {
}

Player::Player(sockaddr_in address, const char* username, int entityID) : Entity(1, entityID), m_Username(username), m_Address(address) {
}

Player::~Player() {
}
