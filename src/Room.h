#ifndef ROOM_H
#define ROOM_H

#include "Directions.h"

class Room
{
private:
	unsigned id;
	String description;

	// some better way to handle the exits in room
	Room *exits[DIR_COUNT];

public:
	Room(unsigned id, String description)
		: id(id)
		, description(description)
	{
		for (unsigned i = 0; i < DIR_COUNT; i++)
			exits[i] = NULL;
	}

	const unsigned &getId() const { return id; }
	const String &getDescription() const { return description; }

	void addExit(Direction dir, Room *room);
	Room *getExit(Direction dir);
};

#endif