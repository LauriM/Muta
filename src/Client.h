#ifndef CLIENT_H
#define CLIENT_H

#include "Network.h"

enum ConnectionState
{
	DISCONNECTED = 0,
	MOTD,
	LOGIN_SCREEN,
	AUTH_DONE,
};

/**
* Represents single connection
*/
struct Client
{
	ClientStream *clientStream;
	ConnectionState connectionState;
	// connection time
	// playerCharacther, etc
};

#endif
