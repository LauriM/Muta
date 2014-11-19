#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <map>

class Action;

class ActionManager
{
public:
	typedef std::map<String, Action*> ActionMap;

public:
	inline static ActionMap& getActionMap() {
		static ActionMap staticActionMap;
		return staticActionMap;
	}
};

#endif