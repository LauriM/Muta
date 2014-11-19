#include "precompiled.h"

#include "Player.h"
#include "Room.h"
#include "ConnectionManager.h"
#include "Action.h"
#include "PlayerManager.h"
#include "Scene.h"

ACTION(n)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	if(player->move(DIR_N))
		return ACTION_OK;

	return BLOCKED;
}

ACTION(s)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	if (player->move(DIR_S))
		return ACTION_OK;

	return BLOCKED;
}

ACTION(w)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	if (player->move(DIR_W))
		return ACTION_OK;

	return BLOCKED;
}

ACTION(e)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	if (player->move(DIR_E))
		return ACTION_OK;

	return BLOCKED;
}

void Player::setRoom(Room *room)
{
	this->room = room;
	roomId = room->getId();
}

bool Player::move(Direction dir)
{
	Room *target = room->getExit(dir);

	if (target == NULL)
	{
		ConnectionManager::sendLine(client, "There is no exit in that direction!");
		return false;
	}

	room = target;

	ConnectionManager::sendLine(client, "Done");

	return true;
}
