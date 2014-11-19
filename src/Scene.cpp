#include "precompiled.h"

#include "Scene.h"
#include "World.h"
#include "PlayerManager.h"

Scene::Scene()
{
	playerManager = new PlayerManager(this);
	world = new World();
}
