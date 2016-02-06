#pragma once

#include <..\ME\Rendering\Rendering.h>
#include <..\ME\engine.h>

class Game : public MangoesEngine {
private:
	bool m_Loading;
public:
	Game(const char* title);
	~Game();
private:
	virtual void Render() override;
	virtual void Update() override;
	virtual void Tick() override;
};

