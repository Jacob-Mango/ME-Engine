#pragma once

#include <ME Engine\Rendering Module\rendering.h>

#include <ME Engine\ME\engine.h>

class Game : public MangoesEngine {
public:
	Game(const char* title);
	~Game();

private:
	virtual void Render(Rendering::RenderModule *module) override;
	virtual void Update() override;
	virtual void Tick() override;
};

