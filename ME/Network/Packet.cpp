#include "Packet.h"

Packet::Packet(Network::Network* network) : m_Network(network) {
	std::thread t1(HandleIncoming, network);
}

Packet::~Packet() {
}

void HandleIncoming(Network::Network* network) {
	while (true) {
		char buf[BUFLEN];
		sockaddr_in from = sockaddr_in();
		if (network->Recieve(buf, from) == 0) {
			std::cout << buf << std::endl;
		}
	}
}