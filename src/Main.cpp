#include "precompiled.h"

#include "ConnectionManager.h"

int main()
{
	ConnectionManager connectionManager;

	for (;;)
		connectionManager.update();

	return 0;
}