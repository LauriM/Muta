#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include "ActionManager.h"
#include "Network.h"
#include "Scene.h"

// Action is a command that can be provided by the client
// The wrapper provides Scene pointer and the client/player that requested the action.

class Scene;
struct Client;

enum ActionErrorCode
{
	ACTION_OK = 0,
	INVALID_ACTION,
	INVALID_PARAMS,
	BLOCKED,
};

class Action
{
public:
	virtual ActionErrorCode call(Scene *scene, Client *client, const std::vector<String> args) = 0;
};

#define ACTION(p_name) \
	inline ActionErrorCode _action_function##p_name(Scene *scene, Client *client, const std::vector<String> args);\
	class _action_class##p_name : public Action {\
	public:\
		_action_class##p_name() {\
			printf("registering command: %s\n", TO_STRING(p_name) );\
			ActionManager::getActionMap().insert(ActionManager::ActionMap::value_type(TO_STRING(p_name), this));\
		}\
		ActionErrorCode call(Scene *scene, Client *client, const std::vector<String> args) { return _action_function##p_name(scene, client, args); }\
	};\
	_action_class##p_name p_name;\
	inline ActionErrorCode _action_function##p_name(Scene *scene, Client *client, const std::vector<String> args)\

#endif