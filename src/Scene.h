#ifndef SCENE_H
#define SCENE_H

class World;
class PlayerManager;

class Scene
{
private:
	PlayerManager *playerManager;
	World *world;

public:
	Scene();

	World *getWorld() const { return world; }
	PlayerManager *getPlayerManager() const { return playerManager; }
};

#endif