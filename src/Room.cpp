#include "precompiled.h"

#include "Room.h"
#include "Action.h"

ACTION(look)
{
	printf("player looks");

	return ACTION_OK;
}

void Room::addExit(Direction dir, Room *room)
{
	exits[dir] = room;
}
