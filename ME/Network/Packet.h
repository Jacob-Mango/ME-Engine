#pragma once

#include <thread>
#include <iostream>
#include <string>
#include <sstream>

#include "..\Utils\StringUtils.h"

#include "..\Level\Level.h"
#include "..\Entity\Player.h"
#include "Network.h"

namespace Network {

	class Packet {
	private:
		Network* m_Network;
		Level::Level* m_Level;
		std::thread* m_Thread;
	public:
		Packet(Network* network, Level::Level* level);
		~Packet();

		void SendToAll(const char* buffer);

		void SendOnUpdate();
	private:
		bool VectorNear(glm::vec3 v1, glm::vec3 v2, float dist);
	private:
		friend void HandleIncoming(Packet* p);
	};
}
