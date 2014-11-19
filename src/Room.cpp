#include "precompiled.h"

#include "Room.h"
#include "ConnectionManager.h"
#include "PlayerManager.h"

void Room::addExit(Direction dir, Room *room)
{
	exits[dir] = room;
}

Room *Room::getExit(Direction dir)
{
	assert(dir < Direction::DIR_COUNT);

	return exits[dir];
}
