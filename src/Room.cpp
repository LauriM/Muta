#include "precompiled.h"

#include "Room.h"
#include "Action.h"

#include "Scene.h"
#include "Network.h"
#include <vector>

inline ActionErrorCode _action_functionlook(Scene *scene, Client *client, const std::vector<String> args); 

ACTION(look)
{
	printf("player looks around.");

	return ACTION_OK;
}

void Room::addExit(Direction dir, Room *room)
{
	exits[dir] = room;
}
