#pragma once

#include <string>

#include "Entity.h"

class Player : public Entity {
private:
	std::string m_Username;

	std::string m_Address; 
	unsigned short m_Port;
public:
	Player(const char* username, int entityID);
	Player(std::string address, unsigned short port, const char* username, int entityID);
	~Player();

	std::string GetUsername() {
		return m_Username;
	}

	std::string GetAddress() {
		return m_Address;
	}

	unsigned short GetPort() {
		return m_Port;
	}
};

