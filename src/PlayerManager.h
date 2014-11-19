#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include <vector>

class Scene;
struct Client;

typedef std::vector<Player*> PlayerList;

// Playermanager handles the master list of players
class PlayerManager
{
private:
	Scene *scene;

	std::vector<Player> players;

public:
	PlayerManager(Scene *scene);

	void clientConnected(Client *client);
	void clientDisconnected(Client *client);

	Player *getPlayerByClient(Client *client);

	void getPlayersInRoom(PlayerList &players, const Room *room);
};

#endif