#include "Packet.h"

namespace Network {

	Packet::Packet(Network* network, Level::Level* level) : m_Network(network), m_Level(level) {
		std::thread t1(std::bind(HandleIncoming, this));
		t1.join();
	}

	Packet::~Packet() {
	}

	void HandleIncoming(Packet* p) {
		while (true) {
			char buf[BUFLEN];
			sockaddr_in from = p->m_Network->Recieve(buf);
			std::string recv = buf;
			if (!recv.compare(0, 2, "00")) {
				printf("Logging in!");
				std::ostringstream netSend;
				int code = 6135;
				netSend << "00" << code << "";

				const char* user = recv.c_str();

				p->m_Level->AddPlayer(Player((std::string) inet_ntoa(from.sin_addr), (int) from.sin_port, user, code));

				p->m_Network->Send(inet_ntoa(from.sin_addr), from.sin_port, netSend.str().c_str());
			} else if (!recv.compare(0, 2, "01")) {
				printf("Disconnecting!");
			} else if (!recv.compare(0, 2, "02")) {
				printf("Moving!");
			}
		}
	}
}