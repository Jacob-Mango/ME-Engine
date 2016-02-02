#pragma once
#include "engine.h"

class Game : public MangoesEngine {
public:
	Game();
	~Game();

private:
	virtual void Render(Rendering::RenderModule *module) override;
	virtual void Update() override;
	virtual void Tick() override;
};

