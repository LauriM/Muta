#include "precompiled.h"

#include "ConnectionManager.h"
#include "World.h"

int main()
{
	ConnectionManager connectionManager;
	World world;

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