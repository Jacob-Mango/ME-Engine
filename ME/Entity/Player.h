#pragma once

#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include "Entity.h"

class Player : public Entity {
private:
	std::string m_Username;

	sockaddr_in m_Address;
public:
	Player(const char* username, int entityID);
	Player(sockaddr_in add, const char* username, int entityID);
	~Player();

	std::string GetUsername() {
		return m_Username;
	}

	sockaddr_in GetAddress() {
		return m_Address;
	}
};

