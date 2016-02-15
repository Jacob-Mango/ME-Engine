#pragma once

#include <sstream>
#include <iostream>
#include <math.h>

#include <..\ME\engine.h>

class Server : public MangoesEngine {
private:
	bool m_Loading;
public:
	Server(const char* title);
	~Server();
private:
	virtual void Update() override;
	virtual void Tick() override;
};
