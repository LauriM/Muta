#include "precompiled.h"

#include "PlayerManager.h"
#include "Scene.h"
#include "World.h"

PlayerManager::PlayerManager(Scene *scene)
	: scene(scene)
{ }

void PlayerManager::clientConnected(Client *client)
{
	players.push_back(Player(client, scene->getWorld()->getRootNode()));
}

void PlayerManager::clientDisconnected(Client *client)
{
	for (unsigned i = 0; i < players.size(); ++i)
	{
		if (players[i].getClient() == client)
		{
			players.erase(players.begin() + i);
			printf("PlayerManager -> client disconnect handled\n");
			return;
		}
	}
}

Player *PlayerManager::getPlayerByClient(Client *client)
{
	assert(client != NULL);

	for (unsigned i = 0; i < players.size(); ++i)
	{
		if (players[i].getClient() == client)
			return &players[i];
	}

	assert(true); // could not find the player by client, this is usually something baad!
	return NULL;
}

void PlayerManager::getPlayersInRoom(PlayerList &players, const Room *room)
{
	for (unsigned i = 0; i < players.size(); i++)
	{
		if (players[i]->getCurrentRoom() == room)
		{
			players.push_back(players[i]);
		}
	}
}
