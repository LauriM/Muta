#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "network.h"

/**
 * Represents single connection
 */
struct Connection
{

};

/**
 * Manages all client connections and provides interface and receive messages from them.
 */
class ConnectionManager
{
private:
	ServerState *serverState;

public:
	ConnectionManager()
		: serverState(NULL)
	{
		serverState = initServer();
	}

	~ConnectionManager()
	{
		uninitServer(serverState);
	}

	void update()
	{
		updateServer(serverState);
	}
};

#endif