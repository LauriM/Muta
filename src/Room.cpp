#include "precompiled.h"

#include "Room.h"
#include "Action.h"
#include "ConnectionManager.h"
#include "PlayerManager.h"

ACTION(look)
{
	ConnectionManager::sendLine(client, "You look around:");

	ConnectionManager::sendLine(client, scene->getPlayerManager()->getPlayerByClient(client)->getCurrentRoom()->getDescription());

	return ACTION_OK;
}

void Room::addExit(Direction dir, Room *room)
{
	exits[dir] = room;
}
