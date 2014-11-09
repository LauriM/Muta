#include "Network.h"

#include <dyad.h>

struct ServerState *initServer()
{
	dyad_init();

	struct ServerState *server = malloc(sizeof(struct ServerState));

	server->server = dyad_newStream();

	dyad_setUpdateTimeout(0.05);

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
	dyad_update(25);
}

static void onLine(dyad_Event *e) {
	char buffer[125]; //max buffer size is 125
	strncpy_s(buffer, 125, e->data, e->size);
	printf("[%s] \n", buffer);

	struct ServerState *server = e->udata;

	server->onLineCallback(e->stream, buffer);
}

void onAccept(dyad_Event *e) {
	dyad_addListener(e->remote, DYAD_EVENT_LINE, onLine, e->udata);

	// Get server from the userdata
	struct ServerState *server = e->udata;

	//TODO: Custom MOTD!
	dyad_writef(e->remote, "## Muta ##\r\n");

	//TODO: log message
	printf("New client connected! [%s]\n", e->msg);

	server->onConnectionCallback(e->remote);
}

void writeLine(ClientStream *clientStream, const char *line)
{
	dyad_writef(clientStream, "%s\r\n", line);
}
