#include "Player.h"

Player::Player(const char* username, int entityID) : Entity(0, entityID), m_Username(username) {
}

Player::Player(std::string address, unsigned short port, const char* username, int entityID) : Entity(0, entityID), m_Username(username), m_Address(address), m_Port(port) {
}

Player::~Player() {
}
