#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include "ActionManager.h"

// Action is a command that can be provided by the client
// The wrapper provides Scene pointer and the client/player that requested the action.

class Scene;
struct Client;

enum ActionErrorCode
{
	ACTION_OK = 0,
	INVALID_ACTION,
	INVALID_PARAMS,
};

class Action
{
private:
	String name;

public:
	const String& getName() const { return name; }

	virtual ActionErrorCode call(Scene *scene, Client *client, const std::vector<String> args);
};

#define ACTION(p_name) \
	class _action_class##p_name : public Action {\
	public:\
		_action_class##p_name() {\
			ActionManager::getActionMap().insert(ActionManager::ActionMap::value_type(TO_STRING(p_name), this));\
		}\
		ActionErrorCode call(Scene *scene, Client *client, const std::vector<String> args);\
	};\
	ActionErrorCode _action_class##p_name::call(Scene *scene, Client *client, const std::vector<String> args)\

#endif