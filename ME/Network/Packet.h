#pragma once

#include <thread>
#include <iostream>

#include "Network.h"

class Packet {
private:
	Network::Network* m_Network;
public:
	Packet(Network::Network* network);
	~Packet();
private:
	friend void HandleIncoming(Network::Network* network);
};

