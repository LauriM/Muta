#include "precompiled.h"

#include "ConnectionManager.h"

namespace global
{
	ConnectionManager *g_connectionManager;
}

ConnectionManager::ConnectionManager()
	: serverState(NULL)
{
	serverState = initServer();
	serverState->onConnectionCallback = &staticOnConnection;
	global::g_connectionManager = this;
}

void ConnectionManager::update()
{
	updateServer(serverState);
}

void ConnectionManager::staticOnConnection(ClientState *clientState)
{
	Client client;

	client.clientState = clientState;

	global::g_connectionManager->addClient(client);
}

void ConnectionManager::addClient(Client client)
{
	printf("Client added to the vector\n");
	clients.push_back(client);

	broadcast("new client connected");
}

void ConnectionManager::broadcast(String line)
{
	for (unsigned i = 0; i < clients.size(); ++i)
		writeLine(clients[i].clientState, line.c_str());
}