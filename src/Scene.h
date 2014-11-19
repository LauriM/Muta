#ifndef SCENE_H
#define SCENE_H

class World;

class Scene
{
private:
	World *world;

public:
	Scene();

	World *getWorld() const { return world; }
};

#endif