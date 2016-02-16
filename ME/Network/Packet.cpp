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
			std::string recv(buf);

			if (!recv.compare(0, 2, "00")) {
				int code = 0;
				const char* user = recv.substr(8).c_str();

				if (isServer) {
					code = p->m_Level->GetFreeEntityCode();
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

					for (unsigned int i = 0; i < p->m_Level->GetPlayers().size(); i++) {
						std::ostringstream n;
						n << "00";
						std::ostringstream c;
						c << p->m_Level->GetPlayers()[i]->GetEntityID() << "";
						int x = 6;
						while (x - c.str().length() > 0) {
							n << "0";
							x--;
						}
						n << p->m_Level->GetPlayers()[i]->GetEntityID() << "";
						n << p->m_Level->GetPlayers()[i]->GetUsername() << "";
						p->m_Network->Send(from, n.str().c_str());

					}
					netSend << user << "";
					p->SendToAll(netSend.str().c_str());
					p->m_Level->AddPlayer(new Player(from, user, code));
				} else {
					code = atoi(recv.substr(2, 6).c_str());
					std::cout << "Maybe? " << code << " ";
					if (p->m_Level->GetPlayerLevelForID(code) == -1) {
						std::cout << "Yes?";
						p->m_Level->AddPlayer(new Player(user, code));
					}
					else {
						std::cout << "No?";
					}
				}
			} else if (!recv.compare(0, 2, "01")) {
				int code = atoi(recv.substr(2, 6).c_str());
				p->m_Level->RemovePlayer(code);
				if (isServer) {
					std::ostringstream netSend;
					netSend << "00" << recv.substr(2, 6);
					p->SendToAll(netSend.str().c_str());
				}
			} else if (!recv.compare(0, 2, "02")) {
				recv = recv.substr(2);
				int code = atoi(recv.substr(0, 6).c_str());
				recv = recv.substr(6);
				Player* c = p->m_Level->GetPlayerForID(code);

				std::vector<std::string> a = StringUtils::split(recv, 'L');

				glm::vec3 rotation;

				if (isServer) {
					glm::vec4 direction;
					glm::vec4 control = glm::vec4(atoi(a[0].c_str()), atoi(a[1].c_str()), atoi(a[2].c_str()), atoi(a[3].c_str()));
					rotation = glm::vec3(atof(a[4].c_str()), atof(a[5].c_str()), atof(a[6].c_str()));
					if (control.w == 1) {
						direction.w = 1;
					}

					if (control.z == 1) {
						direction.x += sin(ToRadians(rotation.y));
						direction.z -= cos(ToRadians(rotation.y));
					}
					else if (control.z == -1) {
						direction.x -= sin(ToRadians(rotation.y));
						direction.z += cos(ToRadians(rotation.y));
					}

					if (control.x == -1) {
						direction.x += sin(ToRadians(rotation.y - 90));
						direction.z -= cos(ToRadians(rotation.y - 90));
					}
					else if (control.x == 1) {
						direction.x += sin(ToRadians(rotation.y + 90));
						direction.z -= cos(ToRadians(rotation.y + 90));
					}

					if (control.y == 1) {
						direction.y += 1;
					}
					else if (control.y == -1) {
						direction.y -= 1;
					}
					c->SetDirection(direction);
					c->SetRotation(rotation);
				} else {
					glm::vec3 position = glm::vec3(atof(a[0].c_str()), atof(a[1].c_str()), atof(a[2].c_str()));
					rotation = glm::vec3(atof(a[3].c_str()), atof(a[4].c_str()), atof(a[5].c_str()));
					bool n = p->VectorNear(position, c->GetPosition(), 1.0f);
					c->SetPosition(position);
					c->SetRotation(rotation);
				}
			}
		}
		p->m_Thread->join();
	}

	void Packet::SendToAll(const char* buffer) {
		for (unsigned int i = 0; i < m_Level->GetPlayers().size(); i++) {
			m_Network->Send(m_Level->GetPlayers()[i]->GetAddress(), buffer);
		}
	}

	bool Packet::VectorNear(glm::vec3 v1, glm::vec3 v2, float dist) {
		return v1.length() + dist <= v2.length() && v1.length() - dist >= v2.length();
	}

	void Packet::SendOnUpdate() {
		if (m_Network->IsServer()) {
			for (unsigned int i = 0; i < m_Level->GetPlayers().size(); i++) {
				std::ostringstream send;
				send << "02";
				glm::vec3 pos = m_Level->GetPlayers()[i]->GetPosition();
				glm::vec3 rot = m_Level->GetPlayers()[i]->GetRotation();

				int code = m_Level->GetPlayers()[i]->GetEntityID();
				std::ostringstream check;
				check << code << "";
				int x = 6;
				while (x - check.str().length() > 0) {
					send << "0";
					x--;
				}
				send << code;

				send << pos.x << "L" << pos.y << "L" << pos.z << "L" << rot.x << "L" << rot.y << "L" << rot.z;

				for (unsigned int j = 0; j < m_Level->GetPlayers().size(); j++) {
					// if (VectorNear(m_Level->GetPlayers()[j]->GetPosition(), pos, 1000)) {
						m_Network->Send(m_Level->GetPlayers()[j]->GetAddress(), send.str().c_str());
					// }
				}
			}
		} else {
			
		}
	}
}