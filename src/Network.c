#include "Network.h"

#include <dyad.h>

struct ServerState *initServer()
{
	dyad_init();

	struct ServerState *server = malloc(sizeof(struct ServerState));

	server->server = dyad_newStream();

//	dyad_addListener(server->server, DYAD_EVENT_ERROR, onError, NULL);
	dyad_addListener(server->server, DYAD_EVENT_ACCEPT, onAccept, server);
	dyad_listen(server->server, 8000);

	return server;
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

static void onAccept(dyad_Event *e) {
	//dyad_addListener(e->remote, DYAD_EVENT_LINE, onLine, NULL);

	// Get server from the userdata
	struct ServerState *server = e->udata;

	//TODO: Custom MOTD!
	dyad_writef(e->remote, "## Muta ##\r\n");

	//TODO: log message
	printf("New client connected! [%s]\n", e->msg);

	struct ClientState *client = malloc(sizeof(struct ClientState));

	client->client = e->stream;

	server->onConnectionCallback(client);
}
