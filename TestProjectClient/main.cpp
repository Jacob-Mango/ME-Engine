#include <iostream>

#include <ME Engine\ME\engine.h>
#include "Game.h"

int main(void) {
	Game* g = new Game("TestProjectClient");
	delete g;
	return 0;
}