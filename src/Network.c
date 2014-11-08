#include "Network.h"

#include <dyad.h>

struct ServerState *initServer()
{
	dyad_init();

	struct ServerState *server = malloc(sizeof(struct ServerState));
}

void uninitServer(struct ServerState *server)
{
	dyad_shutdown();

	free(server);
}

void updateServer(struct ServerState *server)
{
	dyad_update();
}
