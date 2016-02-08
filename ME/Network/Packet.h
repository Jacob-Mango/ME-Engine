#pragma once

#include <thread>
#include <iostream>
#include <string>
#include <sstream>

#include "..\Level\Level.h"
#include "..\Entity\Player.h"
#include "Network.h"

namespace Network {

	class Packet {
	private:
		Network* m_Network;
		Level::Level* m_Level;
	public:
		Packet(Network* network, Level::Level* level);
		~Packet();
	private:
		friend void HandleIncoming(Packet* p);
	};
}
