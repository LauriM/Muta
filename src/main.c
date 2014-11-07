#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dyad.h>

/* An echo server: Echos any data received by a client back to the client */

int x;
int y;

static void onData(dyad_Event *e) {
	dyad_write(e->stream, e->data, e->size);

	char input[125];

//	strncpy(input, e->data, e->size);
	strncpy_s(input, 125, e->data, e->size);

	printf("[%s] \n", input);

	if(strcmp(input, "look") == 0)
	{
		dyad_writef(e->stream, "Pos: %i \n", x, y);
	}

	if(strcmp(input, "w") == 0)
	{
		x--;
		dyad_writef(e->stream, "Moved to west.\n");
	}

	if(strcmp(input, "e") == 0)
	{
		x++;
		dyad_writef(e->stream, "Moved to east.\n");
	}
}

static void onTick(dyad_Event *e)
{
	printf("hehe");

	if(e->stream == NULL)
		return;

	//dyad_writef(e->stream, "Pos: %i\n", x, y);

	printf("haha");
}

static void onAccept(dyad_Event *e) {
	dyad_addListener(e->remote, DYAD_EVENT_DATA, onData, NULL);
	dyad_addListener(e->remote, DYAD_EVENT_TICK, onTick, NULL);
	dyad_writef(e->remote, "## Muta ##\r\n");
	printf("New client connected!");
}

static void onError(dyad_Event *e) {
	printf("server error: %s\n", e->msg);
}

int main(void) {
	printf("Muta engine starting!");
	dyad_Stream *s;
	dyad_init();

	x = 40;
	y = 30;

	s = dyad_newStream();
	dyad_addListener(s, DYAD_EVENT_ERROR,  onError,  NULL);
	dyad_addListener(s, DYAD_EVENT_ACCEPT, onAccept, NULL);
	dyad_listen(s, 8000);

	unsigned timer = 0;

	while (dyad_getStreamCount() > 0) {
		dyad_update();
	}

	return 0;
}
