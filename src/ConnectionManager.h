#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "network.h"

#include <vector>

/**
 * Represents single connection
 */
struct Client 
{
	ClientState *clientState;
	// connection time
	// playerCharacther, etc
};

/**
 * Manages all client connections and provides interface and receive messages from them.
 */
class ConnectionManager
{
private:
	ServerState *serverState;

	std::vector<Client> clients;

public:
	ConnectionManager();

	~ConnectionManager()
	{
		uninitServer(serverState);
	}

	void update();

private:
	void addClient(Client client);

public:

	// When connection/disconnect happens
	// Static because these functions are called from C
	static void staticOnConnection(ClientState *clientState);
	static void staticOnDisconnect(ClientState *clientState); //TODO: call network commands to free the client struct

	// When a line is received from the client
	static void staticOnLine(ClientState *clientState);

	// Send data to specific client
	void sendLine(ClientState *client, String line);

	// Broadcast line to all clients
	void broadcast(String line);
};

namespace global
{
	extern ConnectionManager *g_connectionManager;
}

#endif