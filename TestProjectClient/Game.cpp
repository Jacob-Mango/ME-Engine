#include "Game.h"

#include <iostream>

Game::Game(const char* title) : MangoesEngine(title) {
	Loop();
}

Game::~Game() {

}

void Game::Render(Rendering::RenderModule *module) {

}

void Game::Update() {
	std::cout << "Works!" << std::endl;
}

void Game::Tick() {

}