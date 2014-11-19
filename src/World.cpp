#include "precompiled.h"

#include "World.h"

World::World()
{
	// just building some world for testing purposes, debug etc.

	/*

	 n
	w e
	 s

	[Middle][Last]
	[Root]

	*/

	rootNode = new Room(0, "Hello to Muta, continue to by moving north.");
	Room *middleNode = new Room(0, "Second room, you can move to two directions.");
	Room *lastNode = new Room(0, "Third and the last room of this game.");

	rootNode->addExit(DIR_N, middleNode);
	middleNode->addExit(DIR_S, rootNode);

	middleNode->addExit(DIR_E, lastNode);
	lastNode->addExit(DIR_W, middleNode);
}