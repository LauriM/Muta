#include "precompiled.h"

#include "ConnectionManager.h"
#include "Scene.h"

int main()
{
	ConnectionManager connectionManager;

	Scene scene;

	unsigned i = 0;
	unsigned x = 'a';

	for (;;)
	{
		connectionManager.update();

		i++;
		if (i > 50)
		{
			i = 0;
			x++;
			String lol("broadcast: ");
			connectionManager.broadcast(lol);
		}
	}

	return 0;
}