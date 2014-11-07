#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dyad.h>

int x;
int y;

static void onLine(dyad_Event *e) {
	dyad_write(e->stream, e->data, e->size);

	char buffer[125];
//	strncpy(input, e->data, e->size);
	strncpy_s(buffer, 125, e->data, e->size);

	printf("[%s] \n", buffer);

	if(strncmp(buffer, "look", 4) == 0)
	{
		dyad_writef(e->stream, "## Pos: %i \r\n", x, y);
	}

	if(strncmp(buffer, "w", 1) == 0)
	{
		x--;
		dyad_writef(e->stream, "## Moved to west.\r\n");
	}

	if(strncmp(buffer, "e", 1) == 0)
	{
		x++;
		dyad_writef(e->stream, "## Moved to east.\r\n");
	}
}

static void onTick(dyad_Event *e)
{
	if(e->stream == NULL)
		return;

	dyad_writef(e->stream, "Pos: %i \r\n", x, y);
	dyad_writef(e->stream, "7");
}

static void onAccept(dyad_Event *e) {
	dyad_addListener(e->remote, DYAD_EVENT_LINE, onLine, NULL);
	dyad_addListener(e->remote, DYAD_EVENT_TICK, onTick, NULL);
	dyad_writef(e->remote, "## Muta ##\r\n");
	printf("New client connected! [%s]\n", e->msg);
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
