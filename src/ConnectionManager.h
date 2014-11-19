#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "network.h"

#include <vector>

class ActionManager;
class PlayerManager;

/**
 * Represents single connection
 */
struct Client 
{
	ClientStream *clientStream;
	// connection time
	// playerCharacther, etc
};

/**
 * Manages all client connections and provides interface and receive messages from them.
 */
class ConnectionManager
{
private:
	ActionManager *actionManager;
	PlayerManager *playerManager;

	ServerState *serverState;

	std::vector<Client> clients;

public:
	ConnectionManager(ActionManager *actionManager, PlayerManager *playerManager);

	~ConnectionManager()
	{
		uninitServer(serverState);
	}

	void update();

	Client *getClientForClientStream(ClientStream *stream);

private:
	void addClient(Client client);
	void onLine(ClientStream *stream, const String &line);

public:

	// When connection/disconnect happens
	// Static because these functions are called from C
	static void staticOnConnection(ClientStream *clientStream);
	static void staticOnDisconnect(ClientStream *clientStream); //TODO: call network commands to free the client struct

	// When a line is received from the client
	static void staticOnLine(ClientStream *clientStream, char *line);

	// Send data to specific client
	static void sendLine(Client *client, const String &line);
	static void sendLine(ClientStream *client, const String &line);

	// Broadcast line to all clients
	void broadcast(String line);
};

namespace global
{
	extern ConnectionManager *g_connectionManager;
}

#endif