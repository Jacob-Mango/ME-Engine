#pragma once

#include <sstream>
#include <iostream>
#include <math.h>

#include <glm/gtx/string_cast.hpp>

#include <..\ME\Rendering\Rendering.h>
#include <..\ME\engine.h>

#include <..\ME\Utils\ResourceLoader.h>

class Game : public MangoesEngine {
private:
	bool m_Loading, m_WaitingForLogin;
	glm::vec2 m_PreviousMousePosition;
	int m_MainPlayerID;
public:
	Game(const char* title);
	~Game();
private:
	virtual void Render() override;
	virtual void Update() override;
	virtual void Tick() override;
};

