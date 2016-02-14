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
						c << p->m_Level->GetPlayers()[i].GetEntityID() << "";
						int x = 6;
						while (x - c.str().length() > 0) {
							n << "0";
							x--;
						}
						n << p->m_Level->GetPlayers()[i].GetEntityID() << "";
						n << p->m_Level->GetPlayers()[i].GetUsername() << "";
						p->m_Network->Send(from, n.str().c_str());

					}
					netSend << user << "";
					p->SendToAll(netSend.str().c_str());
					p->m_Level->AddPlayer(Player(from, user, code));
				} else {
					code = atoi(recv.substr(2, 6).c_str());
					std::cout << "Maybe? " << code << " ";
					if (p->m_Level->GetPlayerLevelForID(code) == -1) {
						std::cout << "Yes?";
						p->m_Level->AddPlayer(Player(user, code));
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

				float speed = 1.0f / 30.0f;

				std::vector<std::string> a = StringUtils::split(recv, 'L');

				glm::vec3 rotation;

				if (isServer) {
					glm::vec3 vel;
					glm::vec4 control = glm::vec4(atoi(a[0].c_str()), atoi(a[1].c_str()), atoi(a[2].c_str()), atoi(a[3].c_str()));
					rotation = glm::vec3(atof(a[4].c_str()), atof(a[5].c_str()), atof(a[6].c_str()));
					if (control.z == 1) {
						vel.x += speed * sin(ToRadians(rotation.y));
						vel.z -= speed * cos(ToRadians(rotation.y));
					}
					else if (control.z == -1) {
						vel.x -= speed * sin(ToRadians(rotation.y));
						vel.z += speed * cos(ToRadians(rotation.y));
					}

					if (control.x == -1) {
						vel.x += speed * sin(ToRadians(rotation.y - 90));
						vel.z -= speed * cos(ToRadians(rotation.y - 90));
					}
					else if (control.x == 1) {
						vel.x += speed * sin(ToRadians(rotation.y + 90));
						vel.z -= speed * cos(ToRadians(rotation.y + 90));
					}

					if (control.y == 1) {
						vel.y += speed;
					}
					else if (control.y == -1) {
						vel.y -= speed;
					}
					c->SetVelocity(vel);
					c->SetRotation(rotation);
				} else {
					glm::vec3 position = glm::vec3(atof(a[0].c_str()), atof(a[1].c_str()), atof(a[2].c_str()));
					rotation = glm::vec3(atof(a[3].c_str()), atof(a[4].c_str()), atof(a[5].c_str()));
					c->SetPosition(position);
					c->SetRotation(rotation);
				}
			}
		}
		p->m_Thread->join();
	}

	void Packet::SendToAll(const char* buffer) {
		for (unsigned int i = 0; i < m_Level->GetPlayers().size(); i++) {
			m_Network->Send(m_Level->GetPlayers()[i].GetAddress(), buffer);
		}
	}

	void Packet::SendOnUpdate() {
		if (m_Network->IsServer()) {
			for (unsigned int i = 0; i < m_Level->GetPlayers().size(); i++) {
				std::ostringstream send;
				send << "02";
				glm::vec3 pos = m_Level->GetPlayers()[i].GetPosition();
				glm::vec3 rot = m_Level->GetPlayers()[i].GetRotation();

				int code = m_Level->GetPlayers()[i].GetEntityID();
				std::ostringstream check;
				check << code << "";
				int x = 6;
				while (x - check.str().length() > 0) {
					send << "0";
					x--;
				}
				send << code;

				send << pos.x << "L" << pos.y << "L" << pos.z << "L" << rot.x << "L" << rot.y << "L" << rot.z;
				SendToAll(send.str().c_str());
			}
		} else {
			
		}
	}
}