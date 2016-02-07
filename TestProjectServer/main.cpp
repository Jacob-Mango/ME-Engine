#include <iostream>

#include <..\ME\Rendering\Rendering.h>
#include <..\ME\engine.h>

#include "Server.h"

int main(void) {
	Server* g = new Server("TestProjectServer");
	delete g;
	return 0;
}