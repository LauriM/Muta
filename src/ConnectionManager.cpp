#include "precompiled.h"

#include "ConnectionManager.h"

#include "ActionManager.h"
#include "PlayerManager.h"
#include "Authentication.h"

namespace global
{
	ConnectionManager *g_connectionManager;
}

ConnectionManager::ConnectionManager(ActionManager *actionManager, PlayerManager *playerManager, Authentication *authentication)
	: actionManager(actionManager)
	, playerManager(playerManager)
	, serverState(NULL)
	, authentication(authentication)
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
	Client *client = new Client();

	client->clientStream = clientStream;

	global::g_connectionManager->addClient(client);

	// Send login screen to client
	// TODO: motd.txt

	sendLine(client, "LOGIN!");
	sendLine(client, "Username: ");
}

void ConnectionManager::staticOnLine(ClientStream *clientStream, char*line)
{
	global::g_connectionManager->onLine(clientStream, String(line));
}

void ConnectionManager::onLine(ClientStream *clientStream, const String &line)
{
	Client *client = getClientForClientStream(clientStream);

	switch (client->connectionState)
	{
	case DISCONNECTED:
		printf("wtf?");
		break;
	case AUTH_DONE:
		actionManager->execute(line, client);
		break;
	case MOTD:
		sendLine(client, "########");
		sendLine(client, "# MOTD #");
		sendLine(client, "########");
		sendLine(client, "");
	case LOGIN_SCREEN:
		if (authentication->authenticate(line, line) )//hack
		{
			client->connectionState = AUTH_DONE;

			playerManager->clientConnected(client);

			broadcast(String(line) + String(" logged in"));
		}
		else
		{
			sendLine(client, "Wrong password!\n");
		}
		break;
	}
}

Client *ConnectionManager::getClientForClientStream(ClientStream *state)
{
	for (unsigned i = 0; i < clients.size(); ++i)
	{
		if (clients[i]->clientStream == state)
			return clients[i];
	}

	return NULL;
}

void ConnectionManager::addClient(Client *client)
{
	printf("Client added to the vector\n");
	clients.push_back(client);

	client->connectionState = LOGIN_SCREEN;

	broadcast("new client connected!");
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
		writeLine(clients[i]->clientStream, line.c_str());
}