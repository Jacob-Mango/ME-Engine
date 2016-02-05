#pragma once

#include <..\ME\Rendering\Rendering.h>
#include <..\ME\engine.h>

class Game : public MangoesEngine {
public:
	Game(const char* title);
	~Game();
private:
	virtual void Render(Rendering::RenderModule *module) override;
	virtual void Update(Level::Level* level) override;
	virtual void Tick() override;
};

