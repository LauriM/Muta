#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <map>

#include "Scene.h"

class Action;
struct Client;

class ActionManager
{
private:
	Scene *scene;

public:
	typedef std::map<String, Action*> ActionMap;

public:
	ActionManager(Scene *scene)
		: scene(scene)
	{ }

	inline static ActionMap& getActionMap() {
		static ActionMap staticActionMap;
		return staticActionMap;
	}

	void execute(String line, Client *client);
};

#endif