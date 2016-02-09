#include <iostream>

#include <..\ME\Rendering\Rendering.h>
#include <..\ME\engine.h>

#include "Server.h"

int main(void) {
	Server* s = new Server("TestProjectServer");
	delete s;
	return 0;
}