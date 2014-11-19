#include "precompiled.h"

#include "Room.h"

void Room::addExit(Direction dir, Room *room)
{
	exits[dir] = room;
}
