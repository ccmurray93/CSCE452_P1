// may need #include "stdafx.h" in visual studio
//#include "stdafx.h"
#include "ServerPaint.h"
#include "ClientPaint.h"
// used for multi-threading
#include <process.h>

void serverLoop(void *);
void clientLoop(void);

ServerPaint * server;
ClientPaint * client;

int main()
{

	// initialize the server
	server = new ServerPaint();

	// create thread with arbitrary argument for the run function
	_beginthread(serverLoop, 0, (void*)12);

	// initialize the client 
	client = new ClientPaint();

	clientLoop();
}

void serverLoop(void * arg)
{
	while (true)
	{
		server->update();
	}
}

void clientLoop()
{
	while (true)
	{
		//do game stuff
		//will later run client->update();
	}
}
