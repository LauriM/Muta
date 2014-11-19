#ifndef PLAYER_H
#define PLAYER_H

#include "Directions.h"

class Room;
struct Client;

class Player
{
private:
	String name;
	unsigned roomId;
	Room *room;
	Client *client;

public:
	Player(Client *client, Room *room)
		: name("unnamed")
		, roomId(0)
		, client(client)
		, room(room)
	{ }

	void setRoom(Room *room);

	Room *getCurrentRoom() const { return room; }
	Client *getClient() const { return client; }

	bool move(Direction dir);

	void tellExits();
	void tellLook();
};

#endif