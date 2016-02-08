#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <vector>
#include <string>

#pragma comment(lib,"ws2_32.lib")

// #define BUFLEN 16384
#define BUFLEN 1024

namespace Network {

	class Network {
	private:
		bool m_IsServer;

		SOCKET m_Socket;

		sockaddr_in m_ServerAddress;
		std::vector<sockaddr_in> m_ClientAddress;

		WSADATA m_WSA;
	public:
		Network(int port);
		Network(const char* address, int port);
		~Network();

		int Recieve(char buffer[BUFLEN], sockaddr_in from);
		int Send(const std::string& address, unsigned short port, const char* buffer);

		bool IsServer();

		struct sockaddr_in* Server();
		std::vector<struct sockaddr_in>* Clients();
	};

}