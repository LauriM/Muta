#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dyad.h>

/**
 * Server/Client are owned by the network functions.
 *
 * Using classes should remember to call the cleanup functions
 *
 * NOTE: There can only be one server instance per executable running!
 */

struct ClientState
{
	dyad_Stream *client;
};

typedef void (*ConnectionCallback)(struct ClientState*);

struct ServerState
{
	dyad_Stream *server;

	ConnectionCallback onConnectionCallback;
};

//TODO: Somekind of prefix for these functions!

#ifdef __cplusplus
extern "C"
{
#endif

	struct ServerState *initServer();
	void uninitServer(struct ServerState *server);

	void updateServer(struct ServerState *server);

	void onAccept(dyad_Event *e);

	void writeLine(struct ClientState *clientState, const char *line);

#ifdef __cplusplus
}
#endif

/*
static void onLine(dyad_Event *e) {
	dyad_write(e->stream, e->data, e->size);

	char buffer[125];
	//	strncpy(input, e->data, e->size);
	strncpy_s(buffer, 125, e->data, e->size);

	printf("[%s] \n", buffer);

	if (strncmp(buffer, "look", 4) == 0)
	{
		dyad_writef(e->stream, "## Pos: %i \r\n", x, y);
	}

	if (strncmp(buffer, "w", 1) == 0)
	{
		x--;
		dyad_writef(e->stream, "## Moved to west.\r\n");
	}

	if (strncmp(buffer, "e", 1) == 0)
	{
		x++;
		dyad_writef(e->stream, "## Moved to east.\r\n");
	}

	if (strncmp(buffer, "e", 1) == 0)
	{
		x++;
		dyad_writef(e->stream, "## Moved to east.\r\n");
	}

	if (strncmp(buffer, "say", 3) == 0)
	{
		for (unsigned i = 0; i < streamCount; ++i)
		{
			dyad_writef(streamList[i], e->data);
			dyad_writef(e->stream, "\r\n");
		}
	}

	dyad_writef(e->stream, "\r\n");
}

static void onAccept(dyad_Event *e) {
	dyad_addListener(e->remote, DYAD_EVENT_LINE, onLine, NULL);
	dyad_writef(e->remote, "## Muta ##\r\n");
	printf("New client connected! [%s]\n", e->msg);

	streamList[streamCount] = e->remote;
	streamCount++;
}

static void onError(dyad_Event *e) {
	printf("server error: %s\n", e->msg);
}

int networkMain(void) {
	printf("Muta engine starting!");
	dyad_Stream *s;
	dyad_init();

	x = 40;
	y = 30;

	s = dyad_newStream();
	dyad_setTickInterval(0.0333);
	dyad_addListener(s, DYAD_EVENT_ERROR,  onError,  NULL);
	dyad_addListener(s, DYAD_EVENT_ACCEPT, onAccept, NULL);
	dyad_listen(s, 8000);

	unsigned timer = 0;

	while (dyad_getStreamCount() > 0) {
		dyad_update();
	}

	return 0;
}
*/
