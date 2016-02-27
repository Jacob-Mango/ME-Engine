#include "Network.h"

namespace Network {
	Network::Network(bool isServer) :m_IsServer(isServer) {
		if (m_IsServer) {
			if (WSAStartup(MAKEWORD(2, 2), &m_WSA) != 0) {
				printf("Failed. Error Code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}

			if ((m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
				printf("Could not create socket : %d", WSAGetLastError());
			}

			DWORD dwBytesReturned = 0;
			BOOL bNewBehavior = FALSE;

			if (WSAIoctl(m_Socket, SIO_UDP_CONNRESET, &bNewBehavior, sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL) == SOCKET_ERROR) {
				DWORD dwErr = WSAGetLastError();
				if (WSAEWOULDBLOCK == dwErr) {
					printf("Yea, your stuffed!");
				} else {
					printf("WSAIoctl(SIO_UDP_CONNRESET) Error: %d\n", dwErr);
				}
			}

			m_ServerAddress.sin_family = AF_INET;
			m_ServerAddress.sin_addr.S_un.S_addr = INADDR_ANY;
			m_ServerAddress.sin_port = htons(SERVERPORT);

			int i = bind(m_Socket, (sockaddr*)&m_ServerAddress, sizeof(m_ServerAddress));
			printf("Code: %d", i);
			if (i == SOCKET_ERROR) {
				printf("Bind failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
		} else {
			if (WSAStartup(MAKEWORD(2, 2), &m_WSA) != 0) {
				printf("Failed. Error Code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}

			if ((m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
				printf("socket() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}

			DWORD dwBytesReturned = 0;
			BOOL bNewBehavior = FALSE;

			if (WSAIoctl(m_Socket, SIO_UDP_CONNRESET, &bNewBehavior, sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL) == SOCKET_ERROR) {
				DWORD dwErr = WSAGetLastError();
				if (WSAEWOULDBLOCK == dwErr) {
					printf("Yea, your stuffed!");
				}
				else {
					printf("WSAIoctl(SIO_UDP_CONNRESET) Error: %d\n", dwErr);
				}
			}
		}
	}


	Network::~Network() {
		closesocket(m_Socket);
		WSACleanup();
	}

	sockaddr_in Network::Recieve(char buffer[BUFLEN]) {
		sockaddr_in from = sockaddr_in();
		int size = sizeof(from);
		int ret = recvfrom(m_Socket, buffer, BUFLEN, 0, (SOCKADDR*)&from, &size);
		if (ret < 0) {
			buffer[ret] = 0;
			int x = WSAGetLastError();
			m_LastError = -1;
			printf("recvfrom() failed with error code : %d", x);
			return from;
		} else {
			buffer[ret] = 0;
			m_LastError = 0;
			return from;
		}
	}

	void Network::Send(const std::string& address, unsigned short port, const char* buffer) {
		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = inet_addr(address.c_str());
		add.sin_port = htons(port);
		int ret = sendto(m_Socket, buffer, strlen(buffer), 0, (struct sockaddr*) &add, sizeof(add));
		if (ret < 0) {
			m_LastError = -1;
			printf("sendto() failed with error code : %d", WSAGetLastError());
		}
		m_LastError = 0;
	}

	void Network::Send(sockaddr_in add, const char* buffer) {
		add.sin_family = AF_INET;
		int ret = sendto(m_Socket, buffer, strlen(buffer), 0, (struct sockaddr*) &add, sizeof(add));
		if (ret < 0) {
			m_LastError = -1;
			printf("sendto() failed with error code : %d", WSAGetLastError());
		}
		m_LastError = 0;
	}

	bool Network::IsServer() {
		return m_IsServer;
	}
}