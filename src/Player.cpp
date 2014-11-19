#include "precompiled.h"

#include "Player.h"
#include "Room.h"

void Player::setRoom(Room *room)
{
	this->room = room;
	roomId = room->getId();
}
