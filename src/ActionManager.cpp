#include "precompiled.h"

#include "ActionManager.h"
#include "StringUtil.h"
#include "Action.h"

#include <vector>

void ActionManager::execute(String line, Client *client)
{
	std::vector<String> args;

	explode(&args, line, ' ');

	if (args.size() == 0)
		return;

	ActionMap::iterator it = getActionMap().find(args[0]);

	if (it == getActionMap().end())
		return;

	it->second->call(scene, client, args);
}
