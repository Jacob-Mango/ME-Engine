#include "Server.h"


Server::Server(const char* title) : MangoesEngine(title, true) {
	m_Loading = true;
	Loop();
}

Server::~Server() {

}

void Server::Update() {
	m_Level->Update();
}

void Server::Tick() {
	m_Level->Tick();

	std::cout << std::endl << m_UpdatesPerSecond << std::endl;
}