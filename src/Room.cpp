#include "precompiled.h"

#include "Room.h"
#include "Action.h"
#include "ConnectionManager.h"

ACTION(look)
{
	ConnectionManager::sendLine(client, "You look around.");

	return ACTION_OK;
}

void Room::addExit(Direction dir, Room *room)
{
	exits[dir] = room;
}
