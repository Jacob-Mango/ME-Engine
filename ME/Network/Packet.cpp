#include "Packet.h"

namespace Network {

	Packet::Packet(Network* network, Level::Level* level) : m_Network(network), m_Level(level) {
		m_Thread = new std::thread(std::bind(HandleIncoming, this));
	}

	Packet::~Packet() {
	}

	void HandleIncoming(Packet* p) {
		bool isServer = p->m_Network->IsServer();
		while (true) {
			char buf[BUFLEN];
			sockaddr_in from = p->m_Network->Recieve(buf);
			std::string recv = buf;

			if (!recv.compare(0, 2, "00")) {
				int code = 0;
				const char* user = recv.substr(8).c_str();
				if (isServer) {
					code = p->m_Level->GetFreePlayerCode();
					std::ostringstream netSend;
					netSend << "00";

					std::ostringstream check;
					check << code << "";
					int x = 6;
					while (x - check.str().length() > 0) {
						netSend << "0";
						x--;
					}
					netSend << code << "";

					std::cout << netSend.str().c_str();

					p->m_Network->Send(from, netSend.str().c_str());

					netSend << user << "";
					p->SendToAll(netSend.str().c_str());
					p->m_Level->AddPlayer(Player(from, user, code));
				} else {
					code = atoi(recv.substr(2, 6).c_str());
					p->m_Level->AddPlayer(Player(user, code));
				}
			} else if (!recv.compare(0, 2, "01")) {
			} else if (!recv.compare(0, 2, "02")) {
			}
		}
	}

	void Packet::SendToAll(const char* buffer) {
		for (unsigned int i = 0; i < m_Level->GetPlayers().size(); i++) {
			m_Network->Send(m_Level->GetPlayers()[i].GetAddress(), buffer);
		}
	}
}