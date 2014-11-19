#include "precompiled.h"

#include "ConnectionManager.h"
#include "ActionManager.h"
#include "Scene.h"
#include "Action.h"

int main()
{
	Scene scene;
	ActionManager actionManager(&scene);
	ConnectionManager connectionManager(&actionManager, scene.getPlayerManager());

	unsigned i = 0;
	unsigned x = 'a';

	for (;;)
	{
		connectionManager.update();
	}

	return 0;
}