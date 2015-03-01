#include "precompiled.h"

#include "ConnectionManager.h"
#include "ActionManager.h"
#include "Authentication.h"
#include "Scene.h"
#include "Action.h"

int main()
{
	Scene scene;
	Authentication authentication;
	ActionManager actionManager(&scene);
	ConnectionManager connectionManager(&actionManager, scene.getPlayerManager(), &authentication);

	unsigned i = 0;
	unsigned x = 'a';

	for (;;)
	{
		connectionManager.update();
	}

	return 0;
}