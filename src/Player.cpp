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

	if (player->move(DIR_N))
	{
		player->tellLook();
		player->tellExits();
		return ACTION_OK;
	}

	return BLOCKED;
}

ACTION(s)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	if (player->move(DIR_S))
	{
		player->tellLook();
		player->tellExits();
		return ACTION_OK;
	}

	return BLOCKED;
}

ACTION(w)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	if (player->move(DIR_W))
	{
		player->tellLook();
		player->tellExits();
		return ACTION_OK;
	}

	return BLOCKED;
}

ACTION(e)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	if (player->move(DIR_E))
	{
		player->tellLook();
		player->tellExits();
		return ACTION_OK;
	}

	return BLOCKED;
}

ACTION(exits)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	player->tellExits();

	return ACTION_OK;
}

ACTION(look)
{
	Player *player = scene->getPlayerManager()->getPlayerByClient(client);

	player->tellLook();
	player->tellExits();

	return ACTION_OK;
}

void Player::tellLook()
{
	Room *room = getCurrentRoom();

	ConnectionManager::sendLine(client, "You look around:");

	ConnectionManager::sendLine(client, room->getDescription());
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

void Player::tellExits()
{
	ConnectionManager::sendLine(client, "Exits: ");

	for (unsigned i = 0; i < DIR_COUNT; ++i)
	{
		if (room->getExit(Direction(i)) != NULL)
			ConnectionManager::sendLine(client, "Exit <dir> : <roomname>");
	}
}
