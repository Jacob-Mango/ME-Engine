#include "Server.h"

#include <..\ME\Utils\ResourceLoader.h>

Server::Server(const char* title) : MangoesEngine(title, true) {
	m_Loading = true;

	ResourceLoader rl;

	while (rl.LoadLevel(m_Level) == false) {
		
	}

	Loop();
}

Server::~Server() {

}

void Server::Update(float delta) {
	m_Packet->SendOnUpdate();
	m_Level->Update(m_IsServer, delta);
}

void Server::Tick() {
	m_Level->Tick(m_IsServer);
	std::cout << std::endl << m_UpdatesPerSecond << std::endl;
}