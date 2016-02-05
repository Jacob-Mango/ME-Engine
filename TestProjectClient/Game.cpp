#include "Game.h"

#include <iostream>

Game::Game(const char* title) : MangoesEngine(title) {
	Loop();
}

Game::~Game() {

}

void Game::Render(Rendering::RenderModule *module) {
	module->PrepareRender();
	module->RenderWorld();
	module->RenderPostProccessEffects();
	module->EndRender();
}

void Game::Update(Level::Level* level) {
}

void Game::Tick() {
	std::cout << m_FramesPerSecond << std::endl;
}