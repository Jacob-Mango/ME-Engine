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
		WSADATA m_WSA;

		int m_LastError;
	public:
		Network(int port);
		Network(const char* address, int port);
		~Network();

		sockaddr_in Recieve(char buffer[BUFLEN]);
		void Send(const std::string& address, unsigned short port, const char* buffer);

		bool IsServer();

		int GetLastError() { return m_LastError; }

		std::vector<struct sockaddr_in>* Clients();
	};

}