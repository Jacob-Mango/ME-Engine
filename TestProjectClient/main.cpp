#include <iostream>

#include <..\ME\Rendering\Rendering.h>
#include <..\ME\engine.h>

#include "Game.h"

int main(void) {
	Game* g = new Game("TestProjectClient");
	delete g;
	return 0;
}