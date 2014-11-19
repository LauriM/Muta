#include "precompiled.h"

#include "ConnectionManager.h"

#include "ActionManager.h"
#include "PlayerManager.h"

namespace global
{
	ConnectionManager *g_connectionManager;
}

ConnectionManager::ConnectionManager(ActionManager *actionManager, PlayerManager *playerManager)
	: actionManager(actionManager)
	, playerManager(playerManager)
	, serverState(NULL)
{
	serverState = initServer();
	serverState->onConnectionCallback = &staticOnConnection;
	serverState->onLineCallback = &staticOnLine;
	global::g_connectionManager = this;
}

void ConnectionManager::update()
{
	updateServer(serverState);
}

void ConnectionManager::staticOnConnection(ClientStream *clientStream)
{
	Client client;

	client.clientStream = clientStream;

	global::g_connectionManager->addClient(client);
}

void ConnectionManager::staticOnLine(ClientStream *clientStream, char*line)
{
	global::g_connectionManager->onLine(clientStream, String(line));
}

void ConnectionManager::onLine(ClientStream *clientStream, const String &line)
{
	Client *client = getClientForClientStream(clientStream);

	actionManager->execute(line, client);
}

Client *ConnectionManager::getClientForClientStream(ClientStream *state)
{
	for (unsigned i = 0; i < clients.size(); ++i)
	{
		if (clients[i].clientStream == state)
			return &clients[i];
	}

	return NULL;
}

void ConnectionManager::addClient(Client client)
{
	printf("Client added to the vector\n");
	clients.push_back(client);

	broadcast("new client connected");

	playerManager->clientConnected(&clients[clients.size()- 1]);
}

void ConnectionManager::sendLine(Client *client, const String &line)
{
	sendLine(client->clientStream, line);
}

void ConnectionManager::sendLine(ClientStream *client, const String &line)
{
	writeLine(client, line.c_str());
}

void ConnectionManager::broadcast(String line)
{
	for (unsigned i = 0; i < clients.size(); ++i)
		writeLine(clients[i].clientStream, line.c_str());
}