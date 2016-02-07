#include "Server.h"


Server::Server(const char* title) : MangoesEngine(title, true) {
	m_Loading = true;
	Loop();
}

Server::~Server() {

}

void Server::Render() {
}

void Server::Update() {
}

void Server::Tick() {
	std::cout << m_UpdatesPerSecond << std::endl;
}